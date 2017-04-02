// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// Mar 28 2017
//

#include <stdio.h>
#include "farnarkle.h"

int getInt() {
    int n, c;
    c = getchar();
    n = 0;
    while (c >= '0' && c <= '9') {
        n = 10 * n + (c - '0');
        c = getchar();
    }
    return n;
}

// read N_TILES tiles into array tiles
// return 1 if successful, 0 otherwise
int read_tiles(int tiles[N_TILES]) {
	int counter = 0;
    int input = getInt();
	while (input != 0 && counter < N_TILES) {
        if (input > 0 && input <= MAX_TILE) {
            tiles[counter] = input;
        } else {
            return 0;
        }
        if (counter + 1 != N_TILES) {
            input = getInt();
        }
        counter++;
    }

    if (counter < N_TILES) {
        return 0;
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
