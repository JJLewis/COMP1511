// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// May 09 2017
//

#include <stdio.h>
#include <stdbool.h>
#include "trader_bot.h"

void print_world(struct bot *b) {

	struct location *head = b->location;
	struct location *loc = head;
	bool hasStarted = false;
	
	while (!(loc == head && hasStarted)) {
		hasStarted = true;

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
			sprintf(output, "will %s %i units of %s for $%i", type == LOCATION_BUYER ? "buy":"sell", loc->quantity, loc->commodity->name, loc->price);
		}
		
		printf("%s: %s\n", name, output);
		loc = loc->next;
	}
}
