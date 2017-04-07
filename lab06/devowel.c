// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// 5 April 2017
//

#include <stdio.h>
#include <stdlib.h>

int is_vowel(char c) {
	const char vowels[6] = {"aeiou"};
	int counter = 0;
	while (counter < 5) {
		if (c == vowels[counter]) {
			return 1;
		}
		counter++;
	}
	return 0;
}

int main () {
	char ch = getchar();
	while (ch != EOF) {
		if (!is_vowel(ch)) {
			putchar(ch);
		}
		ch = getchar();		
	}	

	return 0;
}
