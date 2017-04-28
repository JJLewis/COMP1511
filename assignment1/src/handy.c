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

void copyRow(int source[height][width],
               int destination[height][width],
               int height, int width,
               int sIndex, int dIndex) {
    for (int i = 0; i < width; i++) {
        destination[dIndex][i] = source[sIndex][i];
    }
}

void assignRow(int height, int width, double destination[height][width], double row[width], int atIndex) {
    for (int i = 0; i < width; i++) {
        destination[atIndex][i] = width[i];
    }
}

double minElementD(int size, double array[size]) {
    double smallest = array[0];
    for (int i = 0; i < size; i++) {
        if (array[i] < smallest) {
            smallest = array[i];
        }
    }
    return smallest;
}

int maxElementI(int size, int array[size]) {
    double largest = array[0];
    for (int i = 0; i < size; i++) {
        if (array[i] > largest) {
            largest = array[i];
        }
    }
    return largest;
}

int indexOfD(int size, double array[size], int element) {
    for (int i = 0; i < size; i++) {
        if (array[i] == element) {
            return i;
        }
    }
    return -1;
}

int indexOfI(int size, int array[size], int element) {
    for (int i = 0; i < size; i++) {
        if (array[i] == element) {
            return i;
        }
    }
    return -1;
}