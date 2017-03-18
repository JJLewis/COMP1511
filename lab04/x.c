// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// March 18 2017
// Reads an integer n from standard input. and prints an nxn pattern of asterisks and dashes in the shape of an "X".

#include <stdio.h>

int get_input(char *prompt, int *x) {
	printf("%s", prompt);
	if (scanf("%d", x) == 0) {
		printf("Value entered was not an integer.\n");
		return 0;
	}
	return 1;
}

int main () {
	int input;
	get_input("Enter size: ", &input);
	
	// Assuming n >= 5 and ODD
	
	int vert = 0;
	int depth = 0;
	while (vert < input) {
		int hor = 0;
		while (hor < input) {
			if ((hor == depth) || ((input - hor - 1) == depth)) {
				printf("*");
			} else {
				printf("-");
			}
			hor++;
		}
		printf("\n");
		if ((input - (vert + 1)) > (input / 2)) {
			depth++;
		} else {
			depth--;
		}
		vert++;
	}


	return 0;
}
