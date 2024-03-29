//
// Created by Jordan Lewis on 29/4/17.
//

#ifndef SRC_DEBUGGER_H
#define SRC_DEBUGGER_H

#endif //SRC_DEBUGGER_H

#define IS_DEBUGGING 0

void print(char s[]);

void println();

void printD(double x);
void printI(int x);

void printarrI(int size, int array[size]);
void printarrD(int size, double array[size]);

void print2darrI(int height, int width, int array[height][width]);