// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// Apr 11 2017
//

#include <stdio.h>
#include "captcha.h"
#include "debugger.h"

/*
 * Prints out the contents of an image array where 1 = * and 0 = .
 * Only prints when the IS_DEBUGGING flag is TRUE.
 */
void print_image(int height, int width, int pixels[height][width]) {
	if (IS_DEBUGGING) {
		int v = height - 1;
		while (v >= 0) {
			int h = 0;
			while (h < width) {
				printf("%s", pixels[v][h] == 1 ? "*" : ".");
				h++;
			}
			printf("\n");
			v--;
		}
	}
}
