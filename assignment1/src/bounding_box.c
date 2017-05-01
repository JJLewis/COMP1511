// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// Apr 11 2017
//

#include <stdio.h>
#include "captcha.h"

/*
 * Creates a bounding box around a section of 1s in the pixel data.
 *
 * input:
 * 			pixels[height][width]: Raw pixel data from the pbm file.
 * 			start_row: 	Pointer to a value to be assigned at the end of this function
 * 						as the starting row of the bounding box within pixels[height][width]
 * 			start_col: 	Pointer to a value to be assigned at the end of this function
 * 						as the starting column of the bounding box within pixels[height][width]
 * 			box_height: Pointer to a value to be assigned at the end of this function
 * 						as the height of the bounding box of the number in pixels[height][width]
 * 			box_width: 	Pointer to a value to be assigned at the end of this function
 * 						as the width of the bounding box of the number in pixels[height][width]
 * output:
 * 			The output of this function is the assignment of values to the pointers passed in.
 */
void get_bounding_box(
			int height, 
			int width, 
			int pixels[height][width], 
			int *start_row, 
			int *start_column, 
			int *box_height, 
			int *box_width) {
	int firstTop = -1;
	int leastH = width;
	int lastTop = -1;
	int highestH = -1;
	int lastRowWithPixel = -1;

	int v = height - 1;
	while (v >= 0) {
		int h = 0;
		while (h < width) {
			int pixel = pixels[v][h];
			if (pixel == 1) {
				if (firstTop == -1) {
					firstTop = v;
				}
				if (h < leastH) {
					leastH = h;

				}
				if (h > highestH) {
					highestH = h;
				}
				lastRowWithPixel = v;
			}
			h++;
		}
		v--;
	}
	
	if (lastTop == -1) {
		lastTop = lastRowWithPixel;
	}

	*start_row = lastTop;
	*start_column = leastH;
	*box_height = firstTop - lastTop + 1;
	*box_width = highestH - leastH + 1;
}
