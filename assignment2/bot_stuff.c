//
// Created by Jordan Lewis on 13/5/17.
//

#include "jjbot.h"
#include "world.h"
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

// TODO: Should account for distance to the nearest petrol station, and current bot location*
bool should_refuel(bot_t bot, action_t action) {

    // Only say YES to refuelling if the current action is MOVE
    if (action->action != ACTION_MOVE) {
        return false;
    }

    location_t target = action->target;
    int distance_to_target = true_distance_between(b->location, target);

    int remaining_fuel = bot->fuel;

    // If not enough fuel to reach target
    if (remaining_fuel < distance_to_target) return true;

    // If the bot will pass the petrol station on the way to the target
    if (will_pass_petrol(bot->location, target)) return true;

    // If the bot won't have enough fuel to get to a petrol station after reaching the target
    location_t nearest_petrol = nearest_petrol_station(target, -1);
    int target_to_fuel_distance = true_distance_between(target, nearest_petrol);
    int at_target_remaining_fuel = remaining_fuel - distance_to_target;
    if (at_target_remaining_fuel < target_to_fuel_distance) return true;

    return false;
}
