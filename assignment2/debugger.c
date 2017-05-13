//
// Created by Jordan Lewis on 29/4/17.
//

/*
 *      This whole file is a just a bunch of handy print shortcuts I can use elsewhere and make shut-up when needed.
 */

#include <stdio.h>
#include "debugger.h"

void print(char *s) {
    if (IS_DEBUGGING) {
        printf("%s\n", s);
    }
}

void println() {
    if (IS_DEBUGGING) {
        printf("------------------------------\n");
    }
}

void printD(double x) {
    if (IS_DEBUGGING) {
        printf("%lf\n", x);
    }
}

void printI(int x) {
    if (IS_DEBUGGING) {
        printf("%d\n", x);
    }
}

void printarrI(int size, int array[size]) {
    if (IS_DEBUGGING) {
        printf("[");
        for (int i = 0; i < size - 1; i++) {
            printf("%d, ", array[i]);
        }
        printf("%d]\n", array[size - 1]);
    }
}

void printarrD(int size, double array[size]) {
    if (IS_DEBUGGING) {
        printf("[");
        for (int i = 0; i < size - 1; i++) {
            printf("%lf, ", array[i]);
        }
        printf("%lf]\n", array[size - 1]);
    }
}

void print2darrI(int height, int width, int array[height][width]) {
    if (IS_DEBUGGING) {
        printf("[\n");
        for (int i = 0; i < height; i++) {
            printarrI(width, array[i]);
        }
        printf("]\n");
    }
}

void throw_warning(char *s) {
    if (IS_DEBUGGING) {
        println();
        printf("WARNING:: ");
        print(s);
        println();
    }
}