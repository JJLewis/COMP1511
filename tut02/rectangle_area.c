// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// 8 March 2017
// Calculates the area of a rectangle

#include <stdio.h>

int main (void) {
	int length, width;
	
	printf("Please enter rectangle length: ");
	scanf("%d", &length);
	
	printf("Please enter rectangle width: ");
	scanf("%d", &width);	
	
	int area = length * width;
	printf("Area = %d\n", area);

	return 0;
}
