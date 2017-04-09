// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// 9 April 2017
//

#include <stdio.h>
#include <stdlib.h>

int isUppercase(int c) {
	return (c >= 'A' && c <= 'Z');
}

int isLowercase(int c) {
	return (c >= 'a' && c <= 'z');
}

int main () {
	double freq[26] = {0};
	double sum = 0;

	int ch = getchar();
	
	while (ch != EOF) {
		if (isUppercase(ch)) {
			ch += 32;
		}
		if (isLowercase(ch)) {	
			int index = ch - 97;
			freq[index] = freq[index] + 1;	
			sum++;
		}
		ch = getchar();
	}
	
	int count = 0;
	while (count < 26) {
		int numoc = freq[count];
		printf("'%c' %lf %d\n", (count + 97), numoc / sum, numoc);
		count++;
	}

	return 0;
}
