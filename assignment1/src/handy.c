//
// Created by Jordan Lewis on 27/4/17.
//

#include "handy.h"

void copyArray(int source[height][width], int destination[height][width], int height, int width) {
    for (int v = 0; v < height; v++) {
        for (int h = 0; h < width; h++) {
            destination[v][h] = source[v][h];
        }
    }
}

void assignRow(int source[height][width],
               int destination[height][width],
               int height, int width,
               int sIndex, int dIndex) {
    for (int i = 0; i < width; i++) {
        destination[dIndex][i] = source[sIndex][i];
    }
}