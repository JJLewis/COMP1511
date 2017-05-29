//
// Created by Jordan Lewis on 16/5/17.
//

#include "jjbot.h"
#include "world.h"
#include "handy.h"
#include <stdbool.h>
#include <stdlib.h>
#include "debugger.h"

char *get_bot_name(void) {
    return "Plumpess";
}

location_pair_t get_pair_for_action(bot_t b) {
    if (has_cargo(b)) {
        return best_pair_for_commodity(b, b->cargo->commodity);
    } else {
        return best_buy_sell_pair(b);
    }
}

void get_action(struct bot *b, int *action, int *n) {
    location_t current_location = b->location;
    int current_type = current_location->type;

    location_pair_t pair = get_pair_for_action(b);

    // If there aren't any good pairs, don't do anything, just stay put.
    if (pair == NULL) {
        if (has_cargo(b)) {
            // Find closest buyer of commodity to location, and move there and sell.
            // also create a pair so that the default sell action can occur
            action_t an_action = at_null_pair_action(b);
            *action = an_action->action;
            *n = an_action->n;
            free(an_action);
            return;
        } else {
            *action = ACTION_MOVE;
            *n = 0;
            return;
        }
    }

    /*
     * Fuel code here
     */
    if (should_refuel(b, pair)) {
        if (!is_at_either_location(b, pair) && b->location->type != LOCATION_PETROL_STATION) {
            if (has_cargo(b)) {
                location_t nearest_petrol = nearest_petrol_station(b->location, -1);
                int destination_to_petrol = true_distance_between(pair->buyer, nearest_petrol);
                int remaining_fuel = b->fuel - destination_to_petrol;
                if (destination_to_petrol < remaining_fuel) {
                    *action = ACTION_MOVE;
                    *n = amount_move_to(b, nearest_petrol);
                    print("NEITHER REFUEL");
                    return;
                }
            }
        }

        if (pair->distance <= b->maximum_move) {
            int current_type = b->location->type;
            if (current_type != LOCATION_PETROL_STATION) {
                location_t nearest_petrol = nearest_petrol_station(b->location, -1);
                *action = ACTION_MOVE;
                *n = amount_move_to(b, nearest_petrol);
                return;
            }
        }
    }

    action_t an_action;
    switch (current_type) {
        case LOCATION_SELLER:
            an_action = at_seller_action(b, pair);
            break;
        case LOCATION_BUYER:
            an_action = at_buyer_action(b, pair);
            break;
        case LOCATION_PETROL_STATION:
            an_action = at_petrol_action(b, pair);
            break;
        default:
            an_action = create_default_move_action(b, pair);
            break;
    }
    *action = an_action->action;
    *n = an_action->n;
    free(an_action);

    location_t destination = location_from_with_distance(b->location, *n);
    location_t nearest_fuel = nearest_petrol_station(destination, -1);
    int destination_to_fuel_distance = true_distance_between(destination, nearest_fuel);
    int remaining_fuel = b->fuel - (*n * distance_to_direction(*n));
    if (*action == ACTION_MOVE && remaining_fuel < destination_to_fuel_distance) {
        *n = amount_move_to(b, nearest_fuel);
    }

    free(pair);
}
