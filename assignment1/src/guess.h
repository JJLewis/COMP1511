//
// Created by Jordan Lewis on 29/4/17.
//

#ifndef SRC_GUESS_H
#define SRC_GUESS_H

#endif //SRC_GUESS_H

#include "captcha.h"
#include "handy.h"
#include "debugger.h"

void subtractArrays(int size, double arr1[size], double arr2[size], double output[size]);

double sumArray(int size, double source[size]);

int deviationMethod(int numOutcomes,
                    int numFeatures,
                    double allAvgs[numOutcomes][numFeatures],
                    double vals[numFeatures],
                    int ans[numOutcomes]);

int rangeMethod(int numOutcomes,
                int numFeatures,
                double allMaxes[numOutcomes][numFeatures],
                double allMins[numOutcomes][numFeatures],
                double vals[numFeatures],
                int ans[numOutcomes]);

void eliminateOption(int numOptions, int options[numOptions], int toEliminate);


int noHoles2(int height, int width, int pixels[height][width], double features[NUM_FEATURES]);
int noHoles3(double features[NUM_FEATURES]);

int hasHoles(double features[NUM_FEATURES]);