// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// 25 March 2017
//

#include <stdio.h>
#include "farnarkle.h"

int count_farnarkles(int seq1[N_TILES], int seq2[N_TILES]) {
	int counter = 0;
	int matches = 0;
	while (counter < N_TILES) {
		if (seq1[counter] == seq2[counter]) {
			matches++;
		}
		counter++;
	}
	return matches;
}

