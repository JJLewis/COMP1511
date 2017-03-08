// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// 8 March 2017
// Takes 3 inputs for width, height, and length to calculate values of a rectangular prism.

#include <stdio.h>

#define PREFIX "Please enter prism"

void println(char *str) {
	printf("%s\n", str);
}

int get_input(int *x) {
	if (scanf("%d", x) == 0) {
		println("Value entered was not a number.");
		return 0;
	}
	return 1;
}

void do_math(int l, int w, int h) {
	printf("A prism with sides %d %d %d has: \n", l, w, h);
	int v = l * w * h;
	int sa = 2 * (l*w + w*h + l*h);
	int el = 4 * (l+w+h);
	printf("Volume = %d\n", v);
	printf("Area = %d\n", sa);
	printf("Edge Length = %d\n", el);
}


int main() {
	int l, w, h;
	
	printf("%s length: ", PREFIX);
	if (get_input(&l) == 0) {
		return 0;	 	
	}
	printf("%s width: ", PREFIX);
	if (get_input(&w) == 0) {
		return 0;	 	
	}
	printf("%s height: ", PREFIX);
	if (get_input(&h) == 0) {
		return 0;	 	
	}
	
	do_math(l,w,h);	
	
	return 0;
}
