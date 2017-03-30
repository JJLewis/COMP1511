// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// Mar 29 2017
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
		guess = {0};
	} else {
		guess = kLastGuess;
		// the first not locked number is the one being incremented
		int notLocked[N_TILES];
		findNotLockedIndexes(turn, previous_guesses, farnarkles, arkles, notLocked);
		const int fNLocked = notLocked[adjustedIndexForBlanks(0, notLocked)];
		
		if (lenWithoutBlanks(notLocked) > 1) { 
			// If an arkle is found test it against others
			if (kLastArkle > arkles[turn-2]) {
				// find second non-zero value that isn't locked
				// if there is one, set it back to zero and move copy that value to the next one
				// if there isn't one, copy the first non-zero to the first zero that is not locked
				int counter = 1;
				int index = adjustedIndexForBlanks(counter, notLocked);
				while (guess[notLocked[index]] == 0) {
					counter++;
					index = adjustedIndexForBlanks(counter, notLocked);
				}
				const int sNLocked = notLocked[index];
				
				counter = sNLocked;
				index =  

				guess[sNLocked] = 0;

			} else {
				// Otherwise, keep incrementing
				guess[fNLocked] += guess[fNLocked];
			}
		}
	} 
}

#define BLANK -1
int lenWithoutBlanks(int arr[N_TILES]) {
	int counter = 0;
	int sum = 0;
	while (counter < N_TILES) {
		if (arr[counter] != BLANK) {
			sum++;
		}
		counter++;
	}
}

int adjustedIndexForBlanks(int index, int arr[N_TILES]) {
	int aIndex = index;
	while (arr[aIndex] == BLANK) {
		aIndex++;
	}
	return aIndex;
}

void fillArraySequentially(int from, int arr[N_TILES]) {
	int start = from;
	int end = start + N_TILES;
	while (start < end) {
		arr[start] = start;
		start++;
	}
}

int indexOf(int item, int arr[N_TILES]) {
	int i = 0;
	while (i < N_TILES) {
		if (item == arr[i]) {
			return i;
		}
		i++;
	}
	return -1;
}

void findNotLockedIndexes(	int turn,
				int prev[MAX_TURNS][N_TILES], 
				int farnarkles[MAX_TURNS], 
				int arkles[MAX_TURNS], 
				int notLocked[N_TILES]) {
	int cturn = 0;
	notLocked = {};
	fillArraySequentially(0, notLocked);
	while (cturn < turn) {
		if (cturn > 0) {
			int newFarnarkle = farnarkles[cturn] > farnarkles[cturn - 1];
			if (newFarnarkle) {
				int counter = 1;
				while (arkles[cTurn - counter] == 1) {
					counter++;
				}
				notLocked[indexOf(counter)] = -1;
			}
		} else {
			if (farnarkles[cturn] == 1) {
				notLocked[0] = -1;
			}
		}
	}
}
