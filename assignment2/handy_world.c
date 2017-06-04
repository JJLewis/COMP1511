//
// Created by Jordan Lewis on 13/5/17.
//

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "world.h"
#include "debugger.h"

int number_of_locations(bot_t bot) {
    location_t start = find_start_location(bot->location);
    location_t a_location = start;
    int counter = 0;

    do {
        counter++;
        a_location = a_location->next;
    } while (start != a_location);

    return counter;
}

void duplicate_locations(location_t source[MAX_LOCATIONS], location_t destination[MAX_LOCATIONS], int size) {
    for (int i = 0; i < size; i++) {
        destination[i] = source[i];
    }
}

int filter_zero_quantity(location_t locations[MAX_LOCATIONS], int size) {
    location_t temp[MAX_LOCATIONS] = {0};
    int index = 0;
    for (int i = 0; i < size; i++) {
        if (locations[i]->quantity > 0) {
            temp[index] = locations[i];
            index++;
        }
    }
    duplicate_locations(temp, locations, size);
    return index;
}

location_pair_t create_location_pair(location_t seller, location_t buyer) {

    if (seller == NULL) {
        print("In create_location_pair (handy_world.c), SELLER passed was NULL!!!");
        return NULL;
    }
    if (buyer == NULL) {
        print("In create_location_pair (handy_world.c), BUYER passed was NULL!!!");
        return NULL;
    }

    location_pair_t pair = malloc(sizeof(struct location_pair));
    pair->seller = seller;
    pair->buyer = buyer;
    pair->commodity = buyer->commodity;
    pair->distance = true_distance_between(seller, buyer);
    return pair;
}

bool is_location_equal(location_t location1, location_t location2) {
    if (location1->type == location2->type) {
        if (strcmp(location1->name, location2->name) == 0) {
            if (is_commodities_equal(location1->commodity, location2->commodity)) {
                return true;
            }
        }
    }
    return false;
}

bool is_commodities_equal(commodity_t c1, commodity_t c2) {
    if (strcmp(c1->name, c2->name) == 0) {
        return true;
    }
    return false;
}

bool is_at_either_location(bot_t b, location_pair_t pair) {
    return is_location_equal(b->location, pair->seller) || is_location_equal(b->location, pair->buyer);
}

int petrol_left_in_world(bot_t bot) {
    location_t petrol_stations[MAX_LOCATIONS];
    int num_petrol_stations = all_petrol_stations(bot->location, petrol_stations);
    int left_over = bot->fuel;
    for (int i = 0; i < num_petrol_stations; i++) {
        location_t petrol_station = petrol_stations[i];
        left_over += petrol_station->quantity;
    }

    return left_over;
}

bool is_type_of_commodity(location_t loc, int type, commodity_t commodity) {
    return (loc->type == type && is_commodities_equal(loc->commodity, commodity));
}

bool is_buyer_of_commodity(location_t loc, commodity_t commodity) {
    return is_type_of_commodity(loc, LOCATION_BUYER, commodity);
}

bool is_seller_of_commodity(location_t loc, commodity_t commodity) {
    return is_type_of_commodity(loc, LOCATION_SELLER, commodity);
}