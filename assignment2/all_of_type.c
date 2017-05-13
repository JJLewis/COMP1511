//
// Created by Jordan Lewis on 13/5/17.
//

#include "jjbot.h"
#include "world.h"
#include <string.h>

int all_locations_of_commodity_of_type(bot_t *bot, commodity_t *commodity, int type, location_t locations[MAX_LOCATIONS]) {
    location_t *a_location = bot->location;
    int index = 0;
    do {
        if (a_location->type == type) {
            if (strcmp(a_location->commodity->name, commodity->name)) {
                locations[index] = a_location;
                index++;
            }
        }
        a_location = a_location->next;
    } while (a_location != bot->location);
    return index;
}

int all_buyers_of_commodity(bot_t *bot, commodity_t *commodity, location_t locations[MAX_LOCATIONS]) {
    return all_locations_of_commodity_of_type(bot, commodity, LOCATION_BUYER, locations);
}

int all_sellers_of_commodity(bot_t *bot, commodity_t *commodity, location_t locations[MAX_LOCATIONS]) {
    return all_locations_of_commodity_of_type(bot, commodity, LOCATION_SELLER, locations);
}

int all_locations_of_commodity(bot_t *bot, commodity_t *commodity, location_t locations[MAX_LOCATIONS]) {
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

int all_petrol_stations(location_t *a_location, location_t locations[MAX_LOCATIONS]) {
    location_t *tracker = a_location;
    int index = 0;
    do {
        if (tracker->type == LOCATION_PETROL_STATION) {
            locations[index] = tracker;
            index++;
        }
    } while (tracker != start);
    return index;
}