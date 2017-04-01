#include <stdio.h>
#include "farnarkle.h"

int main(void) {
	
	int hidden[N_TILES];
	create_random_tiles(hidden);

	int turn = 1;
	int numFarnarkles = 0;
	
	int aGuess[N_TILES] = {0};
	int farnarkleHistory[MAX_TURNS] = {0};
	int arkleHistory[MAX_TURNS] = {0};
	int guessHistory[MAX_TURNS][N_TILES] = {{0}};
	
	while (numFarnarkles < N_TILES) {
		
		farnarkle_player(turn, guessHistory, farnarkleHistory, arkleHistory, aGuess);
		
		numFarnarkles = count_farnarkles(hidden, aGuess);
		farnarkleHistory[turn - 1] = numFarnarkles;
		arkleHistory[turn - 1] = count_arkles(hidden, aGuess);
	
		int counter = 0;
		while (counter < N_TILES) {
			guessHistory[turn - 1][counter] = aGuess[counter];
			counter++;
		}		

		turn++;


		printf("----------\n");
		print_tiles(hidden);
		print_tiles(aGuess);
	}

	return 0;
}
