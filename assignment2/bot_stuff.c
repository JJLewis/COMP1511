//
// Created by Jordan Lewis on 13/5/17.
//

#include "jjbot.h"

int max_cargo_amount_for_commodity(bot_t *bot, commodity_t *commodity) {
    int weight_max = bot->maximum_cargo_weight / commodity->weight;
    int volume_max = bot->maximum_cargo_volume / commodity->volume;
    if (weight_max < volume_max) {
        return weight_max;
    } else {
        return volume_max;
    }
}