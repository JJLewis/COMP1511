//
// Created by Jordan Lewis on 16/5/17.
//

#include "trader_bot.h"
#include "jjbot.h"
#include "world.h"
#include "handy.h"

char *get_bot_name(void) {
    return "Plumpess";
}

int amount_move_to(bot_t *bot, location_t *destination) {
    int max_move = bot->maximum_move;
    int distance = distance_between(bot->location, destination);
    int t_distance = true_distance_between(bot->location, destination);
    if (t_distance < max_move) {
        return distance;
    }
    return distance_to_direction(distance) * max_move;
}

int amount_to_buy(bot_t *bot, location_pair_t *pair) {
    int max_loadable = max_cargo_amount_for_commodity(bot, pair->commodity);
    int seller_q = pair->seller->quantity;
    int buyer_q = pair->buyer->quantity;
    int to_buy[3] = {max_loadable, seller_q, buyer_q};
    return smallestElementI(3, to_buy);
}









void get_action(struct bot *b, int *action, int *n) {
    location_t *current_location = bot->location;
    int current_type = current_location->type;

    switch (current_type) {
        case LOCATION_START:
            location_pair_t *pair = best_buy_sell_pair(b);
            *action = ACTION_MOVE;
            *n = amount_move_to(bot, pair->seller);
            return;
        case LOCATION_SELLER:
            location_pair_t *pair = best_buy_sell_pair(b);
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
            break;
        default:
            break;
    }
}