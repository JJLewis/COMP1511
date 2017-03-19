// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// Mar 19 2017
// Reads an integer n from standard input. and prints an nxn pattern of asterisks and dashes in the shape of a chessboard.

#include <stdio.h>

int get_input(const char *prompt, int *x) {
	printf("%s", prompt);
	if (scanf("%d", x) == 0) {
		printf("Value entered was not an integer.\n");
		return 0;
	}
	return 1;
}

#define ODD_ROW (vert % 2 == 0)
#define ODD_COL (hor % 2 == 0)

int main () {
	int input;
	if (!get_input("Enter size: ", &input)) {
	       return 1;
	}

	int vert = 0;
	while (vert < input) {
		int hor = 0;
		while (hor < input) {
			if (ODD_ROW) {
				if (ODD_COL) {
					printf("-");
				} else {
					printf("*");
				}
			} else {
				if (ODD_COL) {
					printf("*");				
				} else {
					printf("-");
				}
			}
			hor++;
		}
		vert++;
		printf("\n");
	}

	return 0;
}
