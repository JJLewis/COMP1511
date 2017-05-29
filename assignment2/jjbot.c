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
    int current_type = b->location->type;
    action_t an_action;
    location_pair_t pair = get_pair_for_action(b);
    
    // If there aren't any good pairs, don't do anything, just stay put.
    if (pair == NULL) {
        if (has_cargo(b)) {
            an_action = at_null_pair_action(b);
        } else {
            an_action = create_action(ACTION_MOVE, 0, b->location);
        }
    } else {
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
    }

    if (should_refuel(b, an_action)) {
        location_t nearest_fuel = nearest_petrol_station(b->location, -1);
        int distance = amount_move_to(b, nearest_fuel);
        free(an_action);
        an_action = create_action(ACTION_MOVE, distance, nearest_fuel);
    }

    *action = an_action->action;
    *n = an_action->n;
    free(an_action);
    free(pair);
}
