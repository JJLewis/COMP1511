//
// Created by Jordan Lewis on 28/4/17.
//

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

