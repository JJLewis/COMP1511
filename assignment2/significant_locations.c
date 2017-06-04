//
// Created by Jordan Lewis on 13/5/17.
//
// CONTACT:
// Email: dev_jordanlewis@icloud.com
// Websites:
// https://jjlewis.github.io
// https://github.com/jjlewis/COMP1511

#include <stdlib.h>
#include <stdbool.h>
#include "jjbot.h"
#include "world.h"
#include "debugger.h"

/*
 * Return a boolean reflecting whether or not the bot will pass a non-empty petrol station
 */
bool will_pass_petrol(location_t start, location_t end) {
    int distance = distance_between(start, end);
    int direction = distance_to_direction(distance);

    location_t tracker = start;

    for (int i = 0; i < distance * direction; i++) {
        if (tracker->type == LOCATION_PETROL_STATION) {
            if (tracker->quantity > 0) {
                return true;
            }
        }
        shift_location(tracker, direction);
    }

    return false;
}

/*
 * Finds the nearest petrol station with a minimum amount of fuel of a specified amount.
 *
 * input:
 *          location: Find the nearest petrol station to this location.
 *          minimumFuel: The minimum amount of fuel the petrol station must have.
 *                       Pass -1 for the minimum amount of fuel to be the distance between location and the petrol station.
 *
 * returns: The nearest petrol station with at least the minimum specified amount of fuel. If there isn't return NULL.
 */
location_t nearest_petrol_station(location_t location, int minimumFuel) {
    location_t stations[MAX_LOCATIONS];
    int numStations = all_petrol_stations(location, stations);

    bool can_be_zero = minimumFuel == 0;

    if (!can_be_zero) {
        numStations = filter_zero_quantity(stations, numStations);
    }

    location_t closest = NULL;//stations[0];
    int closestDistance = -1;//true_distance_between(location, closest);
    for (int i = 0; i < numStations; i++) {
        location_t a_location = stations[i];
        int distance = true_distance_between(location, a_location);

        if (minimumFuel == -1) {
            minimumFuel = distance;
        }

        bool zero_allowed = can_be_zero && minimumFuel == 0;
        bool zero_not_allowed = (!can_be_zero && minimumFuel > 0) && a_location->quantity >= minimumFuel;

        bool is_best = false;

        if (zero_not_allowed || zero_allowed) {
            if (closest == NULL) {
                is_best = true;
            } else {
                if (distance < closestDistance) {
                    is_best = true;
                }
            }
            if (is_best && !is_location_equal(location, a_location)) {
                closest = a_location;
                closestDistance = distance;
            }
        }
    }

    return closest;
}

/*
 * Find the closest buyer of a certain commodity to a given location.
 *
 * inputs:
 *          bot: Pointer to the bot struct (used to finding all the buyers of a commodity)
 *          location: The anchor location, finds the closest buyer to this location.
 *          commodity: Look for buyers of this commodity.
 *
 * returns: The location of the closest buyer of commodity to location.
 */
location_t closest_buyer_of_commodity_to(bot_t bot, location_t location, commodity_t commodity) {
    location_t buyers[MAX_LOCATIONS];
    int num_buyers = all_buyers_of_commodity(bot, commodity, buyers);

    location_t closest_buyer = buyers[0];
    int least_distance = true_distance_between(location, closest_buyer);
    for (int i = 1; i < num_buyers; i++) {
        location_t buyer = buyers[i];
        int distance = true_distance_between(location, buyer);
        if (distance < least_distance) {
            closest_buyer = buyer;
            least_distance = distance;
        }
    }

    return closest_buyer;
}

/*
 * Find the best buyer of a commodity.
 * Do this by getting the ratio of price to distance from location.
 * Enter all the ratios into an array, and pick the highest.
 *
 * inputs:
 *          bot: Pointer to the bot struct (used to finding all the buyers of a commodity)
 *          location: The anchor location, the distance for the ratio is measured from here.
 *          commodity: Look for buyers of this commodity.
 *
 * returns: The location of the closest buyer of commodity to location.
 */
location_t best_buyer_of_commodity_to(bot_t bot, location_t location, commodity_t commodity) {
    location_t buyers[MAX_LOCATIONS];
    int num_buyers = all_buyers_of_commodity(bot, commodity, buyers);

    location_t best_buyer = buyers[0];
    int distance = true_distance_between(location, best_buyer);
    double best_ratio = (double)best_buyer->price;

    if (distance > 0) {
        best_ratio = (double)best_buyer->price / (double)true_distance_between(location, best_buyer);
    }

    for (int i = 1; i < num_buyers; i++) {
        location_t buyer = buyers[i];
        distance = true_distance_between(location, buyer);
        int price = buyer->price;
        double ratio = (double)price / (double)distance;
        if (ratio > best_ratio) {
            best_buyer = buyer;
            best_ratio = ratio;
        }

    }

    return best_buyer;
}

/*
 * Returns a boolean about whether or not the bot will pass a location between start and end.
 *
 * inputs:
 *          start: The start location.
 *          end: The end location.
 *          x: The location that the function wants to check if the bot passes.
 *
 * returns: True if the bot will pass x, False if not.
 */
bool will_pass_location(location_t start, location_t end, location_t x) {
    location_t tracker = start;
    int distance = distance_between(start, end);
    int direction = distance_to_direction(distance);
    for (int i = 0; i < distance * direction; i++) {
        shift_location(tracker, direction);
        if (is_location_equal(tracker, x)) {
            return true;
        }
    }
    return false;
}

/*
 * This function assumes the bot is carrying cargo.
 * It finds the best closest buyer to the bot of the commodity that the bot is carrying.
 * Does this by getting the ratio of (price * quantity) to the distance to the buyer and choosing the highest.
 */
location_pair_t best_closest_buyer(bot_t bot) {
    commodity_t commodity = bot->cargo->commodity;
    location_t current_location = bot->location;
    int quantity = bot->cargo->quantity;
    location_t buyers[MAX_LOCATIONS];
    int num_buyers = all_buyers_of_commodity(bot, commodity, buyers);

    location_t best_buyer = NULL;
    double best_ratio = 0;
    for (int i = 0; i < num_buyers; i++) {
        location_t buyer = buyers[i];
        if (quantity <= buyer->quantity) {
            int price = buyer->price;
            int distance = true_distance_between(current_location, buyer);
            double ratio = distance == 0 ? (double)(price * quantity) : (double)(price * quantity) / (double) distance;
            if (ratio > best_ratio) {
                best_buyer = buyer;
                best_ratio = ratio;
            } else if (ratio == best_ratio) {
                if (distance < true_distance_between(current_location, best_buyer)) {
                    best_buyer = buyer;
                }
            }
        }
    }

    if (best_buyer == NULL) {
        throw_warning("BEST CLOSEST BUYER IS NULL!!!");
    }

    return create_location_pair(current_location, best_buyer);
}

/*
 * Returns the location of a petrol station within the shortest route between two locations.
 *
 * inputs:
 *          start: The start location.
 *          end: The end location.
 *
 * returns: A location struct if one is found, otherwise NULL.
 */
location_t petrol_between(location_t start, location_t end) {
    location_t petrol_station = NULL;
    location_t tracker = start;
    int distance = distance_between(start, end);
    int direction = distance_to_direction(distance);
    int true_distance = distance * direction;

    for (int i = 0; i < true_distance; i++) {
        if (tracker->type == LOCATION_PETROL_STATION) {
            if (tracker->quantity > 0) {
                if (petrol_station == NULL) petrol_station = tracker;
                if (tracker->price < petrol_station->price) {
                    petrol_station = tracker;
                }
            }
        }
        shift_location(tracker, direction);
    }

    return petrol_station;
}

/*
 * Finds all buyers of a commodity within the range of fuel left in the bot.
 *
 * input:
 *          bot: The bot, to access how much fuel is left and its current location.
 *          commodity: Only look for buyers of this commodity.
 *          buyers[]: This pointer to an array will have the BUYER locations found added to it, from closest to furthest.
 *
 * output:
 *          buyers[]: Array of locations of BUYERS of specified commodity, in ascending order of distance from the bot.
 *          returns: How many buyers were found in the fuel range.
 */
int buyers_in_fuel_range(bot_t bot, commodity_t commodity, location_t buyers[MAX_LOCATIONS]) {
    int fuel = bot->fuel;
    int counter = 0;

    location_t forward = bot->location;
    location_t backward = bot->location;

    for (int i = 0; i < fuel; i++) {

        forward = forward->next;
        backward = backward->previous;

        if (is_buyer_of_commodity(forward, commodity)) {
            if (forward->quantity > 0) {
                buyers[counter] = forward;
                counter++;
            }
        }

        if (is_buyer_of_commodity(backward, commodity)) {
            if (backward->quantity > 0) {
                buyers[counter] = backward;
                counter++;
            }
        }
    }

    return counter;
}

/*
 * Finds the best buyer in the fuel range of the bot at a seller.
 * Does this by finding all buyers of the commodity of the seller the bot is at in the bot's fuel range.
 * Then makes ratios by calculating the total profit of a trade ((buyer price - seller price) * quantity)
 * then dividing it by the distance between the seller and the buyer.
 * It takes the buyer with the highest ratio as the best_buyer.
 */
location_t best_buyer_in_range_from_this_seller(bot_t bot) {
    location_t seller = bot->location;
    commodity_t commodity = seller->commodity;

    int max_loadable = max_cargo_amount_for_commodity(bot, commodity);
    int can_buy_quantity = seller->quantity > max_loadable ? max_loadable : seller->quantity;

    location_t buyers[MAX_LOCATIONS];
    int num_buyers = buyers_in_fuel_range(bot, commodity, buyers);

    print_array_of_locations(buyers, num_buyers);

    location_t best_buyer = NULL;
    double best_ratio = 0;

    for (int i = 0; i < num_buyers; i++) {
        location_t buyer = buyers[i];
        int distance = true_distance_between(seller, buyer);
        int sell_quantity = buyer->quantity;
        int final_quantity = can_buy_quantity > sell_quantity ? sell_quantity : can_buy_quantity;
        int bs_profit = final_quantity * (buyer->price - seller->price);
        double ratio = (double)bs_profit / (double)distance;

        if (ratio > best_ratio) {
            best_buyer = buyer;
        }
    }

    return best_buyer;
}
