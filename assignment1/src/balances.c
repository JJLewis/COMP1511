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

double get_vertical_balance(int height, int width, int pixels[height][width]) {
	int row_sum = 0;
	int n_black_pixels = 0;
	int v = 0;
	while (v < height) {
		int h = 0;
		while (h < width) {
			if (pixels[v][h] == 1) {
				n_black_pixels++;
				row_sum += v;
			}
			h++;
		}
		v++;
	}
	return ((double)row_sum / n_black_pixels + 0.5) / height;
}

double horizontalHoleBalance(int height, int width, int pixels[height][width]) {
	int isolated[height][width];
	isolateHoles(height, widthpixels, isolated);
	if (numberOfHoles(height, width, isolated) == 0) {
		return 0.5;
	}
	return get_horizontal_balance(height, width, isolated);
}

double verticalHoleBalance(int height, int width, int pixels[height][width]) {
	int isolated[height][width];
	isolateHoles(height, width, pixels, isolated);
	if (numberOfHoles(height, width, isolated) == 0) {
		return 0.5;
	}
	return get_vertical_balance(height, width, isolated);
}