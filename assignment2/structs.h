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

struct location_pair {
    location_t seller;
    location_t buyer;
    commodity_t commodity;
    int distance;
};

typedef struct location_pair *location_pair_t;

struct action {
    int action;
    int n;
    location_t target;
};

typedef struct action *action_t;

#endif //STRUCTS_H
