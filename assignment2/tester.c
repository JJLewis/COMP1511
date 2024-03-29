//
// Created by Jordan Lewis on 20/5/17.
//
// CONTACT:
// Email: dev_jordanlewis@icloud.com
// Websites:
// https://jjlewis.github.io
// https://github.com/jjlewis/COMP1511

#include <stdlib.h>
#include "trader_bot.h"
#include "world.h"
#include "structs.h"
#include "debugger.h"

/*
 * Function for testing the output of the functions of all buyers and seller of a commodity.
 */
void test_all_bs_of_commodity(bot_t bot, commodity_t commodity) {
    print("Buyers");
    location_t buyers[MAX_LOCATIONS];
    int numBuyers = all_buyers_of_commodity(bot, commodity, buyers);
    printI(numBuyers);
    print_array_of_locations(buyers, numBuyers);

    print("Sellers");
    location_t sellers[MAX_LOCATIONS];
    int numSellers = all_sellers_of_commodity(bot, commodity, sellers);
    printI(numSellers);
    print_array_of_locations(sellers, numSellers);
}

/*
 * Function for testing the output of all_commodities function.
 */
void test_all_commodities(bot_t bot) {
    commodity_t commodities[MAX_COMMODITIES];
    int numCommodities = all_commodities(bot->location, commodities);
    for (int i = 0; i < numCommodities; i++) {
        test_all_bs_of_commodity(bot, commodities[i]);
        print("");
        print("");
    }
}

/*
 * Function for testing creating location_pair_t's
 */
void test_location_pairs(bot_t bot) {
    commodity_t commodities[MAX_COMMODITIES];
    int numCommodities = all_commodities(bot->location, commodities);
    location_t buyers[MAX_LOCATIONS], sellers[MAX_LOCATIONS];
    int numBuyers = all_buyers_of_commodity(bot, commodities[0], buyers);
    int numSellers = all_sellers_of_commodity(bot, commodities[0], sellers);
    location_pair_t pair = create_location_pair(sellers[0], buyers[0]);
    println();
    print(pair->seller->name);
    print(pair->buyer->name);
    print(pair->commodity->name);
    printI(pair->distance);
    println();
}

/*
 * Just a function for calling test functions. hahaha.
 */
void test(bot_t bot) {
    test_location_pairs(bot);
}

/*
 * Commented out main to prevent issues with running the auto-tests.
 */
/*
int main(void) {

    struct commodity c[] = {
            // name                   weight    volume
            { "Computers",            17344,     4044 },
            { "Beer",                  1958,     2799 },
            { "Books",                 6628,     8804 },
            { "Mars Bars",              108,       93 },
            { "Televisions",          12609,     4104 },
    };

    struct location l[] = {
            // name                     type             commodity  price quantity  next  previous bots
            { "CSE",               LOCATION_START,           NULL,      0,      0, &l[ 1], &l[29], NULL},
            { "BP",                LOCATION_PETROL_STATION,  NULL,    194,    318, &l[ 2], &l[ 0], NULL},
            { "Mars",              LOCATION_SELLER,         &c[4],    130,   2997, &l[ 3], &l[ 1], NULL},
            { "Whitehouse",        LOCATION_BUYER,          &c[1],    158,   4623, &l[ 4], &l[ 2], NULL},
            { "Lenovo",            LOCATION_SELLER,         &c[0],   1600,    356, &l[ 5], &l[ 3], NULL},
            { "IGA UNSW",          LOCATION_BUYER,          &c[4],    362,   2768, &l[ 6], &l[ 4], NULL},
            { "UNSW Bookshop",     LOCATION_BUYER,          &c[3],    224,   2376, &l[ 7], &l[ 5], NULL},
            { "Quadrangle",        LOCATION_OTHER,           NULL,      0,      0, &l[ 8], &l[ 6], NULL},
            { "Harvey-Norman",     LOCATION_BUYER,          &c[2],    977,   1015, &l[ 9], &l[ 7], NULL},
            { "Physics Lawn",      LOCATION_OTHER,           NULL,      0,      0, &l[10], &l[ 8], NULL},
            { "Aldi",              LOCATION_BUYER,          &c[4],    255,   3778, &l[11], &l[ 9], NULL},
            { "MSY",               LOCATION_BUYER,          &c[0],   3117,    166, &l[12], &l[10], NULL},
            { "J&B Hifi",          LOCATION_BUYER,          &c[0],   3262,    176, &l[13], &l[11], NULL},
            { "Batch Brewing",     LOCATION_SELLER,         &c[1],     92,   6433, &l[14], &l[12], NULL},
            { "4 Pines",           LOCATION_SELLER,         &c[1],     91,  11933, &l[15], &l[13], NULL},
            { "Good Guys",         LOCATION_BUYER,          &c[2],   1305,    826, &l[16], &l[14], NULL},
            { "LG",                LOCATION_SELLER,         &c[2],    616,    905, &l[17], &l[15], NULL},
            { "Apple",             LOCATION_SELLER,         &c[0],   2116,    434, &l[18], &l[16], NULL},
            { "Sony",              LOCATION_SELLER,         &c[2],   1100,    313, &l[19], &l[17], NULL},
            { "Prentice-Hall",     LOCATION_SELLER,         &c[3],    149,   5340, &l[20], &l[18], NULL},
            { "O'Reilly",          LOCATION_SELLER,         &c[3],    100,   8382, &l[21], &l[19], NULL},
            { "Regent Hotel",      LOCATION_BUYER,          &c[1],    121,   4285, &l[22], &l[20], NULL},
            { "Coles",             LOCATION_BUYER,          &c[4],    292,   2409, &l[23], &l[21], NULL},
            { "James Squires",     LOCATION_SELLER,         &c[1],    106,   7547, &l[24], &l[22], NULL},
            { "Addison-Wesley",    LOCATION_SELLER,         &c[3],    215,   6064, &l[25], &l[23], NULL},
            { "Dell",              LOCATION_SELLER,         &c[0],   1953,    107, &l[26], &l[24], NULL},
            { "Caltex",            LOCATION_PETROL_STATION,  NULL,    151,    477, &l[27], &l[25], NULL},
            { "Racecourse",        LOCATION_OTHER,           NULL,      0,      0, &l[28], &l[26], NULL},
            { "Umart",             LOCATION_BUYER,          &c[0],   2739,    318, &l[29], &l[27], NULL},
            { "Dump",              LOCATION_DUMP,            NULL,      0,      0, &l[ 0], &l[28], NULL},
    };

    struct bot bots[] = {
            // name cash fuel turns_left location cargo fuel_tank_capacity maximum_move maximum_cargo_weight maximum_cargo_volume
            {"T-101", 107117, 45, &l[7], NULL, 135, 45, 6, 157370, 1717753},
    };

    struct bot_list bot_lists[] = {
            // bot next
            {&bots[0], NULL},
    };

    l[7].bots = &bot_lists[0];

    test(&bots[0]);

    return 0;
}
*/
