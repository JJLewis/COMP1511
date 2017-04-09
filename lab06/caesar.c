// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// 7 April 2017
//

#include <stdio.h>
#include <stdlib.h>

#define A 'A'//65
#define Z 'Z'//90
#define a 'a'//97
#define z 'z'//122

int isUpper(int c) {
	return A <= c && c <= Z;
}

int isLower(int c) {
	return a <= c && c <= z;
}

int isAlphabet(int c) {
	return isUpper(c) || isLower(c);	
}

int isOutLower(int c, int nc) {
	int limit = isUpper(c) ? A:a;	
	return nc < limit;
}

int isOutUpper(int c, int nc) {
	int limit = isUpper(c) ? Z:z;
	return nc > limit;
}

int isOut(int c, int nc) {	
	return isOutUpper(c, nc) || isOutLower(c, nc);
}	

int fixOutUpper(int c, int upper, int lower, int shift) {
	return (lower - (upper - (c + shift))) - 1;
}

int fixOutLower(int c, int upper, int lower, int shift) {
	return (upper - (lower - (c + shift))) + 1;
}

int fixChar(const int ch, const int nc) {
	int shift = nc - ch;
	int upper = isUpper(ch) ? Z:z;
	int lower = isUpper(ch) ? A:a;	
	if (isOutUpper(ch, nc)) {
		return fixOutUpper(ch, upper, lower, shift);
	} else if (isOutLower(ch, nc)) {
		return fixOutLower(ch, upper, lower, shift);
	}
	return -1;
}

int caesar(int c, int shift) {
	shift %= 26;
	if (isAlphabet(c)) {	
		int nc = c + shift;
		if (isOut(c, nc)) {
			nc = fixChar(c, nc);
		}
		return nc;	
	}
	return c;
}

int main (int argc, char *argv[]) {

	const int shift = atoi(argv[1]);

	int ch = getchar();

	while (ch != EOF) {
		putchar(caesar(ch, shift));
		ch = getchar();
	}	

	return 0;
}
