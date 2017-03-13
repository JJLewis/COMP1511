// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// March 13 2017
// Reads 3 integers and prints them from smallest to largest

#include <stdio.h>

#define PROMPT "Enter integer: "
#define DEBUGGING 0

int main () {
	
	int x,y,z;
	printf(PROMPT);
	scanf("%d", &x);
	printf(PROMPT);
	scanf("%d", &y);
	printf(PROMPT);
	scanf("%d", &z);
		
	// Making use of the fact that booleans in C are simply 0/1 integers to i
	int arr[4] = {};
	arr[(x>y) + (x>z)] = x;
	arr[(y>x) + (y>z)] = y;
	arr[(z>x) + (z>y)] = z;

	// Correct problems with duplicate and triple entries
	arr[(arr[0] != 0) * 3] = arr[1];
	arr[((arr[1] != 0) * 3) + (arr[1] == 0)] = arr[0];
	arr[((arr[2] != 0) * 3) + (arr[2] == 0)*2] = arr[1];
	
	printf("The integers in order are: %d %d %d\n", arr[0], arr[1], arr[2]);
	
	return 0;
}
