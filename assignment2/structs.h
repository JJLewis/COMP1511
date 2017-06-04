//
// Created by Jordan Lewis on 20/5/17.
//

#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct bot *bot_t;
typedef struct location *location_t;
typedef struct cargo *cargo_t;
typedef struct commodity *commodity_t;
typedef struct bot_list *bot_list_t;

/*
 * Holds a pair of locations, for ease of passing as an argument or returning as a function.
 * Buyer and Seller commodity must/should be the same.
 */
struct location_pair {
    location_t seller;
    location_t buyer;
    commodity_t commodity; // The commodity of both the buyer and the seller
    int distance; // True distance between the buyer and the seller
};

typedef struct location_pair *location_pair_t;

/*
 * Just wrapping up the get_action values that need to be assigned so that it can be easily used/returned for functions.
 */
struct action {
    int action;
    int n;
    location_t target; // Target location struct if the action is MOVE, otherwise NULL
};

typedef struct action *action_t;

#endif //STRUCTS_H
