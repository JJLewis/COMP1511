//
// Created by Jordan Lewis on 27/4/17.
//

#include "captcha.h"
#include "neighbours.h"
#include "handy.h"

void replaceAll(int pixels[height][width], int height, int width, int num, int withNum) {
    for (int v = 0; v < height; v++) {
        for (int h = 0; h < width; h++) {
            if (pixels[v][h] == num) {
                pixels[v][h] == withNum;
            }
        }
    }
}

coord_t findFirst(int pixels[height][width], int height, int width, int num, coord_t after) {
    coord_t location;
    location.x = -1;
    location.y = -1;
    for (int v = 0; v < height; v++) {
        for (int h = 0; h < width; h++) {
            if (pixels[v][h] == num) {
                location.y = v;
                location.x = h;
                if (v > after.y) {
                    return location;
                } else if (h > after.x) {
                    return location;
                }
            }
        }
    }
    return location;
}

int aKindaFloodFill(int pixels[height][width], int height, int width, int orig, int wall, int enc) {
    coord_t start;
    start.x = -1;
    start.y = -1;
    coord_t first = findFirst(pixels, height, width, orig, start);
    didChange = FALSE;

    // Repeat until the original number is no longer found
    while (first.x != -1) {
        int setTo = -1;

        // Decide whether the pixel should be an outside space, or an enclosed space
        if (isNextTo(pixels, height, width, first, EDGE) || isNextTo(pixels, height, width, first, wall)) {
            setTo = wall;
            didChange = TRUE;
        } else if (isNextTo(pixels, height, width, first, 1) || isNextTo(pixels, height, width, first, enc)) {
            setTo = enc;
        }

        // Set the current target pixel to the new value
        pixels[first.y][first.x] = setTo;

        // Set the pixel above the target to the new value if possible
        if (first.y + 1 < height) {
            if (isXonTop(pixels, height, width, first, orig)) {
                pixels[first.y + 1][first.x] = setTo;
            }
        }

        // Set the pixel to the right of the target to the new value if possible
        if (first.x + 1 < width) {
            if (isXonRight(pixels, height, width, first, orig)) {
                pixels[first.y][first.x + 1] = setTo;
            }
        }

        // Find the next pixel to test, check, and change
        first = findFirst(pixels, height, width, orig, first);
    }

    return didChange;
}

