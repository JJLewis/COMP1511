// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// Apr 11 2017
//

#include <stdio.h>
#include "captcha.h"

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
				//if (lastRowWithPixel - v > 1) {
				//	lastTop = lastRowWithPixel;
				//}
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
