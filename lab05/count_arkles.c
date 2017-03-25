// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// 25 March 2017
//

#include <stdio.h>
#include "farnarkle.h"

// return number of arkles
int count_arkles(int seq1[N_TILES], int seq2[N_TILES]) {
	int i = 0;
	int matches = 0;
	while (i < N_TILES) {
		int j = 0;
		while (j < N_TILES) {
			if (seq1[i] == seq2[j] && i != j) {
				matches++;
			}
			j++;
		}
		i++;
	}
	return matches;
}
