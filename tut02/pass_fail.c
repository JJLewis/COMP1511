// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// 8 March 2017
// Determine if you passed or failed

#include <stdio.h>

void println(char *str) {
	printf("%s\n");
}

#define ERROR "ERROR"

int main (void) {
	int mark;
	
	printf("Please enter your mark: ");
	scanf("%d", &mark);
	
	if (mark < 0 || mark > 100) {
		println(ERROR);
	} else if (mark < 50) {
		println("FAIL");
	} else if (mark < 100) {
		print;n("PASS");
	}
	
	return 0;
}
