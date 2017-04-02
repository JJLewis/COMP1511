// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// Mar 28 2017
//

#include <stdio.h>
#include "farnarkle.h"

// read N_TILES tiles into array tiles
// return 1 if successful, 0 otherwise
int read_tiles(int tiles[N_TILES]) {
	int counter = 0;
	while (counter < N_TILES) {
		int input;
		if(scanf("%d", &input) == 0) {
			return 0;
		} else {
			if (input > 0 && input <= MAX_TILE) {
				tiles[counter] = input;
			}
		}
		counter++;
	}
	return 1;
}

// print tiles on a single line
void print_tiles(int tiles[N_TILES]) {
	int count = 0;
	while (count < N_TILES) {
		if (count != 0) { printf(" "); }
		printf("%d", tiles[count]);	
		count++;
		if (count == N_TILES) { printf("\n"); }
	}
}
