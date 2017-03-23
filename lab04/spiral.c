// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// Mar 22 2017
// Reads an integer n from standard input. and prints an nxn pattern of asterisks and dashes in the shape of a spiral.

#include <stdio.h>

int get_input(const char *prompt, int *x) {
	printf("%s", prompt);
	if (scanf("%d", x) == 0) {
		printf("Value entered was not an integer.\n");
		return 0;
	}
	return 1;
}

int should_print_star (int x, int y, int size) {
	int counter = 0;
	const int lim = size * size;
	int adjsize = size;
	int direction = 0; // 0 left, 1 down, 2 right, 3 up
	int posx = 0;
	int posy = 0;
	int numTurns = 0;	
	int length = 1;

	while (counter <= lim) {

		if (posx == x && posy == y) {
			return 1;
		}

		if (direction == 0) {posx += 1;}
		if (direction == 1) {posy += 1;}
		if (direction == 2) {posx -= 1;}
		if (direction == 3) {posy -= 1;}

		length++;

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
	return 0;
}

void run_print_loop(int input) {
	int vert = 0;
	while (vert < input) {
		int hor = 0;
		while (hor < input) {
			if (should_print_star(hor, vert, input)) {
					printf("*");
			} else {
					printf("-");
			}
			hor++;
		}
		printf("\n");
		vert++;
	}
}

int main () {
	int input;

	if (!get_input("Enter size: ", &input)) {
	       return 1;
	}
	
	run_print_loop(input);

	return 0;
}
