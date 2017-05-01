//
// Created by Jordan Lewis on 29/4/17.
//

#include "guess.h"

/*
 * Takes two 1D arrays and subtracts every element from arr2 from it's corresponding element in arr1.
 * Returns the output as the array output[size]
 */
void subtractArrays(int size, double arr1[size], double arr2[size], double output[size]) {
    for (int i = 0; i < size; i++) {
        output[i] = arr1[i] - arr2[i];
    }
}

/*
 * Sums every element in the array and returns the result.
 */
double sumArray(int size, double source[size]) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += source[i];
    }
    return sum;
}

/*
 * Makes a guess based on how far each feature is from the average for that number.
 * Makes this decision by selecting the number with the least overall distance from the averages.
 *
 * input:
 *          allAvgs[numOutcomes][numFeatures]: 2D array where each row is an array of average values for each feature
 *          vals[numFeatures]: Array containing the values for each feature in the array
 *          ans[numOutcomes]: Array of all possible outcomes, will contain -1 for numbers/options that have been eliminated
 *
 * output: Returns a guess from the possible answers provided in ans[numOutcomes]
 */
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

/*
 * Makes a guess based on how far each feature is from the centre of the max and min for that number.
 * Makes this decision by selecting the number with the least overall distance from the averages.
 *
 * input:
 *          allMaxes[numOutcomes][numFeatures]: 2D array where each row is an array of max values for each feature
 *          allMins[numOutcomes][numFeatures]: 2D array where each row is an array of min values for each feature
 *          vals[numFeatures]: Array containing the values for each feature in the array
 *          ans[numOutcomes]: Array of all possible outcomes, will contain -1 for numbers/options that have been eliminated
 *
 * output: Returns a guess from the possible answers provided in ans[numOutcomes]
 */
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

/*
 * Eliminate an option given the number of eliminate and the array to eliminate it from.
 *
 * input:
 *          numOptions: The number of possible options
 *          options[numOptions]: An array of options to have an option eliminated.
 *          toEliminate: The option to be eliminated from options
 */
void eliminateOption(int numOptions, int options[numOptions], int toEliminate) {
    int index = indexOfI(numOptions, options, toEliminate);
    if (index != -1) {
        options[index] = -1;
    }
}