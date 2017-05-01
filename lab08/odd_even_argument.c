#include <stdio.h>
#include <stdlib.h>

#define MAXINPUT 1000

int main(int argc, char *argv[]) {
	int inputs[MAXINPUT] = {};
	
	int i = 0;
	for (i = 1; i < argc; i++) {
		inputs[i - 1] = atoi(argv[i]);
	}

	printf("Odd numbers were:");
	i = 0;
	for (i = 0; i < argc - 1; i++) {
		if (inputs[i] % 2 != 0) {
			printf(" %d", inputs[i]);
		}
	}
	printf("\n");
	printf("Even numbers were:");
	i = 0;
	for (i = 0; i < argc - 1; i++) {
		if (inputs[i] % 2 == 0) {
			printf(" %d", inputs[i]);
		}
	}
	printf("\n");	
	return 0;
}
