#include <stdio.h>
#include <string.h>
#include "Board.h"
#include "AlphaBeta.h"

void moveInput(struct gameBoard *Game, struct Move *Input, enum Color turn){
    struct MoveList moves;
    generateMoves(Game, &moves, turn);
    InsertSort(moves.moves, moves.count);
    printf("POSSIBLE MOVES: \n");
    printMoves(&moves);
    printf("\n");
    int found = 0;
    while (1) {
        printf("Which piece to move?\n");
        scanf("%d",&(Input->start));
        printf("Where to?\n");
        scanf("%d", &(Input->end));
        for (int x = 0; x < moves.count; ++x) {
            if (moves.moves[x].start == Input->start && Input->end == moves.moves[x].end) {
                found = 1;
                break;
            }
        }
        if (found){
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
            return;
        }
        else {
            printf("Try again, invalid move\n");
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
    printf("[%d - %d]\n", Input->start, Input->end);

    //apply castle changes
    if (Input->piece == King) {
        if (turn == White) Game->WhiteCastle = Neither;
        else Game->BlackCastle = Neither;
        if (abs(Input->start - Input->end) == 2) {
            if (turn == White) {
                if (Input->end == 5) {
                    Game->game[White][Rook] ^= 1ULL << 7;
                    Game->game[White][Rook] |= 1ULL << 4;
                }
                else {
                    Game->game[White][Rook] ^= 1ULL;
                    Game->game[White][Rook] |= 1ULL << 2;
                }
            }
            else {
                if (Input->end == 61) {
                    Game->game[Black][Rook] ^= 1ULL << 63;
                    Game->game[Black][Rook] |= 1ULL << 60;
                }
                else {
                    Game->game[Black][Rook] ^= 1ULL << 56;
                    Game->game[Black][Rook] |= 1ULL << 58;
                }
            }
        }
    }
    if (Input->piece == Rook) {
        if (turn == White && Game->WhiteCastle != Neither) {
            if (Input->start == 0) {
                if (Game->WhiteCastle == WhiteBoth) Game->WhiteCastle = WhiteQueen;
                else Game->WhiteCastle = Neither;
            }
            else if (Input->start == 7) {
                if (Game->WhiteCastle == WhiteBoth) Game->WhiteCastle = WhiteKing;
                else Game->WhiteCastle = Neither;
            }
        }
        else if (turn == Black && Game->BlackCastle != Neither) {
            if (Input->start == 63)
                if (Game->BlackCastle == BlackBoth) Game->BlackCastle = BlackKing;
                else Game->BlackCastle = Neither;
            }
            else if (Input->start == 56) {
                if (Game->BlackCastle == BlackBoth) Game->BlackCastle = BlackQueen;
                else Game->BlackCastle = Neither;
            }
    }
}

//time to beat: user - 1.003 

int main(){
    struct gameBoard Game;
    setupBlankGame(&Game);
    //setupGame(&Game);
    struct Move move;
    struct Move Input;
    
    while (gameOver(White, &Game) == Play && gameOver(Black, &Game) == Play) {
        PrintBoard(&Game, -1, -1);
        int nodes = 0;
        int eval = alphabeta(DEPTH, &Game, White, -10000000, 10000000, 1, &move, &nodes);
        printf("Start: %d End: %d Piece: %d maxEval: %d\nCastle: %d Nodes Explored: %d\n",move.start,move.end,move.piece, eval, Game.WhiteCastle, nodes);
        makeMove(&Game, &move, White);
        PrintBoard(&Game, move.start, move.end);

        moveInput(&Game, &Input, Black);
        makeMove(&Game, &Input, Black);
        PrintBoard(&Game, Input.start, Input.end);
    }
    if (gameOver(White, &Game) == Stalemate) printf("DRAW - Stalemate\n");
    if (gameOver(White, &Game) == Checkmate) printf("Black Win\n");
    else printf("White Win\n");
    return 0;
    /*
    int eval = alphabeta(DEPTH, &Game, White, -10000000, 10000000, 1, &move,);
    printf("Start: %d End: %d Piece: %d maxEval: %d\n",move.start,move.end,move.piece, eval);
    PrintBoard(&Game, move.start, move.end);*/

}
