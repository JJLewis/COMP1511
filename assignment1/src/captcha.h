//
// Created by Jordan Lewis on 17/4/17.
//

#include "debugger.h"

#define TRUE 1
#define FALSE 0

#define NUM_FEATURES 10
#define H_NUM_FEATURES 5

struct coord {
	int x;
	int y;
};

typedef struct coord coord_t;

int read_pbm(char filename[], int height, int width, int pixels[height][width]);

int get_pbm_dimensions(char filename[], int *height, int *width);

void print_image(int height, int width, int pixels[height][width]);

void get_bounding_box(int height, int width, int pixels[height][width],
		                  int *start_row, int *start_column, int *box_height, int *box_width);

void copy_pixels(int height, int width, int pixels[height][width],
		                 int start_row, int start_column, int copy_height, int copy_width,
				                  int copy[copy_height][copy_width]);

// balances.h
double get_horizontal_balance(int height, int width, int pixels[height][width]);
double get_vertical_balance(int height, int width, int pixels[height][width]);
double get_horizontal_hole_balance(int height, int width, int pixels[height][width]);
double get_vertical_hole_balance(int height, int width, int pixels[height][width]);

// hole_count.c
int countHoles(int height, int width, int pixels[height][width]);
void isolateHoles(int height, int width, int pixels[height][width], int output[height][width]);
int numberOfHoles(int height, int width, int pixels[height][width]);

// other_metrics.c
double get_density(int height, int width, int pixels[height][width]);
double get_hole_fraction(int height, int width, int pixels[height][width]);

// feature_array.c
void get_image_features(int height, int width, int pixels[height][width], double features[NUM_FEATURES]);

// half_image_features.c
void get_halved_features(int height, int width, int pixels[height][width], double features[H_NUM_FEATURES], int side);

// manual_guess.c
int crack(int height, int width, int pixels[height][width]);

// crack_digit.c
int getGuess(char filename[]);