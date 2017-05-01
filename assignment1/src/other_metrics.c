//
// Created by Jordan Lewis on 28/4/17.
//

#include "captcha.h"

/*
 * Sums all of the black pixels in an image
 *
* output: Returns the sum of all the black pixels in an image
 */
int sumBlackPixels(int height, int width, int pixels[height][width]) {
    int sum = 0;
    for (int v = 0; v < height; v++) {
        for (int h = 0; h < width; h++) {
            if (pixels[v][h] == 1) {
                sum++;
            }
        }
    }
    return sum;
}

/*
 * Returns the density of black pixels in an image.
 */
double get_density(int height, int width, int pixels[height][width]) {
    return (double)sumBlackPixels(height, width, pixels) / (double)(height * width);
}

/*
 * Returns the density of the space a hole takes up in an image.
 */
double get_hole_fraction(int height, int width, int pixels[height][width]) {
    int isolated[height][width];
    isolateHoles(height, width, pixels, isolated);
    int sum = sumBlackPixels(height, width, isolated);
    return (double)sum / (double)(height * width);
}