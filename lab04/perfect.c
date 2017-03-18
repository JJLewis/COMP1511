// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// March 18 2017
// Reads a positive integer n from standard input and prints all the factors of n, their sum and if indicates if n is a perfect number.

#include <stdio.h>
#include <math.h>
#include <strings.h>

int main () {
	
	int input;
	printf("Enter number: ");
	scanf("%d", &input);
	
	printf("The factors of %d are:\n", input);

	int sum = 0;
	int count = 1;
	while (count <= input) {
		if (input % count == 0) {
			sum += count;
			printf("%d\n", count);
		}
		count++;
	}
	printf("Sum of factors = %d\n", sum);
	
	printf("%d is%s a perfect number\n", input, (sum %  input == 0) ? "":" not");

	return 0;
}
