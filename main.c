#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Board.h"
#include "AlphaBeta.h"
#include <time.h>
void moveInput(struct gameBoard *Game, struct Move *Input, enum Color turn){
    struct MoveList moves;
    generateMoves(Game, &moves, turn);
    InsertSort(moves.moves, moves.count);
    //printf("POSSIBLE MOVES: \n");
    //printMoves(&moves);
    //printf("\n");
    int found = 0;
    
    while (1) {
        char c;
        int i;
        printf("Which piece to move?\n");
        scanf("%c", &c);
        scanf("%d", &i);
        Input->start = 7 - (c - 'a') + 8*(i-1);
        scanf("%c", &c);
        scanf("%d", &i);
        Input->end   = 7 - (c - 'a') + 8*(i-1);
        scanf("%c", &c);
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
                    if (i == Pawn && Input->end/8 == (7-7*turn)) {
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
void makeMove(struct gameBoard *Game, struct Move *Input, enum Color turn, struct Stack *stack) {
    Game->game[turn][Input->piece] ^= (1ULL << Input->start);
    Game->game[turn][Input->piece] |= (1ULL << Input->end);
    int removed = CheckCollision(1ULL << Input->end, Game, Game, !turn);
    if (removed) stack->pointer = 0;
    if (Input->piece == Pawn) stack->pointer = 0;
    if (removed - 1 == Rook) {
        if (turn == White && Input->end == 63) {
            if (Game->BlackCastle == BlackBoth) Game->BlackCastle = BlackKing;
            else Game->BlackCastle = Neither;
        }
        else if (turn == White && Input->end == 56) {
            if (Game->BlackCastle == BlackBoth) Game->BlackCastle = BlackQueen;
            else Game->BlackCastle = Neither;
        }
        else if (turn == Black && Input->end == 7) {
            if (Game->WhiteCastle == WhiteBoth) Game->WhiteCastle = WhiteKing;
            else Game->WhiteCastle = Neither;
        }
        else if (turn == Black && Input->end == 0) {
            if (Game->WhiteCastle == WhiteBoth) Game->WhiteCastle = WhiteQueen;
            else Game->WhiteCastle = Neither; 
        }
    }
    //en passant remove piece
    if (Game->enPassant[!turn] < 8 && Input->start/8 == 4 - turn && Input->end % 8 == Game->enPassant[!turn] && Input->piece == Pawn) {
        Game->game[!turn][Pawn] ^= 1ULL << (Input->end - 8 + 16*turn);
    }
    Game->enPassant[turn] = 8;
    Game->enPassant[!turn] = 8;
    if (Input->piece == Pawn && abs(Input->start - Input->end) == 16) {
        Game->enPassant[turn] = Input->start % 8;
    }
    if (Input->piece == Pawn && Input->end/8 == (7-7*turn)) {
        Game->game[turn][Pawn] ^= (1ULL << Input->end);
        Game->game[turn][Input->promotion] |= (1ULL << Input->end);
    }
    //printf("[%d - %d]\n", Input->start, Input->end);

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
    //setupBlankGame(&Game);
    setupGame(&Game);

    //initialize tt table
    struct TTEntry *ttTable = malloc(sizeof(struct TTEntry) * TT_SIZE);
    
    enum Color Turn = White;

    struct Stack stack;
    setupStack(&stack);

    PrintBoard(&Game, -1, -1);

    while (gameOver(Turn, &Game) == Play && search(&stack, computeHash(&Game, Turn)) != 3) {
        if (Turn == White) {
            printf("_______________________________________________________\n");
            struct Move move;

            struct timespec start, end;

            move.start = -1;
            move.end = -1;

            set_Nodes(0);

            clock_gettime(CLOCK_MONOTONIC, &start);

            int eval = alphabeta(DEPTH, &Game, -INF, INF, 1, &move, ttTable, &stack);
            
            clock_gettime(CLOCK_MONOTONIC, &end);

            if (move.start == -1) {
                struct MoveList moves;
                generateMoves(&Game, &moves, White);
                move = moves.moves[0];
            }
            makeMove(&Game, &move, White, &stack);
            
            push(&stack, computeHash(&Game, Black));
            double delta_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
            printf("nps: %d, nodes: %d\n", (int)(get_Nodes()/delta_time), get_Nodes());
            PrintBoard(&Game, move.start, move.end);
            if (search(&stack, computeHash(&Game, Black)) == 3) break;
        }
        else {
            printf("_______________________________________________________\n");
            struct Move Input;
            moveInput(&Game, &Input, Black);
            makeMove(&Game, &Input, Black, &stack);
            push(&stack, computeHash(&Game, White));
            PrintBoard(&Game, Input.start, Input.end);
            if (search(&stack, computeHash(&Game, White)) == 3) break;
        }
        Turn = !Turn;
    }
    if (gameOver(White, &Game) == Stalemate || search(&stack, computeHash(&Game, Turn)) == 3) printf("DRAW - Stalemate\n");
    else if (gameOver(White, &Game) == Checkmate) printf("Black Win\n");
    else printf("White Win\n");
    
    deleteStack(&stack);
    free(ttTable);
    return 0;
    
/*
    int nodes = 0;
    int eval = alphabeta(DEPTH, &Game, White, -10000000, 10000000, 1, &move, ttTable, &nodes);
    printf("Start: %d End: %d Piece: %d maxEval: %d More Moves? : %d Nodes Explored: %d\n",move.start,move.end,move.piece, eval, MoreMoves(&Game, White),nodes);
    PrintBoard(&Game, move.start, move.end);
    struct MoveList moves;
    generateMoves(&Game, &moves, White);
    printMoves(&moves);
*/
    }
