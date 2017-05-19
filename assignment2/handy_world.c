//
// Created by Jordan Lewis on 13/5/17.
//

#include "world.h"

int number_of_locations(bot_t *bot) {
    location_t *start = find_start_location(bot->location);
    location_t *a_location = start;
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

// TODO: Check if location[i].quantity works
int filter_zero_quantity(location_t locations[MAX_LOCATIONS], int size) {
    location_t temp[MAX_LOCATIONS] = {0};
    int index = 0;
    for (int i = 0; i < size; i++) {
        if (locations[i].quantity > 0) {
            temp[index] = locations[i];
            index++;
        }
    }
    duplicate_locations(temp, locations, size);
    return index;
}

location_pair_t *create_location_pair(location_t *seller, location_t *buyer) {
    location_pair_t *pair = malloc(sizeof(location_pair_t));
    pair->seller = seller;
    pair->buyer = buyer;
    pair->commodity = seller->commodity;
    pair->distance = true_distance_between(seller, buyer);
    return pair;
}