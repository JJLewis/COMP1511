//
// Created by Jordan Lewis on 13/5/17.
//
// CONTACT:
// Email: dev_jordanlewis@icloud.com
// Websites:
// https://jjlewis.github.io
// https://github.com/jjlewis/COMP1511

#ifndef WORLD_H
#define WORLD_H

// Define the sign value for the direction vector for moving through the world.
#define DIRECTION_FORWARD 1
#define DIRECTION_BACKWARD -1

#endif //WORLD_H

#include <stdbool.h>
#include "trader_bot.h"
#include "structs.h"

// motion.c
int distance_between(location_t location1, location_t location2);
int true_distance_between(location_t location1, location_t location2);
void shift_location(location_t location, int direction);
int distance_to_direction(int distance);
int amount_move_to(bot_t bot, location_t destination);

// handy_world.c
int filter_zero_quantity(location_t locations[MAX_LOCATIONS], int size);
location_pair_t create_location_pair(location_t seller, location_t buyer);
bool is_location_equal(location_t location1, location_t location2);
bool is_commodities_equal(commodity_t c1, commodity_t c2);
bool is_at_either_location(bot_t b, location_pair_t pair);
int petrol_left_in_world(bot_t bot);
bool is_buyer_of_commodity(location_t loc, commodity_t commodity);
bool is_seller_of_commodity(location_t loc, commodity_t commodity);

// significant_locations.c
bool will_pass_petrol(location_t start, location_t end);
location_t nearest_petrol_station(location_t location, int minimumFuel);
location_t closest_buyer_of_commodity_to(bot_t bot, location_t location, commodity_t commodity);
location_t best_buyer_of_commodity_to(bot_t bot, location_t location, commodity_t commodity);
bool will_pass_location(location_t start, location_t end, location_t x);
location_pair_t best_closest_buyer(bot_t bot);
location_t petrol_between(location_t start, location_t end);
int buyers_in_fuel_range(bot_t bot, commodity_t commodity, location_t buyers[MAX_LOCATIONS]);
location_t best_buyer_in_range_from_this_seller(bot_t bot);

// all_of_type.c
int all_commodities(location_t location, commodity_t commodities[MAX_COMMODITIES]);
int all_locations_of_commodity_of_type(bot_t bot, commodity_t commodity, int type, location_t locations[MAX_LOCATIONS]);
int all_buyers_of_commodity(bot_t bot, commodity_t commodity, location_t locations[MAX_LOCATIONS]);
int all_sellers_of_commodity(bot_t bot, commodity_t commodity, location_t locations[MAX_LOCATIONS]);
int all_petrol_stations(location_t a_location, location_t locations[MAX_LOCATIONS]);
