// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// 25 March 2017
//

#include <stdio.h>
#include "farnarkle.h"

int main(void) {
	int hidden_seq[N_TILES];

	create_random_tiles(hidden_seq);

	int score = 1;
	int nF = 0;
	while (nF < N_TILES) {
		int guess[N_TILES];
		printf("Enter guess for turn %d: ", score);
		read_tiles(guess);
		nF = count_farnarkles(hidden_seq, guess);
		printf("%d farnarkles %d arkles\n", nF, count_arkles(hidden_seq, guess));
		score++;
	}
	printf("You win\n");

	return 0;
}
