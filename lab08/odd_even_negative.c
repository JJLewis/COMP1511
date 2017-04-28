#include <stdio.h>

#define MAXINPUT 1000

int main(int argc, char *argv[]) {
	int inputs[MAXINPUT] = {};
	
	int numIn = 0;
	int in;
	scanf("%d", &in);
	while (in > 0) {
		inputs[numIn] = in;
		numIn++;
		scanf("%d", &in);
	}

	printf("Odd numbers were:");
	int i = 0;
	for (i = 0; i < numIn; i++) {
		if (inputs[i] % 2 != 0) {
			printf(" %d", inputs[i]);
		}
	}
	printf("\n");
	printf("Even numbers were:");
	i = 0;
	for (i = 0; i < numIn; i++) {
		if (inputs[i] % 2 == 0) {
			printf(" %d", inputs[i]);
		}
	}
	printf("\n");	
	return 0;
}
