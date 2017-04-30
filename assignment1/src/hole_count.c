//
// Created by Jordan Lewis on 27/4/17.
//

#include "captcha.h"
#include "neighbours.h"
#include "handy.h"
#include <stdio.h>
#include "debugger.h"

/*
 * Searches through a 2D array and replaces every element equal to num, with withNum.
 * NOTE: This directly changes the array that is passed into it.
 */
void replaceAll(int height, int width, int pixels[height][width], int num, int withNum) {
    for (int v = 0; v < height; v++) {
        for (int h = 0; h < width; h++) {
            if (pixels[v][h] == num) {
                pixels[v][h] = withNum;
            }
        }
    }
}

/*
 * Find the coordinates (row and column index) of the first instance of num in pixels[height][width] after a given point
 * If it cannot find it, return (-1,-1).
 *
 * input:
 *          num: The target number that the function is looking for.
 *          coord_t after: Start searching after this location.
 *
 * output: Returns a coord_t containing the location of first instance of num after (coord_t) after.
 */
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

/*
 * My attempt at a flood fill.
 * Works by comparing neighbours and assigning the the current pixel and the pixels above and to the right (if possible)
 * to the a number.
 * This function should be run several times to ensure optimal outcomes.
 *
 * inputs:
 *          orig: The number denoting blank spaces.
 *          wall: A number denoting pixels connected to edges of the image.
 *          enc: A number denoting pixels that are in an enclosed area.
 *
 * output: Returns a integer (boolean) reflecting whether or not the array was changed.
 */
int aKindaFloodFill(int height, int width, int pixels[height][width], int orig, int wall, int enc) {
    coord_t start;
    start.x = -1;
    start.y = -1;
    coord_t first = findFirst(height, width, pixels, orig, start);
    int didChange = FALSE;

    // Repeat until the original number is no longer found
    while (first.x != -1) {
        int setTo = -1;

        // Decide whether the pixel should be an outside space, or an enclosed space
        if (isNextTo(height, width, pixels, first, EDGE) || isNextTo(height, width, pixels, first, wall)) {
            setTo = wall;
            didChange = TRUE;
        } else if (isNextTo(height, width, pixels, first, 1) || isNextTo(height, width, pixels, first, enc)) {
            setTo = enc;
        }

        // Set the current target pixel to the new value
        pixels[first.y][first.x] = setTo;

        // Set the pixel above the target to the new value if possible
        if (first.y + 1 < height) {
            if (isXonTop(height, width, pixels, first, orig)) {
                pixels[first.y + 1][first.x] = setTo;
            }
        }

        // Set the pixel to the right of the target to the new value if possible
        if (first.x + 1 < width) {
            if (isXonRight(height, width, pixels, first, orig)) {
                pixels[first.y][first.x + 1] = setTo;
            }
        }

        // Find the next pixel to test, check, and change
        first = findFirst(height, width, pixels, orig, first);
    }

    return didChange;
}

/*
 * Vertically flips the source array into output array.
 */
void vertFlip(int height, int width, int source[height][width], int output[height][width]) {
    for (int i = 0; i < height; i++) {
        copyRow(height, width, source, output, height - i - 1, i);
    }
}

/*
 * Horizontally flips the source array into the output array.
 */
void horFlip(int height, int width, int source[height][width], int output[height][width]) {
    for (int v = 0; v < height; v++) {
        for (int h = 0; h < width; h++) {
            output[v][h] = source[v][width - h - 1];
        }
    }
}

/*
 * Counts the number of holes in an image by looking for clear horizontal lines.
 *
 * outputs: Returns the number of holes.
 */
int countHoles(int height, int width, int isolated[height][width]) {
    coord_t start;
    start.x = -1;
    start.y = -1;
    if (findFirst(height, width, isolated, 1, start).x == -1) {
        return 0;
    }

    int numHoles = 1;
    int wasPrevRowBlank = FALSE;

    int startRow, startCol, boxHeight, boxWidth;
    get_bounding_box(height, width, isolated, &startRow, &startCol, &boxHeight, &boxWidth);

    // Get just the section of the images with the holes.
    int extracted[boxHeight][boxWidth];
    copy_pixels(height, width, isolated, startRow, startCol, boxHeight, boxWidth, extracted);

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

/*
 * Converts the pixels in a hole to 1s and all other pixels to 0s
 *
 * output:  output[height][width] is pixels array where the hole is 1s and all others are 0s.
 */
void isolateHoles(int height, int width, int pixels[height][width], int output[height][width]) {
    int encNum = 3;
    int didChange = TRUE;

    int pixelsCopy[height][width];
    copyArray(height, width, pixels, pixelsCopy);

    // isolate the number of holes
    aKindaFloodFill(height, width, pixelsCopy, 0, 2, 3);

    int flipped1[height][width], flipped2[height][width];

    // Repeat flipping and running my attempt at a flood fill several times
    vertFlip(height, width, pixelsCopy, flipped1);
    horFlip(height, width, flipped1, flipped2);
    aKindaFloodFill(height, width, flipped2, encNum, 2, encNum + 1);
    encNum++;

    horFlip(height, width, flipped2, flipped1);
    aKindaFloodFill(height, width, flipped1, encNum, 2, encNum + 1);
    encNum++;

    vertFlip(height, width, flipped1, flipped2);
    horFlip(height, width, flipped2, flipped1);
    aKindaFloodFill(height, width, flipped1, encNum, 2, encNum + 1);
    encNum++;

    horFlip(height, width, flipped1, flipped2);
    aKindaFloodFill(height, width, flipped2, encNum, 2, encNum + 1);
    encNum++;

    vertFlip(height, width, flipped2, flipped1);
    horFlip(height, width, flipped1, flipped2);
    aKindaFloodFill(height, width, flipped2, encNum, 2, encNum + 1);
    encNum++;

    // For any stray holes that shouldn't be there, keep running the loop until nothing changes.
    while (didChange) {
        didChange = aKindaFloodFill(height, width, flipped2, encNum, 2, encNum + 1);
        encNum++;
    }

    // Make all but the hole 0s
    // Replace 2s with 3s
    replaceAll(height, width, flipped2, 2, 3);
    // Replace 1s with 3s
    replaceAll(height, width, flipped2, 1, 3);
    // Replace 3s with 0s
    replaceAll(height, width, flipped2, 3, 0);

    // Make inside the hole 1s
    replaceAll(height, width, flipped2, encNum, 1);

    copyArray(height, width, flipped2, output);
}

/*
 * Given the pixel data for a number, return the number of holes found in it.
 *
 * output: Returns the number of holes in an image.
 */
int numberOfHoles(int height, int width, int pixels[height][width]) {
    int isolated[height][width];
    isolateHoles(height, width, pixels, isolated);
    return countHoles(height, width, isolated);
}