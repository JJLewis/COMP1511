// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// 8 March 2017
// Takes an age as an int for input and outputs a recommended age range for dating, unless the age is below 15, whereby an empty range is generated

#include <stdio.h>

int get_input(int *x) {
	if (scanf("%d", x) == 0) {
		printf("Value entered was not a number.\n");
		return 0;
	}
	return 1;
}

int main() {
	int year;

	printf("Enter Year: ");
	if (get_input(&year) == 0) {
		return 0;
	}
	
	int a=year%19;
	int b=year/100;
	int c=year%100;
	int d=b/4;
	int e=b%4;
	int f=(b+8)/25;
	int g=(b-f+1)/3;
	int h=(19*a+b-d-g+15)%30;
	int i=c/4;
	int k=c%4;
	int l=(32+2*e+2*i-h-k)%7;
	int m=(a+11*h+22*l)/451;
	int easter_month =(h+l-7*m+114)/31; // [3=March, 4=April]
	int p=(h+l-7*m+114)%31;
	int easter_date=p+1;
	
	char months[12][10] = {	"January", 
				"February", 
				"March", 
				"April", 
				"May", 
				"June", 
				"July", 
				"August", 
				"September", 
				"October", 
				"November", 
				"December" };
	
	printf("Easter is %s %d in %d.\n", months[easter_month - 1],  easter_date, year);

	return 0;
}
