//
// Created by Jordan Lewis on 13/5/17.
//

#include <stdlib.h>
#include "world.h"
#include "debugger.h"

/*
 * Calculates the distance between two locations.
 * NOTE: This function calculates two distances and returns the lesser of the two.
 * i.e. ->next distance & ->previous distance
 * If the ->previous distance is lesser than the ->next distance, this function will return a negative value.
 * This is because *n in get_action requires a negative value to move backwards.
 *
 * inputs:
 *          location1: The start location.
 *          location2: The end location.
 *
 * returns: An integer, like a vector, whereby the sign is direction and size is distance.
 */
int distance_between(location_t location1, location_t location2) {
    
	if (location1 == NULL || location2 == NULL) {
		return MAX_LOCATIONS * 2;
	}

	int forward_distance = 0;
    location_t tracking_location = location1;
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

/*
 * This function simply takes the distance returned from distance_between and eliminates the sign to make the value positive.
 * Order of inputs here does not matter.
 *
 * inputs:
 *          location1: The start/end location.
 *          location2: The end/start location.
 *
 * returns: An positive integer of the actual distance between the two points.
 */
int true_distance_between(location_t location1, location_t location2) {
    int distance = distance_between(location1, location2);
    int direction = distance_to_direction(distance);
    return distance * direction;
}

/*
 * Moves the struct pointer location one spot in either the next, or previous direction depending on the argument direction.
 *
 * inputs:
 *          location: The struct pointer to be shifted one spot.
 *          direction: 1 for next, -1 for previous; These are #define'd as DIRECTION_FORWARD & DIRECTION_BACKWARD
 *
 * output:
 *          location: Shifted across 1.
 */
void shift_location(location_t location, int direction) {
    if (direction == DIRECTION_FORWARD) {
        location = location->next;
    } else {
        location = location->previous;
    }
}

/*
 * Extracts just the sign of a distance to return either 1 or -1, #define'd as DIRECTION_FORWARD & DIRECTION_BACKWARD
 */
int distance_to_direction(int distance) {
    if (distance > 0) {
        return DIRECTION_FORWARD;
    } else {
        return DIRECTION_BACKWARD;
    }
}

void move_location(location_t location, int distance) {
    int direction = distance_to_direction(distance);
    // Multiplying the distance by the direction makes the distance always +ve
    for (int i = 0; i < distance * direction; i++) {
        shift_location(location, direction);
    }
}

location_t location_from_with_distance(location_t start, int distance) {
	location_t a_location = start;
	int direction = distance_to_direction(distance);
	for (int i = 0; i < distance * direction; i++) {
		if (direction == DIRECTION_FORWARD) {
			a_location = a_location->next;
		} else {
			a_location = a_location->previous;
		}
	}
	return a_location;
}

/*
 * Calculate and return the exact amount to move (just so it doesn't get reduced by the overlords running my bot).
 * It respects the maximum_move rule set by the overlords.
 * So if the distance to the destination is greater, it will simply move the maximum_allowed move in the correct direction.
 * If it is lesser, it will return the vector "distance" between the two locations from the function distance_between()
 */
int amount_move_to(bot_t bot, location_t destination) {
    int max_move = bot->maximum_move;
    int distance = distance_between(bot->location, destination);
	if (distance == MAX_LOCATIONS * 2) {
		throw_warning("Trying to move to NULL");
		return 0;
	}
    int t_distance = true_distance_between(bot->location, destination);
    if (t_distance < max_move) {
        return distance;
    }
    return distance_to_direction(distance) * max_move;
}
