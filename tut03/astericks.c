// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// March 15 2017
// Prints out the specified number of asterisks

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
	
	int num;
	get_input("Please enter an integer: ", &num);

	int counter = 0;
	while (counter < num) {
		printf("*\n");
		counter++;
	}

	return 0;
}
