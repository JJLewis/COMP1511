//
// Created by Jordan Lewis on 13/5/17.
//

#include "jjbot.h"
#include "world.h"

int cost_of_travel(location_t *start, location_t *end) {
    int distance = true_distance_between(start, end);
    location_t *petrol = nearest_petrol_station(end, -1);
    return distance * petrol->price;
}