// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// 8 March 2017
// Take the side lengths of a triangle to calculate it's area

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PREFIX "Enter side"

void println(char *str) {
	printf("%s\n", str);
}

double get_input(double *x) {
	if (scanf("%lf", x) == 0) {
		println("Value entered was not a number.");
		return 0;
	}
	return 1;
}

double heron_formula(double a, double b, double c) {
	return (a + b + c)/2;
}

void do_math(double a, double b, double c) {
	double s = heron_formula(a,b,c);
	double area = sqrt(s*(s-a)*(s-b)*(s-c));
	
	// The area formula will produce -nan if the triange inequality is violated
	// Thus checking if the area is > 0 is enough
	if (area > 0) {
		printf("Area = %lf\n", area);
	} else {
		println("Error: triangle inequality violated.");
	}
}


int main() {
	double a,b,c;
	
	printf("%s 1: ", PREFIX);
	if (get_input(&a) == 0) {
		return 0;	 	
	}
	printf("%s 2: ", PREFIX);
	if (get_input(&b) == 0) {
		return 0;	 	
	}
	printf("%s 3: ", PREFIX);
	if (get_input(&c) == 0) {
		return 0;	 	
	}
	
	do_math(a,b,c);	
	
	return 0;
}
