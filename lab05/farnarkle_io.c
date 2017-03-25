// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// Mar 25 2017
//

#include <stdio.h>
#include "farnarkle.h"

int get_input(const char *prompt, int *x) {
	printf("%s", prompt);
	if (scanf("%d", x) == 0) {
		printf("Value entered was not an integer.\n");
		return 0;
	}
	return 1;
}

// read N_TILES tiles into array tiles
// return 1 if successful, 0 otherwise
int read_tiles(int tiles[N_TILES]) {
	int counter = 0;
	while (counter < N_TILES) {
		int input;
		if(get_input("", &input)) {
			if (input > 0 && input <= MAX_TILE) {
				tiles[counter] = input;
			}
		} else {
			return 0;
		}
		counter++;
	}
	return 1;
}

// print tiles on a single line
void print_tiles(int tiles[N_TILES]) {
	int count = 0;
	while (count < N_TILES) {
		printf(" %d", tiles[count]);
		count++;
	}
}
