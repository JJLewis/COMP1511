// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// March 13 2017
// Reads 3 integers and prints them from smallest to largest
// MISSION ACCOMPLISHED IN 2 INT VARS (^_^)

#include <stdio.h>

#define PROMPT "Enter integer: "
#define DEBUGGING 0

#define X inputs[0]
#define Y inputs[1]
#define Z inputs[2]

int main () {

	// Just replace x,y,z with int array and pass pointers to indexes	
	int inputs[3];
	printf(PROMPT);
	scanf("%d", &X);
	printf(PROMPT);
	scanf("%d", &Y);
	printf(PROMPT);
	scanf("%d", &Z);
		
	// Making use of the fact that booleans in C are simply 0/1 integers to i
	int order[4] = {};
	order[(X>Y) + (X>Z)] = X;
	order[(Y>X) + (Y>Z)] = Y;
	order[(Z>X) + (Z>Y)] = Z;

	// Correct problems with duplicate and triple entries
	order[(order[0] != 0) * 3] = order[1];
	order[((order[1] != 0) * 3) + (order[1] == 0)] = order[0];
	order[((order[2] != 0) * 3) + (order[2] == 0)*2] = order[1];
	
	printf("The integers in order are: %d %d %d\n", order[0], order[1], order[2]);
		
	return 0;
}
