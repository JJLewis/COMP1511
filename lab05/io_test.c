// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// 25 March 2017
//

#include <stdio.h>
#include "farnarkle.h"

int main(void) {
	int tiles[N_TILES]; 
	printf("Enter sequence: ");
	if (read_tiles(tiles) == 1) {
		printf("Sequence read was: ");
		print_tiles(tiles);
		printf("\n");
	} else {
		printf("Could not read tiles\n");
	}   
}
