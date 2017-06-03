//
// Created by Jordan Lewis on 13/5/17.
//

#ifndef JJBOT_H
#define JJBOT_H

#define MIN_LAPS 2
#define MAX_CONSECUTIVE_MOVES 3

#endif //JJBOT_H

#include "trader_bot.h"
#include <stdbool.h>
#include "structs.h"

// bot_stuff.c
int max_cargo_amount_for_commodity(bot_t bot, commodity_t commodity);
int number_of_sustainable_turns(bot_t bot, location_pair_t pair);
bool has_cargo(bot_t bot);
int cargo_quantity_for(bot_t bot, commodity_t commodity);
bool is_full_fuel(bot_t bot);
int max_buyable_petrol(bot_t bot, location_t petrol_station);
bool should_refuel(bot_t bot, action_t action);
bool can_reach_target(bot_t bot, location_t target, int fuel_modifier);
int amount_should_buy(bot_t bot, location_pair_t pair);

// money.c
int cost_of_travel(location_pair_t pair);
location_pair_t best_pair_for_commodity(bot_t bot, commodity_t commodity);
location_pair_t best_buy_sell_pair(bot_t bot);
int amount_to_buy(bot_t bot, location_pair_t pair);

// actions.c
action_t create_action(int action, int n, location_t target);
action_t create_default_move_action(bot_t bot, location_pair_t pair);
action_t idle_action(bot_t b);
action_t at_seller_action(bot_t b, location_pair_t pair);
action_t at_buyer_action(bot_t b, location_pair_t pair);
action_t at_petrol_action(bot_t b, location_pair_t pair);
action_t at_null_pair_action(bot_t b);
