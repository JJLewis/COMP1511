// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// Mar 22 2017
// Reads an integer n from standard input. and prints an nxn pattern of asterisks and dashes in the shape of a spiral.

#include <stdio.h>
#include <math.h>

int get_input(const char *prompt, int *x) {
	printf("%s", prompt);
	if (scanf("%d", x) == 0) {
		printf("Value entered was not an integer.\n");
		return 0;
	}
	return 1;
}

int should_print_star (int x, int y, int size, int debug, int sum) {
	int counter = 0;
	const int lim = size * size;
	int adjsize = size;
	int direction = 0; // 0 left, 1 down, 2 right, 3 up
	int posx = 0;
	int posy = 0;
	int numTurns = 0;	
	int length = 1;
	int overallLength = 1;

	while (counter <= lim) {

		if (posx == x && posy == y) {
			if (sum == -1) {
				return 1;
			} else {
				int remainder = sum % 10;
				int returnv = remainder - overallLength;
				int finalReturn = 10 + returnv;

				if (finalReturn < 0) {
					int diff = (finalReturn / -10) + 1;
					finalReturn += 10 * diff;
				}

				if (finalReturn >= 10) {
					int diff = (finalReturn / 10);
					finalReturn -= 10 * diff;
				}

				return finalReturn;
			}		
		}

		if (direction == 0) {posx += 1;}
		if (direction == 1) {posy += 1;}
		if (direction == 2) {posx -= 1;}
		if (direction == 3) {posy -= 1;}

		length++;
		overallLength++;

		if (length == adjsize) {

			direction++;
			if (direction == 4) { direction = 0; }

			numTurns += 1;

			length = 1;
			if (adjsize == 3) {
				length = 0;
			}

			if (numTurns != 1 && (numTurns - 1) % 2 == 0) {
				adjsize -= 2;
				if (adjsize < 3) {
					break;
				}
			}

		}

		counter++;		
	}
	return -1;
}

int print_loop(int input, int sum, int debug) {
	int vert = 0;
	int returnSum = 0;
	while (vert < input) {
		int hor = 0;
		while (hor < input) {
			int returned = should_print_star(hor, vert, input, debug, sum);
			if (returned != -1) {		
				if (!debug && sum != -1) {
					printf("%d", returned);
				}
				returnSum++;
			} else {
				if (!debug && sum != -1) {
					printf("-");
				}
			}
			hor++;
		}
		if (!debug && sum != -1) {
			printf("\n");
		}
		vert++;
	}
	return returnSum;
}

void run_print_loop(int input, int debug) {
	int sum = print_loop(input, -1, debug);
	print_loop(input, sum, debug);
}

int main () {
	int input = 7;
	
	if (!get_input("Enter size: ", &input)) {
	       return 1;
	}
	
	run_print_loop(input, 0);
	//run_print_loop(input, 1);

	return 0;
}
