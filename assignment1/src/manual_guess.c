//
// Created by Jordan Lewis on 28/4/17.
//

#include "captcha.h"
#include "handy.h"

#include <stdio.h>
#include "debugger.h"

void subtractArrays(int size, double arr1[size], double arr2[size], double output[size]) {
    for (int i = 0; i < size; i++) {
        output[i] = arr1[i] - arr2[i];
    }
}

double sumArray(int size, double source[size]) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += source[i];
    }
    return sum;
}

int deviationMethod(int numOutcomes,
                    int numFeatures,
                    double allAvgs[numOutcomes][numFeatures],
                    double vals[numFeatures],
                    int ans[numOutcomes]) {

    double deviations[numOutcomes];
    for (int i = 0; i < numOutcomes; i++) {
        if (ans[i] != -1) {
            double diffs[numFeatures];
            subtractArrays(numFeatures, allAvgs[i], vals, diffs);
            deviations[i] = sumArray(numFeatures, diffs);
        } else {
            deviations[i] = 100;
        }
    }
    double smallestElement = minElementD(numOutcomes, deviations);
    int index = indexOfD(numOutcomes, deviations, smallestElement);

    return ans[index];
}

int rangeMethod(int numOutcomes,
                int numFeatures,
                double allMaxes[numOutcomes][numFeatures],
                double allMins[numOutcomes][numFeatures],
                double vals[numFeatures],
                int ans[numOutcomes]) {

    double allDiffs[numOutcomes];
    for (int n = 0; n < numOutcomes; n++) {
        if (ans[n] != -1) {
            double diff[numFeatures];
            for (int f = 0; f < numFeatures; f++) {
                double max = allMaxes[n][f];
                double min = allMins[n][f];
                double mid = (max + min) / 2.0;
                double factor = 1.0 / (max - mid);

                double val = vals[f];
                diff[f] = (val - mid) * factor;
            }
            allDiffs[n] = sumArray(numFeatures, diff);
        } else {
            allDiffs[n] = 100;
        }
    }
    double smallestElement = minElementD(numOutcomes, allDiffs);
    int index = indexOfD(numOutcomes, allDiffs, smallestElement);

    return ans[index];
}

void eliminateOption(int numOptions, int options[numOptions], int toEliminate) {
    int index = indexOfI(numOptions, options, toEliminate);
    if (index != -1) {
        options[index] = -1;
    }
}

#define N_NO_HOLES_FEATS 3
int noHoles3(double features[NUM_FEATURES]) {

    double height = features[0];
    double width = features[1];
    double hBalance = features[2];
    double vBalance = features[3];
    double blackDensity = features[4];
    double area = features[7];

    double vals[N_NO_HOLES_FEATS] = {vBalance, hBalance, blackDensity};
    //           vB             hB          bD
    double avg1s[N_NO_HOLES_FEATS] = {0.513545995, 0.525280464, 0.371528497};
    double avg2s[N_NO_HOLES_FEATS] = {0.50816045, 0.544074217, 0.379821942};
    //double avg3s[N_NO_HOLES_FEATS] = {0.503079739, 0.572549886, 0.418143286};
    double avg7s[N_NO_HOLES_FEATS] = {0.403378435, 0.530864138, 0.333130337};
    double allAvgs[3][N_NO_HOLES_FEATS];// = {avg1s, avg2s, avg7s};
    assignRow(3, N_NO_HOLES_FEATS, allAvgs, avg1s, 0);
    assignRow(3, N_NO_HOLES_FEATS, allAvgs, avg2s, 1);
    assignRow(3, N_NO_HOLES_FEATS, allAvgs, avg7s, 2);

    double max1s[N_NO_HOLES_FEATS] = {0.497575446, 0.698155444, 0.589670014};
    double max2s[N_NO_HOLES_FEATS] = {0.595729921, 0.627140656, 0.561155914};
    //double max3s[N_NO_HOLES_FEATS] = {0.852272727, 0.683075463, 0.588235294};
    double max7s[N_NO_HOLES_FEATS] = {0.480858086, 0.699111111, 0.503267974};
    double allMaxes[3][N_NO_HOLES_FEATS];// = {max1s, max2s, max7s};
    assignRow(3, N_NO_HOLES_FEATS, allMaxes, max1s, 0);
    assignRow(3, N_NO_HOLES_FEATS, allMaxes, max2s, 1);
    assignRow(3, N_NO_HOLES_FEATS, allMaxes, max7s, 2);

    double min1s[N_NO_HOLES_FEATS] = {0.442459505, 0.4232532, 0.171948052};
    double min2s[N_NO_HOLES_FEATS] = {0.440241902, 0.42096118, 0.264520202};
    //double min3s[N_NO_HOLES_FEATS] = {0.433945922, 0.512787524, 0.216878403};
    double min7s[N_NO_HOLES_FEATS] = {0.305428249, 0.419571295, 0.203488372};
    double allMins[3][N_NO_HOLES_FEATS];// = {min1s, min2s, min7s};
    assignRow(3, N_NO_HOLES_FEATS, allMins, min1s, 0);
    assignRow(3, N_NO_HOLES_FEATS, allMins, min2s, 1);
    assignRow(3, N_NO_HOLES_FEATS, allMins, min7s, 2);

    int ans[3] = {1,2,7};

    if (vBalance > 0.4809)      { eliminateOption(3, ans, 7); }
    if (blackDensity > 0.50327) { eliminateOption(3, ans, 7); }

    if (hBalance < 0.51279)     { eliminateOption(3, ans, 3); }
    if (blackDensity < 0.265)   { eliminateOption(3, ans, 2); }

    if (indexOfI(3, ans, -1) == -1) {
        return -1;
    }

    int rangeGuess = rangeMethod(3, N_NO_HOLES_FEATS, allMaxes, allMins, vals, ans);
    int deviationGuess = deviationMethod(3, N_NO_HOLES_FEATS, allAvgs, vals, ans);
    if (rangeGuess == 2 && deviationGuess != 2) {
        return 2;
    } else {
        return deviationGuess;
    }
}

int noHoles2(int height, int width, int pixels[height][width], double features[NUM_FEATURES]) {

    int startRow, startCol, boxHeight, boxWidth;
    get_bounding_box(height, width, pixels, &startRow, &startCol, &boxHeight, &boxWidth);

    int extracted[boxHeight][boxWidth];
    copy_pixels(height, width, pixels, startRow, startCol, boxHeight, boxWidth, extracted);

    double halvedFeatures[H_NUM_FEATURES];
    get_halved_features(boxHeight, boxWidth, extracted, halvedFeatures);

    int numHoles = (int)halvedFeatures[0];
    double hHoleBalance = halvedFeatures[1];
    double vHoleBalance = halvedFeatures[2];

    if (numHoles == 2) {
        return 3;
    } else if (numHoles == 1) {
        // either 2, 5, 7
        if (vHoleBalance > 0.5) {
            return 5;
        } else {
            // either 2, 7
            return noHoles3(features);
        }
    } else if (numHoles == 0) {
        return 1;
    }
    return -1;
}

#define N_HAS_HOLE_FEATS 6
int hasHoles(double features[NUM_FEATURES]) {
    double height = features[0];
    double width = features[1];
    double hBalance = features[2];
    double vBalance = features[3];
    double blackDensity = features[4];
    double holeDensity = features[5];
    double holeCount = features[6];
    double area = features[7];
    double hHoleBalance = features[8];
    double vHoleBalance = features[9];

    if (holeCount == 2) {
        return 8;
    }

    double vals[N_HAS_HOLE_FEATS] = {vBalance, hBalance, blackDensity, holeDensity, hHoleBalance, vHoleBalance};
    //           vB             hB          bD          hD       hHoleB       vHoleB
    double avg0s[N_HAS_HOLE_FEATS] = {0.50224126, 0.49946983, 0.51078787, 0.25400239, 0.500646788, 0.500470992};
    double avg4s[N_HAS_HOLE_FEATS] = {0.51961881, 0.54726439, 0.44558401, 0.06440427, 0.545390918, 0.497673672};
    double avg6s[N_HAS_HOLE_FEATS] = {0.51598543, 0.46690274, 0.51049573, 0.11210898, 0.520124085, 0.66581604};
    double avg9s[N_HAS_HOLE_FEATS] = {0.48285105, 0.52934610, 0.50199315, 0.12144133, 0.485020415, 0.332551043};
    double allAvgs[4][N_HAS_HOLE_FEATS];// = {avg0s, avg4s, avg6s, avg9s};
    assignRow(4, N_HAS_HOLE_FEATS, allAvgs, avg0s, 0);
    assignRow(4, N_HAS_HOLE_FEATS, allAvgs, avg4s, 1);
    assignRow(4, N_HAS_HOLE_FEATS, allAvgs, avg6s, 2);
    assignRow(4, N_HAS_HOLE_FEATS, allAvgs, avg9s, 3);


    double max0s[N_HAS_HOLE_FEATS] = {0.54402028, 0.53911205, 0.69516509, 0.47796353, 0.557639752, 0.528851315};
    double max4s[N_HAS_HOLE_FEATS] = {0.58678802, 0.63155040, 0.59935897, 0.16258741, 0.671568627, 0.584854995};
    double max6s[N_HAS_HOLE_FEATS] = {0.60045118, 0.51220430, 0.65046296, 0.21785714, 0.667913832, 0.716302953};
    double max9s[N_HAS_HOLE_FEATS] = {0.54267401, 0.59926090, 0.68684896, 0.23958333, 0.604333868, 0.375364431};
    double allMaxes[4][N_HAS_HOLE_FEATS];// = {max0s, max4s, max6s, max9s};
    assignRow(4, N_HAS_HOLE_FEATS, allMaxes, max0s, 0);
    assignRow(4, N_HAS_HOLE_FEATS, allMaxes, max4s, 1);
    assignRow(4, N_HAS_HOLE_FEATS, allMaxes, max6s, 2);
    assignRow(4, N_HAS_HOLE_FEATS, allMaxes, max9s, 3);

    double min0s[N_HAS_HOLE_FEATS] = {0.455238095, 0.428082192, 0.30862069, 0.117391304, 0.445364425, 0.462624113};
    double min4s[N_HAS_HOLE_FEATS] = {0.449059561, 0.44899676, 0.259800664, 0.02182285, 0.437693419, 0.359429066};
    double min6s[N_HAS_HOLE_FEATS] = {0.46015561, 0.401942067, 0.308943089, 0.052083333, 0.392874693, 0.620032116};
    double min9s[N_HAS_HOLE_FEATS] = {0.425593363, 0.469117435, 0.327489481, 0.051445578, 0.336236934, 0.293334824};
    double allMins[4][N_HAS_HOLE_FEATS];// = {min0s, min4s, min6s, min9s};
    assignRow(4, N_HAS_HOLE_FEATS, allMins, min0s, 0);
    assignRow(4, N_HAS_HOLE_FEATS, allMins, min4s, 1);
    assignRow(4, N_HAS_HOLE_FEATS, allMins, min6s, 2);
    assignRow(4, N_HAS_HOLE_FEATS, allMins, min9s, 3);

    int ans[4] = {0, 4, 6, 9};

    // Filter Smallest Maxes
    if (vHoleBalance > 0.37537)     { eliminateOption(4, ans, 9); }
    if (hHoleBalance > 0.55764)     { eliminateOption(4, ans, 0); }
    if (vBalance > 0.5427)          { eliminateOption(4, ans, 9); }
    if (hBalance > 0.5123)          { eliminateOption(4, ans, 6); }
    if (holeDensity > 0.1626)       { eliminateOption(4, ans, 4); }
    if (blackDensity > 0.5994)      { eliminateOption(4, ans, 4); }

    // Filter Largest Minimums
    if (vHoleBalance < 0.62004)     { eliminateOption(4, ans, 6); }
    if (hHoleBalance < 0.44537)     { eliminateOption(4, ans, 0); }
    if (hBalance < 0.4692)          { eliminateOption(4, ans, 9); }
    if (vBalance < 0.4602)          { eliminateOption(4, ans, 6); }
    if (blackDensity < 0.3275)      { eliminateOption(4, ans, 9); }
    if (holeDensity < 0.1174)       { eliminateOption(4, ans, 0); }

    if (indexOfI(4, ans, -1) == -1) {
        return -1;
    }
    if (vHoleBalance > 0.620032) {
        return 6;
    }
    if (vHoleBalance < 0.375365) {
        return 9;
    }

    return rangeMethod(4, N_HAS_HOLE_FEATS, allMaxes, allMins, vals, ans);
}

int crack(int height, int width, int pixels[height][width]) {
    double features[NUM_FEATURES];
    get_image_features(height, width, pixels, features);
    double numHoles = features[6];
    if (numHoles == 0) {
        return noHoles2(height, width, pixels, features);
    } else {
        return hasHoles(features);
    }
}