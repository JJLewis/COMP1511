// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// May 09 2017
//

#include <stdio.h>
#include <stdbool.h>
#include "trader_bot.h"

int nearest_fuel(struct bot *b) {
	int forwardSteps = 0;
	int backwardSteps = 0;
	
	struct location *loc = b->location;

	while (loc->type != LOCATION_PETROL_STATION) {
		forwardSteps++;	
		loc = loc->next;
	}

	loc = b->location;

	while (loc->type != LOCATION_PETROL_STATION) {
		backwardSteps++;
		loc = loc->previous;
	}

	if (forwardSteps <= backwardSteps) {
		return forwardSteps;
	} else {
		return -backwardSteps;
	}
}
