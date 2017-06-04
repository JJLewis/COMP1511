//
// Created by Jordan Lewis on 13/5/17.
//
// CONTACT:
// Email: dev_jordanlewis@icloud.com
// Websites:
// https://jjlewis.github.io
// https://github.com/jjlewis/COMP1511

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "jjbot.h"
#include "world.h"
#include "debugger.h"

/*
 * Returns the maximum quantity of a commodity a bot can carry according to the max_cargo_weight and max_cargo_volume
 * It does some division and takes the lesser of the two.
 * Also, integer arithmetic automatically floors, which is good, since rounding up may cause returning 1 more than possible.
 */
int max_cargo_amount_for_commodity(bot_t bot, commodity_t commodity) {
    int weight_max = bot->maximum_cargo_weight / commodity->weight;
    int volume_max = bot->maximum_cargo_volume / commodity->volume;
    if (weight_max < volume_max) {
        return weight_max;
    } else {
        return volume_max;
    }
}

/*
 * Simply returns a true or false about whether or not the bot is carrying some sort of cargo.
 */
bool has_cargo(bot_t bot) {
    if (bot->cargo != NULL) {
        if (bot->cargo->quantity > 0) {
            return true;
        }
    }
    return false;
}

/*
 * Returns the quantity of a commodity in a bot's cargo.
 */
int cargo_quantity_for(bot_t bot, commodity_t commodity) {
    cargo_t cargo = bot->cargo;
    while (!is_commodities_equal(cargo->commodity, commodity)) {
        if (cargo->next == NULL) {
            return 0;
        }
        cargo = cargo->next;
    }
    return cargo->quantity;
}

/*
 * True or false on whether or not the bot is at full fuel, by comparing the fuel_tank_capacity to the amount of fuel left.
 */
bool is_full_fuel(bot_t bot) {
    return bot->fuel == bot->fuel_tank_capacity;
}

/*
 * Returns the maximum quantity of petrol a bot can buy at a petrol station.
 * Calculated by taking the lesser of the max affordable and what's available.
 */
int max_buyable_petrol(bot_t bot, location_t petrol_station) {
    int available_quantity = petrol_station->quantity;
    int price = petrol_station->price;
    int cash = bot->cash;
    int max_affordable = (int)floorf((double)cash / (double)price);
    return available_quantity > max_affordable ? max_affordable : available_quantity;
}

/*
 * Returns a true of false on whether or not the bot should head/redirect to petrol and refuel.
 * This function accounts for various possibilities where the bot should/must refuel to perform.
 * These possibilities are as follows:
 *      If not enough fuel to reach target
 *      If the bot will pass the petrol station on the way to the target
 *      If the bot won't have enough fuel to get to a petrol station after reaching the target
 * There are also conditions for when the bot should NOT refuel:
 *      The bot is not MOVING, rather BUYING or SELLING
 *      The bot has a full tank of fuel
 *      Not enough turns to get to a petrol station then reach the target destination
 *      The world is out of fuel
 *      Not going to make it to the closest petrol station, so don't even bother trying
 *
 * inputs:
 *          bot: Used for it's location, fuel, and information on the game such as turns left.
 *          action: The action that jjbot.c had decided upon before calling this. Used for the target location the bot wants to reach.
 *
 * returns: Boolean, true to refuel, false to keep doing what it was going to do.
 */
bool should_refuel(bot_t bot, action_t action) {

    // Only say YES to refuelling if the current action is MOVE
    if (action->action != ACTION_MOVE) {
        return false;
    }

    if (is_full_fuel(bot)) return false;

    if (bot->turns_left < 4) return false; // Move Refuel Move Sell/Buy

    location_t target = action->target;
    int distance_to_target = true_distance_between(bot->location, target);

    int remaining_fuel = bot->fuel;

    // If not enough fuel to reach target
    if (remaining_fuel < distance_to_target) return true;

    // If the bot will pass the petrol station on the way to the target
    if (will_pass_petrol(bot->location, target)) return true;

    // If the bot won't have enough fuel to get to a petrol station after reaching the target
    location_t nearest_petrol = nearest_petrol_station(target, -1);
    if (nearest_petrol == NULL) {
        if (petrol_left_in_world(bot) == bot->fuel) {
            return false; // If world out of fuel
        } else {
            if (has_cargo(bot)) {
                return false;
            } else {
                return true;
            }
        }
    }
    int target_to_fuel_distance = true_distance_between(target, nearest_petrol);
    int at_target_remaining_fuel = remaining_fuel - distance_to_target;
    int bot_to_fuel_distance = true_distance_between(bot->location, nearest_petrol);
    if (bot_to_fuel_distance > remaining_fuel) return false; // Not going to make it to petrol so don't bother, just die
    if (at_target_remaining_fuel < target_to_fuel_distance) return true;

    return false;
}

/*
 * Returns a boolean about whether or not the bot can reach a location from where it is now.
 * This function accounts for various reasons why a bot may not reach it's target, along with some where it will.
 * This algorithm considers:
 *      If the bot already has enough fuel to reach the target
 *      If there are enough turns left in the game to reach the target and then do a SELL action
 *      If not:
 *          If the bot can refuel on the way to the target
 *          If the bot can move the other way, then refuel, then have enough fuel to reach the target
 *
 * inputs:
 *          bot: The bot to move, used for its current fuel and location state.
 *          target: The target location the bot wants to head to.
 *          fuel_modifier: In case a closer stop needs to be made, just subtract that from the current fuel amount, and do the same algorithm.
 *                          NOTE: This will be 0 most of the time.
 *
 * returns: True if the bot can somehow reach the target, False if it cannot.
 */
bool can_reach_target(bot_t bot, location_t target, int fuel_modifier) {
    /*
     * Check fuel left in bot against distance to travel
     * Check amount of remaining fuel in the world
     * Check if the bot can reach fuel before target if it can
     * Check if there are enough turns left in the game to reach the target
     */
    bool can_reach = true;
    int fuel_left = bot->fuel - fuel_modifier;
    int distance = true_distance_between(bot->location, target);

    if (petrol_left_in_world(bot) < distance) return false;

    if (fuel_left < distance) {
        // If intermediate petrol stop will allow reaching the a BUYER
        location_t petrol_in_between = petrol_between(bot->location, target);
        if (petrol_in_between == NULL) {
            can_reach = false; // No intermediate petrol station
        } else {
            if (petrol_in_between->quantity + fuel_left < distance) { // If it can't buy enough fuel to reach the target
                can_reach = false; // Petrol station doesn't have enough fuel
            } else {
                // Need to check if it can reach the petrol station between the bot and the target
                return can_reach_target(bot, petrol_in_between, 0);
            }
        }

        // Get to a petrol station in the opposite direction, then head to the target
        location_t nearest_petrol = nearest_petrol_station(bot->location, -1);
        if (nearest_petrol == NULL) {
            return false;
        } else {
            int to_petrol_distance = true_distance_between(bot->location, nearest_petrol);
            if (fuel_left < to_petrol_distance) {
                can_reach = false; // Can't even get to another petrol station
            } else {
                int max_buyable = max_buyable_petrol(bot, nearest_petrol);
                int at_petrol_remaining_fuel = fuel_left - to_petrol_distance;
                int petrol_to_target_distance = true_distance_between(nearest_petrol, target);
                int required_petrol = petrol_to_target_distance - at_petrol_remaining_fuel;
                if (required_petrol > max_buyable) {
                    can_reach = false; // Again not enough petrol
                } else {
                    can_reach = true;
                }
            }
        }
    } else {
        // It can reach the target, just check if there are enough turns to do that
        int required_move_turns = (int)ceilf((double) distance / (double) bot->maximum_move);
        if (required_move_turns + 1 > bot->turns_left) return false; // Plus 1 for SELL action
    }

    return can_reach;
}

/*
 * An extension on top of amount_to_buy.
 * This function prevents over-buying, causing cargo to be left over after a SELL.
 * This function considers if the bot can reach the desired BUYER
 *      If it can, simply return the outcome of amount_to_buy
 *      If not, look for a closer BUYER and calculate the amount_to_buy from the new found BUYER
 *      If a closer BUYER is not found or cannot be reached return 0.
 *
 * returns: The quantity of a commodity the bot should buy, 0 if it shouldn't buy any.
 */
int amount_should_buy(bot_t bot, location_pair_t pair) {
    if (can_reach_target(bot, pair->buyer, 0)) {
        return amount_to_buy(bot, pair);
    } else {
        location_t next_best_buyer = best_buyer_in_range_from_this_seller(bot);
        if (next_best_buyer == NULL || !can_reach_target(bot, next_best_buyer, 0)) {
            return 0;
        }
        location_pair_t new_pair = create_location_pair(bot->location, next_best_buyer);
        int to_buy = amount_to_buy(bot, new_pair);
        free(new_pair); // NO LEEEEEAAAAAAKKKKKSSS!!!
        return to_buy;
    }
}
