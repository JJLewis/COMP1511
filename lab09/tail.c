// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// May 03 2017
//

#include <stdio.h>
#include <stdlib.h>

#define NUM_LINES 10
#define MAX_LINE 1024

void copyToRow(char source[MAX_LINE], char destination[NUM_LINES][MAX_LINE], int index) {
	for (int i = 0; i < MAX_LINE; i++) {
		destination[index][i] = source[i];
		if (source[i] == '\n') {
			break;
		}
	}
}

int lengthOf(char string[MAX_LINE]) {
	int counter = 0;
	for (int i = 0; i < MAX_LINE; i++) {
		if (string[i] == '\n') {
			break;
		}
		counter++;
	}
	return counter;
}

void printLastLines(FILE *inStream) {
	
	char lastTen[NUM_LINES][MAX_LINE];
	
	int index = 0;
	char line[MAX_LINE];
	int numLines = 0;
	
	while (fgets(line, MAX_LINE, inStream) != NULL) {
		copyToRow(line, lastTen, index);
		numLines++;
		index++;
		if (index == NUM_LINES) {
			index = 0;
		}
	}

	fclose(inStream);

	numLines = numLines < NUM_LINES ? numLines:NUM_LINES;
	
	for (int i = 0; i < numLines; i++) {
		if (numLines < NUM_LINES) {
			index = i;
		}

		//printf("%s", lastTen[index]);
		int length = lengthOf(lastTen[index]);
		for (int c = 0; c < length; c++) {
			putchar(lastTen[index][c]);
		}
		putchar('\n');
		
		index++;
		if (index == NUM_LINES) {
			index = 0;
		}
	}
}

int main (int argc, char* argv[]) {
	
	FILE *inStream;
	if (argc == 2) {
		inStream = fopen(argv[1], "r");
		if (inStream == NULL) {
			return 1;
		}

		printLastLines(inStream);
	} else {
		printf("Usage is: <path to file to read from tail>\n");
		return 1;
	}

	return 0;
}
