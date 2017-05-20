//
// Created by Jordan Lewis on 20/5/17.
//

#ifndef ASSIGNMENT2_STRUCTS_H
#define ASSIGNMENT2_STRUCTS_H

#endif //ASSIGNMENT2_STRUCTS_H

typedef struct bot *bot_t;
typedef struct location *location_t;
typedef struct cargo *cargo_t;
typedef struct commodity *commodity_t;
typedef struct bot_list *bot_list_t;

struct location_pair {
    location_t seller;
    location_t buyer;
    commodity_t commodity;
    int distance;
};

typedef struct location_pair *location_pair_t;