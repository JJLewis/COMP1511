// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// Apr 01 2017
//

#include <stdio.h>
#include "farnarkle.h"

#define kLastGuess previous_guesses[turn-1]
#define kLastFarnarkle farnarkles[turn-1]
#define kLastArkle arkles[turn-1]
#define kCurrentFarnarkle farnarkles[turn]
#define kCurrentArkle arkles[turn]

int indexOfNext0After(int after, int arr[N_TILES]) {
	int counter = after + 1;
	while (counter < N_TILES) {
		if (arr[counter] == 0) {
			return counter;
		}
		counter++;
	}
	return -1;
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
	return sum;
}

int adjustedIndexForBlanks(int index, int arr[N_TILES]) {
	int aIndex = index;
	while (arr[aIndex] == BLANK) {
		aIndex++;
	}
	return aIndex;
}


// finds the index of the second not locked number in the array that is the next guess
int find_nthNotLocked(int n, int guess[N_TILES], int notLocked[N_TILES]) {
	int counter = n - 1;
	int index = adjustedIndexForBlanks(counter, notLocked);
	while (guess[notLocked[index]] == 0) {
		counter++;
		index = adjustedIndexForBlanks(counter, notLocked);
	}
	return notLocked[index];
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


void fillArraySequentially(int from, int arr[N_TILES]) {
	int start = from;
	int end = start + N_TILES;
	while (start < end) {
		arr[start] = start;
		start++;
	}
}

void resetArrayValuesTo(int value, int arr[N_TILES]) {
	int counter = 0;
	while (counter < N_TILES) {
		arr[counter] = value;
		counter++;
	}
}

void findNotLockedIndexes(	int turn,
				int prev[MAX_TURNS][N_TILES], 
				int farnarkles[MAX_TURNS], 
				int arkles[MAX_TURNS], 
				int notLocked[N_TILES]) {
	int cturn = 0;
	resetArrayValuesTo(0, notLocked);
	fillArraySequentially(0, notLocked);
	while (cturn < turn) {
		if (cturn > 0) {
			int newFarnarkle = farnarkles[cturn] > farnarkles[cturn - 1];
			if (newFarnarkle) {
				int counter = 1;
				while (arkles[cturn - counter] == 1) {
					counter++;
				}
				notLocked[indexOf(counter, notLocked)] = -1;
			}
		} else {
			if (farnarkles[cturn] == 1) {
				notLocked[0] = -1;
			}
		}
		cturn++;
	}
}

void printInt(int a) {
	printf("%d\n", a);
}

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
	
	


	//int guess[N_TILES] = {};
	if (turn == 1) {
		// make initial guess
		resetArrayValuesTo(0, guess);	
	} else {
		guess = kLastGuess;
		// the first not locked number is the one being incremented
		int notLocked[N_TILES] = {0};
		findNotLockedIndexes(turn, previous_guesses, farnarkles, arkles, notLocked);
		const int fNLocked = notLocked[adjustedIndexForBlanks(0, notLocked)];
		// The first not locked index is the one being incremented
	
		// making sure that there is still more than one spot that needs filling	
		if (lenWithoutBlanks(notLocked) > 1) { 
			// If an arkle is found test it against others
			if (kLastArkle > arkles[turn-2]) {
				// find second non-zero value that isn't locked
				// if there is one, set it back to zero and move copy that value to the next one
				// if there isn't one, copy the first non-zero to the first zero that is not locked
				
				// this is the index of the second non-zero unlocked number in guess
				const int sNLocked = find_nthNotLocked(2, guess, notLocked);				
				// however, if a second non-zero doesn't exist it will return 2nd unlocked number
				
				// if it is 0, then search for the third, and fourth and so on, until the last one
				// if a non-zero is found, shift the copy of the value to the next zero
				// 	make sure to check for farnarkles
				// 	unless it is the last one and another zero could not be found, increment the fNLocked
				// if a non-zero is not found then check if the fNLocked was incremented, if not, increment it
				if (guess[sNLocked] == 0) {
					int counter = 3;
					while (find_nthNotLocked(counter, guess, notLocked) == 0 && counter < lenWithoutBlanks(notLocked)) {
						counter++;	
					}

					// if it got to the end and all were zeros
					if (!(counter < lenWithoutBlanks(notLocked))) {
						// check if the first was incremented in the previous guess
						// if move to the next
						int prevFirst = kLastGuess[fNLocked];
						if (prevFirst == guess[fNLocked]) {
							guess[fNLocked] = guess[fNLocked] + 1;
						} else {
							guess[sNLocked] = guess[fNLocked];
						}	
					} else {
						// a non-zero must've been found
						int index = notLocked[adjustedIndexForBlanks(counter - 1, notLocked)];
						// check if there has been an increase in farnarkles
						// 	if there has, copy but don't set the prev to 0
						// 	otherwise, copy and reset the prev
						int nIndex = indexOfNext0After(index, guess);
						if (nIndex == -1) {
							// if no more to copy to, increment the first
							guess[fNLocked] = guess[fNLocked] + 1;
						} else {
							guess[nIndex] = guess[fNLocked];
						}
						if (kLastFarnarkle == kCurrentFarnarkle) {
							// No change, can reset
							guess[index] = 0; // reset
						} else {
							// Has been a change, don't reset
							// lock this index
							// don't do anything
						}
					}
				} else {
					// if it isn't set 
					guess[sNLocked] = 0;
				}


			} else {
				// check if increase in farnarkle
				// if there is, actually dw
				//if (
				// Otherwise, keep incrementing as there are no more to shift to
				guess[fNLocked] = guess[fNLocked] + 1;
				//print_tiles(guess);
			}
		}
	}
}	



