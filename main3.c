#include <stdio.h>
#include <string.h>
#include "Board2.h"
#include "AlphaBeta3.h"

void moveInput(struct gameBoard *Game, struct Move *Input, enum Color turn){
    printf("Which piece to move?\n");
    scanf("%d",&(Input->start));
    printf("Where to?\n");
    scanf("%d", &(Input->end));
    for (int i = 0; i < 6; ++i) {
        if ((1ULL << Input->start) & Game->game[turn][i]) {
            Input->piece = i;
            if (i == Pawn && Input->end == (7-7*turn)) {
                printf("What would you like the piece to promote to?\n");
                printf("Knight : 2 - Bishop : 3 - Rook : 4 - Queen : 5\n");
                int x;
                scanf("%d", &x);
                Input->promotion = x;
            }
        }
    }
}
void makeMove(struct gameBoard *Game, struct Move *Input, enum Color turn) {
    CheckCollision(1ULL << Input->start, Game, Game);
    CheckCollision(1ULL << Input->end, Game, Game);
    Game->game[turn][Input->piece] += (1ULL << Input->end);

    if (Input->piece == Pawn && Input->end/8 == (7-7*turn)) {
        Game->game[turn][Pawn] ^= (1ULL << Input->end);
        Game->game[turn][Input->promotion] |= (1ULL << Input->end);
    }
}

//time to beat: user - 0.967 

int main(){
    struct gameBoard Game;
    setupBlankGame(&Game);
    //setupGame(&Game);
    
    struct Move move;
    struct Move Input;
    struct MoveList moves;
    //PrintBoard(&Game, -1, -1);
    //generateMoves(&Game, &moves, White);
    //printMoves(&moves);
    


    //return 0;
    while (!gameOver(White, &Game) && !gameOver(Black, &Game)) {
        PrintBoard(&Game, -1, -1);
        int eval = alphabeta(DEPTH, &Game, White, -10000000, 10000000, 1, &move);
        printf("Start: %d End: %d Piece: %d maxEval: %d\n",move.start,move.end,move.piece, eval);
        makeMove(&Game, &move, White);
        PrintBoard(&Game, move.start, move.end);

        moveInput(&Game, &Input, Black);
        makeMove(&Game, &Input, Black);
        PrintBoard(&Game, Input.start, Input.end);
    }
    return 0;
    int eval = alphabeta(DEPTH, &Game, White, -10000000, 10000000, 1, &move);
    printf("Start: %d End: %d Piece: %d maxEval: %d\n",move.start,move.end,move.piece, eval);
    PrintBoard(&Game, move.start, move.end);

}
