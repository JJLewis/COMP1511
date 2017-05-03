// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// May 03 2017
//

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[]) {
	
	if (argc != 4) {
		printf("Usage is: <start number> <end number> <output file path>\n");
		return 1;
	}

	int start = atoi(argv[1]);
	int end = atoi(argv[2]);

	FILE *outputStream;
	outputStream = fopen(argv[3], "w");
	
	for (int i = start; i <= end; i++) {
		fprintf(outputStream, "%d\n", i);
	}

	fclose(outputStream);

	return 0;
}
