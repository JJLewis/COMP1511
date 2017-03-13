// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// March 12 2017
// Accepts 3 integers and prints it out in order

#include <stdio.h>

int main () {
	int x,y,z;
	printf("Enter Integer: ");
	scanf("%d", &x);
	printf("Enter Integer: ");
	scanf("%d", &y);
	printf("Enter Integer: ");
	scanf("%d", &z);

	int o1,o2,o3;

	if (x > y && x > z) {
		o1 = x;
		if (y > z) {
			o2 = y;
			o3 = z;
		}
	} else if (y > x && y > z) {
		o1 = y;
		if (x > z) {
			o2 = x;
			o3 = z;
		}
	} else if (z > x && z > y) {
		o1 = z;
		if (x > y) {
			o2 = x;
			o3 = y;
		}
	}

	printf("The integers in order are: %d %d %d\n", o1, o2, o3);

	return 0;
}
