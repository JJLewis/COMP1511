//
// Created by Jordan Lewis on 13/5/17.
//

#include "jjbot.h"
#include "world.h"
#include "handy.h"
#include "debugger.h"
#include <math.h>
#include <stdlib.h>

int cost_of_travel(location_pair_t pair) {
    int distance = pair->distance;
    location_t petrol = nearest_petrol_station(pair->buyer, -1);
    return distance * petrol->price;
}

double gain_per_turn(location_t seller, location_t buyer, bot_t bot, int max_cargo) {
    int distance = true_distance_between(seller, buyer);
    int travelTurns = (int)ceilf((double)bot->maximum_move / (double)distance);
    int tradeTurns = 2 + 2 * travelTurns; // buy, travel, sell, travel back to buy

    int maxLoadable = max_cargo_amount_for_commodity(bot, seller->commodity);

    int buyCost = seller->price * maxLoadable;
    int sellCost = buyer->price * maxLoadable;

    location_pair_t pair = create_location_pair(seller, buyer);
    int travelCost = cost_of_travel(pair);
    free(pair);

    int netGain = sellCost - (buyCost + 2 * travelCost);

    double gainPerTurn = (double)netGain / (double)tradeTurns;

    return gainPerTurn;
}

location_pair_t best_pair_for_commodity(bot_t bot, commodity_t commodity) {
    location_t buyers[MAX_LOCATIONS] = {0};
    location_t sellers[MAX_LOCATIONS] = {0};
    int numBuyers = all_buyers_of_commodity(bot, commodity, buyers);
    int numSellers = all_sellers_of_commodity(bot, commodity, sellers);

    numBuyers = filter_zero_quantity(buyers, numBuyers);
    numSellers = filter_zero_quantity(sellers, numSellers);

    int maxLoadable = max_cargo_amount_for_commodity(bot, commodity);

    double gainMatix[numSellers][numBuyers];

    for (int s = 0; s < numSellers; s++) {
        location_t seller = sellers[s];
        // Account for the seller offering less than the max
        if (seller->quantity < maxLoadable) { maxLoadable = seller->quantity; }
        for (int b = 0; b < numBuyers; b++) {
            location_t buyer = buyers[b];
            // Account for the buyer buying less than the max OR how much the seller is offering
            if (buyer->quantity < maxLoadable) { maxLoadable = buyer->quantity; }
            gainMatix[s][b] = gain_per_turn(seller, buyer, bot, maxLoadable);
        }
    }

    int row, col;
    double highestGain = coord_of_max_D(numSellers, numBuyers, gainMatix, &row, &col);

    if (highestGain < 0) {
        throw_warning("Best Pair for Commodity was -ve!");
    }

    return create_location_pair(sellers[row], buyers[col]);
}

// TODO: Should floor or ceil num_turns_2_exhaust?
int gain_from_exhausting(bot_t bot, location_pair_t pair) {
    int max_loadable = max_cargo_amount_for_commodity(bot, pair->commodity);
    int seller_amount = pair->seller->quantity;
    int seller_price = pair->seller->price;
    int buyer_amount = pair->buyer->quantity;
    int buyer_price = pair->buyer->price;
    int max_amount = seller_amount > buyer_amount ? seller_amount : buyer_amount;
    int num_turns_2_exhaust = floorf((double)max_amount / (double)max_loadable);
    int travel_cost = cost_of_travel(pair);

    int total_profit = max_amount * (buyer_price - seller_price);
    int total_lost_in_transit = 2 * travel_cost * num_turns_2_exhaust;

    return total_profit - total_lost_in_transit;
}

location_pair_t best_buy_sell_pair(bot_t bot) {
    commodity_t commodities[] = {0};
    int num_commodities = all_commodities(bot->location, commodities);

    location_pair_t best_pair = best_pair_for_commodity(bot, commodities[0]);
    int max_gain = gain_from_exhausting(bot, best_pair);

    for (int c = 1; c < num_commodities; c++) {
        location_pair_t pair = best_pair_for_commodity(bot, commodities[c]);
        int gain = gain_from_exhausting(bot, pair);
        if (gain > max_gain) {
            free(best_pair); // Free all structs that aren't the best so not required.
            best_pair = pair;
            max_gain = gain;
        } else {
            free(pair); // Free all structs that aren't the best so not required.
        }
    }

    return best_pair;
}
