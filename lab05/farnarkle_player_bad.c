// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// Mar 28 2017
//

#include <stdio.h>
#include "farnarkle.h"

#define kLastGuess previous_guesses[turn-1]
#define kLastFarnarkle farnarkles[turn-1]
#define kLastArkle arkles[turn-1]

// an automated farnarkle_player
// given all previous guesses and their farnarkles and arkle counts
// make a new guess
//
// inputs:
// turn - which turn this is
// previous_guesses contains the turn - 1 previous_guesses
// farnarkles[i] contains the number of farnarkles for previous_guess[i]
// arkles[i] contains the number of arkles for previous_guess[i]
//
// output:
// guess - the next guess
//
void farnarkle_player(	int turn, 
			int previous_guesses[MAX_TURNS][N_TILES], 
			int farnarkles[MAX_TURNS], 
			int arkles[MAX_TURNS], 
			int guess[N_TILES]) {
	
	


	int guess[N_TILES] = {};
	if (turn == 1) {
		// make initial guess
		create_random_tiles(&new_guess);		
	} else {
		guess = kLastGuess;

		// increment both numbers in pair
		// evaluate if result is better or worse than before
		// if an arkle disappears, we know that one of two numbers in the previous turn exists elsewhere in the set
		// if an farnarkle disappears, we know that one of two numbers in the previous turn exists elsewhere in the set
		// if an arkle appears, increment the first
		// 	if it stays increment move to 
		// if there is no change, increment both again

		// check if the last two numbers are the same or different
		// if different then work on the last pair

			

	} 
}

int nthPair(const int cTurn, int last[N_TILES], int prev[MAX_TURNS][N_TILES]) {
	int turn = cTurn;
	int original = prev[0];
	while (turn > 0) {
		int counter = 0;
		int tturn = prev[turn];
		while (counter < N_TILES) {
			int inv = N_TILES - counter - 1;
			
			int o1 = original[inv-1];
			int o2 = original[inv];
			int t1 = tturn[inv-1];
			int t2 = tturn[inv];
			
			if (!(o1 == t1 && o2 == t2)) {
				return (inv - 1) / 2;		
			}
			
			counter += 2;
		}
		turn--;
	}
	return 0;
}






