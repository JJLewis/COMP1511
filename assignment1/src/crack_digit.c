// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// Apr 13 2017
//

#include <stdio.h>
#include "captcha.h"
#include <stdlib.h>
#include <strings.h>
#include "debugger.h"

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

// Jared Steiner: I love you
void make_filename(int num, int ver, char filename[30]) {

    int pointer_point = 0;

    pointer_point += sprintf(filename, "../pbms/digit/");
    pointer_point += sprintf(filename + pointer_point,"%d", num);
    pointer_point += sprintf(filename + pointer_point, "_");
    if (ver < 10) {
        sprintf(filename + pointer_point, "0%d.pbm", ver);
    } else {
        sprintf(filename + pointer_point, "%d.pbm", ver);
    }
}

int guessFile(int n, int f) {
    char filedir[30];
    make_filename(n, f, filedir);
    return getGuess(filedir);
}

int guessAllForNum(int n) {
    int numWrong = 0;
    for (int f = 0; f < 100; f++) {
        int guess = guessFile(n, f);
        if (guess != n) {
            printI(guess);
            numWrong++;
        }
    }
    print("Num Wrong: ");
    printI(numWrong);
    return numWrong;
}

int testAllNumbers() {
    int totalWrong = 0;
    for (int n = 0; n < 10; n++) {
        totalWrong += guessAllForNum(n);
    }
    print("Total Wrong: ");
    printI(totalWrong);
    return totalWrong;
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
    printf("%d\n", guess);

    return 0;
}

