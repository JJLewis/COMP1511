//
// Created by Jordan Lewis on 28/5/17.
//

#include "jjbot.h"
#include "world.h"
#include "debugger.h"
#include <stdlib.h>

action_t create_action(int action, int n, location_t target) {
    action_t an_action = malloc(sizeof(struct action));
    an_action->action = action;
    an_action->n = n;
    an_action->target = target;
    return an_action;
}

action_t create_default_move_action(bot_t b, location_pair_t pair) {
    int n = amount_move_to(b, pair->seller);
    if (has_cargo(b)) {
        n = amount_move_to(b, pair->buyer);
    }
    location_t target = has_cargo(b) ? pair->buyer:pair->seller;
    return create_action(ACTION_MOVE, n, target);
}

action_t at_seller_action(bot_t b, location_pair_t pair) {
    if (is_location_equal(b->location, pair->seller)) {
        if (has_cargo(b)) {
            return create_action(ACTION_MOVE, amount_move_to(b, pair->buyer), pair->buyer);
        } else {
                 println();
                print("PLANNING TO SELL TO:");
                print_location(pair->buyer);
                println();
            if (can_reach_target(b, pair->buyer)) {
               return create_action(ACTION_BUY, amount_to_buy(b, pair), NULL);
            } else {
                throw_warning("WAS GOING TO BUY BUT CANNOT REACH TARGET!!!");
                // Do nothing since cannot reach a petrol station or buyer target, what can you do?
                return create_action(ACTION_MOVE, 0, b->location);
            }
        }
    } else {
        return create_default_move_action(b, pair);
    }
}

action_t at_buyer_action(bot_t b, location_pair_t pair) {
    if (is_location_equal(b->location, pair->buyer)) {
        if (has_cargo(b)) {
            return create_action(ACTION_SELL, cargo_quantity_for(b, pair->commodity), NULL);
        } else {
            return create_action(ACTION_MOVE, amount_move_to(b, pair->seller), pair->seller);
        }
    } else {
        return create_default_move_action(b, pair);
    }
}

action_t at_petrol_action(bot_t b, location_pair_t pair) {
    if (is_full_fuel(b)) {
        return create_action(ACTION_MOVE, amount_move_to(b, pair->buyer), pair->buyer);
    } else {
        if (b->location->quantity > 0) {
            return create_action(ACTION_BUY, b->fuel_tank_capacity - b->fuel, NULL);
        } else {
            return create_default_move_action(b, pair);
        }
    }
}

action_t at_null_pair_action(bot_t b) {
    commodity_t commodity = b->cargo->commodity;
    int fuel_left = b->fuel;
    location_t best_buyer = best_buyer_of_commodity_to(b, b->location, commodity);

    if (is_location_equal(b->location, best_buyer)) {
        return create_action(ACTION_SELL, cargo_quantity_for(b, commodity), NULL);
    }

    int distance_to_best = true_distance_between(b->location, best_buyer);
    if (distance_to_best < b->fuel) {
        return create_action(ACTION_MOVE, amount_move_to(b, best_buyer), best_buyer);
    } else {
        location_t closest_buyer = closest_buyer_of_commodity_to(b, b->location, commodity);

        if (is_location_equal(b->location, closest_buyer)) {
            return create_action(ACTION_SELL, cargo_quantity_for(b, commodity), NULL);
        }

        int distance_to_closest = true_distance_between(b->location, closest_buyer);
        if (distance_to_closest < b->fuel) {
            return create_action(ACTION_MOVE, amount_move_to(b, closest_buyer), closest_buyer);
        } else {
            location_t nearest_fuel = nearest_petrol_station(b->location, -1);

            if (is_location_equal(b->location, nearest_fuel)) {
                return create_action(ACTION_BUY, b->fuel_tank_capacity - b->fuel, NULL);
            }
            return create_action(ACTION_MOVE, amount_move_to(b, nearest_fuel), nearest_fuel);
        }
    }
}
