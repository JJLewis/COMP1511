//
// Created by Jordan Lewis on 30/4/17.
//

#include "captcha.h"
#include "tester.h"
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

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