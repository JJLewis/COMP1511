#include <stdio.h>

#define MAXINPUT 1000

int main(int argc, char *argv[]) {
	int inputs[MAXINPUT] = {};
	int indivisible[MAXINPUT] = {};

	int numIn = 0;
	while (scanf("%d", &inputs[numIn]) != EOF) {
		numIn++;
	}
	
	int numInDiv = 0;
	int outer = 0;
	for (outer = 0; outer < numIn; outer++) {
		int inner = 0;
		int wasDivided = 0;
		for (inner = 0; inner < numIn; inner++) {
			if (outer != inner) {
				if (inputs[outer] % inputs[inner] == 0) {
					wasDivided = 1;
					break;
				}
			}
		}
		if (!wasDivided) {
			indivisible[numInDiv] = inputs[outer];
			numInDiv++;
		}
	}

	printf("Indivisible numbers:");
	int i = 0;
	for (i = 0; i < numInDiv; i++) {
		printf(" %d", indivisible[i]);
	}
	printf("\n");
	
	return 0;
}
