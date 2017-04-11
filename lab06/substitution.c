// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// 9 April 2017
//

#include <stdio.h>
#include <stdlib.h>

#define A 'A'//65
#define Z 'Z'//90
#define a 'a'//97
#define z 'z'//122
#define TO_UPPER -32
#define TO_LOWER 32

int isUpper(int c) {
	return A <= c && c <= Z;
}

int isLower(int c) {
	return a <= c && c <= z;
}

int isAlphabet(int c) {
	return isUpper(c) || isLower(c);	
}

int subcipher(int c, char key[27]) {
	if (!isAlphabet(c)) { return c; }	
	int nc = c;
	if (isUpper(c)) { nc += TO_LOWER; }
	int index = nc - 97;
	nc = key[index];
	if (isUpper(c)) { nc += TO_UPPER; }
	return nc;
}	

int main (int argc, char *argv[]) {

	int ch = getchar();

	while (ch != EOF) {
		putchar(subcipher(ch, argv[1]));
		ch = getchar();
	}	

	return 0;
}
