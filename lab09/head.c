// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// May 03 2017
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 1024

void printLines(int numLines, FILE *inStream) {
	if (inStream == NULL) {
		return;
	}

	for (int i = 0; i < numLines; i++) {
		char line[MAX_LINE];
		if (fgets(line, MAX_LINE, inStream) != NULL) {
			printf("%s", line);
		} else {
			break;
		}
	}

	fclose(inStream);
}



int main (int argc, char* argv[]) {
	
	FILE *inStream;
	if (argc == 2) {
		inStream = fopen(argv[1], "r");
		printLines(10, inStream);
	} else if (argc == 4) {
		inStream = fopen(argv[3], "r");
		printLines(atoi(argv[2]), inStream);
	} else {
		printf("Usage is: [-n <number of lines to read from top>] <path to file>\n");
		return 1;
	}

	return 0;
}
