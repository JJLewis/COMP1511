//
// Created by Jordan Lewis on 30/4/17.
//

#include "captcha.h"
#include <stdio.h>

/*
 * Finds and returns the column for the first clear column (column without any 1s).
 * If it is not found, it returns a -1.
 *
 * output: Returns the column for the first clear column, if not found, return -1.
 */
int findCut(int height, int width, int pixels[height][width]) {
    int cutAt = -1;
    for (int h = 0; h < width; h++) {
        int found1 = FALSE;
        for (int v = 0; v < height; v++) {
            if (pixels[v][h] == 1) {
                found1 = TRUE;
                break;
            }
        }
        if (!found1) {
            cutAt = h;
            break;
        }
    }
    return cutAt;
}

/*
 * Pulls out the first number of a sequence of numbers in an pbm, e.g. a Captcha
 *
 * input:
 *          pixels[height][width]: pbm array containing > 1 numbers
 *          nHeight, nWidth: Pointers to the height and width of the first number extracted from pixels
 *                           Will be assigned by the end of the function.
 *          firstNumber[height][width]: (OUTPUT) pbm array containing the first number that was extracted from pixels
 *          rHeight, rWidth: Pointers to the height and width of the remaining pixels after extracting the first number
 *                           Will be assigned by the end of the function.
 *          remainder[height][width]: (OUTPUT) The remaining pixel data for the remaining sequence of numbers.
 *                                    To be assigned by the end of this function.
 *
 * output:
 *          nHeight, nWidth: New height and width for firstNumber[height][width]
 *          firstNumber: Bounded pbm array containing the first number of the sequence
 *          rHeight, rWidth: New height and width for remainder[height][width]
 *          remainder[height][width]: Bounded pixel data containing the remaining sequence of numbers
 */
void get_first_number(  int height, int width, int pixels[height][width],
                        int *nHeight, int *nWidth, int firstNumber[height][width],
                        int *rHeight, int *rWidth, int remainder[height][width]) {

    // Find first clear vertical line
    int cutAt = findCut(height, width, pixels);

    if (cutAt != -1) {
        int startRow, startCol, boxHeight, boxWidth;

        int tempNum[height][cutAt];
        // Copy pixels to tempNum from start to end of the first number
        copy_pixels(height, width, pixels, 0, 0, height, cutAt, tempNum);
        // Get the bounding box of the first number
        get_bounding_box(height, cutAt, tempNum, &startRow, &startCol, &boxHeight, &boxWidth);
        // Copy the data within the above bounding box into the firstNumber (output) array
        copy_pixels(height, cutAt, tempNum, startRow, startCol, boxHeight, boxWidth, firstNumber);
        *nHeight = boxHeight;
        *nWidth = boxWidth;

        int tempRemainder[height][width - cutAt];
        // Copy from pixels to tempRemainder starting from the end of the number that was extracted to the end of the image.
        copy_pixels(height, width, pixels, 0, cutAt, height, width - cutAt, tempRemainder);
        // Bound the remainder
        get_bounding_box(height, width - cutAt, tempRemainder, &startRow, &startCol, &boxHeight, &boxWidth);
        copy_pixels(height, width - cutAt, tempRemainder, startRow, startCol, boxHeight, boxWidth, remainder);
        *rHeight = boxHeight;
        *rWidth = boxWidth;
    }
}

/*
 * Cracks a given Captcha image array, and prints the result.
 *
 * input:
 *          pixels[height][width]: Raw pixel data from the Captcha pbm file.
 */
void crack_captcha(int height, int width, int pixels[height][width]) {

    int remainder1[height][width];
    int r1H, r1W;

    int remainder2[height][width];
    int r2H, r2W;

    int num[height][width];
    int nH, nW;

    get_first_number(height, width, pixels, &nH, &nW, num, &r1H, &r1W, remainder1);
    int guess1 = crack(nH, nW, num);
    print_image(nH, nW, num);
    print_image(r1H, r1W, remainder1);
    println();

    get_first_number(r1H, r1W, remainder1, &nH, &nW, num, &r2H, &r2W, remainder2);
    int guess2 = crack(nH, nW, num);
    print_image(nH, nW, num);
    print_image(r2H, r2W, remainder2);
    println();

    get_first_number(r2H, r2W, remainder2, &nH, &nW, num, &r1H, &r1W, remainder1);
    int guess3 = crack(nH, nW, num);
    print_image(nH, nW, num);
    print_image(r1H, r1W, remainder1);
    println();

    int guess4 = crack(r1H, r1W, remainder1);
    print_image(r1H, r1W, remainder1);
    println();

    printf("%d%d%d%d\n", guess1, guess2, guess3, guess4);
}