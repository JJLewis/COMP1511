//
// Created by Jordan Lewis on 30/4/17.
//

#include <stdio.h>
#include "captcha.h"
#include <stdlib.h>
#include "debugger.h"

/*
 * Takes a filename (path to pbm file) and prints a guess for the Captcha.
 *
 * input: filename[]: A path to a pbm file.
 */
void getCaptchaGuess(char filename[]) {
    int height, width;
    int start_row, start_column, box_width, box_height;

    if (get_pbm_dimensions(filename, &height, &width) != 1) {
        return ;
    }

    int pixels[height][width];
    if (read_pbm(filename, height, width, pixels)) {
        get_bounding_box(height, width, pixels, &start_row, &start_column, &box_height, &box_width);

        int box_pixels[box_height][box_width];
        copy_pixels(height, width, pixels, start_row, start_column, box_height, box_width, box_pixels);

        crack_captcha(box_height, box_width, box_pixels);
    }
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <image-file>\n", argv[0]);
        return 1;
    }

    getCaptchaGuess(argv[1]);

    return 0;
}
