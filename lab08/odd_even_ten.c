#include <stdio.h>

int main(int argc, char *argv[]) {
	int inputs[10] = {};
	int i = 0;
	for (i = 0; i < 10; i++) {
		scanf("%d", &inputs[i]);
	}
	printf("Odd numbers were:");
	i = 0;
	for (i = 0; i < 10; i++) {
		if (inputs[i] % 2 != 0) {
			printf(" %d", inputs[i]);
		}
	}
	printf("\n");
	printf("Even numbers were:");
	i = 0;
	for (i = 0; i < 10; i++) {
		if (inputs[i] % 2 == 0) {
			printf(" %d", inputs[i]);
		}
	}
	printf("\n");	
	return 0;
}
