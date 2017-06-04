//
// Created by Jordan Lewis on 13/5/17.
//

#include "handy.h"

/*
 * Finds and return the largest double element in array.
 */
double maxElementD(int size, double array[size]) {
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
 * Find the coordinates of the largest element in a matrix.
 */
double coord_of_max_D(int height, int width, double matrix[height][width], int *row, int *column) {
    double largest = matrix[0][0];
    int lRow = 0;
    int lCol = 0;
    for (int v = 0; v < height; v++) {
        for (int h = 0; h < width; h++) {
            if (matrix[v][h] > largest) {
                lRow = v;
                lCol = h;
                largest = matrix[v][h];
            }
        }
    }

    *row = lRow;
    *column = lCol;
    return largest;
}

/*
 * Finds the smallest integer element in an array of integers.
 */
int smallestElementI(int size, int array[size]) {
    int smallest = array[0];
    for (int i = 0; i < size; i++) {
        if (array[i] < smallest) {
            smallest = array[i];
        }
    }
    return smallest;
}