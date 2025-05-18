#include <stdlib.h>
#include "Board2.h"
#include <stdio.h>
#include "AlphaBeta3.h"


int pawnPst[] = {
    0,  0,  0,  0,  0,  0,  0,  0,
    5, 10, 10,-20,-20, 10, 10,  5,
    5, -5,-10,  0,  0,-10, -5,  5,
    0,  0,  0, 20, 20,  0,  0,  0,
    5,  5, 10, 25, 25, 10,  5,  5,
    10, 10, 20, 30, 30, 20, 10, 10,
    50, 50, 50, 50, 50, 50, 50, 50,
    0,  0,  0,  0,  0,  0,  0,  0};
int knightPst[] = {
    -50,-40,-30,-30,-30,-30,-40,-50,
    -40,-20,  0,  5,  5,  0,-20,-40,
    -30,  5, 10, 15, 15, 10,  5,-30,
    -30,  0, 15, 20, 20, 15,  0,-30,
    -30,  5, 15, 20, 20, 15,  5,-30,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -40,-20,  0,  0,  0,  0,-20,-40,
    -50,-40,-30,-30,-30,-30,-40,-50};

int bishopPst[] = {
    -20,-10,-10,-10,-10,-10,-10,-20,
    -10,  5,  0,  0,  0,  0,  5,-10,
    -10, 10, 10, 10, 10, 10, 10,-10,
    -10,  0, 10, 10, 10, 10,  0,-10,
    -10,  5,  5, 10, 10,  5,  5,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -20,-10,-10,-10,-10,-10,-10,-20};
int rookPst[] = {
     0,  0,  5,  10, 10, 5,  0,  0,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
     5,  10, 10, 10, 10, 10, 10, 5,
     0,  0,  0,  0,  0,  0,  0,  0,};
int queenPst[] = {
    -20,-10,-10, -5, -5,-10,-10,-20
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5,  5,  5,  5,  0,-10,
     -5,  0,  5,  5,  5,  5,  0, -5,
     -5,  0,  5,  5,  5,  5,  0, -5,
    -10,  0,  5,  5,  5,  5,  0,-10,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -20,-10,-10, -5, -5,-10,-10,-20,};
int kingPst[] = {
     20,  30,  10,  0,   0,   10,  30,  20,
     20,  20,  0,   0,   0,   0,   20,  20,
    -10, -20, -20, -20, -20, -20, -20, -10,
    -20, -30, -30, -40, -40, -30, -30, -20,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30,
};

int max(int a, int b) {
    return a > b ? a : b;
}

void printMoves(struct MoveList *moves) {
    printf("Moves: %d \n", moves->count);
    for (int i = 0; i < moves->count; ++i) {
        if (i % 10 == 0) printf("\n");
        printf("[%d : %d - %d] ", moves->moves[i].start, moves->moves[i].end, moves->moves[i].piece);
    }
}

void generateMoves(struct gameBoard *game, struct MoveList *moves, enum Color color) {
    moves->count = 0;
    int position = 0;
    long long int currentPiece = 0;
    long long int tempPiece = 0;
    if (color == White){
        for (int Piece = Queen; Piece >= King; --Piece){
            enum Piece piece = (enum Piece)Piece;
            if (piece == Pawn) {
                currentPiece = game->whitePawns;
                while (currentPiece){
                    position = __builtin_ctzll(currentPiece);
                    currentPiece &= currentPiece - 1;
                    if (position/8 == 1 && !((1ULL << (position + 16)) & allBitboard(game))) { //pawn move 2 forward
                        struct Move move = {position, position + 16, Pawn};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    if (position/8 < 7 && !((1ULL << (position + 8)) & allBitboard(game))) {
                        struct Move move = {position, position + 8, Pawn};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    if (position/8 < 7 && position % 8 > 0 && ((1ULL << (position + 9)) & blackBitBoard(game))) {
                        struct Move move = {position, position + 9, Pawn};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    if (position/8 < 7 && position % 8 < 7 && ((1ULL << (position + 7)) & blackBitBoard(game))) {
                        struct Move move = {position, position + 7, Pawn};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                }
            }
            if (piece == Knight) {
                currentPiece = game->whiteKnights;
                while (currentPiece) {
                    position = __builtin_ctzll(currentPiece);
                    currentPiece &= currentPiece - 1;
                    if (position/8 < 7) {
                        if (position % 8 > 1 && !(whiteBitboard(game) & (1ULL << (position + 6)))) {
                            struct Move move = {position, position + 6, Knight};
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                        if (position % 8 < 6 && !(whiteBitboard(game) & (1ULL << (position + 10)))) {
                            struct Move move = {position, position + 10, Knight};
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                        if (position/8 < 6) {
                            if (position % 8 > 0 && !(whiteBitboard(game) & (1ULL << (position + 15)))) {
                                struct Move move = {position , position + 15, Knight};
                                moves->moves[moves->count] = move;
                                moves->count += 1;
                            }
                            if (position % 8 < 7 && !(whiteBitboard(game) & (1ULL << (position + 17)))) {
                                struct Move move = {position, position + 17, Knight};
                                moves->moves[moves->count] = move;
                                moves->count += 1;
                            }
                        }
                    }
                    if (position/8 > 0) {
                        if (position % 8 > 1 && !(whiteBitboard(game) & (1ULL << (position - 10)))) {
                            struct Move move = {position, position - 10, Knight};
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                        if (position % 8 < 6 && !(whiteBitboard(game) & (1ULL << (position - 6)))) {
                            struct Move move = {position, position - 6, Knight};
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                        if (position/8 > 1) {
                            if (position % 8 > 0 && !(whiteBitboard(game) & (1ULL << (position - 17)))) {
                                struct Move move = {position , position - 17, Knight};
                                moves->moves[moves->count] = move;
                                moves->count += 1;
                            }
                            if (position % 8 < 7 && !(whiteBitboard(game) & (1ULL << (position - 15)))) {
                                struct Move move = {position, position - 15, Knight};
                                moves->moves[moves->count] = move;
                                moves->count += 1;
                            }
                        }
                    }
                }
            }
            if (piece == Rook || piece == Queen) {
                if (piece == Rook) currentPiece = game->whiteRooks;
                else currentPiece = game->whiteQueen;
                while (currentPiece) {
                    position = __builtin_ctzll(currentPiece);
                    currentPiece &= currentPiece - 1;
                    for (int y = position/8 + 1; y <= 7; ++y) {
                        if (whiteBitboard(game) & (1ULL << (position % 8 + 8*y))) break;
                        struct Move move = {position, position % 8 + 8*y, piece};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                        if (blackBitBoard(game) & (1ULL << (position % 8 + 8*y))) break;
                    }
                    for (int y = position/8 - 1; y >= 0; --y) {
                        if (whiteBitboard(game) & (1ULL << (position % 8 + 8*y))) break;
                        struct Move move = {position, position % 8 + 8*y, piece};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                        if (blackBitBoard(game) & (1ULL << (position % 8 + 8*y))) break;
                    }
                    for (int x = position % 8 + 1; x <= 7; ++x) {
                        if (whiteBitboard(game) & (1ULL << ((position/8) *8 + x))) break;
                        struct Move move = {position, (position/8) *8 + x, piece};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                        if (blackBitBoard(game) & (1ULL << ((position/8) *8 + x))) break;
                    }
                    for (int x = position % 8 -1; x >= 0; --x) {
                        if (whiteBitboard(game) & (1ULL << ((position/8) *8 + x))) break;
                        struct Move move = {position, (position/8) *8 + x, piece};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                        if (blackBitBoard(game) & (1ULL << ((position/8) *8 + x))) break;
                    }
                }
            }
            if (piece == Bishop || piece == Queen) {
                if (piece == Bishop) currentPiece = game->whiteBishops;
                else currentPiece = game->whiteQueen;
                while (currentPiece) {
                    position = __builtin_ctzll(currentPiece);
                    currentPiece &= currentPiece - 1;
                    for (int y = position/8 + 1, x = position % 8 + 1; x <= 7 && y <= y; ++x, ++y) {
                        if (whiteBitboard(game) & (1ULL << (8*y + x))) break;
                        struct Move move = {position, 8*x + y, piece};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                        if (blackBitBoard(game) & (1ULL << (8*y + x))) break;
                    }
                    for (int y = position/8 + 1, x = position % 8 - 1; x >= 0 && y <= 7; --x, ++y) {
                        if (whiteBitboard(game) & (1ULL << (8*y + x))) break;
                        struct Move move = {position, 8*y + x, piece};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                        if (blackBitBoard(game) & (1ULL << (8*y + x))) break;
                    }
                    for (int y = position/8 -1, x = position % 8 - 1; x >= 0 && y >= 0; --x, --y) {
                        if (whiteBitboard(game) & (1ULL << (8*y + x))) break;
                        struct Move move = {position, 8*y + x, piece};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                        if (blackBitBoard(game) & (1ULL << (8*y + x))) break;
                    }
                    for (int y = position/8 - 1, x = position % 8 + 1; x <= 7 && y >= 0; ++x, --y) {
                        if (whiteBitboard(game) & (1ULL << (8*y + x))) break;
                        struct Move move = {position, 8*y + x, piece};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                        if (blackBitBoard(game) & (1ULL << (8*y + x))) break;
                    }
                }
            }
            if (piece == King) {
                tempPiece = game->whiteKing;
                position = __builtin_ctzll(game->whiteKing);
                if (position == 64) continue;
                if (position/8 < 7) {
                    if (!(whiteBitboard(game) & (1ULL << (position + 8)))) {
                        game->whiteKing = 1ULL << (position + 8);
                        if (!inCheck(game, White)) {
                            struct Move move = {position, position + 8, King};
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                        game->whiteKing = tempPiece;
                    }
                    if (position % 8 > 0 && !(whiteBitboard(game) & (1ULL << (position + 7)))) {
                        game->whiteKing = 1ULL << (position + 7);
                        if (!inCheck(game, White)) {
                            struct Move move = {position, position + 7, King};
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                        game->whiteKing = tempPiece;
                    }
                    if (position % 8 < 7 && !(whiteBitboard(game) & (1ULL << (position + 9)))) {
                        game->whiteKing = 1ULL << (position + 9);
                        if (!inCheck(game, White)) {
                            struct Move move = {position, position + 9, King};
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                        game->whiteKing = tempPiece;
                    }
                }
                if (position/8 > 0) {
                    if (!(whiteBitboard(game) & (1ULL << (position - 8)))) {
                        game->whiteKing = 1ULL << (position - 8);
                        if (!inCheck(game, White)) {
                            struct Move move = {position, position - 8, King};
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                        game->whiteKing = tempPiece;
                    }
                    if (position % 8 > 0 && !(whiteBitboard(game) & (1ULL << (position - 9)))) {
                        game->whiteKing = 1ULL << (position - 9);
                        if (!inCheck(game, White)) {
                            struct Move move = {position, position - 9, King};
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                        game->whiteKing = tempPiece;
                    }
                    if (position % 8 < 7 && !(whiteBitboard(game) & (1ULL << (position - 7)))) {
                        game->whiteKing = 1ULL << (position - 7);
                        if (!inCheck(game, White)) {
                            struct Move move = {position, position - 7, King};
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                        game->whiteKing = tempPiece;
                    }
                }
                if (position % 8 > 0 && !(whiteBitboard(game) & (1ULL << (position - 1)))) {
                        game->whiteKing = 1ULL << (position - 1);
                        if (!inCheck(game, White)) {
                            struct Move move = {position, position - 1, King};
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                        game->whiteKing = tempPiece;
                }
                if (position % 8 < 7 && !(whiteBitboard(game) & (1ULL << (position + 1)))) {
                        game->whiteKing = 1ULL << (position + 1);
                        if (!inCheck(game, White)) {
                            struct Move move = {position, position + 1, King};
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                        game->whiteKing = tempPiece;
                }

            }
        }
    }
    else {
        for (int Piece = Queen; Piece >= King; --Piece){
            enum Piece piece = (enum Piece)Piece;
            if (piece == Pawn) {
                currentPiece = game->blackPawns;
                while (currentPiece) {
                    position = __builtin_ctzll(currentPiece);
                    currentPiece &= currentPiece - 1;
                    if (position/8 == 6 && !((1ULL << (position - 16)) & allBitboard(game))) {
                        struct Move move = {position , position - 16, piece};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    if (position/8 > 0 && !((1ULL << (position - 8)) & allBitboard(game))) {
                        struct Move move = {position, position - 8, piece};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    if (position/8 > 0 && position % 8 > 0 && ((1ULL << position - 9) & whiteBitboard(game))) {
                        struct Move move = {position, position -9, piece};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    if (position/8 > 0 && position % 8 < 7 && ((1ULL << (position - 7) & whiteBitboard(game)))) {
                        struct Move move = {position, position - 7, piece};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                }
            }
            if (piece == Knight) {
                currentPiece = game->blackKnights;
                while (currentPiece) {
                    position = __builtin_ctzll(currentPiece);
                    currentPiece &= currentPiece - 1;
                    if (position/8 < 7) {
                        if (position % 8 > 1 && !(blackBitBoard(game) & (1ULL << (position + 6)))) {
                            struct Move move = {position, position + 6, Knight};
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                        if (position % 8 < 6 && !(blackBitBoard(game) & (1ULL << (position + 10)))) {
                            struct Move move = {position, position + 10, Knight};
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                        if (position/8 < 6) {
                            if (position % 8 > 0 && !(blackBitBoard(game) & (1ULL << (position + 15)))) {
                                struct Move move = {position , position + 15, Knight};
                                moves->moves[moves->count] = move;
                                moves->count += 1;
                            }
                            if (position % 8 < 7 && !(blackBitBoard(game) & (1ULL << (position + 17)))) {
                                struct Move move = {position, position + 17, Knight};
                                moves->moves[moves->count] = move;
                                moves->count += 1;
                            }
                        }
                    }
                    if (position/8 > 0) {
                        if (position % 8 > 1 && !(blackBitBoard(game) & (1ULL << (position - 10)))) {
                            struct Move move = {position, position - 10, Knight};
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                        if (position % 8 < 6 && !(blackBitBoard(game) & (1ULL << (position - 6)))) {
                            struct Move move = {position, position - 6, Knight};
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                        if (position/8 > 1) {
                            if (position % 8 > 0 && !(blackBitBoard(game) & (1ULL << (position - 17)))) {
                                struct Move move = {position , position - 17, Knight};
                                moves->moves[moves->count] = move;
                                moves->count += 1;
                            }
                            if (position % 8 < 7 && !(blackBitBoard(game) & (1ULL << (position - 15)))) {
                                struct Move move = {position, position - 15, Knight};
                                moves->moves[moves->count] = move;
                                moves->count += 1;
                            }
                        }
                    }
                }
            }
            if (piece == Rook || piece == Queen) {
                if (piece == Rook) currentPiece = game->blackRooks;
                else currentPiece = game->blackQueen;
                while (currentPiece) {
                    position = __builtin_ctzll(currentPiece);
                    currentPiece &= currentPiece - 1;
                    for (int y = position/8 + 1; y <= 7; ++y) {
                        if (blackBitBoard(game) & (1ULL << (position % 8 + 8*y))) break;
                        struct Move move = {position, position % 8 + 8*y, piece};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                        if (whiteBitboard(game) & (1ULL << (position % 8 + 8*y))) break;
                    }
                    for (int y = position/8 - 1; y >= 0; --y) {
                        if (blackBitBoard(game) & (1ULL << (position % 8 + 8*y))) break;
                        struct Move move = {position, position % 8 + 8*y, piece};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                        if (whiteBitboard(game) & (1ULL << (position % 8 + 8*y))) break;
                    }
                    for (int x = position % 8 + 1; x <= 7; ++x) {
                        if (blackBitBoard(game) & (1ULL << ((position/8) *8 + x))) break;
                        struct Move move = {position, (position/8) *8 + x, piece};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                        if (whiteBitboard(game) & (1ULL << ((position/8) *8 + x))) break;
                    }
                    for (int x = position % 8 -1; x >= 0; --x) {
                        if (blackBitBoard(game) & (1ULL << ((position/8) *8 + x))) break;
                        struct Move move = {position, (position/8) *8 + x, piece};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                        if (whiteBitboard(game) & (1ULL << ((position/8) *8 + x))) break;
                    }
                }
            }
            if (piece == Bishop || piece == Queen) {
                if (piece == Bishop) currentPiece = game->blackBishops;
                else currentPiece = game->blackQueen;
                while (currentPiece) {
                    position = __builtin_ctzll(currentPiece);
                    currentPiece &= currentPiece - 1;
                    for (int y = position/8 + 1, x = position % 8 + 1; x <= 7 && y <= y; ++x, ++y) {
                        if (blackBitBoard(game) & (1ULL << (8*y + x))) break;
                        struct Move move = {position, 8*x + y, piece};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                        if (whiteBitboard(game) & (1ULL << (8*y + x))) break;
                    }
                    for (int y = position/8 + 1, x = position % 8 - 1; x >= 0 && y <= 7; --x, ++y) {
                        if (blackBitBoard(game) & (1ULL << (8*y + x))) break;
                        struct Move move = {position, 8*y + x, piece};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                        if (whiteBitboard(game) & (1ULL << (8*y + x))) break;
                    }
                    for (int y = position/8 -1, x = position % 8 - 1; x >= 0 && y >= 0; --x, --y) {
                        if (blackBitBoard(game) & (1ULL << (8*y + x))) break;
                        struct Move move = {position, 8*y + x, piece};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                        if (whiteBitboard(game) & (1ULL << (8*y + x))) break;
                    }
                    for (int y = position/8 - 1, x = position % 8 + 1; x <= 7 && y >= 0; ++x, --y) {
                        if (blackBitBoard(game) & (1ULL << (8*y + x))) break;
                        struct Move move = {position, 8*y + x, piece};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                        if (whiteBitboard(game) & (1ULL << (8*y + x))) break;
                    }
                }
            }
            if (piece == King) {
                position = __builtin_ctzll(game->blackKing);
                tempPiece = game->blackKing;
                if (position == 64) continue;
                if (position/8 < 7) {
                    if (!(blackBitBoard(game) & (1ULL << (position + 8)))) {
                        game->blackKing = 1ULL << (position + 8);
                        if (!inCheck(game, Black)) {
                            struct Move move = {position, position + 8, King};
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                        game->blackKing = tempPiece;
                    }
                    if (position % 8 > 0 && !(blackBitBoard(game) & (1ULL << (position + 7)))) {
                        game->blackKing = 1ULL << (position + 7);
                        if (!inCheck(game, Black)) {
                            struct Move move = {position, position + 7, King};
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                        game->blackKing = tempPiece;
                    }
                    if (position % 8 < 7 && !(blackBitBoard(game) & (1ULL << (position + 9)))) {
                        game->blackKing = 1ULL << (position + 9);
                        if (!inCheck(game, Black)) {
                            struct Move move = {position, position + 9, King};
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                        game->blackKing = tempPiece;
                    }
                }
                if (position/8 > 0) {
                    if (!(blackBitBoard(game) & (1ULL << (position - 8)))) {
                        game->blackKing = 1ULL << (position - 8);
                        if (!inCheck(game, Black)) {
                            struct Move move = {position, position - 8, King};
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                        game->blackKing = tempPiece;
                    }
                    if (position % 8 > 0 && !(blackBitBoard(game) & (1ULL << (position - 9)))) {
                        game->blackKing = 1ULL << (position - 9);
                        if (!inCheck(game, Black)) {
                            struct Move move = {position, position - 9, King};
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                        game->blackKing = tempPiece;
                    }
                    if (position % 8 < 7 && !(blackBitBoard(game) & (1ULL << (position - 7)))) {
                        game->blackKing = 1ULL << (position - 7);
                        if (!inCheck(game, Black)) {
                            struct Move move = {position, position - 7, King};
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                        game->blackKing = tempPiece;
                    }
                }
                if (position % 8 > 0 && !(blackBitBoard(game) & (1ULL << (position - 1)))) {
                        game->blackKing = 1ULL << (position - 1);
                        if (!inCheck(game, Black)) {
                            struct Move move = {position, position - 1, King};
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                        game->blackKing = tempPiece;
                }
                if (position % 8 < 7 && !(blackBitBoard(game) & (1ULL << (position + 1)))) {
                        game->blackKing = 1ULL << (position + 1);
                        if (!inCheck(game, Black)) {
                            struct Move move = {position, position + 1, King};
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                        game->blackKing = tempPiece;
                }

            }
        }
    }
}

int inCheck(struct gameBoard *game, enum Color turn) //check if "turn" color is in check
{
    if (turn == White) {
        int position = __builtin_ctzll(game->whiteKing);
        
        //check for pawn attacks
        if (position/8 < 6){
            long long int PossiblePawn = 0b0ULL;
            if (position % 8 > 0) PossiblePawn += (game->whiteKing << 7);
            if (position % 8 < 7) PossiblePawn += (game->whiteKing << 9);
            if (PossiblePawn & game->blackPawns) return 1;
        }

        //check for knight attakcs
        if (position/8 < 7) {
            long long int possibleKnight = 0b0ULL;
            if (position % 8 > 1) possibleKnight += (game->whiteKing << 10);
            if (position % 8 < 6) possibleKnight += (game->whiteKing << 6);
            if (position/8 < 6) {
                if (position % 8 > 0) possibleKnight += (game->whiteKing << 17);
                if (position % 8 < 7) possibleKnight += (game->whiteKing << 15);
            }
            if (possibleKnight & game->blackKnights) return 1;
        }
        if (position/8 > 0) {
            long long int possibleKnight = 0b0ULL;
            if (position % 8 > 1) possibleKnight += (game->whiteKing >> 10);
            if (position % 8 < 6) possibleKnight += (game->whiteKing >> 6);
            if (position/8 > 1){
                if (position % 8 > 0) possibleKnight += (game->whiteKing >> 17);
                if (position % 8 < 7) possibleKnight += (game->whiteKing >> 15);
            }
            if (possibleKnight & game->blackKnights) return 1;
        }

        if (position/8 < 7) {
            if ((1ULL << (position + 8)) & game->blackKing) return 1;
            if (position%8 < 7) {
                if ((1ULL << (position + 9)) & game->blackKing) return 1;
            }
            if (position%8 > 0) {
                if ((1ULL << (position + 7)) & game->blackKing) return 1;
            }
        }
        if (position/8 > 0) {
            if ((1ULL << (position - 8)) & game->blackKing) return 1;
            if (position%8 < 7) {
                if ((1ULL << (position - 7)) & game->blackKing) return 1;
            }
            if (position%8 > 0) {
                if ((1ULL << (position - 9)) & game->blackKing) return 1;
            }
        }
        if (position % 8 > 0) {
            if ((1ULL << (position - 1)) & game->blackKing) return 1;
        }
        if (position % 8 < 7) {
            if ((1ULL << (position + 1)) & game->blackKing) return 1;
        }


        //Check Vertical Up
        for (long long int current = game->whiteKing << 8; __builtin_ctzll(current)/8 < 8; current = current << 8) {
            if ((current & game->blackRooks) | (current & game->blackQueen)) return 1;
            if (current & allBitboard(game)) break;
        }

        //Check Vertival Down
        for (long long int current = game->whiteKing >> 8; current != 0; current = current >> 8) {
            if ((current & game->blackRooks) | (current & game->blackQueen)) return 1;
            if (current & allBitboard(game)) break;
        }

        //Check Horizontal Left
        for (long long int current = game->whiteKing << 1; __builtin_ctzll(current)%8 < 8 && __builtin_ctzll(current)%8 > 0; current = current << 1) {
            if ((current & game->blackRooks) | (current & game->blackQueen)) return 1;
            if (current & allBitboard(game)) break;
        }
        //Check Horizontal Right
        for (long long int current = game->whiteKing >> 1; __builtin_ctzll(current)%8 >= 0 && current != 0 && __builtin_ctzll(current)%8 < 7; current = current >> 1) {
            if ((current & game->blackRooks) | (current & game->blackQueen)) return 1;
            if (current & allBitboard(game)) break;
        }

        //Check Diagonal Top left
        for (long long int current = game->whiteKing << 9; __builtin_ctzll(current)%8 < 8 && __builtin_ctzll(current)%8 > 0 && __builtin_ctzll(current)/8 < 8; current = current << 9){
            if ((game->blackBishops | game->blackQueen) & current) return 1;
            if (current & allBitboard(game)) break; 
        }

        //Check Diagonal Top Right
        for (long long int current = game->whiteKing << 7; __builtin_ctzll(current)%8 < 7 && __builtin_ctzll(current)/8 < 8; current = current << 7) {
            if ((game->blackBishops | game->blackQueen) & current) return 1;
            if (current & allBitboard(game)) break; 
        }

        //Check Diagonal Bottom Left
        for (long long int current = game->whiteKing >> 7; __builtin_ctzll(current)%8 < 8 && __builtin_ctzll(current)%8 > 0 && current != 0; current = current >> 7){
            if ((game->blackBishops | game->blackQueen) & current) return 1;
            if (current & allBitboard(game)) break; 
        }

        //Check Diagonal Bottom Right
        for (long long int current = game->whiteKing >> 9; __builtin_ctzll(current)%8 < 7 && current != 0; current = current >> 9){
            if ((game->blackBishops | game->blackQueen) & current) return 1;
            if (current & allBitboard(game)) break; 
        }
    }
    else {
        int position = __builtin_ctzll(game->blackKing);

        //check for pawn attacks
        if (position/8 > 1){
            long long int PossiblePawn = 0b0ULL;
            if (position % 8 > 0) PossiblePawn += (game->blackKing >> 7);
            if (position % 8 < 7) PossiblePawn += (game->blackKing >> 9);
            if (PossiblePawn & game->whitePawns) return 1;
        }
                //check for knight attakcs
        if (position/8 < 7) {
            long long int possibleKnight = 0b0ULL;
            if (position % 8 > 1) possibleKnight += (game->blackKing << 10);
            if (position % 8 < 6) possibleKnight += (game->blackKing << 6);
            if (position/8 < 6) {
                if (position % 8 > 0) possibleKnight += (game->blackKing << 17);
                if (position % 8 < 7) possibleKnight += (game->blackKing << 15);
            }
            if (possibleKnight & game->whiteKnights) return 1;
        }
        if (position/8 > 0) {
            long long int possibleKnight = 0b0ULL;
            if (position % 8 > 1) possibleKnight += (game->blackKing >> 10);
            if (position % 8 < 6) possibleKnight += (game->blackKing >> 6);
            if (position/8 > 1){
                if (position % 8 > 0) possibleKnight += (game->blackKing >> 17);
                if (position % 8 < 7) possibleKnight += (game->blackKing >> 15);
            }
            if (possibleKnight & game->whiteKnights) return 1;
        }

        if (position/8 < 7) {
            if ((1ULL << (position + 8)) & game->whiteKing) return 1;
            if (position%8 < 7) {
                if ((1ULL << (position + 9)) & game->whiteKing) return 1;
            }
            if (position%8 > 0) {
                if ((1ULL << (position + 7)) & game->whiteKing) return 1;
            }
        }
        if (position/8 > 0) {
            if ((1ULL << (position - 8)) & game->whiteKing) return 1;
            if (position%8 < 7) {
                if ((1ULL << (position - 7)) & game->whiteKing) return 1;
            }
            if (position%8 > 0) {
                if ((1ULL << (position - 9)) & game->whiteKing) return 1;
            }
        }
        if (position % 8 > 0) {
            if ((1ULL << (position - 1)) & game->whiteKing) return 1;
        }
        if (position % 8 < 7) {
            if ((1ULL << (position + 1)) & game->whiteKing) return 1;
        }

        //Check Vertical Up
        for (long long int current = game->blackKing << 8; __builtin_ctzll(current)/8 < 8; current = current << 8) {
            if ((current & game->whiteRooks) | (current & game->whiteQueen)) return 1;
            if (current & allBitboard(game)) break;
        }

        //Check Vertival Down
        for (long long int current = game->blackKing >> 8; current != 0; current = current >> 8) {
            if ((current & game->whiteRooks) | (current & game->whiteQueen)) return 1;
            if (current & allBitboard(game)) break;
        }

        //Check Horizontal Left
        for (long long int current = game->blackKing << 1; __builtin_ctzll(current)%8 < 8 && __builtin_ctzll(current)%8 > 0; current = current << 1) {
            if ((current & game->whiteRooks) | (current & game->whiteQueen)) return 1;
            if (current & allBitboard(game)) break;
        }
        //Check Horizontal Right
        for (long long int current = game->blackKing >> 1; __builtin_ctzll(current)%8 >= 0 && current != 0 && __builtin_ctzll(current)%8 < 7; current = current >> 1) {
            if ((current & game->whiteRooks) | (current & game->whiteQueen)) return 1;
            if (current & allBitboard(game)) break;
        }
        //Check Diagonal Top left
        for (long long int current = game->blackKing << 9; __builtin_ctzll(current)%8 < 8 && __builtin_ctzll(current)%8 > 0 && __builtin_ctzll(current)/8 < 8; current = current << 9){
            if ((game->whiteBishops | game->whiteQueen) & current) return 1;
            if (current & allBitboard(game)) break; 
        }
        //Check Diagonal Top Right
        for (long long int current = game->blackKing << 7; __builtin_ctzll(current)%8 < 7 && __builtin_ctzll(current)/8 < 8; current = current << 7) {
            if ((game->whiteBishops | game->whiteQueen) & current) return 1;
            if (current & allBitboard(game)) break; 
        }
        //Check Diagonal Bottom Left
        for (long long int current = game->blackKing >> 7; __builtin_ctzll(current)%8 < 8 && __builtin_ctzll(current)%8 > 0 && current != 0; current = current >> 7){
            if ((game->whiteBishops | game->whiteQueen) & current) return 1;
            if (current & allBitboard(game)) break; 
        }
        //Check Diagonal Bottom Right
        for (long long int current = game->blackKing >> 9; __builtin_ctzll(current)%8 < 7 && current != 0; current = current >> 9){
            if ((game->whiteBishops | game->whiteQueen) & current) return 1;
            if (current & allBitboard(game)) break; 
        }

    }
    return 0;    
}

int evaluate(struct gameBoard *game){
    int score = 0;
    int coord;
    unsigned long long int current;

    current = (*game).whitePawns;
    while (current){
        coord = __builtin_ctzll(current);
        current &= current -1;
        score = score + 100 + pawnPst[coord];
    }
    current = (*game).whiteKnights;
    while (current){
        coord = __builtin_ctzll(current);
        current &= current -1;
        score = score + 300 + knightPst[coord];
    }
    current = (*game).whiteBishops;
    while (current){
        coord = __builtin_ctzll(current);
        current &= current -1;
        score = score + 300 + bishopPst[coord];
    }
    current = (*game).whiteRooks;
    while (current){
        coord = __builtin_ctzll(current);
        current &= current -1;
        score = score + 500 + rookPst[coord];
    }
    current = (*game).whiteQueen;
    while (current){
        coord = __builtin_ctzll(current);
        current &= current -1;
        score = score + 800 + queenPst[coord];
    }
    current = (*game).whiteKing;
    while (current){
        coord = __builtin_ctzll(current);
        current &= current -1;
        score = score + 1000000 + kingPst[coord];
    }

    //Black
    current = (*game).blackPawns;
    while (current){
        coord = __builtin_ctzll(current);
        current &= current -1;
        score = score - (100 + pawnPst[63 - coord]);
    }
    current = (*game).blackKnights;
    while (current){
        coord = __builtin_ctzll(current);
        current &= current -1;
        score = score - (300 + knightPst[63 - coord]);
    }
    current = (*game).blackBishops;
    while (current){
        coord = __builtin_ctzll(current);
        current &= current -1;
        score = score - (300 + bishopPst[63 - coord]);
    }
    current = (*game).blackRooks;
    while (current){
        coord = __builtin_ctzll(current);
        current &= current -1;
        score = score - (500 + rookPst[63 - coord]);
    }
    current = (*game).blackQueen;
    while (current){
        coord = __builtin_ctzll(current);
        current &= current -1;
        score = score - (800 + queenPst[63 - coord]);
    }
    current = (*game).blackKing;
    while (current){
        coord = __builtin_ctzll(current);
        current &= current -1;
        score = score - (1000000 + kingPst[63 - coord]);  
    }
    return score;
}

int gameOver (enum Color turn, struct gameBoard *game) //check if "turn" color lost
{
    struct MoveList l;
    generateMoves(game, &l, turn);
    if (l.count > 0) {
        return Play;
    }
    if (inCheck(game, turn)) return Checkmate;
    return Stalemate;

}
//ASSUME ITS WHITE PLAYING AS MAXIMIZING

int alphabeta(int depth, struct gameBoard *game, enum Color Turn, int alpha, int beta) {
    if (depth == 0 || gameOver(Turn, game)) return evaluate(game);
    long long int = TempPiece;
    struct gameBoard newGame = &game;
    int eval;
    //Maximizing Player
    if (Turn == White) {
        int maxEval = -1000000;
       
        struct MoveList moves;
        generateMoves(game, &moves, Turn);
        struct Move move;

        for (int i = 0; i < moves.count; ++i) {
            move = moves.moves[moves.count];
            if (move.piece = Pawn) {
                checkCollision((1ULL << move.start), game, &newGame);
                newGame.whitePawns -= (1ULL << move.start);
                eval = alphabeta(depth-1, &newGame, Black, alpha, beta);
                newGame.whitePawns = game->whitePawns;
                maxEval = max(eval, maxEval);
                alpha = max(alpha, eval);
                if (beta <= alpha) break;
            }
        }
        return maxEval;
    }
}