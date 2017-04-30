//
// Created by Jordan Lewis on 27/4/17.
//

#include "handy.h"

/*
 * Straight up duplicate's an array from a source to destination.
 * Good for having to do one time manipulations to an array.
 */
void copyArray(int height, int width, int source[height][width], int destination[height][width]) {
    for (int v = 0; v < height; v++) {
        for (int h = 0; h < width; h++) {
            destination[v][h] = source[v][h];
        }
    }
}

/*
 * Copies a row from a source 2D array to a destination 2D array.
 *
 * input:
 *          sIndex: Index of row to copy from source.
 *          dIndex: Index of destination row in destination.
 */
void copyRow(   int height, int width,
                int source[height][width],
                int destination[height][width],
                int sIndex, int dIndex) {
    for (int i = 0; i < width; i++) {
        destination[dIndex][i] = source[sIndex][i];
    }
}

/*
 * Assigns a 1D array to a row in a 2D array.
 *
 * input:
 *          row[width]: 1D array to be assigned to a row in destination 2D array.
 *                      Must have the same width as destination.
 *          atIndex: Destination index for the assignment.
 */
void assignRow(int height, int width, double destination[height][width], double row[width], int atIndex) {
    for (int i = 0; i < width; i++) {
        destination[atIndex][i] = row[i];
    }
}

/*
 * Finds and returns the smallest double element in array.
 */
double minElementD(int size, double array[size]) {
    double smallest = array[0];
    for (int i = 0; i < size; i++) {
        if (array[i] < smallest) {
            smallest = array[i];
        }
    }
    return smallest;
}

/*
 * Finds and return the largest integer element in array.
 */
int maxElementI(int size, int array[size]) {
    double largest = array[0];
    for (int i = 0; i < size; i++) {
        if (array[i] > largest) {
            largest = array[i];
        }
    }
    return largest;
}

/*
 * Find and returns the index of a given double element in array.
 */
int indexOfD(int size, double array[size], double element) {
    for (int i = 0; i < size; i++) {
        if (array[i] == element) {
            return i;
        }
    }
    return -1;
}

/*
 * Finds and returns the index of a given integer element in array.
 */
int indexOfI(int size, int array[size], int element) {
    for (int i = 0; i < size; i++) {
        if (array[i] == element) {
            return i;
        }
    }
    return -1;
}