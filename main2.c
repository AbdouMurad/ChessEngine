#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Board.h"
#include "AlphaBeta.h"
#include <string.h>
#include <stdlib.h>


void init_game();
void set_position_startpos();
void apply_moves(const char *moves_str);
char *seach_best_move();

int GameReady = 0;
struct gameBoard Game;
struct Stack stack;
struct TTEntry *ttTable;
int turn = White;

void init_game() {
    if (GameReady) {
        free(ttTable);
        deleteStack(&stack);
    }
    turn = White;
    setupStack(&stack);
    ttTable = malloc(sizeof(struct TTEntry) * TT_SIZE);
}

void makeMove(struct Move *Input, enum Color turn) {
    Game.game[turn][Input->piece] ^= (1ULL << Input->start);
    Game.game[turn][Input->piece] |= (1ULL << Input->end);
    int removed = CheckCollision(1ULL << Input->end, &Game, &Game, !turn);
    if (removed) stack.pointer = 0;
    if (Input->piece == Pawn) stack.pointer = 0;
    if (removed - 1 == Rook) {
        if (turn == White && Input->end == 63) {
            if (Game.BlackCastle == BlackBoth) Game.BlackCastle = BlackKing;
            else Game.BlackCastle = Neither;
        }
        else if (turn == White && Input->end == 56) {
            if (Game.BlackCastle == BlackBoth) Game.BlackCastle = BlackQueen;
            else Game.BlackCastle = Neither;
        }
        else if (turn == Black && Input->end == 7) {
            if (Game.WhiteCastle == WhiteBoth) Game.WhiteCastle = WhiteKing;
            else Game.WhiteCastle = Neither;
        }
        else if (turn == Black && Input->end == 0) {
            if (Game.WhiteCastle == WhiteBoth) Game.WhiteCastle = WhiteQueen;
            else Game.WhiteCastle = Neither; 
        }
    }
    //en passant remove piece
    if (Game.enPassant[!turn] < 8 && Input->start/8 == 4 - turn && Input->end % 8 == Game.enPassant[!turn] && Input->piece == Pawn) {
        Game.game[!turn][Pawn] ^= 1ULL << (Input->end - 8 + 16*turn);
    }
    Game.enPassant[turn] = 8;
    Game.enPassant[!turn] = 8;
    if (Input->piece == Pawn && abs(Input->start - Input->end) == 16) {
        Game.enPassant[turn] = Input->start % 8;
    }
    if (Input->piece == Pawn && Input->end/8 == (7-7*turn)) {
        Game.game[turn][Pawn] ^= (1ULL << Input->end);
        Game.game[turn][Input->promotion] |= (1ULL << Input->end);
    }

    //apply castle changes
    if (Input->piece == King) {
        if (turn == White) Game.WhiteCastle = Neither;
        else Game.BlackCastle = Neither;
        if (abs(Input->start - Input->end) == 2) {
            if (turn == White) {
                if (Input->end == 5) {
                    Game.game[White][Rook] ^= 1ULL << 7;
                    Game.game[White][Rook] |= 1ULL << 4;
                }
                else {
                    Game.game[White][Rook] ^= 1ULL;
                    Game.game[White][Rook] |= 1ULL << 2;
                }
            }
            else {
                if (Input->end == 61) {
                    Game.game[Black][Rook] ^= 1ULL << 63;
                    Game.game[Black][Rook] |= 1ULL << 60;
                }
                else {
                    Game.game[Black][Rook] ^= 1ULL << 56;
                    Game.game[Black][Rook] |= 1ULL << 58;
                }
            }
        }
    }
    if (Input->piece == Rook) {
        if (turn == White && Game.WhiteCastle != Neither) {
            if (Input->start == 0) {
                if (Game.WhiteCastle == WhiteBoth) Game.WhiteCastle = WhiteQueen;
                else Game.WhiteCastle = Neither;
            }
            else if (Input->start == 7) {
                if (Game.WhiteCastle == WhiteBoth) Game.WhiteCastle = WhiteKing;
                else Game.WhiteCastle = Neither;
            }
        }
        else if (turn == Black && Game.BlackCastle != Neither) {
            if (Input->start == 63)
                if (Game.BlackCastle == BlackBoth) Game.BlackCastle = BlackKing;
                else Game.BlackCastle = Neither;
            }
            else if (Input->start == 56) {
                if (Game.BlackCastle == BlackBoth) Game.BlackCastle = BlackQueen;
                else Game.BlackCastle = Neither;
            }
    }
}

void handle_position(char *input) {
    char *ptr = input + 9;  // Skip "position "
    char string[256] = {0};
    char moves[1024] = {0};
    int is_startpos = 0;

    // 1. Determine if it's "startpos" or "fen"
    if (strncmp(ptr, "startpos", 8) == 0) {
        is_startpos = 1;
        setupGame(&Game);
        ptr += 8;
    } else if (strncmp(ptr, "fen", 3) == 0) {
        ptr += 4;  // skip "fen "
        // Copy FEN string up until "moves" or end
        char *moves_ptr = strstr(ptr, " moves");
        int fen_length = moves_ptr ? (int)(moves_ptr - ptr) : strlen(ptr);
        strncpy(string, ptr, fen_length);
        string[fen_length] = '\0';

        // Set board from FEN
        turn = fen(&Game, string);
        printf("Parsed FEN: %s\n", string);
        fflush(stdout);
        ptr = moves_ptr ? moves_ptr : ptr + fen_length;
    }

    // 2. Check for "moves" and collect them
    if (strstr(ptr, "moves")) {
        ptr = strstr(ptr, "moves") + 6; // skip "moves "
        strncpy(moves, ptr, sizeof(moves) - 1);
        moves[sizeof(moves) - 1] = '\0';

        // Split moves and apply them one by one
        char *move = strtok(moves, " ");
        while (move) {
            struct Move Input; 
            Input.start = 7 - (move[0] - 'a') + (move[1] - '1') * 8;
            Input.end = 7 - (move[2] - 'a') + (move[3] - '1') * 8;
            
            for (int piece = 0; piece < 6; ++piece) {
                if (Game.game[turn][piece] & 1ULL << Input.start) {
                    Input.piece = piece;
                    break;
                }
            }
            
            if (Input.piece == Pawn && (Input.end/8 == 7 || Input.end/8 == 0)) {
                char c = move[4];
                if (c == 'k') Input.promotion = Knight;
                else if (c == 'b') Input.promotion = Bishop;
                else if (c == 'r') Input.promotion = Rook;
                else if (c == 'q') Input.promotion = Queen;
            }

            makeMove(&Input, turn);
            turn = !turn;
            printf("Parsed move: %s\n", move);
            fflush(stdout);
            move = strtok(NULL, " ");
        }
    }

    if (is_startpos)
        printf("Starting from standard position.\n");
        fflush(stdout);
}



void uci_loop() {
    char input[512];

    while (fgets(input, sizeof(input), stdin)) {
        // Remove trailing newline
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "uci") == 0) {
            printf("id name Chesster\n");
            printf("id author Abdou Murad\n");
            printf("uciok\n");
            fflush(stdout);
        } else if (strncmp(input, "isready", 7) == 0) {
            printf("readyok\n");
            fflush(stdout);
        } else if (strcmp(input, "ucinewgame") == 0) {
            init_game();
            GameReady = 1;
        } else if (strncmp(input, "position", 8) == 0) {
            handle_position(input);
        } else if (strncmp(input, "go", 2) == 0) {
            struct Move BestMove;
            if (!GameReady) {
                init_game();
                GameReady = 1;
            }
            alphabeta(DEPTH, &Game, -INF, INF, !turn, &BestMove, ttTable, &stack);
            char move[6];
            move[0] = 'a' + (7 - BestMove.start % 8);
            move[1] = '1' + BestMove.start/8;
            move[2] = 'a' + (7 - BestMove.end % 8);
            move[3] = '1' + BestMove.end/8;
            if (BestMove.piece == Pawn && (BestMove.end/8 == 0 || BestMove.end/8 == 7)) {
                if (BestMove.promotion == Queen) move[4] = 'q';
                else if (BestMove.promotion == Knight) move[4] = 'n';
                else if (BestMove.promotion == Bishop) move[4] = 'b';
                else if (BestMove.promotion == Rook) move[4] = 'r';
                move[5] = '\0';
            }
            else move[4] = '\0';
            printf("bestmove %s\n", move);
            fflush(stdout);
        } else if (strncmp(input, "quit", 4) == 0) {
            deleteStack(&stack);
            free(ttTable);
            break;
        }
        // Optional: Add support for 'stop', 'ponderhit', etc. later
    }
}

int main() {
    uci_loop();
}