// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// 25 March 2017
//

#include <stdio.h>
#include "farnarkle.h"

int int_exists(int num, int arr[N_TILES]) {
	int i = 0;
	while (i < N_TILES) {
		if (num == arr[i]) {
			return 1;
		}
		i++;
	}
	return 0;
}

void array_with_equal_elements(int num, int arr[N_TILES]) {
	int i = 0;
	while (i < N_TILES) {
		arr[i] = num;
		i++;
	}
}

// return number of arkles
int count_arkles(int seq1[N_TILES], int seq2[N_TILES]) {
	int i = 0;
	int matches = 0;
	int foundAt[N_TILES] = {};
	array_with_equal_elements(-1, foundAt);
	while (i < N_TILES) {
		int j = 0;
		while (j < N_TILES) {
			if (seq1[i] == seq2[j] && !int_exists(j, foundAt)) {
				if (seq1[i] != seq2[i] && seq1[j] != seq2[j]) {
					foundAt[i] = j;
					matches++;
					break;
				}
			}
			j++;
		}
		i++;
	}

	return matches;
}
