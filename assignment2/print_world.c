// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// May 09 2017
//
// CONTACT:
// Email: dev_jordanlewis@icloud.com
// Websites:
// https://jjlewis.github.io
// https://github.com/jjlewis/COMP1511

/*
 *      This whole file is an extension of debugger.h/c and prints in various ways location structs.
 *      Note the way these functions print are mostly formatted by printing dividing lines before and after the core print statement.
 *      All functions in this file obey the IS_DEBUGGING flag rule.
 */

#include <stdio.h>
#include <stdbool.h>
#include "trader_bot.h"
#include "world.h"
#include "structs.h"
#include "debugger.h"

void print_target_destination(bot_t bot, location_t loc) {
    if (IS_DEBUGGING && loc != NULL) {
        println();
        printf("TARGET DESTINATION (%d): ", true_distance_between(bot->location, loc));
        print_location(loc);
        println();
    }
}

void print_array_of_locations(location_t locations[MAX_LOCATIONS], int size) {
    if (IS_DEBUGGING) {
        println();
        for (int i = 0; i < size; i++) {
            location_t loc = locations[i];
            print_location(loc);
        }
        println();
    }
}

void print_location(location_t loc) {
    if (IS_DEBUGGING) {
        if (loc == NULL) {
            throw_warning("LOCATION TO PRINT IS NULL");
        } else {
            char output[80] = "";
            char *name = loc->name;
            int type = loc->type;

            if (type == LOCATION_START) {
                sprintf(output, "start");
            } else if (type == LOCATION_DUMP) {
                sprintf(output, "dump");
            } else if (type == LOCATION_OTHER) {
                sprintf(output, "other");
            } else if (type == LOCATION_PETROL_STATION) {
                sprintf(output, "Petrol Station %i units of available fuel for $%i", loc->quantity, loc->price);
            } else {
                // Buyer or Seller
                sprintf(output, "will %s %i units of %s for $%i", type == LOCATION_BUYER ? "buy" : "sell", loc->quantity,
                        loc->commodity->name, loc->price);
            }

            printf("%s: %s\n", name, output);
        }
    }
}

void print_world(struct bot *b) {
    if (IS_DEBUGGING) {
        struct location *head = b->location;
        struct location *loc = head;
        bool hasStarted = false;

        while (!(loc == head && hasStarted)) {
            hasStarted = true;

            print_location(loc);

            loc = loc->next;
        }
    }
}
