//
// Created by Jordan Lewis on 13/5/17.
//

#include "jjbot.h"
#include "world.h"
#include <math.h>
#include <stdbool.h>

int max_cargo_amount_for_commodity(bot_t *bot, commodity_t *commodity) {
    int weight_max = bot->maximum_cargo_weight / commodity->weight;
    int volume_max = bot->maximum_cargo_volume / commodity->volume;
    if (weight_max < volume_max) {
        return weight_max;
    } else {
        return volume_max;
    }
}

/*
 * Seller and Buyer are the ones being exploited.
 */
// TODO: Estimate how many more times a pair will last, if not long, look for the next pair
int number_of_sustainable_move_turns(bot_t *bot, location_pair_t *pair) {
    int fuel_left = bot->fuel;
    int distance = pair->distance;
    return floorf((double)fuel_left / (double)distance);
}

// TODO: Should account for distance to the nearest petrol station, and current bot location*
bool should_refuel(bot_t *bot, location_pair_t *pair) {
    if (number_of_sustainable_turns(bot, pair) < LOW_FUEL_THRESHOLD) {
        return true;
    }
    return false;
}