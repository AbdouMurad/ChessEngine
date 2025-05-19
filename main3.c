#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Board2.h"
#include "AlphaBeta3.h"

void moveInput(int *start, int *end){
    printf("Which piece to move?\n");
    scanf("%d",start);
    printf("Where to?\n");
    scanf("%d",end);
}

//time to beat: 1.798 

int main(){
    struct gameBoard Game;
    //setupBlankGame(&Game);
    setupGame(&Game);
    struct MoveList l;
    generateMoves(&Game, &l, White);
    //printMoves(&l);


    struct Move move;
    int eval = alphabeta(DEPTH, &Game, White, -10000000, 10000000, 1, &move);
    printf("Start: %d End: %d Piece: %d maxEval: %d\n",move.start,move.end,move.piece, eval);
    PrintBoard(&Game, move.start, move.end);

}
