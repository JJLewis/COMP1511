//
// Created by Jordan Lewis on 27/4/17.
//

#include "captcha.h"
#include "neighbours.h"

int isXonRight(int pixels[height][width], int height, int width, coord_t location, int x) {
    if (x == EDGE) {
        return location.x + 1 == width;
    }
    if (location.x + 1 == width) {
        return FALSE;
    } else {
        return pixels[location.y][location.x + 1] == x;
    }
}

int isXonLeft(int pixels[height][width], int height, int width, coord_t location, int x) {
    if (x == EDGE) {
        return location.x == 0;
    }
    if (location.x == 0) {
        return FALSE;
    } else {
        pixels[location.y][location.x - 1] == x;
    }
}

int isXonTop(int pixels[height][width], int height, int width, coord_t location, int x) {
    if (x == EDGE) {
        return location.x + 1 == height;
    }
    if (location.x + 1 == height) {
        return FALSE;
    } else {
        return pixels[location.y + 1][location.x] == x;
    }
}

int isXonBottom(int pixels[height][width], int height, int width, coord_t location, int x) {
    if (x == EDGE) {
        return location.x - 1 == height;
    }
    if (location.x == 0) {
        return FALSE;
    } else {
        return pixels[location.y - 1][location.x] == x;
    }
}

int isNextTo(int pixels[height][width], int height, int width, coord_t location, int x) {
    int isAboveBelow = isXonTop(pixels, height, width, location, x) || isXonBottom(pixels, height, width, location, x);
    int isBeside = isXonLeft(pixels, height, width, location, x) || isXonRight(pixels, height, width, location, x);
    return isAboveBelow || isBeside;
}