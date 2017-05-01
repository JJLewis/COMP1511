// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// Apr 12 2017
//

#include <stdio.h>
#include "captcha.h"

/*
 * Copies a section out of the pixels[height][width] into copy[copy_height][copy_width].
 * This function is best used in conjunction with get_bounding_box and it's outputs.
 *
 * inputs:
 * 			start_row, start_column, copy_height, copy_width: Define the section of pixels[height][width]
 * 			to be copied into copy[copy_height][copy_width]
 * output:
 * 			copy[copy_height][copy_width] will have the section of pixels copied to it.
 */
void copy_pixels(
		int height, 
		int width, 
		int pixels[height][width], 
		int start_row, 
		int start_column, 
		int copy_height, 
		int copy_width, 
		int copy[copy_height][copy_width]) {
	int v = start_row;	
	while (v < start_row + copy_height) {
		int h = start_column;
		while (h < start_column + copy_width) {
			copy[v - start_row][h - start_column] = pixels[v][h];
			h++;
		}
		v++;
	}
}
