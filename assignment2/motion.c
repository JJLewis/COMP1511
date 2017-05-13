//
// Created by Jordan Lewis on 13/5/17.
//

#include "world.h"

int distance_between(location_t *location1, location_t *location2) {
    int forward_distance = 0;
    location_t *tracking_location = location1;
    while (tracking_location != location2) {
        forward_distance++;
        tracking_location = tracking_location->next;
    }

    int back_distance = 0;
    tracking_location = location1;
    while (tracking_location != location2) {
        back_distance++;
        tracking_location = tracking_location->previous;
    }

    if (forward_distance < back_distance) {
        return forward_distance;
    } else {
        return -back_distance;
    }
}

int true_distance_between(location_t *location1, location_t *location2) {
    int distance = distance_between(location1, location2);
    int direction = distance_to_direction(distance);
    return distance * direction;
}

void shift_location(location_t *location, int direction) {
    if (direction == DIRECTION_FORWARD) {
        location = location->next;
    } else {
        location = location->previous;
    }
}

int distance_to_direction(int distance) {
    if (distance > 0) {
        return DIRECTION_FORWARD;
    } else {
        return DIRECTION_BACKWARD;
    }
}

void move_location(location_t *location, int distance) {
    int direction = distance_to_direction(distance);
    // Multiplying the distance by the direction makes the distance always +ve
    for (int i = 0; i < distance * direction; i++) {
        shift_location(location, direction);
    }
}