// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// 8 March 2017
// Prints out the english for an integer entered by the user

#include <stdio.h>

int get_input(int *x) {
	if (scanf("%d", x) == 0) {
		printf("Value entered was not a number.\n");
		return 0;
	}
	return 1;
}

int main() {
	int input;
	
	printf("Please enter an integer: ");
	if (get_input(&input) == 0) {
		return 0;	 	
	}
	
	if (input < 1) {
		printf("You entered a number less than one.\n");
	} else if (input > 5) {
		printf("You entered a number greater than five.\n");
	} else {
		char eng[5][6] = {"one", "two", "three", "four", "five"};
		printf("You entered %s.\n", eng[input - 1]);
	}
	return 0;
}
