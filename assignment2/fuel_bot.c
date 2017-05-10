// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// May 09 2017
//

#include <stdio.h>
#include <stdbool.h>
#include "trader_bot.h"

void get_action(struct bot *bot, int *action, int *n) {
	
	struct location *loc = bot->location;

	if (loc->type == LOCATION_PETROL_STATION) {
		if (bot->fuel < bot->fuel_tank_capacity) {
			*action = ACTION_BUY;
			*n = bot->fuel_tank_capacity - bot->fuel;
			return;
		} else {
			*action = ACTION_MOVE;
			*n = bot->maximum_move;
		}
	} else {
		*action = ACTION_MOVE;
		int distToFuel = nearest_fuel(bot);
		*n = distToFuel;
		if (distToFuel > bot->maximum_move) {
			*n = bot->maximum_move;
		}
	}
}
