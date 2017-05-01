// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// Apr 12 2017
//

#include <stdio.h>
#include "captcha.h"

/*
 * Finds the horizontal balance of the black pixels of an image.
 * Horizontal balance is the horizontal centre of gravity of the image.
 *
 * input: pixels[height][width]: Bounding boxed number image data.
 * output: 0.5 if there is no hole, otherwise, closer to 0 to the right, and to 1 to the left.
 */
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

/*
 * Finds the vertical balance of the black pixels of an image.
 * Vertical balance is the vertical centre of gravity of the image.
 *
 * input: pixels[height][width]: Bounding boxed number image data.
 * output: 0.5 if there is no hole, otherwise, closer to 0 to the top, and to 1 to the bottom.
 */
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

/*
 * Get the horizontal balance of the holes in an image.
 * This is done by running the get_horizontal_balance function
 * on an image whereby the hole is filled with 1s and all other pixels are 0s.
 *
 * input: pixels[height][width]: Bounding boxed number image data.
 * output: 0.5 if there is no hole, otherwise, closer to 0 to the right, and to 1 to the left.
 */
double get_horizontal_hole_balance(int height, int width, int pixels[height][width]) {
	int isolated[height][width];
	isolateHoles(height, width, pixels, isolated);
	if (countHoles(height, width, isolated) == 0) {
		return 0.5;
	}
	return get_horizontal_balance(height, width, isolated);
}

/*
 * Get the vertical balance of the holes in an image.
 * This is done by running the get_vertical_balance function
 * on an image whereby the hole is filled with 1s and all other pixels are 0s.
 *
 * input: pixels[height][width]: Bounding boxed number image data.
 * output: 0.5 if there is no hole, otherwise, closer to 0 to the top, and to 1 to the bottom.
 */
double get_vertical_hole_balance(int height, int width, int pixels[height][width]) {
	int isolated[height][width];
	isolateHoles(height, width, pixels, isolated);
	if (countHoles(height, width, isolated) == 0) {
		return 0.5;
	}
	return get_vertical_balance(height, width, isolated);
}