#!/bin/bash

gcc crack_captcha.c split_captcha.c debugger.c balances.c bounding_box.c copy_pixels.c feature_array.c half_image_features.c handy.c hole_count.c manual_guess.c neighbours.c other_metrics.c print_image.c read_pbm.c guess_has_hole.c guess_functions.c guess_no_holes.c -o crack_captcha

