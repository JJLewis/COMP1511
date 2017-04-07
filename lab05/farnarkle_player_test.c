#include <stdio.h>
#include "farnarkle.h"

// read N_TILES tiles into array tiles
// return 1 if successful, 0 otherwise
static int read_tiles1(int tiles[N_TILES]) {
    int i;

    i = 0;
    while (i < N_TILES) {
        if (scanf("%d", &tiles[i]) != 1) {
            return 0;
        }
        if (tiles[i] < 1 || tiles[i] > MAX_TILE) {
            return 0;
        }
        i = i + 1;
    }
    return 1;
}

// print tiles on a single line
static void print_tiles1(int tiles[N_TILES]) {
    int i;

    i = 0;
    while (i < N_TILES) {
        printf("%d", tiles[i]);
        if (i < N_TILES - 1) {
            printf(" ");
        }
        i = i + 1;
    }
    printf("\n");
}

static int count_farnarkles1(int sequence1[N_TILES], int sequence2[N_TILES]) {
    int i, n_farnarkles;

    n_farnarkles = 0;
    i = 0;
    while(i < N_TILES) {
        if (sequence1[i] == sequence2[i]) {
            n_farnarkles = n_farnarkles + 1;
        }
        i = i + 1;
    }
    return n_farnarkles;
}

static int count_arkles1(int sequence1[N_TILES], int sequence2[N_TILES]) {
    int i, j, n_arkles;
    int tile_used1[N_TILES] = {0};
    int tile_used2[N_TILES] = {0};

    // note tiles used in a farnarkle
    i = 0;
    while (i < N_TILES) {
        if (sequence1[i] == sequence2[i]) {
            tile_used1[i] = 1;
            tile_used2[i] = 1;
        }
        i = i + 1;
    }
    n_arkles = 0;
    i = 0;
    while (i < N_TILES) {
        j = 0;
        while (j < N_TILES) {

            // if the tiles in positions i and j are an arnakle
            // and the tiles have not been used in an arkle or farnarkle

            if ((sequence1[i] == sequence2[j]) && (tile_used1[i] == 0) && (tile_used2[j] == 0)) {
                n_arkles = n_arkles + 1;
                tile_used1[i] = 1;
                tile_used2[j] = 1;
            }
            j = j + 1;
        }
        i = i + 1;
    }
    return n_arkles;
}

// an automated farnarkle_player
// given all previous guesses and their farnarkles and arkle counts
// make a new guess
//
// inputs:
// turn - which turn this is
// previous_guesses contains the turn - 1 previous_guesses
// farnarkles[i] contains the number of farnarkles for previous_guess[i]
// arkles[i] contains the number of arkles for previous_guess[i]
//
// output:
// guess - the next guess

int main(void) {
    int hidden_code[N_TILES];
    int turn, previous_guesses[MAX_TURNS][N_TILES], farnarkles[MAX_TURNS], arkles[MAX_TURNS];
    int guess[N_TILES];
    read_tiles1(hidden_code);
    turn = 0;
    printf("Hidden code: ");
    print_tiles1(hidden_code);
    while (read_tiles1(previous_guesses[turn])) {
        farnarkles[turn] = count_farnarkles1(hidden_code, previous_guesses[turn]);
        arkles[turn] = count_arkles1(hidden_code, previous_guesses[turn]);
        printf("Previous guess: ");
        print_tiles1(previous_guesses[turn]);
        printf("%d farnarkles\n", farnarkles[turn]);
        printf("%d arkles\n", arkles[turn]);
        turn = turn + 1;
    }
    farnarkle_player(turn + 1, previous_guesses, farnarkles, arkles, guess);
    printf("Guess: ");
    print_tiles1(guess);
}
