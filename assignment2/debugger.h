//
// Created by Jordan Lewis on 29/4/17.
//

#ifndef SRC_DEBUGGER_H
#define SRC_DEBUGGER_H

#endif //SRC_DEBUGGER_H

#include "structs.h"

#define IS_DEBUGGING 1

// debugger.c
void print(char *s);
void println();
void printD(double x);
void printI(int x);
void printarrI(int size, int array[size]);
void printarrD(int size, double array[size]);
void print2darrI(int height, int width, int array[height][width]);
void throw_warning(char *s);

// print_world.c
void print_target_destination(location_t loc);
void print_array_of_locations(location_t locations[], int size);
void print_location(location_t loc);
void print_world(struct bot *b);