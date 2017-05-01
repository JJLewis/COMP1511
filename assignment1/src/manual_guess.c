//
// Created by Jordan Lewis on 28/4/17.
//

#include "guess.h"

/*
 * Guesses a number by using all of the other functions in this program.
 *
 * output: Returns the guess for the supplied image.
 */
int crack(int height, int width, int pixels[height][width]) {
    double features[NUM_FEATURES];
    get_image_features(height, width, pixels, features);
    double numHoles = features[6];
    if (numHoles == 0) {
        return noHoles(height, width, pixels, features);
    } else {
        return hasHoles(features);
    }
}