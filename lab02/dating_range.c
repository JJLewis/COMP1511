// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// 8 March 2017
// Takes an age as an int for input and outputs a recommended age range for dating, unless the age is below 15, whereby an empty range is generated

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
	
	printf("Enter your age: ");
	if (get_input(&input) == 0) {
		return 0;
	}
		
	int lower = input / 2 + 7;
	int upper = input + 2 * (input - lower);
	if (lower < input && upper > input) {
		printf("Your dating range is %d to %d years old.\n", lower, upper);
	} else {
		printf("You are too young to be dating.\n");
	}

	return 0;
}
