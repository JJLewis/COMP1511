// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// March 12 2017
// Reads an integer and prints a square of asterisks that size

#include <stdio.h>
//#include <math.h>

int get_input(char *prompt, int *x) {
	printf("%s", prompt);
	if (scanf("%d", x) == 0) {
		printf("Value entered was not an integer.\n");
		return 0;
	}
	return 1;
}

#define SQ size*size//(int)pow((double)size, 2)
#define DIVABLE (counter+1) % size == 0

int main () {
	
	int size;

	if (!get_input("Square size: ", &size)) {
	       return 1;
	}	       
	
	int counter = 0;
	while (counter < SQ) {
		printf("*");
		if (DIVABLE) {
			printf("\n");
		}
		counter++;
	}

	return 0;
}
