//
// Created by Jordan Lewis on 16/5/17.
//
// CONTACT:
// Email: dev_jordanlewis@icloud.com
// Websites:
// https://jjlewis.github.io
// https://github.com/jjlewis/COMP1511



/*
*  ________  __      __        __    __  __                      __
* |        \|  \    /  \      |  \  |  \|  \                    |  \
*  \$$$$$$$$ \$$\  /  $$      | $$\ | $$ \$$  _______   ______  | $$  ______
*    | $$     \$$\/  $$       | $$$\| $$|  \ /       \ /      \ | $$ |      \
*    | $$      \$$  $$        | $$$$\ $$| $$|  $$$$$$$|  $$$$$$\| $$  \$$$$$$\
*    | $$       \$$$$         | $$\$$ $$| $$| $$      | $$  | $$| $$ /      $$
*    | $$       | $$          | $$ \$$$$| $$| $$_____ | $$__/ $$| $$|  $$$$$$$
*    | $$       | $$          | $$  \$$$| $$ \$$     \ \$$    $$| $$ \$$    $$
*     \$$        \$$           \$$   \$$ \$$  \$$$$$$$  \$$$$$$  \$$  \$$$$$$$
*
 */



/*
 *      Since the Safety Pig was appreciated last time,
 *      I thought I'd keep up my tradition and provide you with a Sanity Rabbit this time.
 *      I hope my code doesn't make you cry nearly as much this time.
 *      I tried to take on your comments on my style from the last assignment.
 *
 *      Anyways below is Sanity Rabbit. I hope he treats you well.
 *               ,
 *              /|      __
 *             / |   ,-~ /
 *            Y :|  //  /
 *            | jj /( .^
 *            >-"~"-v"
 *           /       Y
 *          jo  o    |
 *         ( ~T~     j
 *          >._-' _./
 *         /   "~"  |
 *        Y     _,  |
 *       /| ;-"~ _  l
 *      / l/ ,-"~    \
 *      \//\/      .- \
 *       Y        /    Y
 *       l       I     !
 *       ]\      _\    /"\
 *      (" ~----( ~   Y.  )
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~
 */



// Look! I put the C libs before my headers!!
#include <stdlib.h>
#include <stdbool.h>
#include "jjbot.h"
#include "world.h"
#include "handy.h"
#include "debugger.h"

/*
 * Name my bot.
 * FYI: Gwendolyn is a Rick and Morty reference.
 * http://rickandmorty.wikia.com/wiki/Gwendolyn
 */
char *get_bot_name(void) {
    return "Gwendolyn"; // Plumpess
}

/*
 * My remarkably short get_action function.
 * This is the brains for Gwendolyn.
 *
 * Works by getting the best pair for the turn:
 * If it is NULL, get the action struct for NULL pair
 * If it has a value, check the current location type and get the appropriate action struct from them.
 *
 * Then check if the bot needs to refuel based on the action it plans to take.
 * If it does need to, overwrite the previously decided action with an action for refuelling.
 * That is, unless the nearest_fuel is NULL, then just do as it was going to do, and let the bot run out of fuel.
 *
 * Finally, assign the action struct values to the action and n pointers in the argument of the function.
 * Print out the target destination if one exists.
 * Free the action struct.
 * Free the location pair struct.
 *
 * End of function no memory leaks.
 */
void get_action(struct bot *b, int *action, int *n) {
    int current_type = b->location->type;
    action_t an_action;
    location_pair_t pair = get_pair_for_action(b);
    
    // If there aren't any good pairs, don't do anything, just stay put.
    if (pair == NULL) {
        an_action = at_null_pair_action(b);
    } else {
        switch (current_type) {
            case LOCATION_SELLER:
                an_action = at_seller_action(b, pair);
                break;
            case LOCATION_BUYER:
                an_action = at_buyer_action(b, pair);
                break;
            case LOCATION_PETROL_STATION:
                an_action = at_petrol_action(b, pair);
                break;
            default:
                an_action = create_default_move_action(b, pair);
                break;
        }
    }

    if (should_refuel(b, an_action)) {
	    location_t nearest_fuel = nearest_petrol_station(b->location, -1);
        if (nearest_fuel != NULL) {
            int distance = amount_move_to(b, nearest_fuel);
            free(an_action);
            an_action = create_action(ACTION_MOVE, distance, nearest_fuel);
        } else {
            throw_warning("SHOULD REFUEL but can't/won't: NULL nearest_fuel");
        }
    }

    *action = an_action->action;
    *n = an_action->n;
    print_target_destination(b, an_action->target);
    free(an_action);
    free(pair);
}
