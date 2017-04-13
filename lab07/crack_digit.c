// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// Apr 13 2017
//

#include <stdio.h>
#include "captcha.h"

int main(int argc, char *argv[]) {
    int height, width, start_row, start_column, box_width, box_height;
    double balance;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <image-file>\n", argv[0]);
        return 1;
    }

    if (get_pbm_dimensions(argv[1], &height, &width) != 1) {
        return 1;
    }

    int pixels[height][width];
    if (read_pbm(argv[1], height, width, pixels)) {
        get_bounding_box(height, width, pixels, &start_row, &start_column, &box_height, &box_width);

        int box_pixels[box_height][box_width];
        copy_pixels(height, width, pixels, start_row, start_column, box_height, box_width, box_pixels);

        balance = get_horizontal_balance(box_height, box_width, box_pixels);
	
	if (balance < 0.5) {
		printf("6");
	} else {
		printf("3");
	}
	printf("\n");

        //printf("Horizontal balance %.3lf\n", balance);
    }
    return 0;
}

