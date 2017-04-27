//
// Created by Jordan Lewis on 27/4/17.
//

#ifndef SRC_NEIGHBOURS_H
#define SRC_NEIGHBOURS_H

#endif //SRC_NEIGHBOURS_H

#define EDGE -1

int isXonRight  (int pixels[height][width], int height, int width, coord_t location, int x);
int isXonLeft   (int pixels[height][width], int height, int width, coord_t location, int x);
int isXonTop    (int pixels[height][width], int height, int width, coord_t location, int x);
int isXonBottom (int pixels[height][width], int height, int width, coord_t location, int x);

int isNextTo    (int pixels[height][width], int height, int width, coord_t location, int x);