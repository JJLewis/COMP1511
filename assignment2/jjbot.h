//
// Created by Jordan Lewis on 13/5/17.
//

#ifndef ASSIGNMENT2_JJBOT_H
#define ASSIGNMENT2_JJBOT_H

#endif //ASSIGNMENT2_JJBOT_H

#include "trader_bot.h"
#include <stdbool.h>

#define LOW_FUEL_THRESHOLD 5

typedef struct bot *bot_t;
typedef struct location *location_t;
typedef struct cargo *cargo_t;
typedef struct commodity *commodity_t;
typedef struct bot_list *bot_list_t;

struct location_pair {
    location_t *seller;
    location_t *buyer;
    commodity_t *commodity;
    int distance;
};

typedef struct location_pair *location_pair_t;

// bot_stuff.c
int max_cargo_amount_for_commodity(bot_t bot, commodity_t *commodity);
int number_of_sustainable_turns(bot_t bot, location_pair_t *pair);
bool has_cargo(bot_t bot);
int cargo_quantity_for(bot_t bot, commodity_t *commodity);
bool is_full_fuel(bot_t bot);
int number_of_sustainable_move_turns(bot_t bot, location_pair_t *pair);
bool should_refuel(bot_t bot, location_pair_t *pair);

// money.c
int cost_of_travel(location_pair_t *pair);
location_pair_t best_pair_for_commodity(bot_t bot, commodity_t *commodity);
location_pair_t *best_buy_sell_pair(bot_t bot);
