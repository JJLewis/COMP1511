//
// Created by Jordan Lewis on 29/4/17.
//

#include "guess.h"

#define N_OUTCOMES 3
#define N_FEATURES 3

int noHoles3(double features[NUM_FEATURES]) {

    double height = features[0];
    double width = features[1];
    double hBalance = features[2];
    double vBalance = features[3];
    double blackDensity = features[4];
    double area = features[7];

    double vals[N_FEATURES] = {vBalance, hBalance, blackDensity};
    //           vB             hB          bD
    double avg1s[N_FEATURES] = {0.513545995, 0.525280464, 0.371528497};
    double avg2s[N_FEATURES] = {0.50816045, 0.544074217, 0.379821942};
    //double avg3s[N_FEATURES] = {0.503079739, 0.572549886, 0.418143286};
    double avg7s[N_FEATURES] = {0.403378435, 0.530864138, 0.333130337};
    double allAvgs[N_OUTCOMES][N_FEATURES];// = {avg1s, avg2s, avg7s};
    assignRow(N_OUTCOMES, N_FEATURES, allAvgs, avg1s, 0);
    assignRow(N_OUTCOMES, N_FEATURES, allAvgs, avg2s, 1);
    assignRow(N_OUTCOMES, N_FEATURES, allAvgs, avg7s, 2);

    double max1s[N_FEATURES] = {0.497575446, 0.698155444, 0.589670014};
    double max2s[N_FEATURES] = {0.595729921, 0.627140656, 0.561155914};
    //double max3s[N_FEATURES] = {0.852272727, 0.683075463, 0.588235294};
    double max7s[N_FEATURES] = {0.480858086, 0.699111111, 0.503267974};
    double allMaxes[N_OUTCOMES][N_FEATURES];// = {max1s, max2s, max7s};
    assignRow(N_OUTCOMES, N_FEATURES, allMaxes, max1s, 0);
    assignRow(N_OUTCOMES, N_FEATURES, allMaxes, max2s, 1);
    assignRow(N_OUTCOMES, N_FEATURES, allMaxes, max7s, 2);

    double min1s[N_FEATURES] = {0.442459505, 0.4232532, 0.171948052};
    double min2s[N_FEATURES] = {0.440241902, 0.42096118, 0.264520202};
    //double min3s[N_FEATURES] = {0.433945922, 0.512787524, 0.216878403};
    double min7s[N_FEATURES] = {0.305428249, 0.419571295, 0.203488372};
    double allMins[N_OUTCOMES][N_FEATURES];// = {min1s, min2s, min7s};
    assignRow(N_OUTCOMES, N_FEATURES, allMins, min1s, 0);
    assignRow(N_OUTCOMES, N_FEATURES, allMins, min2s, 1);
    assignRow(N_OUTCOMES, N_FEATURES, allMins, min7s, 2);

    int ans[N_OUTCOMES] = {1,2,7};

    // Eliminate with Lowest Maxes
    if (vBalance > 0.48086)      {
        print("vB");
        printD(hBalance);
        eliminateOption(N_OUTCOMES, ans, 7); }
    if (blackDensity > 0.50327) { eliminateOption(N_OUTCOMES, ans, 7); }

    // Eliminate with Highest Mins
    //if (hBalance < 0.51279)     { eliminateOption(N_OUTCOMES, ans, 3); }
    if (blackDensity < 0.265)   { eliminateOption(N_OUTCOMES, ans, 2); }

    if (indexOfI(N_OUTCOMES, ans, -1) == -1) {
        return -1;
    }

    int rangeGuess = rangeMethod(N_OUTCOMES, N_FEATURES, allMaxes, allMins, vals, ans);
    int deviationGuess = deviationMethod(N_OUTCOMES, N_FEATURES, allAvgs, vals, ans);

    println();
    printarrI(N_OUTCOMES, ans);
    printI(rangeGuess);
    printI(deviationGuess);
    println();

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