//
// Created by Jordan Lewis on 28/5/17.
//

#include <stdlib.h>
#include <stdio.h>
#include "jjbot.h"
#include "world.h"
#include "debugger.h"

/*
 * Mallocs, initialises and creates an action struct with all the required data.
 */
action_t create_action(int action, int n, location_t target) {
    action_t an_action = malloc(sizeof(struct action));
    an_action->action = action;
    an_action->n = n;
    an_action->target = target;
    return an_action;
}

/*
 * The default action for the bot is to:
 *      Move to the seller if the bot is not carrying cargo
 *      Move to a buyer if the bot does have cargo (to sell it off)
 */
action_t create_default_move_action(bot_t b, location_pair_t pair) {
    throw_warning("DEFAULT MOVE ACTION");
    int n = amount_move_to(b, pair->seller);
    if (has_cargo(b)) {
        n = amount_move_to(b, pair->buyer);
    }
    location_t target = has_cargo(b) ? pair->buyer:pair->seller;
    return create_action(ACTION_MOVE, n, target);
}

/*
 * Returns an idle action, which is literally "MOVE 0"
 * This should barely ever be called.
 */
action_t idle_action(bot_t b) {
    return create_action(ACTION_MOVE, 0, b->location);
}

/*
 * Returns the appropriate action to take when the bot is at a location of type SELLER
 * First, check if the seller it is at is the seller it was trying to reach
 *      If it is, then either buy or move towards the seller depending on whether or not the bot has cargo.
 *          Note that it will only buy if the bot can reach a buyer to sell the commodity to, so as to not die with cargo.
 *      If not, move towards the target seller.
 */
action_t at_seller_action(bot_t b, location_pair_t pair) {
    if (is_location_equal(b->location, pair->seller)) {
        if (has_cargo(b)) {
            return create_action(ACTION_MOVE, amount_move_to(b, pair->buyer), pair->buyer);
        } else {
            println();
            printf("PLANNING TO SELL TO (%d): ", pair->distance);
            print_location(pair->buyer);
            println();
            int to_buy = amount_should_buy(b, pair);
            if (to_buy > 0) {
                return create_action(ACTION_BUY, to_buy, NULL);
            } else {
                throw_warning("ACTUALLY CANNOT REACH A BUYER");
                return idle_action(b);
            }
        }
    } else {
        return create_default_move_action(b, pair);
    }
}

/*
 * Returns the appropriate action to take when the bot is a a location of type BUYER
 * First, check if the buyer it is at is the buyer it was trying to reach
 *      If it is, then either sell all of the cargo the bot is carrying or move towards a seller to buyer more
 *          Note that it will search for the "best buy sell pair" since the seller could have run out so no point moving there.
 *      If not, keep moving towards the target buyer.
 */
action_t at_buyer_action(bot_t b, location_pair_t pair) {
    if (is_location_equal(b->location, pair->buyer)) {
        if (has_cargo(b)) {
            return create_action(ACTION_SELL, cargo_quantity_for(b, pair->commodity), NULL);
        } else {
            location_pair_t new_pair = best_buy_sell_pair(b);
            action_t action = create_action(ACTION_MOVE, amount_move_to(b, new_pair->seller), new_pair->seller);
            free(new_pair);
            return action;
        }
    } else {
        return create_default_move_action(b, pair);
    }
}

/*
 * Returns the appropriate action to take when the bot is a a location of type PETROL_STATION
 * If the bot's fuel tank is full, just do the default move action
 * Otherwise, as long as the petrol station has petrol to sell, refuel as much as possible.
 */
action_t at_petrol_action(bot_t b, location_pair_t pair) {
    if (is_full_fuel(b)) {
        return create_default_move_action(b, pair);
    } else {
        if (b->location->quantity > 0) {
            return create_action(ACTION_BUY, b->fuel_tank_capacity - b->fuel, NULL);
        } else {
            return create_default_move_action(b, pair);
        }
    }
}

/*
 * Returns the appropriate action to take when my algorithm could not find a profitable buyer & seller pair to exploit
 * If the bot has cargo, then it should:
 *      Find a buyer with the highest price:
 *          If it is there already, SELL everything for that commodity.
 *          If not, and the bot can reach it, move towards the highest buyer
 *      If the bot cannot reach the highest buyer, find the closest buyer of the same commodity
 *          Check if the bot is already there at the closest buyer
 *              If it is, SELL everything for that commodity
 *              If not, check if the bot can reach the closest, and if it can, move towards it.
 *      If the bot cannot reach the closest buyer, find the nearest petrol station with enough fuel to cover returning back to where it is
 *          If the bot is already at the petrol station, refuel as much as possible
 *          If not, move towards the nearest petrol station.
 * If the bot DOES NOT have cargo, that means there are probably no more buyer seller pairs of any commodity that the
 * bot can use to make money, so PRINT a WARNING and IDLE, stay at where it is, so as to not burn fuel or waste money.
 */
action_t at_null_pair_action(bot_t b) {
    if (has_cargo(b)) {
        commodity_t commodity = b->cargo->commodity;
        int fuel_left = b->fuel;
        location_t best_buyer = best_buyer_of_commodity_to(b, b->location, commodity);

        // Try to sell all of the cargo
        if (is_location_equal(b->location, best_buyer)) {
            return create_action(ACTION_SELL, cargo_quantity_for(b, commodity), NULL);
        }

        if (can_reach_target(b, best_buyer, 0)) {
            // Move to the highest buyer of the commodity
            return create_action(ACTION_MOVE, amount_move_to(b, best_buyer), best_buyer);
        } else {
            location_t closest_buyer = closest_buyer_of_commodity_to(b, b->location, commodity);

            // Try to sell all to the closest seller
            if (is_location_equal(b->location, closest_buyer)) {
                return create_action(ACTION_SELL, cargo_quantity_for(b, commodity), NULL);
            }

            if (can_reach_target(b, closest_buyer, 0)) {
                // Move to the closest buyer of the commodity
                return create_action(ACTION_MOVE, amount_move_to(b, closest_buyer), closest_buyer);
            } else {
                location_t nearest_fuel = nearest_petrol_station(b->location, -1);

                // Refuel
                if (is_location_equal(b->location, nearest_fuel)) {
                    return create_action(ACTION_BUY, b->fuel_tank_capacity - b->fuel, NULL);
                }

                // Move towards the closest petrol station
                return create_action(ACTION_MOVE, amount_move_to(b, nearest_fuel), nearest_fuel);
            }
        }
    } else {
        throw_warning("HAAAAALP, I DUNNO WAT TU DU!!");
        return idle_action(b);
    }
}
