//
// Created by Jordan Lewis on 17/4/17.
//

#define TRUE 1
#define FALSE 0

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
double horizontalHoleBalance(int pixels[height][width], int height, int width);
double verticalHoleBalance(int pixels[height][width], int height, int width);

// hole_count.c
void isolateHoles(int pixels[height][width], int output[height][width], int height, int width);
int numberOfHoles(int pixels[height][width], int height, int width);

// other_metrics.c
double getDensity(int pixels[height][width], int height, int width);
double getHoleFraction(int pixels[height][width], int height, int width);