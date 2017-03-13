// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// March 13 2017
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

	// If X is the largest
	if (x > y && x > z) {
		o1 = x;
		// Now if Y is greater than Z, then Y must be in the middle and Z be the smallest
		if (y > z) {
			o2 = y;
			o3 = z;
		}
		// Refer to the above, but now test if Y is the largest
	} else if (y > x && y > z) {
		o1 = y;
		// Again, find the 2nd & 3rd numbers like the above comment
		if (x > z) {
			o2 = x;
			o3 = z;
		}
		// Same again but for Z
	} else if (z > x && z > y) {
		o1 = z;
		// Again, find the 2nd & 3rd numbers like the above comment
		if (x > y) {
			o2 = x;
			o3 = y;
		}
	}

	printf("The integers in order are: %d %d %d\n", o1, o2, o3);

	return 0;
}
