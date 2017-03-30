// Jordan Lewis (jordan.lewis@student.unsw.edu.au)
// Mar 25 2017
//

#define N_TILES 4
#define MAX_TILE 8

int read_tiles(int tiles[N_TILES]);
void print_tiles(int tiles[N_TILES]);

int count_farnarkles(int seq1[N_TILES], int seq2[N_TILES]);
int count_arkles(int seq1[N_TILES], int seq2[N_TILES]);

int int_exists(int num, int arr[N_TILES]);
int array_with_equal_elements(int num, int arr[N_TILES]);

void create_random_tiles(int tiles[N_TILES]);

#define MAX_TURNS 100

void farnarkle_player(int turn, int previous_guesses[MAX_TURNS][N_TILES], int farnarkles[MAX_TURNS], int arkles[MAX_TURNS], int guess[N_TILES]);
