//
// Created by Jordan Lewis on 13/5/17.
//

#include <stdbool.h>
#include <string.h>
#include "world.h"

/*
 * Check if a commodity exists in an array of commodities.
 * inputs:
 *          x: The target commodity we are searching for
 *          commodities[]: An array of commodities, with size MAX_COMMODITIES(from trader_bot.h)
 *          size: The actual number of elements in the commodities[] array, don't want to waste time comparing NULLs.
 */
bool commodity_exists(commodity_t x, commodity_t commodities[MAX_COMMODITIES], int size) {
    for (int i = 0; i < size; i++) {
        if (is_commodities_equal(x, commodities[i])) {
            return true;
        }
    }
    return false;
}

/*
 * Get an array of all of the commodities in the world.
 *
 * input:
 *          location: A reference location to start the search from (can be anywhere in the world).
 *          commodities[]: A pointer to an array that will be modified to have all the commodities of the world to be in it.
 * output:
 *          commodities[]: Will have commodity struct points placed in it.
 *          returns the number of commodities in the commodities[] array
 */
int all_commodities(location_t location, commodity_t commodities[MAX_COMMODITIES]) {
    location_t a_location = location;
    int numCommodities = 0;
    do {
        commodity_t a_commodity = a_location->commodity;
        if (a_commodity != NULL) {
            if (!commodity_exists(a_commodity, commodities, numCommodities)) {
                commodities[numCommodities] = a_commodity;
                numCommodities++;
            }
        }
        a_location = a_location->next;
    } while (a_location != location);

    return numCommodities;
}

/*
 * Get an array of all locations of either BUYER or SELLER of a specific commodity in the world.
 *
 * inputs:
 *          bot: A pointer to bot is used to get a starting location to run the search from.
 *          commodity: The target commodity, for the locations to have.
 *          type: Either BUYER or SELLER.
 *          locations[]: A pointer to an array that will be modified to have all the locations of the specified type and commodity in the world to be in it.
 * output:
 *          locations[]: Will have location struct points placed in it.
 *          returns the number of locations in the locations[] array
 */
int all_locations_of_commodity_of_type(bot_t bot, commodity_t commodity, int type, location_t locations[MAX_LOCATIONS]) {
    location_t a_location = bot->location;
    int index = 0;
    do {
        if (a_location->type == type) {
            if (strcmp(a_location->commodity->name, commodity->name) == 0) {
                locations[index] = a_location;
                index++;
            }
        }
        a_location = a_location->next;
    } while (a_location != bot->location);
    return index;
}

/*
 * A shortcut, slightly more verbose function for calling all_locations_of_commodity_of_type but just for BUYERs.
 * Refer to all_locations_of_commodity_of_type
 */
int all_buyers_of_commodity(bot_t bot, commodity_t commodity, location_t locations[MAX_LOCATIONS]) {
    return all_locations_of_commodity_of_type(bot, commodity, LOCATION_BUYER, locations);
}

/*
 * A shortcut, slightly more verbose function for calling all_locations_of_commodity_of_type but just for SELLERs.
 * Refer to all_locations_of_commodity_of_type
 */
int all_sellers_of_commodity(bot_t bot, commodity_t commodity, location_t locations[MAX_LOCATIONS]) {
    return all_locations_of_commodity_of_type(bot, commodity, LOCATION_SELLER, locations);
}

int all_locations_of_commodity(bot_t bot, commodity_t commodity, location_t locations[MAX_LOCATIONS]) {
    location_t buyers[MAX_LOCATIONS] = {0};
    location_t sellers[MAX_LOCATIONS] = {0};
    int numBuyers = all_buyers_of_commodity(bot, commodity, buyers);
    int numSellers = all_sellers_of_commodity(bot, commodity, sellers);

    // Copy all Buyers
    for (int i = 0; i < numBuyers; i++) {
        locations[i] = buyers[i];
    }

    // Copy all Sellers
    for (int i = numBuyers; i < numBuyers + numSellers; i++) {
        locations[i] = sellers[numBuyers - i];
    }

    return numBuyers + numSellers;
}

/*
 * Get an array of all petrol stations in the world.
 *
 * inputs:
 *          location: A reference location to start the search from (can be anywhere in the world).
 *          locations[]: A pointer to an array that will be modified to have all the locations of petrol stations in the world to be in it.
 * output:
 *          locations[]: Will have location struct points placed in it.
 *          returns the number of locations in the locations[] array
 */
int all_petrol_stations(location_t a_location, location_t locations[MAX_LOCATIONS]) {
    location_t tracker = a_location;
    int index = 0;
    do {
        if (tracker->type == LOCATION_PETROL_STATION) {
            locations[index] = tracker;
            index++;
        }
        tracker = tracker->next;
    } while (tracker != a_location);
    return index;
}