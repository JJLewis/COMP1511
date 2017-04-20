//
// Created by Jordan Lewis on 17/4/17.
//

#include "crack_captcha.h"
#include <time.h>
#include <stdlib.h>

double sigmoid(double t, int deriv) {
    if (deriv) {
        return t * (1 - t);
    }
    return 1.0 / (1.0 + exp(-t));
}

void randMatrix(int height, int width, int matrix[height][width]) {
    int h = 0;
    while (h < height) {
        int w = 0;
        while (w < width) {
            matrix[h][w] = rand();
        }
    }
}