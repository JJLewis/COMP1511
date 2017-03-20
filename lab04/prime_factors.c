// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// Mar 20 2017
// Reads a integer n from standard input and prints the decomposition of n into prime factors. If n is prime it instead should print a message indicating this. 

#include <stdio.h>
#include <math.h>

int get_input(const char *prompt, int *x) {
	printf("%s", prompt);
	if (scanf("%d", x) == 0) {
		printf("Value entered was not an integer.\n");
		return 0;
	}
	return 1;
}

int is_prime(int x) {
	// For a number to be prime, check if divisible by all ints upto the sqrt of the number
	const int xsqrt = sqrt(x);
	int counter = 2;
	while (counter <= xsqrt) {
		if (x % counter == 0) {
			return 0;
		}
		counter++;
	}
	return 1;
}	

void next_prime_factor(int x) {

	if (is_prime(x)) {
		printf("%d", x);
		return;
	}

	const int xsqrt = sqrt(x);
	int counter = 2;
	while (counter <= xsqrt) {
		if (x % counter == 0) {
			printf("%d", counter);
			if (!is_prime(x)) {
				printf(" * ");
			}
			next_prime_factor(x / counter);
			break;
		}
		counter++;
	}
}

int main () {
	int input;
	if (!get_input("Enter number: ", &input)) {
	       return 1;
	}
	
	if (is_prime(input)) {
		printf("%d is prime\n", input);
	} else {
		printf("The prime factorization of %d is:\n", input);
		next_prime_factor(input);
		printf(" = %d\n", input);
	}	
		
	return 0;
}
