//
// Created by Jordan Lewis on 28/4/17.
//

#include "captcha.h"

int sumBlackPixels(int pixels[height][width], int height, int width) {
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

double getDensity(int pixels[height][width], int height, int width) {
    return (double)sumBlackPixels(pixels, height, width) / (double)(height * width);
}

double getHoleFraction(int pixels[height][width], int height, int width) {
    int isolated[height][width];
    isolateHoles(pixels, isolated, height, width);
    sum = sumBlackPixels(isolated, height, width);
    return (double)sum / (double)(height * width);
}