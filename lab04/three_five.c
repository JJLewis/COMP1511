// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// March 18 2017
// Reads a positive integer n and print all the positive integers < n divisible by 3 or 5.

#include <stdio.h>

int get_input(const char *prompt, int *x) {
	printf("%s", prompt);
	if (scanf("%d", x) == 0) {
		printf("Value entered was not an integer.\n");
		return 0;
	}
	return 1;
}

#define DIV3 (counter % 3 == 0)
#define DIV5 (counter % 5 == 0)

int main () {
	
	int input;
	get_input("Enter number: ", &input);

	int counter = 1;
	while (counter < input) {
		if (DIV3 || DIV5) {
			printf("%d\n", counter);
		}
		counter++;
	}

	return 0;
}
