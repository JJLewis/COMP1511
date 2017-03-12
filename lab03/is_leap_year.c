// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// March 12 2017
// Takes a year as input and prints whether or not it is a leap year

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
	
	int year;
	if (get_input("Enter Year: ", &year) == 0) {
		return 1;
	}

	int is_div_4 = year % 4 == 0;
	int is_div_100 = year % 100 == 0;
	int is_div_400 = year % 400 == 0;
	
	// A year is a leap year if evenly divisble by 4 and not 100, unless also evenly divisble by 400
	if ((is_div_4 && !is_div_100) || (is_div_100 && is_div_400)) {
		printf("%d is a leap year.\n", year);
	} else {
		printf("%d is not a leap year.\n" , year);
	}

	return 0;
}
