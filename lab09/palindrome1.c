// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// May 03 2017
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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

void allLower(char string[BUFSIZE], int length) {
	for (int i = 0; i < length; i++) {
		string[i] = tolower(string[i]);
	}
}

void copyArray(char source[BUFSIZE], char destination[BUFSIZE], int length) {
	for (int i = 0; i < length; i++) {
		destination[i] = source[i];
	}
}

int removeSpaces(char string[BUFSIZE], int length) {
	char cpString[BUFSIZE];
	copyArray(string, cpString, length);
	int counter = 0;
	for (int i = 0; i < length; i++) {
		if (isalpha(string[i])) {
			cpString[counter] = string[i];
			counter++;
		}
	}
	copyArray(cpString, string, counter);
	return counter;
}

int isPalindrome(char string[BUFSIZE], int length) {
	int half = length / 2.0;
	int isReversed = TRUE;
	for (int i = 0; i < half; i++) {
		if (string[i] != string[length - i - 1]) {
			isReversed = FALSE;
		}
	}
	return isReversed;
}

int main (int argc, char* argv[]) {
	
	char string[BUFSIZE];
	printf("Enter a string: ");

	fgets(string, BUFSIZE, stdin);
	
	int length = lengthOfString(string);
	
	allLower(string, length);
	int newLength = removeSpaces(string, length);

	printf("String is %sa palindrome\n", isPalindrome(string, newLength) ? "":"not ");

	return 0;
}
