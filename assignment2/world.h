//
// Created by Jordan Lewis on 13/5/17.
//

#ifndef WORLD_H
#define WORLD_H

#endif //WORLD_H

#include <stdbool.h>
#include "trader_bot.h"
#include "structs.h"

#define DIRECTION_FORWARD 1
#define DIRECTION_BACKWARD -1

// motion.c
int distance_between(location_t location1, location_t location2);
int true_distance_between(location_t location1, location_t location2);
void shift_location(location_t location, int direction);
int distance_to_direction(int distance);
void move_location(location_t location, int distance);
location_t location_from_with_distance(location_t start, int distance);
int amount_move_to(bot_t bot, location_t destination);

// handy_world.c
int number_of_locations(bot_t bot);
int filter_zero_quantity(location_t locations[MAX_LOCATIONS], int size);
location_pair_t create_location_pair(location_t seller, location_t buyer);
bool is_location_equal(location_t location1, location_t location2);
bool is_commodities_equal(commodity_t c1, commodity_t c2);
bool is_at_either_location(bot_t b, location_pair_t pair);

// significant_locations.c
location_t find_start_location(location_t a_location);
location_t highest_buyer_of_commodity(bot_t bot, commodity_t commodity);
location_t lowest_seller_of_commodity(bot_t bot, commodity_t commodity);
bool will_pass_petrol(location_t start, location_t end);
location_t nearest_petrol_station(location_t location, int minimumFuel);
location_t closest_buyer_of_commodity_to(bot_t bot, location_t location, commodity_t commodity);
location_t best_buyer_of_commodity_to(bot_t bot, location_t location, commodity_t commodity);

// all_of_type.c
int all_commodities(location_t location, commodity_t commodities[MAX_COMMODITIES]);
int all_locations_of_commodity_of_type(bot_t bot, commodity_t commodity, int type, location_t locations[MAX_LOCATIONS]);
int all_buyers_of_commodity(bot_t bot, commodity_t commodity, location_t locations[MAX_LOCATIONS]);
int all_sellers_of_commodity(bot_t bot, commodity_t commodity, location_t locations[MAX_LOCATIONS]);
int all_locations_of_commodity(bot_t bot, commodity_t commodity, location_t locations[MAX_LOCATIONS]);
int all_petrol_stations(location_t a_location, location_t locations[MAX_LOCATIONS]);
