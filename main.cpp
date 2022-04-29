#include <mpi.h>
#include "includes.h"
#include "board_rep.cpp"
#include "board.cpp"
#include "search.cpp"
#include "parse_inp.cpp"
#include "init.cpp"
#include "parallel.cpp"

// Global Variables.
struct board* b;
int directionOffsets[] = {-8, 8, -1, 1, -9, 9, -7, 7};
int numSquaresToEdge[64][8];
std::vector<struct move> moves;
char board_start[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w";
int moves_ctr = 0;
struct move best_move;
int global_depth = 5;
int myrank, npes;

// Driver code.
int main (int argc, char** argv) {

  srand(time(NULL));
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &npes);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

  if (myrank == 0) {
	  printf("Welcome to chess!\n");

    play();

	  printf("Thanks for playing!\n");
  } else {
    consumer();
  }
  MPI_Finalize();
}

