//
// Created by Jordan Lewis on 27/4/17.
//

#ifndef SRC_HANDY_H
#define SRC_HANDY_H

#endif //SRC_HANDY_H

void copyArray(int height, int width, int source[height][width], int destination[height][width]);
void copyRow(int height, int width, int source[height][width], int destination[height][width], int sIndex, int dIndex);

void assignRow(int height, int width, double destination[height][width], double row[width], int atIndex);

double minElementD(int size, double array[size]);

int maxElementI(int size, int array[size]);

int indexOfI(int size, int array[size], int element);
int indexOfD(int size, double array[size], int element);