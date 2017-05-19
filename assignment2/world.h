//
// Created by Jordan Lewis on 13/5/17.
//

#ifndef ASSIGNMENT2_WORLD_H_H
#define ASSIGNMENT2_WORLD_H_H

#define DIRECTION_FORWARD 1
#define DIRECTION_BACKWARD -1

#endif //ASSIGNMENT2_WORLD_H_H

#include "jjbot.h"

// motion.c
int distance_between(location_t *location1, location_t *location2);
int true_distance_between(location_t *location1, location_t *location2);
void shift_location(location_t *location, int direction);
int distance_to_direction(int distance);
void move_location(location_t *location, int distance);

// handy_world.c
int number_of_locations(bot_t *bot);
int filter_zero_quantity(location_t locations[MAX_LOCATIONS], int size);
location_pair_t *create_location_pair(location_t *seller, location_t *buyer);

// significant_locations.c
location_t *find_start_location(location_t *a_location);
location_t *highest_buyer_of_commodity(bot_t *bot, commodity_t *commodity);
location_t *lowest_seller_of_commodity(bot_t *bot, commodity_t *commodity);
bool will_pass_petrol(location_t *start, location_t *end);
location_t *nearest_petrol_station(location_t *location, int minimumFuel);

// all_of_type.c
int all_commodities(location_t *location, commodity_t commodities[]);
int all_locations_of_commodity_of_type(bot_t *bot, commodity_t *commodity, int type, location_t locations[MAX_LOCATIONS]);
int all_buyers_of_commodity(bot_t *bot, commodity_t *commodity, location_t locations[MAX_LOCATIONS]);
int all_sellers_of_commodity(bot_t *bot, commodity_t *commodity, location_t locations[MAX_LOCATIONS]);
int all_locations_of_commodity(bot_t *bot, commodity_t *commodity, location_t locations[MAX_LOCATIONS]);
int all_petrol_stations(location_t *a_location, location_t locations[MAX_LOCATIONS]);