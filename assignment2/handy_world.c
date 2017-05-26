//
// Created by Jordan Lewis on 13/5/17.
//

#include "world.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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

    location_pair_t pair = malloc(sizeof(location_pair_t));
    pair->seller = seller;
    pair->buyer = buyer;
    pair->commodity = seller->commodity;
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