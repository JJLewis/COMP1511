//
// Created by Jordan Lewis on 28/4/17.
//

#include "captcha.h"

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

double get_density(int height, int width, int pixels[height][width]) {
    return (double)sumBlackPixels(height, width, pixels) / (double)(height * width);
}

double get_hole_fraction(int height, int width, int pixels[height][width]) {
    int isolated[height][width];
    isolateHoles(height, width, pixels, isolated);
    int sum = sumBlackPixels(height, width, isolated);
    return (double)sum / (double)(height * width);
}