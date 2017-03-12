// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// March 12 2017
// Reads an positive integer n and then prints the cubes of the integers from 1 to n

#include <stdio.h>
#include <math.h>

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
	if (get_input("Sum how many cubes? ", &num) == 0) {
		return 1;
	}

	int sum = 0;
	for (int i = 1; i <= num; i++) {
		int cube = (int)pow((double)i,3);
		sum += cube;
		printf("%d^3", i);
		if (i != num) {
			printf(" + ");
		}
	}
	printf(" = %d\n", sum);

	return 0;
}
