// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// Mar 18 2017
// Reads an integer n from standard input. and prints an nxn pattern of asterisks and dashes in the shape of an "+".

#include <stdio.h>

int get_input(const char *prompt, int *x) {
	printf("%s", prompt);
	if (scanf("%d", x) == 0) {
		printf("Value entered was not an integer.\n");
		return 0;
	}
	return 1;
}

#define VTARGET (input / 2 == vert)
#define HTARGET (input / 2 == hor)

int main () {
	int input;
	if (!get_input("Enter size: ", &input)) {
	       return 1;
	}

	int vert = 0;

	while (vert < input) {
		int hor = 0;
		while (hor < input) {
			if (VTARGET || HTARGET) {
				printf("*");
			} else {
				printf("-");
			}
			hor++;
		}
		printf("\n");
		vert++;
	}

	return 0;
}
