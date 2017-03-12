// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// March 12 2017
//

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

	return 0;
}
