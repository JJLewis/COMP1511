//
// Created by Jordan Lewis on 13/5/17.
//

#ifndef ASSIGNMENT2_JJBOT_H
#define ASSIGNMENT2_JJBOT_H

#endif //ASSIGNMENT2_JJBOT_H

#include "trader_bot.h"

typedef struct bot bot_t;
typedef struct location location_t;
typedef struct cargo cargo_t;
typedef struct commodity commodity_t;
typedef struct bot_list bot_list_t;

// bot_stuff.c
int max_cargo_amount_for_commodity(bot_t *bot, commodity_t *commodity);

// money.c
int cost_of_travel(location_t *start, location_t *end);
void best_pair_for_commodity(bot_t *bot, commodity_t *commodity, location_t *b_seller, location_t *b_buyer);