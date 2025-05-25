#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Board.h"
#include "AlphaBeta3.h"

void moveInput(int *start, int *end){
    printf("Which piece to move?\n");
    scanf("%d",start);
    printf("Where to?\n");
    scanf("%d",end);
}

void setupBlankGame(struct gameBoard *game)
{
    // White Pieces
    (*game).whitePawns =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8
    (*game).whiteKnights =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x42, for knights on b1 & g1)
    0b00000000ULL;         // Row 8
    (*game).whiteBishops =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x24, for bishops on c1 & f1)
    0b00000000ULL;         // Row 8
    (*game).whiteRooks =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x81, for rooks on a1 & h1)
    0b00000000ULL;         // Row 8

    (*game).whiteQueen =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b000000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x10)
    0b00000000ULL;         // Row 8

    (*game).whiteKing =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x08)
    0b10000000ULL;         // Row 8

    (*game).whiteCastle = 3;

    // Black Pieces

    (*game).blackPawns =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b01100000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8

    (*game).blackKnights =
    0b00000000ULL << 56 |  // Row 1 (0x42)
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8

    (*game).blackBishops =
    0b00000000ULL << 56 |  // Row 1 (0x24)
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8

    (*game).blackRooks =
    0b00000000ULL << 56 |  // Row 1 (0x81)
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8

    (*game).blackQueen =
    0b00000000ULL << 56 |  // Row 1 (0x08)
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8

    (*game).blackKing =
    0b00000000ULL << 56 |  // Row 1 (0x10)
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b01000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8

    (*game).blackCastle = 3;

};
void setupGame(struct gameBoard *game){
    // White Pieces
    (*game).whitePawns =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b10110111ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8
    (*game).whiteKnights =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x42, for knights on b1 & g1)
    0b01000010ULL;         // Row 8
    (*game).whiteBishops =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x24, for bishops on c1 & f1)
    0b00100100ULL;         // Row 8
    (*game).whiteRooks =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x81, for rooks on a1 & h1)
    0b00000001ULL;         // Row 8

    (*game).whiteQueen =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x10)
    0b00010000ULL;         // Row 8

    (*game).whiteKing =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00001000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x08)
    0b00000000ULL;         // Row 8

    (*game).whiteCastle = 3;

    // Black Pieces

    (*game).blackPawns =
    0b00000000ULL << 56 |  // Row 1
    0b11110111ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8

    (*game).blackKnights =
    0b01000010ULL << 56 |  // Row 1 (0x42)
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8

    (*game).blackBishops =
    0b00100100ULL << 56 |  // Row 1 (0x24)
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8

    (*game).blackRooks =
    0b10000001ULL << 56 |  // Row 1 (0x81)
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8

    (*game).blackQueen =
    0b00010000ULL << 56 |  // Row 1 (0x08)
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8

    (*game).blackKing =
    0b00000000ULL << 56 |  // Row 1 (0x10)
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8

    (*game).blackCastle = 1;
}
int main(){
    //assume computer is white for now

    int moves = 0;
    int turn = 0; //0 - white / 1 - black 

    struct gameBoard game;
    setupBlankGame(&game);
    //setupBlankGame(&game);
    int depth = 7;
    int newScore, currentScore;
    int start, end;
    printBoard(&game,0,0);


    struct MoveList list;
    generateMoves(&game, &list, White);
    printMoves(&list);
    printf("Game Over: %d\n", gameOver(White, &game));

    return 0;

}
/*
    while(1){
        #ifdef SECOND
            currentScore = evaluate(&game);
            newScore =alphabeta(depth,depth,&game,0,-10000000,1000000, &moves,&start,&end);
            printf("Predicted Score: %d / Current Score: %d\n",newScore,currentScore);
            printf("Moves Calculated: %d / Depth: %d\n", moves,depth);
            printf("Starting Move: %d End Move: %d\n\n\n",start,end);
            makeMove(&game,start,end);
            printBoard(&game,start,end);
            moveInput(&start,&end);
            makeMove(&game,start,end);
            printBoard(&game,start,end);
        #else
            moveInput(&start,&end);
            makeMove(&game, start, end);
            printBoard(&game,start,end);
            currentScore = evaluate(&game);
            newScore =alphabeta(depth,depth,&game,1,-10000000,1000000, &moves,&start,&end);
            printf("Predicted Score: %d / Current Score: %d\n",newScore,currentScore);
            printf("Moves Calculated: / %d Depth: %d\n", moves,depth);
            printf("Starting Move: %d End Move: %d\n\n\n",start,end);
            makeMove(&game,start,end);
            printBoard(&game,start,end);
        #endif
        
}*/