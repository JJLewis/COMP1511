// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// March 13 2017
// Reads 3 integers and prints them from smallest to largest

#include <stdio.h>

#define PROMPT "Enter integer: "

int main () {
	
	int x,y,z;
	printf(PROMPT);
	scanf("%d", &x);
	printf(PROMPT);
	scanf("%d", &y);
	printf(PROMPT);
	scanf("%d", &z);

	// Making use of the fact that booleans in C are simply 0/1 integers to insert the right numbers into the correct positions in an array, then to read them back in order.	
	int arr[3] = {};
	arr[(x>=y) + (x>=z)] = x;
	arr[(y>=x) + (y>=z)] = y;
	arr[(z>=x) + (z>=y)] = z;


	printf("The integers in order are: %d %d %d\n", arr[0], arr[1], arr[2]);

	return 0;
}
