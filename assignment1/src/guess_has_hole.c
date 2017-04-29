//
// Created by Jordan Lewis on 29/4/17.
//

#include "guess.h"

#define N_OUTCOMES 4
#define N_FEATURES 6

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

    double vals[N_FEATURES] = {vBalance, hBalance, blackDensity, holeDensity, hHoleBalance, vHoleBalance};
    //           vB             hB          bD          hD       hHoleB       vHoleB
    double avg0s[N_FEATURES] = {0.50224126, 0.49946983, 0.51078787, 0.25400239, 0.500646788, 0.500470992};
    double avg4s[N_FEATURES] = {0.51961881, 0.54726439, 0.44558401, 0.06440427, 0.545390918, 0.497673672};
    double avg6s[N_FEATURES] = {0.51598543, 0.46690274, 0.51049573, 0.11210898, 0.520124085, 0.66581604};
    double avg9s[N_FEATURES] = {0.48285105, 0.52934610, 0.50199315, 0.12144133, 0.485020415, 0.332551043};
    double allAvgs[N_OUTCOMES][N_FEATURES];// = {avg0s, avg4s, avg6s, avg9s};
    assignRow(N_OUTCOMES, N_FEATURES, allAvgs, avg0s, 0);
    assignRow(N_OUTCOMES, N_FEATURES, allAvgs, avg4s, 1);
    assignRow(N_OUTCOMES, N_FEATURES, allAvgs, avg6s, 2);
    assignRow(N_OUTCOMES, N_FEATURES, allAvgs, avg9s, 3);


    double max0s[N_FEATURES] = {0.54402028, 0.53911205, 0.69516509, 0.47796353, 0.557639752, 0.528851315};
    double max4s[N_FEATURES] = {0.58678802, 0.63155040, 0.59935897, 0.16258741, 0.671568627, 0.584854995};
    double max6s[N_FEATURES] = {0.60045118, 0.51220430, 0.65046296, 0.21785714, 0.667913832, 0.716302953};
    double max9s[N_FEATURES] = {0.54267401, 0.59926090, 0.68684896, 0.23958333, 0.604333868, 0.375364431};
    double allMaxes[N_OUTCOMES][N_FEATURES];// = {max0s, max4s, max6s, max9s};
    assignRow(N_OUTCOMES, N_FEATURES, allMaxes, max0s, 0);
    assignRow(N_OUTCOMES, N_FEATURES, allMaxes, max4s, 1);
    assignRow(N_OUTCOMES, N_FEATURES, allMaxes, max6s, 2);
    assignRow(N_OUTCOMES, N_FEATURES, allMaxes, max9s, 3);

    double min0s[N_FEATURES] = {0.455238095, 0.428082192, 0.30862069, 0.117391304, 0.445364425, 0.462624113};
    double min4s[N_FEATURES] = {0.449059561, 0.44899676, 0.259800664, 0.02182285, 0.437693419, 0.359429066};
    double min6s[N_FEATURES] = {0.46015561, 0.401942067, 0.308943089, 0.052083333, 0.392874693, 0.620032116};
    double min9s[N_FEATURES] = {0.425593363, 0.469117435, 0.327489481, 0.051445578, 0.336236934, 0.293334824};
    double allMins[N_OUTCOMES][N_FEATURES];// = {min0s, min4s, min6s, min9s};
    assignRow(N_OUTCOMES, N_FEATURES, allMins, min0s, 0);
    assignRow(N_OUTCOMES, N_FEATURES, allMins, min4s, 1);
    assignRow(N_OUTCOMES, N_FEATURES, allMins, min6s, 2);
    assignRow(N_OUTCOMES, N_FEATURES, allMins, min9s, 3);

    int ans[N_OUTCOMES] = {0, 4, 6, 9};

    // Filter Smallest Maxes
    if (vHoleBalance > 0.37537)     { eliminateOption(N_OUTCOMES, ans, 9); }
    if (hHoleBalance > 0.55764)     { eliminateOption(N_OUTCOMES, ans, 0); }
    if (vBalance > 0.5427)          { eliminateOption(N_OUTCOMES, ans, 9); }
    if (hBalance > 0.5123)          { eliminateOption(N_OUTCOMES, ans, 6); }
    if (holeDensity > 0.1626)       { eliminateOption(N_OUTCOMES, ans, 4); }
    if (blackDensity > 0.5994)      { eliminateOption(N_OUTCOMES, ans, 4); }

    // Filter Largest Minimums
    if (vHoleBalance < 0.62004)     { eliminateOption(N_OUTCOMES, ans, 6); }
    if (hHoleBalance < 0.44537)     { eliminateOption(N_OUTCOMES, ans, 0); }
    if (hBalance < 0.4692)          { eliminateOption(N_OUTCOMES, ans, 9); }
    if (vBalance < 0.4602)          { eliminateOption(N_OUTCOMES, ans, 6); }
    if (blackDensity < 0.3275)      { eliminateOption(N_OUTCOMES, ans, 9); }
    if (holeDensity < 0.1174)       { eliminateOption(N_OUTCOMES, ans, 0); }

    if (indexOfI(N_OUTCOMES, ans, -1) == -1) {
        return -1;
    }
    if (vHoleBalance > 0.620032) {
        return 6;
    }
    if (vHoleBalance < 0.375365) {
        return 9;
    }

    return rangeMethod(N_OUTCOMES, N_FEATURES, allMaxes, allMins, vals, ans);
}