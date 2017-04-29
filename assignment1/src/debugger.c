//
// Created by Jordan Lewis on 29/4/17.
//

#include <stdio.h>
#include "debugger.h"

void println() {
    printf("------------------------------\n");
}

void printD(double x) {
    printf("%lf\n", x);
}
void printI(int x) {
    printf("%d\n", x);
}

void printarrI(int size, int array[size]) {
    printf("[");
    for (int i = 0; i < size - 1; i++) {
        printf("%d, ", array[i]);
    }
    printf("%d]\n", array[size - 1]);
}

void printarrD(int size, double array[size]) {
    printf("[");
    for (int i = 0; i < size - 1; i++) {
        printf("%lf, ", array[i]);
    }
    printf("%lf]\n", array[size - 1]);
}

void print2darrI(int height, int width, int array[height][width]) {
    printf("[\n");
    for (int i = 0; i < height; i++) {
        printarrI(width, array[i]);
    }
    printf("]\n");
}