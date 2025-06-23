#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Board.h"
#include "AlphaBeta.h"
#include <string.h>
#include <stdlib.h>
/*
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
    CheckCollision(1ULL << Input->start, Game, Game);
    int removed = CheckCollision(1ULL << Input->end, Game, Game);
    Game->game[turn][Input->piece] |= (1ULL << Input->end);
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
*/

void init_game();
void set_position_startpos();
void apply_moves(const char *moves_str);
char *seach_best_move();

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

struct gameBoard Game;
struct Stack stack;
struct TTEntry *ttTable;

void init_game() {
    setupStack(&stack);
    ttTable = malloc(sizeof(struct TTEntry) * TT_SIZE);
}

void set_position_startpos() {
    setupGame(&Game);
}
void set_position_from_fen(const char *fen);
void apply_moves(const char *moves_str);
char* search_best_move(); // Stub


void uci_loop() {
    char line[4096];

    while (fgets(line, sizeof(line), stdin)) {
        if (strncmp(line, "uci", 3) == 0) {
            printf("id name MyEngine\n");
            printf("id author Abdou Y. Murad\n");
            printf("uciok\n");
        } else if (strncmp(line, "isready", 7) == 0) {
            printf("readyok\n");
        } else if (strncmp(line, "ucinewgame", 10) == 0) {
            init_game();
        } else if (strncmp(line, "position", 8) == 0) {
            char* ptr = line + 9;
            if (strncmp(ptr, "startpos", 8) == 0) {
                set_position_startpos();
                ptr += 8;
                if (strncmp(ptr, " moves", 6) == 0) {
                    ptr += 6;
                    apply_moves(ptr);
                }
            } else if (strncmp(ptr, "fen", 3) == 0) {
                ptr += 4;
                char fen[256];
                int i = 0;
                while (*ptr && strncmp(ptr, " moves", 6) != 0 && i < 255) {
                    fen[i++] = *ptr++;
                }
                fen[i] = '\0';
                set_position_from_fen(fen);
                if (strncmp(ptr, " moves", 6) == 0) {
                    ptr += 6;
                    apply_moves(ptr);
                }
            }
        } else if (strncmp(line, "go", 2) == 0) {
            char* bestmove = search_best_move();
            printf("bestmove %s\n", bestmove);
            free(bestmove); // if dynamically allocated
        } else if (strncmp(line, "quit", 4) == 0) {
            break;
        }
    }
}

int main() {
    struct gameBoard Game;
    //setupBlankGame(&Game);
    setupGame(&Game);
    
    //initialize tt table
    struct TTEntry *ttTable = malloc(sizeof(struct TTEntry) * TT_SIZE);
    
    enum Color Turn = White;

    struct Stack stack;
    setupStack(&stack);




    free(ttTable);
    deleteStack(&stack);
}