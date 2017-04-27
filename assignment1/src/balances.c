// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// Apr 12 2017
//

#include <stdio.h>
#include "captcha.h"

double get_horizontal_balance(int height, int width, int pixels[height][width]) {
	int column_sum = 0;	
	int n_black_pixels = 0;
	int v = 0;
	while (v < height) {
		int h = 0;
		while (h < width) {
			if (pixels[v][h] == 1) {
				n_black_pixels++;
				column_sum += h;
			}
			h++;
		}
		v++;
	}
	return ((double)column_sum / n_black_pixels + 0.5) / width;
}
