// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// May 16 2017
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

double grade2labmark(char grade, bool isPlus) {
	if (grade == 'A') {
		if (isPlus) {
			return 1.2;
		}
		return 1;
	}
	if (grade == 'B') {
		return 0.8;
	}
	if (grade == 'C') {
		return 0.5;
	}
	if (grade == '.') {
		return 0;
	}
	return 0;
}

double grades2labmark(char grades[]) {
	double sum = 0;
	int index = strlen(grades) - 1;
	int num_grades = 0;
	while (index >= 0) {
		if (grades[index] == '+') {
			index--;
			sum += grade2labmark(grades[index], true);
		} else {
			sum += grade2labmark(grades[index], false);
		}
		index--;
		num_grades++;
	}
	
	if (sum > 10) {
		return 10;
	}
	return sum;
}


int main (int argc, char* argv[]) {
	
	if (argc < 2) {
		exit(EXIT_FAILURE);
	}

	printf("%.1f\n", grades2labmark(argv[1]));

	return 0;
}
