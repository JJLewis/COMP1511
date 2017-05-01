//
// Created by Jordan Lewis on 27/4/17.
//

#ifndef SRC_NEIGHBOURS_H
#define SRC_NEIGHBOURS_H

#endif //SRC_NEIGHBOURS_H

#define EDGE -1

int isXonRight  (int height, int width, int pixels[height][width], coord_t location, int x);
int isXonLeft   (int height, int width, int pixels[height][width], coord_t location, int x);
int isXonTop    (int height, int width, int pixels[height][width], coord_t location, int x);
int isXonBottom (int height, int width, int pixels[height][width], coord_t location, int x);

int isNextTo    (int height, int width, int pixels[height][width], coord_t location, int x);