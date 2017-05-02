// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// May 02 2017
//

#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 4096

int main (int argc, char* argv[]) {
	
	char string[BUFSIZE];
	printf("Enter a string: ");

	fgets(string, BUFSIZE, stdin);
	
	for (int i = 0; i <= BUFSIZE; i++) {
		if (string[i] == '\n') {
			break;
		}
		printf("%c\n", string[i]);
	}

	return 0;
}
