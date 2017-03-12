// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// March 12 2017
// Takes a range of  years as input and prints all leap years in that range  

#include <stdio.h>
#include <stdlib.h>

int get_input(char *prompt, int *x) {
	printf("%s", prompt);
	if (scanf("%d", x) == 0) {
		printf("Value entered was not an integer.\n");
		return 0;
	}
	return 1;
}

int is_leap(int year) {
	int is_div_4 = year % 4 == 0;
	int is_div_100 = year % 100 == 0;
	int is_div_400 = year % 400 == 0;
	
	// A year is a leap year if evenly divisble by 4 and not 100, unless also evenly divisble by 400
	if ((is_div_4 && !is_div_100) || (is_div_100 && is_div_400)) {
		return 1;
	} else {
		return 0;
	}
}

int main () {
	
	int start, end;
	if (get_input("Enter start year: ", &start) == 0) {
		return 1;
	}

	if (get_input("Enter finish year: ", &end) == 0) {
		return 1;
	}

	int incr = 1;
	int count = start;
	printf("The leap years between %d and %d are: ", start, end);
	while (count <= end) {
		if (is_leap(count)) {
			printf("%d ", count);			
		}
		count += incr;
	}
	printf("\n");
	

	return 0;
}
