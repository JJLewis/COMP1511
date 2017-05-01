#include <stdio.h>

int main(int argc, char *argv[]) {
	int inputs[10] = {};
	int i = 0;
	for (i = 0; i < 10; i++) {
		scanf("%d", &inputs[i]);
	}
	printf("Numbers were:");
	i = 0;
	for (i = 0; i < 10; i++) {
		printf(" %d", inputs[10 - i - 1]);
	}
	printf("\n");
	return 0;
}
