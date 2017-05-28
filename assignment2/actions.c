//
// Created by Jordan Lewis on 28/5/17.
//

#include "jjbot.h"
#include "world.h"
#include <stdlib.h>

action_t create_action(int action, int n) {
    action_t an_action = malloc(sizeof(struct action));
    an_action->action = action;
    an_action->n = n;
    return an_action;
}

action_t create_default_move_action(bot_t b, location_pair_t pair) {
    int n = amount_move_to(b, pair->seller);
    if (has_cargo(b)) {
        n = amount_move_to(b, pair->buyer);
    }
    return create_action(ACTION_MOVE, n);
}

action_t at_seller_action(bot_t b, location_pair_t pair) {
    if (is_location_equal(b->location, pair->seller)) {
        if (has_cargo(b)) {
            return create_action(ACTION_MOVE, amount_move_to(b, pair->buyer));
        } else {
            return create_action(ACTION_BUY, amount_to_buy(b, pair));
        }
    } else {
        return create_default_move_action(b, pair);
    }
}

action_t at_buyer_action(bot_t b, location_pair_t pair) {
    if (is_location_equal(b->location, pair->buyer)) {
        if (has_cargo(b)) {
            return create_action(ACTION_SELL, cargo_quantity_for(b, pair->commodity));
        } else {
            return create_action(ACTION_MOVE, amount_move_to(b, pair->seller));
        }
    } else {
        return create_default_move_action(b, pair);
    }
}

action_t at_petrol_action(bot_t b, location_pair_t pair) {
    if (is_full_fuel(b)) {
        return create_action(ACTION_MOVE, amount_move_to(b, pair->buyer));
    } else {
        if (b->location->quantity > 0) {
            return create_action(ACTION_BUY, b->fuel_tank_capacity - b->fuel);
        } else {
            return create_default_move_action(b, pair);
        }
    }
}
