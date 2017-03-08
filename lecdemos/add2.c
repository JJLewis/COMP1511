// Add two numbers
// Jordan Lewis
// March 2017

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv)
{
	int x, y, sum;
	char *error_msg = "Not a number; giving up\n";
	char *thx = "Thanks for doing the right thing\n";
	// get two numbers
	printf("Gimme the first number: ");
	if (scanf("%d", &x) == 0) {
		printf(error_msg);
		return 1;
	} else {
		printf(thx);
	}

	printf("Second number: ");
	if (scanf("%d", &y) == 0) {
		printf(error_msg);
		return 1;
	} else {
		printf(thx);
	}

	// add numbers together
	sum = x + y;
	// print sum
	printf("Sum = %d\n", sum);
	return 0;
}
