// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// March 15 2017
// Prints out multiples of 10 between two numbers

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
	int start, end;
	
	get_input("Enter start: ", &start);
	get_input("Enter end: ", &end);

	int counter = start;
	while (counter < end) {
		if (counter % 10 == 0) {
			printf("%d\n", counter);
		}
		counter++;
	}

	return 0;
}
