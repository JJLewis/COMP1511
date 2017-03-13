// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// March 12 2017
// Accepts 3 integers and prints it out in order

#include <stdio.h>

#define PROMPT "Enter Integer: "

int get_input(char *prompt, int *x) {
	printf(prompt);
	if (scanf("%d", x) == 0) {
		printf("Value entered was not an integer.\n");
		return 0;
	}
	return 1;
}

void swap2(int *x, int *y) {
	int *temp = *x;
	*x = *y;
	*y = temp;
}

void sort(int *x, int *y, int *z) {
	// Mini Bubble Sort	
	if (*x > *y) { swap2(x, y); }
	if (*y > *z) { swap2(y, z); }
	if (*x > *y) { swap2(x, y); }
}

int main () {
	int x,y,z;
	get_input(PROMPT, &x);
	get_input(PROMPT, &y);
	get_input(PROMPT, &z);

	sort(&x, &y, &z);

	printf("The integers in order are: %d %d %d\n", x, y, z);

	return 0;
}
