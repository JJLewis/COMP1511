//
// Created by Jordan Lewis on 27/4/17.
//

#include "captcha.h"
#include "neighbours.h"
#include "handy.h"

void replaceAll(int height, int width, int pixels[height][width], int num, int withNum) {
    for (int v = 0; v < height; v++) {
        for (int h = 0; h < width; h++) {
            if (pixels[v][h] == num) {
                pixels[v][h] == withNum;
            }
        }
    }
}

coord_t findFirst(int height, int width, int pixels[height][width], int num, coord_t after) {
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

int aKindaFloodFill(int height, int width, int pixels[height][width], int orig, int wall, int enc) {
    coord_t start;
    start.x = -1;
    start.y = -1;
    coord_t first = findFirst(pixels, height, width, orig, start);
    int didChange = FALSE;

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

void vertFlip(int height, int width, int source[height][width], int output[height][width]) {
    for (int i = 0; i < height; i++) {
        copyRow(source, output, height, width, height - i - 1, i);
    }
}

void horFlip(int height, int width, int source[height][width], int output[height][width]) {
    for (int v = 0; v < height; v++) {
        for (int h = 0; h < width; h++) {
            output[v][h] = source[v][width - h - 1];
        }
    }
}

int countHoles(int height, int width, int pixels[height][width]) {
    coord_t start;
    start.x = -1;
    start.y = -1;
    if (findFirst(pixels, height, width, 1, start).x == -1) {
        return FALSE;
    }

    int numHoles = 1;
    int wasPrevRowBlank = FALSE;

    int startRow, startCol, boxHeight, boxWidth;
    get_bounding_box(height, width, pixels, &startRow, &startCol, &boxHeight, &boxWidth);
    int extracted[boxHeight][boxWidth];
    copy_pixels(boxHeight, boxWidth, pixels, startRow, startCol, boxHeight, boxWidth, extracted);

    for (int v = 0; v < boxHeight; v++) {
        int hasFound1 = FALSE;
        for (int h = 0; h < boxWidth; h++) {
            if (extracted[v][h] == 1) {
                hasFound1 = TRUE;
                break;
            }
        }
        if (!hasFound1 && !wasPrevRowBlank) {
            numHoles++;
            wasPrevRowBlank = TRUE;
        }
    }

    return numHoles;
}

void isolateHoles(int height, int width, int pixels[height][width], int output[height][width]) {
    int encNum = 3;
    int didChange = TRUE;

    // isolate the number of holes
    aKindaFloodFill(pixels, height, width, 0, 2, 3);

    int flipped1[height][width], flipped2[height][width];

    vertFlip(height, width, pixels, flipped1);
    horFlip(height, width, flipped1, flipped2);
    aKindaFloodFill(height, width, flipped2, encNum, 2, encNum + 1);
    encNum++;

    horFlip(height, width, flipped2, flipped1);
    aKindaFloodFill(height, width, flipped1, encNum, 2, encNum + 1);
    encNum++;

    horFlip(height, width, flipped1, flipped2);
    aKindaFloodFill(height, width, flipped2, encNum, 2, encNum + 1);
    encNum++;

    while (didChange) {
        didChange = aKindaFloodFill(height, width, flipped2, encNum, 2, encNum + 1);
        encNum++;
    }

    replaceAll(height, width, flipped2, 2, 3);
    replaceAll(height, width, flipped2, 1, 3);
    replaceAll(height, width, flipped2, 3, 0);
    replaceAll(height, width, flipped2, encNum, 1);

    copyArray(height, width, flipped2, output);
}

int numberOfHoles(int height, int width, int pixels[height][width]) {
    int isolated[height][width];
    isolateHoles(height, width, pixels, isolated);
    return countHoles(height, width, isolated);
}