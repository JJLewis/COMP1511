// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// 8 March 2017
// Calculates the area of a rectangle

#include <stdio.h>

int main (void) {
	double length, width;
	
	printf("Please enter rectangle length: ");
	scanf("%lf", &length);
	
	printf("Please enter rectangle width: ");
	scanf("%lf", &width);	
	
	double area = length * width;
	printf("Area = %lf\n", area);

	return 0;
}
