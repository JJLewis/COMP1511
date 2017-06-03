//
// Created by Jordan Lewis on 13/5/17.
//

#include "jjbot.h"
#include "world.h"
#include "debugger.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

int max_cargo_amount_for_commodity(bot_t bot, commodity_t commodity) {
    int weight_max = bot->maximum_cargo_weight / commodity->weight;
    int volume_max = bot->maximum_cargo_volume / commodity->volume;
    if (weight_max < volume_max) {
        return weight_max;
    } else {
        return volume_max;
    }
}

bool has_cargo(bot_t bot) {
    if (bot->cargo != NULL) {
        if (bot->cargo->quantity > 0) {
            return true;
        }
    }
    return false;
}

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

bool is_full_fuel(bot_t bot) {
    return bot->fuel == bot->fuel_tank_capacity;
}

int max_buyable_petrol(bot_t bot, location_t petrol_station) {
    int available_quantity = petrol_station->quantity;
    int price = petrol_station->price;
    int cash = bot->cash;
    int max_affordable = (int)floorf((double)cash / (double)price);
    return available_quantity > max_affordable ? max_affordable : available_quantity;
}

bool should_refuel(bot_t bot, action_t action) {

    // Only say YES to refuelling if the current action is MOVE
    if (action->action != ACTION_MOVE) {
        return false;
    }

    if (bot->fuel == bot->fuel_tank_capacity) return false;

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

int amount_should_buy(bot_t bot, location_pair_t pair) {
    if (can_reach_target(bot, pair->buyer, 0)) {
        return amount_to_buy(bot, pair);
    } else {
        location_t next_best_buyer = best_buyer_in_range_from_this_seller(bot);
        if (next_best_buyer == NULL) {
            return 0;
        }
        location_pair_t new_pair = create_location_pair(bot->location, next_best_buyer);
        int to_buy = amount_to_buy(bot, new_pair);
        free(new_pair);
        return to_buy;
    }
}
