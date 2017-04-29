//
// Created by Jordan Lewis on 27/4/17.
//

#include "captcha.h"
#include "neighbours.h"

int isXonRight(int height, int width, int pixels[height][width], coord_t location, int x) {
    if (x == EDGE) {
        return location.x + 1 == width;
    }
    if (location.x + 1 == width) {
        return FALSE;
    } else {
        return pixels[location.y][location.x + 1] == x;
    }
}

int isXonLeft(int height, int width, int pixels[height][width], coord_t location, int x) {
    if (x == EDGE) {
        return location.x == 0;
    }
    if (location.x == 0) {
        return FALSE;
    } else {
        return pixels[location.y][location.x - 1] == x;
    }
}

int isXonTop(int height, int width, int pixels[height][width], coord_t location, int x) {
    if (x == EDGE) {
        return location.y + 1 == height;
    }
    if (location.y + 1 == height) {
        return FALSE;
    } else {
        return pixels[location.y + 1][location.x] == x;
    }
}

int isXonBottom(int height, int width, int pixels[height][width], coord_t location, int x) {
    if (x == EDGE) {
        return location.y - 1 == 0;
    }
    if (location.y == 0) {
        return FALSE;
    } else {
        return pixels[location.y - 1][location.x] == x;
    }
}

int isNextTo(int height, int width, int pixels[height][width], coord_t location, int x) {
    int isAboveBelow = isXonTop(height, width, pixels, location, x) || isXonBottom(height, width, pixels, location, x);
    int isBeside = isXonLeft(height, width, pixels, location, x) || isXonRight(height, width, pixels, location, x);
    return isAboveBelow || isBeside;
}
