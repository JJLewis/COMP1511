// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// Apr 13 2017
//

#include <stdio.h>
#include "captcha.h"
#include <stdlib.h>
#include "debugger.h"
#include "tester.h"

int getGuess(char filename[]) {
    int height, width;
    int start_row, start_column, box_width, box_height;

    if (get_pbm_dimensions(filename, &height, &width) != 1) {
        return 0;
    }

    int pixels[height][width];
    if (read_pbm(filename, height, width, pixels)) {
        get_bounding_box(height, width, pixels, &start_row, &start_column, &box_height, &box_width);

        int box_pixels[box_height][box_width];
        copy_pixels(height, width, pixels, start_row, start_column, box_height, box_width, box_pixels);

        int guess = crack(height, width, pixels);
        return guess;
    }
    return -1;
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <image-file>\n", argv[0]);
        return 1;
    }


    // Testing Code
    //int number = atoi(argv[1]);
    //guessFile(number, atoi(argv[2]));
    //guessAllForNum(number);
    //testAllNumbers();
    int guess = getGuess(argv[1]);
    printI(guess);

    return 0;
}

