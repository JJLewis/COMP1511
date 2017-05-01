//
// Created by Jordan Lewis on 28/4/17.
//

#include "captcha.h"
#include "debugger.h"

/*
 * Draws a vertical line of 1s down the left edge of the 2D array of pixels.
 */
void sealLeftWall(int height, int width, int pixels[height][width]) {
    for (int v = 0; v < height; v++) {
        pixels[v][0] = 1;
    }
}

/*
 * Draws a vertical line of 1s down the right edge of the 2D array of pixels.
 */
void sealRightWall(int height, int width, int pixels[height][width]) {
    for (int v = 0; v < height; v++) {
        pixels[v][width - 1] = 1;
    }
}

/*
 * Gets half image features by copying either the left or right half of the original pixel array
 * and sealing the opposite wall. It then feeds the new "half image" into the get_image_features function.
 * It then pulls out only the features that can be relevant and assigns them to features[H_NUM_FEATURES].
 *
 * input:
 *          features[H_NUM_FEATURES]: Will have the half image features assigned to it.
 *          side: 0 for right side, 1 for left side.
 */
void get_halved_features(int height, int width, int pixels[height][width], double features[H_NUM_FEATURES], int side) {
    int nWidth = width/2;

    int half[height][nWidth];

    if (side == 0) {
        copy_pixels(height, width, pixels, 0, 0, height, nWidth, half);
        sealRightWall(height, nWidth, half);
    } else {
        copy_pixels(height, width, pixels, 0, nWidth, height, nWidth, half);
        sealLeftWall(height, nWidth, half);
    }

    double fullFeatures[NUM_FEATURES];
    get_image_features(height, nWidth, half, fullFeatures);

    features[0] = fullFeatures[6];
    features[1] = fullFeatures[8];
    features[2] = fullFeatures[9];
    features[3] = fullFeatures[2];
    features[4] = fullFeatures[3];
}