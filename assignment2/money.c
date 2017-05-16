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
        // Account for the seller offering less than the max
        if (seller->quantity < maxLoadable) { maxLoadable = seller->quantity; }
        for (int b = 0; b < numBuyers; b++) {
            location_t *buyer = buyers[b];
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

    *b_seller = sellers[row];
    *b_buyer = buyers[col];
}

// TODO: Should floor or ceil num_turns_2_exhaust?
int gain_from_exhausting(bot_t *bot, location_t *seller, location_t *buyer) {
    int max_loadable = max_cargo_amount_for_commodity(bot, seller->commodity);
    int seller_amount = seller->quantity;
    int seller_price = seller->price;
    int buyer_amount = buyer->quantity;
    int buyer_price = buyer->price;
    int max_amount = seller_amount > buyer_amount ? seller_amount : buyer_amount;
    int num_turns_2_exhaust = floorf((double)max_amount / (double)max_loadable);
    int travel_cost = cost_of_travel(seller, buyer);

    int total_profit = max_amount * (buyer_price - seller_price);
    int total_lost_in_transit = 2 * travel_cost * num_turns_2_exhaust;

    return total_profit - total_lost_in_transit;
}

void best_buy_sell_pair(bot_t *bot, location_t *b_seller, location_t *b_buyer) {
    commodity_t commodities[];
    int num_commodities = all_commodities(bot->location, commodities);

    location_t *best_seller;
    location_t *best_buyer;
    best_pair_for_commodity(bot, commodities[0], best_seller, best_buyer);
    int max_gain = gain_from_exhausting(best_seller, best_buyer);

    for (int c = 1; c < num_commodities; c++) {
        location_t *seller;
        location_t *buyer;
        best_pair_for_commodity(bot, commodities[i], seller, buyer);
        int gain = gain_from_exhausting(bot, seller, buyer);
        if (gain > max_gain) {
            best_seller = seller;
            best_buyer = buyer;
            max_gain = gain;
        }
    }

    *b_seller = best_seller;
    *b_buyer = best_buyer;
}