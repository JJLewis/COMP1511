//
// Created by Jordan Lewis on 13/5/17.
//

#include "world.h"
#include <stdbool.h>

location_t find_start_location(location_t a_location) {
    location_t current = a_location;
    while (current->type != LOCATION_START) {
        current = current->next;
    }
    return current;
}

location_t highest_buyer_of_commodity(bot_t bot, commodity_t *commodity) {
    location_t buyers[MAX_LOCATIONS] = {0};
    int numBuyers = all_buyers_of_commodity(bot, commodity, buyers);

    location_t highest = buyers[0];
    for (int i = 0; i < numBuyers; i++) {
        location_t a_location = buyers[i];
        if (a_location->quantity > 0) {
            if (a_location->price > highest->price) {
                highest = a_location;
            }
        }
    }

    return highest;
}

location_t lowest_seller_of_commodity(bot_t bot, commodity_t *commodity) {
    location_t sellers[MAX_LOCATIONS] = {0};
    int numSellers = all_sellers_of_commodity(bot, commodity, sellers);

    location_t lowest = sellers[0];
    for (int i = 0; i < numSellers; i++) {
        location_t a_location = sellers[i];
        if (a_location->quantity > 0) {
            if (a_location->price < lowest->price) {
                lowest = a_location;
            }
        }
    }

    return lowest;
}

bool will_pass_petrol(location_t start, location_t end) {
    int direction = distance_to_direction(distance_between(start, end));

    location_t tracker = start;
    while (tracker != end) {
        if (tracker->type == LOCATION_PETROL_STATION) {
            return true;
        }
        shift_location(tracker, direction);
    }

    return false;
}

// TODO: Remember that a -1 for min distance will return a 'self sustaining' petrol station, ie, enough fuel to cover the distance travelled for it
// Should it be 2x the distance?
location_t nearest_petrol_station(location_t location, int minimumFuel) {
    location_t stations[MAX_LOCATIONS];
    int numStations = all_petrol_stations(location, stations);

    location_t closest = stations[0];
    int closestDistance = true_distance_between(location, closest);
    for (int i = 0; i < numStations; i++) {
        location_t a_location = stations[i];
        int distance = true_distance_between(location, a_location);

        if (minimumFuel == -1) {
            minimumFuel = distance;
        }

        if (a_location->quantity > minimumFuel) {
            if (distance < closestDistance) {
                closestDistance = distance;
                closest = a_location;
            }
        }
    }

    return closest;
}
