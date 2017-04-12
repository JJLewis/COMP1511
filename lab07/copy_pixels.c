// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// Apr 11 2017
//

#include <stdio.h>
#include "captcha.h"

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
