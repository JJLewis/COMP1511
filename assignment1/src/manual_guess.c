//
// Created by Jordan Lewis on 28/4/17.
//

#include "captcha.h"
#include "handy.h"

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
        double diffs[numFeatures];
        subtractArrays(numFeatures, allAvgs[i], vals, diffs);
        deviations[i] = sumArray(numFeatures, diffs);
    }
    double smallestElement = minElement(numOutcomes, deviations);
    int index = indexOf(numOutcomes, deviations, smallestElement);

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
    }
    double smallestElement = minElement(numOutcomes, allDiffs);
    int index = indexOf(numOutcomes, allDiffs, smallestElement);

    return ans[index];
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
    double allAvgs[4] = {avg0s, avg4s, avg6s, avg9s};

    double max0s[N_HAS_HOLE_FEATS] = {0.54402028, 0.53911205, 0.69516509, 0.47796353, 0.557639752, 0.528851315};
    double max4s[N_HAS_HOLE_FEATS] = {0.58678802, 0.63155040, 0.59935897, 0.16258741, 0.671568627, 0.584854995};
    double max6s[N_HAS_HOLE_FEATS] = {0.60045118, 0.51220430, 0.65046296, 0.21785714, 0.667913832, 0.716302953};
    double max9s[N_HAS_HOLE_FEATS] = {0.54267401, 0.59926090, 0.68684896, 0.23958333, 0.604333868, 0.375364431};
    double allMaxes[4] = {max0s, max4s, max6s, max9s};

    double min0s[N_HAS_HOLE_FEATS] = {0.455238095, 0.428082192, 0.30862069, 0.117391304, 0.445364425, 0.462624113};
    double min4s[N_HAS_HOLE_FEATS] = {0.449059561, 0.44899676, 0.259800664, 0.02182285, 0.437693419, 0.359429066};
    double min6s[N_HAS_HOLE_FEATS] = {0.46015561, 0.401942067, 0.308943089, 0.052083333, 0.392874693, 0.620032116};
    double min9s[N_HAS_HOLE_FEATS] = {0.425593363, 0.469117435, 0.327489481, 0.051445578, 0.336236934, 0.293334824};
    double allMins[4] = {min0s, min4s, min6s, min9s};

    int ans[4] = {0,4,6,9};
    

}
