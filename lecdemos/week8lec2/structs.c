//
// Created by Jordan Lewis on 26/4/17.
//

#include <stdio.h>

struct date {
    int day;
    int month;
    int year;
};

int main(void) {

    struct date date1;

    date1.day = 1;

    datep = &date1;

    datep->day = 2;

    printf("%d", date1.day);

    return 0;
}