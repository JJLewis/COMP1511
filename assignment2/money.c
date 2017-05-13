//
// Created by Jordan Lewis on 13/5/17.
//

#include "jjbot.h"
#include "world.h"
#include "handy.h"
#include "debugger.h"
#include <math.h>

int cost_of_travel(location_t *start, location_t *end) {
    int distance = true_distance_between(start, end);
    location_t *petrol = nearest_petrol_station(end, -1);
    return distance * petrol->price;
}

double gain_per_turn(location_t *seller, location_t *buyer, bot_t *bot, int max_cargo) {
    int distance = true_distance_between(seller, buyer);
    int travelTurns = (int)ceilf((double)bot->maximum_move / (double)distance);
    int tradeTurns = 2 + 2 * travelTurns; // buy, travel, sell, travel back to buy

    int buyCost = seller->price * maxLoadable;
    int sellCost = buyer->price * maxLoadable;
    int travelCost = cost_of_travel(seller, buyer);

    int netGain = sellCost - (buyCost + 2 * travelCost);

    double gainPerTurn = (double)netGain / (double)tradeTurns;

    return gainPerTurn;
}

void best_pair_for_commodity(bot_t *bot, commodity_t *commodity, location_t *b_seller, location_t *b_buyer) {
    location_t buyers[MAX_LOCATIONS] = {0};
    location_t sellers[MAX_LOCATIONS] = {0};
    int numBuyers = all_buyers_of_commodity(bot, commodity, buyers);
    int numSellers = all_sellers_of_commodity(bot, commodity, sellers);

    numBuyers = filter_zero_quantity(buyers, numBuyers);
    numSellers = filter_zero_quantity(sellers, numSellers);

    int maxLoadable = max_cargo_amount_for_commodity(bot, commodity);

    double gainMatix[numSellers][numBuyers];

    for (int s = 0; s < numSellers; s++) {
        location_t *seller = sellers[s];
        if (seller->quantity < maxLoadable) { maxLoadable = seller->quantity; }
        for (int b = 0; b < numBuyers; b++) {
            location_t *buyer = buyers[b];
            if (buyer->quantity < maxLoadable) { maxLoadable = buyer->quantity; }
            gainMatix[s][b] = gain_per_turn(seller, buyer, bot, maxLoadable);
        }
    }

    int row, col;
    double highestGain = coord_of_max_D(numSellers, numBuyers, gainMatix, &row, &col);

    if (highestGain < 0) {
        throw_warning("Best Pair for Commodity was -ve!");
    }

    *b_seller = sellers[row];
    *b_buyer = buyers[col];
}