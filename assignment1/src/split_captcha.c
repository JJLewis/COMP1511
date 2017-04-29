//
// Created by Jordan Lewis on 30/4/17.
//

#include "captcha.h"
#include <stdio.h>

void get_first_number(int height, int width, int pixels[height][width],
                   int *nHeight, int *nWidth, int firstNumber[height][width],
                   int *rHeight, int *rWidth, int remainder[height][width]) {

    int cutAt = -1;
    for (int h = 0; h < width; h++) {
        int found1 = FALSE;
        for (int v = 0; v < height; h++) {
            if (pixels[v][h] == 1) {
                found1 = TRUE;
                break;
            }
        }
        if (found1) {
            cutAt = h;
            break;
        }
    }

    if (cutAt != -1) {
        int startRow, startCol, boxHeight, boxWidth;

        int tempNum[height][cutAt];
        copy_pixels(height, width, pixels, 0, 0, height, cutAt, tempNum);
        get_bounding_box(height, cutAt, tempNum, &startRow, &startCol, &boxHeight, &boxWidth);
        copy_pixels(height, cutAt, tempNum, startRow, startCol, boxHeight, boxWidth, firstNumber);
        *nHeight = boxHeight;
        *nWidth = boxWidth;

        int tempRemainder[height][width - cutAt];
        copy_pixels(height, width, pixels, 0, cutAt, height, width - cutAt, tempRemainder);
        get_bounding_box(height, width - cutAt, pixels, &startRow, &startCol, &boxHeight, &boxWidth);
        copy_pixels(height, width - cutAt, tempRemainder, startRow, startCol, boxHeight, boxWidth, remainder);
        *rHeight = boxHeight;
        *rWidth = boxWidth;
    }
}

void crack_captcha(int height, int width, int pixels[height][width]) {

    int remainder1[height][width];
    int r1H, r1W;

    int remainder2[height][width];
    int r2H, r2W;

    int num[height][width];
    int nH, nW;

    get_first_number(height, width, pixels, &nH, &nW, num, &r1H, &r1W, remainder1);
    int guess1 = crack(nH, nW, num);

    get_first_number(r1H, r1W, remainder1, &nH, &nW, num, &r2H, &r2W, remainder2);
    int guess2 = crack(nH, nW, num);

    get_first_number(r2H, r2W, remainder2, &nH, &nW, num, &r1H, &r1W, remainder1);
    int guess3 = crack(nH, nW, num);

    get_first_number(r1H, r1W, remainder1, &nH, &nW, num, &r2H, &r2W, remainder2);
    int guess4 = crack(nH, nW, num);

    printf("%d%d%d%d\n", guess1, guess2, guess3, guess4);
}