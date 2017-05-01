//
// Created by Jordan Lewis on 29/4/17.
//

#include "guess.h"

#define N_OUTCOMES 3
#define N_FEATURES 3

/*
 * Given an array of features for a number that has holes, guess it, and return the guess.
 * Works by first getting features for the left half of the image.
 * Then further narrows down the results by getting the right half of the image.
 * Both half features artificially creates holes by filling in the opposite wall.
 *
 * input:
 *          features[NUM_FEATURES]: The feature data for an image
 * output:
 *          Returns the final guess based on the features given in the argument.
 */
int noHoles(int height, int width, int pixels[height][width], double features[NUM_FEATURES]) {

    int startRow, startCol, boxHeight, boxWidth;
    get_bounding_box(height, width, pixels, &startRow, &startCol, &boxHeight, &boxWidth);

    int extracted[boxHeight][boxWidth];
    copy_pixels(height, width, pixels, startRow, startCol, boxHeight, boxWidth, extracted);

    double leftHalvedFeatures[H_NUM_FEATURES];
    get_halved_features(boxHeight, boxWidth, extracted, leftHalvedFeatures, 1);

    int left_numHoles = (int)leftHalvedFeatures[0];
    double left_hHoleBalance = leftHalvedFeatures[1];
    double left_vHoleBalance = leftHalvedFeatures[2];

    double rightHalvedFeatures[H_NUM_FEATURES];
    get_halved_features(boxHeight, boxWidth, extracted, rightHalvedFeatures, 0);
    int right_numHoles = (int)rightHalvedFeatures[0];
    double right_minHBalance = rightHalvedFeatures[3];

    if (left_numHoles == 2) {
        return 3;
    } else if (left_numHoles == 1) {
        // either 2, 5, 7
        if (left_vHoleBalance > 0.5) {
            return 5;
        } else {
            // either 2, 7
            if (right_numHoles == 0) {
                double fullVBalance = 1 - features[3];
                double leftHBalance = leftHalvedFeatures[3];
                double leftVBalance = leftHalvedFeatures[4];

                if (fullVBalance > 0.4808) { // this lessens the error for 2 by 10
                    // either 1,2
                    double fullHBalance = features[2];
                    if (fullHBalance > 0.62714) {
                        return 1;
                    }

                    if (leftVBalance > 0.5606) {
                        return 1;
                    }

                    if (leftHBalance < 0.2954) {
                        return 1;
                    }

                    return 2;
                }

                /* No difference
                if (leftHBalance < 0.325) {
                    return 2;
                }
                */

                return 7;
            } else {
                return 2;
            }
        }
    } else if (left_numHoles == 0) {
        if (right_minHBalance < 0.61515) {
            return 7;
        }
        return 1;
    }
    return -1;
}