// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// March XX 2017
//

#include <stdio.h>

int get_input(const char *prompt, int *x) {
	printf("%s", prompt);
	if (scanf("%d", x) == 0) {
		printf("Value entered was not an integer.\n");
		return 0;
	}
	return 1;
}

int main () {
	int input;
	if (!get_input(": ", &input)) {
	       return 1;
	}

		

	return 0;
}
