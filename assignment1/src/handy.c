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

double minElement(int size, double array[size]) {
    double smallest = array[0];
    for (int i = 0; i < size; i++) {
        if (array[i] < smallest) {
            smallest = array[i];
        }
    }
    return smallest;
}

int indexOf(int size, double array[size], int element) {
    for (int i = 0; i < size; i++) {
        if (array[i] == element) {
            return i;
        }
    }
    return -1;
}