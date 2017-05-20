//
// Created by Jordan Lewis on 16/5/17.
//

#include "trader_bot.h"
#include "jjbot.h"
#include "world.h"
#include "handy.h"
#include <stdbool.h>

char *get_bot_name(void) {
    return "Plumpess";
}

int amount_move_to(bot_t bot, location_t destination) {
    int max_move = bot->maximum_move;
    int distance = distance_between(bot->location, destination);
    int t_distance = true_distance_between(bot->location, destination);
    if (t_distance < max_move) {
        return distance;
    }
    return distance_to_direction(distance) * max_move;
}

int amount_to_buy(bot_t bot, location_pair_t pair) {
    int max_loadable = max_cargo_amount_for_commodity(bot, pair->commodity);
    int seller_q = pair->seller->quantity;
    int buyer_q = pair->buyer->quantity;
    int to_buy[3] = {max_loadable, seller_q, buyer_q};
    return smallestElementI(3, to_buy);
}

bool is_at_either_location(bot_t b, location_pair_t pair) {
    return is_location_equal(b->location, pair->seller) || is_location_equal(b->location, pair->buyer);
}

void get_action(struct bot *b, int *action, int *n) {
    location_t current_location = bot->location;
    int current_type = current_location->type;

    location_pair_t pair;
    if (has_cargo(b)) {
        pair = best_pair_for_commodity(b, b->cargo->commodity);
    } else {
        pair = best_buy_sell_pair(b);
    }


    /*
     * Fuel code here
     */
    if (should_refuel(b, pair)) {
        if (!is_at_either_location(b, pair)) {
            if (has_cargo(b)) {
                location_t nearest_petrol = nearest_petrol_station(bot->location, -1);
                *action = ACTION_MOVE;
                *n = amount_move_to(b, nearest_petrol);
            }
        }
    }

    switch (current_type) {
        case LOCATION_START:
            *action = ACTION_MOVE;
            *n = amount_move_to(bot, pair->seller);
            return;
        case LOCATION_SELLER:
            // If at the correct seller
            if (is_location_equal(bot->location, pair->seller)) {
                if (has_cargo(bot)) {
                    // Move to buyer
                    *action = ACTION_MOVE;
                    *n = amount_move_to(bot, pair->buyer);
                } else {
                    *action = ACTION_BUY;
                    *n = amount_to_buy(bot, pair);
                }
            } else {
                // If not at the right seller (ie still in transit)
                *action = ACTION_MOVE;
                *n = amount_move_to(bot, pair->seller);
            }
            break;
        case LOCATION_BUYER:
            if (is_location_equal(b->location, pair->buyer)) {
                if (has_cargo(b)) {
                    *action = ACTION_BUY;
                    *n = cargo_quantity_for(b, pair->commodity);
                } else {
                    *action = ACTION_MOVE;
                    *n = amount_move_to(bot, pair->seller);
                }
            }
            break;
        case LOCATION_PETROL_STATION:
            if (is_full_fuel(b)) {
                *action = ACTION_MOVE;
                *n = amount_move_to(b->location, pair->buyer);
            } else {
                *action = ACTION_BUY;
                *n = b->fuel_tank_capacity - b->fuel;
            }
            break;
        default:
            *action = ACTION_MOVE;
            if (has_cargo(b)) {
                *n = amount_move_to(b->location, pair->buyer);
            } else {
                *n = amount_move_to(b->location, pair->seller);
            }
            break;
    }

    free(pair);
}