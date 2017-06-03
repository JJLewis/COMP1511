//
// Created by Jordan Lewis on 13/5/17.
//

#include "world.h"
#include "jjbot.h"
#include "debugger.h"
#include <stdbool.h>
#include <stdlib.h>

location_t find_start_location(location_t a_location) {
    location_t current = a_location;
    while (current->type != LOCATION_START) {
        current = current->next;
    }
    return current;
}

location_t highest_buyer_of_commodity(bot_t bot, commodity_t commodity) {
    location_t buyers[MAX_LOCATIONS] = {0};
    int numBuyers = all_buyers_of_commodity(bot, commodity, buyers);

    location_t highest = buyers[0];
    for (int i = 0; i < numBuyers; i++) {
        location_t a_location = buyers[i];
        if (a_location->quantity > 0) {
            if (a_location->price > highest->price) {
                highest = a_location;
            }
        }
    }

    return highest;
}

location_t lowest_seller_of_commodity(bot_t bot, commodity_t commodity) {
    location_t sellers[MAX_LOCATIONS] = {0};
    int numSellers = all_sellers_of_commodity(bot, commodity, sellers);

    location_t lowest = sellers[0];
    for (int i = 0; i < numSellers; i++) {
        location_t a_location = sellers[i];
        if (a_location->quantity > 0) {
            if (a_location->price < lowest->price) {
                lowest = a_location;
            }
        }
    }

    return lowest;
}

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

// TODO: Remember that a -1 for min distance will return a 'self sustaining' petrol station, ie, enough fuel to cover the distance travelled for it
// Should it be 2x the distance?
location_t nearest_petrol_station(location_t location, int minimumFuel) {
    location_t stations[MAX_LOCATIONS];
    int numStations = all_petrol_stations(location, stations);
	
    bool can_be_zero = minimumFuel == 0;
	
	if (!can_be_zero) {
		numStations = filter_zero_quantity(stations, numStations);
	}

//	print_array_of_locations(stations, numStations);

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
	
//	print("Now checking:");
//	print_location(a_location);
//	printI(distance);

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

location_t best_buyer_in_range_from_this_seller(bot_t bot) {
    location_t seller = bot->location;
    commodity_t commodity = seller->commodity;
    /*
     * Get quantity seller has
     * get quantity can buy
     * take the lesser of the two
     * for each buyer get the lesser of can buy vs can sell
     * get amount can make from transaction
     */
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
