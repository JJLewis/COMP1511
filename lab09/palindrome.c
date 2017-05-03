// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// May 03 2017
//

#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 4096
#define TRUE 1
#define FALSE 0

int lengthOfString(char string[BUFSIZE]) {
	int count = 0;
	for (int i = 0; i <= BUFSIZE; i++) {
		if (string[i] == '\n') {
			break;
		}
		count++;
	}
	return count;
}	

int main (int argc, char* argv[]) {
	
	char string[BUFSIZE];
	printf("Enter a string: ");

	fgets(string, BUFSIZE, stdin);
	
	int length = lengthOfString(string);
	int half = length/2.0;
	
	int isPalindrome = TRUE;
	for (int i = 0; i < half; i++) {
		if (string[i] != string[length - i - 1]) {
			isPalindrome = FALSE;
		}
	}

	printf("String is %sa palindrome\n", isPalindrome ? "":"not ");

	return 0;
}
