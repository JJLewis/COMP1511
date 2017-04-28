//
// Created by Jordan Lewis on 28/4/17.
//

#include "captcha.h"

void sealLeftWall(int height, int width, int pixels[height][width]) {
    for (int v = 0; v < height; v++) {
        pixels[v][0] = 1;
    }
}

void get_halved_features(int height, int width, int pixels[height][width], double features[5]) {
    int nWidth = width/2;

    int half[height][nWidth];
    copy_pixels(height, width, pixels, 0, nWidth, height, nWidth, half);
    sealLeftWall(height, nWidth, half);

    double fullFeatures[NUM_FEATURES];
    get_image_features(height, nWidth, half, features);

    features[0] = fullFeatures[6];
    features[1] = fullFeatures[8];
    features[2] = fullFeatures[9];
    features[3] = fullFeatures[2];
    features[4] = fullFeatures[3];
}