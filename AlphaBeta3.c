#include <stdlib.h>
#include "Board2.h"
#include <stdio.h>
#include "AlphaBeta3.h"

int pieceValue[] = {1000000,100,300,300,500,800};
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
int min(int a, int b) {
    return a < b ? a : b;
}
int abs(int a) {
    return a > 0 ? a : -1 * a;
}


void InsertSort(struct Move *moves, int count) {
    if (count < 2) return;
    if (count < 3) {
        if (moves[0].score < moves[1].score){
            struct Move move = moves[0];
            moves[0] = moves[1];
            moves[1] = move;
        }
        return;
    }
    struct Move temp;
    int j = 0;
    for (int i = 1; i < count; ++i) {
        temp = moves[i];
        for (j = i - 1; j >= 0 && moves[j].score < temp.score; --j) {
            moves[j+1] = moves[j];
        }
        moves[j+1] = temp;
    }
}

void printMoves(struct MoveList *moves) {
    printf("Moves: %d \n", moves->count);
    for (int i = 0; i < moves->count; ++i) {
        if (i % 10 == 0) printf("\n");
        printf("[%d : %d - %d - %d", moves->moves[i].start, moves->moves[i].end, moves->moves[i].piece, moves->moves[i].score);
        if (moves->moves[i].piece == Pawn && (moves->moves[i].end/8 == 7 | moves->moves[i].end/8 == 0)) printf(" - %d] ", moves->moves[i].promotion);
        else printf("] ");
    }
    printf("\n");
}

//for debug - broken
void printPieceMoves(struct MoveList *moves, enum Piece piece) {
    printf("Moves: %d \n", moves->count);
    for (int i = 0; i < moves->count; ++i) {
        if (i % 10 == 0) printf("\n");
        if (moves->moves[i].piece != piece) continue;
        printf("[%d : %d - %d - %d", moves->moves[i].start, moves->moves[i].end, moves->moves[i].piece, moves->moves[i].score);
        if (moves->moves[i].piece == Pawn && (moves->moves[i].end/8 == 7 | moves->moves[i].end/8 == 0)) printf(" - %d] ", moves->moves[i].promotion);
        else printf("] ");
    }
    printf("\n");
}

void generateMoves(struct gameBoard *Game, struct MoveList *moves, enum Color color) {
    moves->count = 0;
    int position = 0;
    long long int currentPiece = 0;
    long long int tempPiece = 0;
    struct gameBoard newGame = *Game;
    for (int Piece = Queen; Piece >= King; --Piece){
        enum Piece piece = (enum Piece)Piece;
        if (piece == Pawn) {
            currentPiece = Game->game[color][piece];
            while (currentPiece){
                position = __builtin_ctzll(currentPiece);
                currentPiece &= currentPiece - 1;
                if (position/8 == 1 +5*color && !(((1ULL << (position + 8 - 16 * color)) | (1ULL << (position + 16 - 32 * color))) & AllBitBoard(Game))) { //pawn move 2 forward
                    struct Move move = {position, position + 16 - 32 * color, piece};
                    move.score = 0;
                    newGame.game[color][Pawn] ^= 1ULL << position;
                    newGame.game[color][Pawn] |= 1ULL << (position + 16 - 32 * color);
                    if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                    else if (inCheck(&newGame, !color)) move.score += 200;
                    newGame = *Game;
                    moves->moves[moves->count] = move;
                    moves->count += 1;
                }
                if (((color == White && position/8 < 7) || (color == Black && position/8 > 0)) && !((1ULL << (position + 8 - 16 * color)) & AllBitBoard(Game))) {
                    if ((color == White && position/8 < 6) || (color == Black && position/8 > 1)) { 
                        struct Move move = {position, position + 8 - 16 * color, Pawn};
                        move.score = 0;
                        newGame.game[color][Pawn] ^= 1ULL << position;
                        newGame.game[color][Pawn] |= 1ULL << (position + 8 - 16 * color);
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        newGame = *Game;
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    else {
                        for (int k = Knight; k <= Queen; ++k) {
                            enum Piece t = (enum Piece)k;
                            struct Move move = {position, position + 8 - 16 * color, Pawn, t};
                            move.score = 0;
                            newGame.game[color][Pawn] ^= 1ULL << position;
                            newGame.game[color][k] |= 1ULL << (position + 8 - 16*color);
                            move.score += pieceValue[k];
                            if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                            else if (inCheck(&newGame, !color)) move.score += 200;
                            newGame = *Game;
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                    }
                }
                if (((color == White && position/8 < 7) || (color == Black && position/8 > 0)) && position % 8 > 0 && ((1ULL << (position + 7 - 16 * color)) & ColorBitBoard(Game, !color))) {
                    if ((color == White && position/8 < 6) || (color == Black && position/8 > 1)) {
                        struct Move move = {position, position + 7 - 16 * color, Pawn};
                        move.score = 0;
                        newGame.game[color][Pawn] ^= 1ULL << position;
                        newGame.game[color][Pawn] |= 1ULL << (position + 7 - 16 * color);
                        move.score += pieceValue[CheckCollision(1ULL << (position + 7 - 16 * color), Game, &newGame)-1] * 10 - pieceValue[Pawn];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        newGame = *Game;
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    else {
                        for (int k = Knight; k <= Queen; ++k) {
                            enum Piece t = (enum Piece)k;
                            struct Move move = {position, position + 7 - 16*color, Pawn, t};
                            move.score = 0;
                            newGame.game[color][Pawn] ^= 1ULL << position;
                            newGame.game[color][Pawn] |= 1ULL << (position + 7 - 16*color);
                            move.score += pieceValue[CheckCollision(1ULL << (position + 7 - 16*color), Game, &newGame)-1] * 10 - pieceValue[Pawn];
                            if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                            else if (inCheck(&newGame, !color)) move.score += 200;
                            move.score += pieceValue[k];
                            newGame = *Game;
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                    }
                }
                if (((color == White && position/8 < 7) || (color == Black && position/8 > 0)) && position % 8 < 7 && ((1ULL << (position + 9 - 16 * color)) & ColorBitBoard(Game, !color))) {
                    if (position/8 < 6) {
                        struct Move move = {position, position + 9 - 16 * color, Pawn};
                        move.score = 0;
                        newGame.game[color][Pawn] ^= 1ULL << position;
                        newGame.game[color][Pawn] |= 1ULL << (position + 9 - 16 * color);
                        move.score += pieceValue[CheckCollision(1ULL << (position + 9 - 16 * color), Game, &newGame)-1] * 10 - pieceValue[Pawn];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        newGame = *Game;
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    else {
                        for (int k = Knight; k <= Queen; ++k) {
                            enum Piece t = (enum Piece)k;
                            struct Move move = {position, position + 9 - 16 * color, Pawn, t};
                            move.score = 0;
                            newGame.game[color][Pawn] ^= 1ULL << position;
                            newGame.game[color][Pawn] |= 1ULL << (position + 9 - 16 * color);
                            move.score += pieceValue[CheckCollision(1ULL << (position + 9 - 16 * color), Game, &newGame)-1] * 10 - pieceValue[Pawn];
                            if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                            else if (inCheck(&newGame, !color)) move.score += 200;
                            move.score += pieceValue[k];
                            newGame = *Game;
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                    }
                }
            }
        }
        if (piece == Knight) {
            currentPiece = Game->game[color][Knight];
            while (currentPiece) {
                position = __builtin_ctzll(currentPiece);
                currentPiece &= currentPiece - 1;
                if (position/8 < 7) {
                    if (position % 8 > 1 && !(ColorBitBoard(Game, color) & (1ULL << (position + 6)))) {
                        struct Move move = {position, position + 6, Knight};
                        move.score = 0;
                        newGame.game[color][piece] ^= 1ULL << position;
                        newGame.game[color][piece] |= 1ULL << (position + 6);
                        int x = CheckCollision(1ULL << (position + 6), Game, &newGame);
                        if (x) move.score += pieceValue[x-1]*10 - pieceValue[piece];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        newGame = *Game;
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    if (position % 8 < 6 && !(ColorBitBoard(Game, color) & (1ULL << (position + 10)))) {
                        struct Move move = {position, position + 10, Knight};
                        move.score = 0;
                        newGame.game[color][piece] ^= 1ULL << position;
                        newGame.game[color][piece] |= 1ULL << (position + 10);
                        int x = CheckCollision(1ULL << (position + 10), Game, &newGame);
                        if (x) move.score += pieceValue[x-1]*10 - pieceValue[piece];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        newGame = *Game;
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    if (position/8 < 6) {
                        if (position % 8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position + 15)))) {
                            struct Move move = {position , position + 15, Knight};
                            move.score = 0;
                            newGame.game[color][piece] ^= 1ULL << position;
                            newGame.game[color][piece] |= 1ULL << (position + 15);
                            int x = CheckCollision(1ULL << (position + 15), Game, &newGame);
                            if (x) move.score += pieceValue[x-1]*10 - pieceValue[piece];
                            if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                            else if (inCheck(&newGame, !color)) move.score += 200;
                            newGame = *Game;
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                        if (position % 8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position + 17)))) {
                            struct Move move = {position, position + 17, Knight};
                            move.score = 0;
                            newGame.game[color][piece] ^= 1ULL << position;
                            newGame.game[color][piece] |= 1ULL << (position + 17);
                            int x = CheckCollision(1ULL << (position + 17), Game, &newGame);
                            if (x) move.score += pieceValue[x-1]*10 - pieceValue[piece];
                            if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                            else if (inCheck(&newGame, !color)) move.score += 200;
                            newGame = *Game;
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                    }
                }
                if (position/8 > 0) {
                    if (position % 8 > 1 && !(ColorBitBoard(Game, color) & (1ULL << (position - 10)))) {
                        struct Move move = {position, position - 10, Knight};
                        move.score = 0;
                        newGame.game[color][piece] ^= 1ULL << position;
                        newGame.game[color][piece] |= 1ULL << (position - 10);
                        int x = CheckCollision(1ULL << (position - 10), Game, &newGame);
                        if (x) move.score += pieceValue[x-1]*10 - pieceValue[piece];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        newGame = *Game;
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    if (position % 8 < 6 && !(ColorBitBoard(Game, color) & (1ULL << (position - 6)))) {
                        struct Move move = {position, position - 6, Knight};
                        move.score = 0;
                        newGame.game[color][piece] ^= 1ULL << position;
                        newGame.game[color][piece] |= 1ULL << (position - 6);
                        int x = CheckCollision(1ULL << (position - 6), Game, &newGame);
                        if (x) move.score += pieceValue[x-1]*10 - pieceValue[piece];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        newGame = *Game;
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    if (position/8 > 1) {
                        if (position % 8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position - 17)))) {
                            struct Move move = {position , position - 17, Knight};
                            move.score = 0;
                            newGame.game[color][piece] ^= 1ULL << position;
                            newGame.game[color][piece] |= 1ULL << (position - 17);
                            int x = CheckCollision(1ULL << (position - 17), Game, &newGame);
                            if (x) move.score += pieceValue[x-1]*10 - pieceValue[piece];
                            if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                            else if (inCheck(&newGame, !color)) move.score += 200;
                            newGame = *Game;
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                        if (position % 8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position - 15)))) {
                            struct Move move = {position, position - 15, Knight};
                            move.score = 0;
                            newGame.game[color][piece] ^= 1ULL << position;
                            newGame.game[color][piece] |= 1ULL << (position - 15);
                            int x = CheckCollision(1ULL << (position - 15), Game, &newGame);
                            if (x) move.score += pieceValue[x-1]*10 - pieceValue[piece];
                            if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                            else if (inCheck(&newGame, !color)) move.score += 200;
                            newGame = *Game;
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                    }
                }
            }
        }
        if (piece == Rook || piece == Queen) {
            currentPiece = Game->game[color][Piece];
            while (currentPiece) {
                position = __builtin_ctzll(currentPiece);
                currentPiece &= currentPiece - 1;
                for (int y = position/8 + 1; y <= 7; ++y) {
                    if (ColorBitBoard(Game, color) & (1ULL << (position % 8 + 8*y))) break;
                    struct Move move = {position, position % 8 + 8*y, piece};
                    move.score = 0;
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << (position % 8 + 8*y);
                    int z = CheckCollision(1ULL << (position % 8 + 8*y), Game, &newGame);
                    if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                    if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                    else if (inCheck(&newGame, !color)) move.score += 200;
                    newGame = *Game;
                    moves->moves[moves->count] = move;
                    moves->count += 1;
                    if (ColorBitBoard(Game, !color) & (1ULL << (position % 8 + 8*y))) break;
                }
                for (int y = position/8 - 1; y >= 0; --y) {
                    if (ColorBitBoard(Game, color) & (1ULL << (position % 8 + 8*y))) break;
                    struct Move move = {position, position % 8 + 8*y, piece};
                    move.score = 0;
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << (position % 8 + 8*y);
                    int z = CheckCollision(1ULL << (position % 8 + 8*y), Game, &newGame);
                    if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                    if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                    else if (inCheck(&newGame, !color)) move.score += 200;
                    newGame = *Game;                    
                    moves->moves[moves->count] = move;
                    moves->count += 1;
                    if (ColorBitBoard(Game, !color) & (1ULL << (position % 8 + 8*y))) break;
                }
                for (int x = position % 8 + 1; x <= 7; ++x) {
                    if (ColorBitBoard(Game, color) & (1ULL << ((position/8) *8 + x))) break;
                    struct Move move = {position, (position/8) *8 + x, piece};
                    move.score = 0;
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << ((position/8) *8 + x);
                    int z = CheckCollision(1ULL << ((position/8) *8 + x), Game, &newGame);
                    if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                    if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                    else if (inCheck(&newGame, !color)) move.score += 200;
                    newGame = *Game;
                    moves->moves[moves->count] = move;
                    moves->count += 1;
                    if (ColorBitBoard(Game, !color) & (1ULL << ((position/8) *8 + x))) break;
                }
                for (int x = position % 8 -1; x >= 0; --x) {
                    if (ColorBitBoard(Game, color) & (1ULL << ((position/8) *8 + x))) break;
                    struct Move move = {position, (position/8) *8 + x, piece};
                    move.score = 0;
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << ((position/8) *8 + x);
                    int z = CheckCollision(1ULL << ((position/8) *8 + x), Game, &newGame);
                    if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                    if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                    else if (inCheck(&newGame, !color)) move.score += 200;
                    newGame = *Game;
                    moves->moves[moves->count] = move;
                    moves->count += 1;
                    if (ColorBitBoard(Game, !color) & (1ULL << ((position/8) *8 + x))) break;
                }
            }
        }
        if (piece == Bishop || piece == Queen) {
            currentPiece = Game->game[color][piece];
            while (currentPiece) {
                position = __builtin_ctzll(currentPiece);
                currentPiece &= currentPiece - 1;
                for (int y = position/8 + 1, x = position % 8 + 1; x <= 7 && y <= 7; ++x, ++y) {
                    if (ColorBitBoard(Game, color) & (1ULL << (8*y + x))) break;
                    struct Move move = {position, 8*y + x, piece};
                    move.score = 0;
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << (8*y + x);
                    int z = CheckCollision(1ULL << (8*y + x), Game, &newGame);
                    if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                    if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                    else if (inCheck(&newGame, !color)) move.score += 200;
                    newGame = *Game;
                    moves->moves[moves->count] = move;
                    moves->count += 1;
                    if (ColorBitBoard(Game, !color) & (1ULL << (8*y + x))) break;
                }
                for (int y = position/8 + 1, x = position % 8 - 1; x >= 0 && y <= 7; --x, ++y) {
                    if (ColorBitBoard(Game, color) & (1ULL << (8*y + x))) break;
                    struct Move move = {position, 8*y + x, piece};
                    move.score = 0;
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << (8*y + x);
                    int z = CheckCollision(1ULL << (8*y + x), Game, &newGame);
                    if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                    if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                    else if (inCheck(&newGame, !color)) move.score += 200;
                    newGame = *Game;
                    moves->moves[moves->count] = move;
                    moves->count += 1;
                    if (ColorBitBoard(Game, !color) & (1ULL << (8*y + x))) break;
                }
                for (int y = position/8 -1, x = position % 8 - 1; x >= 0 && y >= 0; --x, --y) {
                    if (ColorBitBoard(Game, color) & (1ULL << (8*y + x))) break;
                    struct Move move = {position, 8*y + x, piece};
                    move.score = 0;
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << (8*y + x);
                    int z = CheckCollision(1ULL << (8*y + x), Game, &newGame);
                    if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                    if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                    else if (inCheck(&newGame, !color)) move.score += 200;
                    newGame = *Game;
                    moves->moves[moves->count] = move;
                    moves->count += 1;
                    if (ColorBitBoard(Game, !color) & (1ULL << (8*y + x))) break;
                }
                for (int y = position/8 - 1, x = position % 8 + 1; x <= 7 && y >= 0; ++x, --y) {
                    if (ColorBitBoard(Game, color) & (1ULL << (8*y + x))) break;
                    struct Move move = {position, 8*y + x, piece};
                    move.score = 0;
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << (8*y + x);
                    int z = CheckCollision(1ULL << (8*y + x), Game, &newGame);
                    if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                    if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                    else if (inCheck(&newGame, !color)) move.score += 200;
                    newGame = *Game;
                    moves->moves[moves->count] = move;
                    moves->count += 1;
                    if (ColorBitBoard(Game, !color) & (1ULL << (8*y + x))) break;
                }
            }
        }
        if (piece == King) {
            tempPiece = Game->game[color][King];
            position = __builtin_ctzll(tempPiece);
            if (tempPiece == 0) {
                continue;
            }
            if (position/8 < 7) {
                if (!(ColorBitBoard(Game, color) & (1ULL << (position + 8)))) {
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << (position + 8);
                    int z = CheckCollision(1ULL << (position + 8), Game, &newGame);
                    if (!inCheck(&newGame, color)) {
                        struct Move move = {position, position + 8, King};
                        move.score = 0;
                        if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    newGame = *Game;
                }
                if (position % 8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position + 7)))) {
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << (position + 7);
                    int z = CheckCollision(1ULL << (position + 7), Game, &newGame);
                    if (!inCheck(&newGame, color)) {
                        struct Move move = {position, position + 7, King};
                        move.score = 0;
                        if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    newGame = *Game;
                }
                if (position % 8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position + 9)))) {
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << (position + 9);
                    int z = CheckCollision(1ULL << (position + 9), Game, &newGame);
                    if (!inCheck(&newGame, color)) {
                        struct Move move = {position, position + 9, King};
                        move.score = 0;
                        if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    newGame = *Game;
                }
            }
            if (position/8 > 0) {
                if (!(ColorBitBoard(Game, color) & (1ULL << (position - 8)))) {
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << (position - 8);
                    int z = CheckCollision(1ULL << (position - 8), Game, &newGame);
                    if (!inCheck(&newGame, color)) {
                        struct Move move = {position, position - 8, King};
                        move.score = 0;
                        if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    newGame = *Game;
                }
                if (position % 8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position - 9)))) {
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << (position -9);
                    int z = CheckCollision(1ULL << (position -9), Game, &newGame);
                    if (!inCheck(&newGame, color)) {
                        struct Move move = {position, position -9, King};
                        move.score = 0;
                        if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    newGame = *Game;
                }
                if (position % 8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position - 7)))) {
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << (position -7);
                    int z = CheckCollision(1ULL << (position -7), Game, &newGame);
                    if (!inCheck(&newGame, color)) {
                        struct Move move = {position, position -7, King};
                        move.score = 0;
                        if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    newGame = *Game;
                }
            }
            if (position % 8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position - 1)))) {
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << (position -1);
                    int z = CheckCollision(1ULL << (position -1), Game, &newGame);
                    if (!inCheck(&newGame, color)) {
                        struct Move move = {position, position -1, King};
                        move.score = 0;
                        if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    newGame = *Game;
            }
            if (position % 8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position + 1)))) {
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << (position +1);
                    int z = CheckCollision(1ULL << (position + 1), Game, &newGame);
                    if (!inCheck(&newGame, color)) {
                        struct Move move = {position, position + 1, King};
                        move.score = 0;
                        if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    newGame = *Game;
            }
            //castle
            if (!inCheck(Game, color) && ((color == White && Game->WhiteCastle != Neither) || (color == Black && Game->BlackCastle != Neither))) {
                if (color == White) {
                    //check left castle
                    if (Game->WhiteCastle == WhiteBoth || Game->WhiteCastle == WhiteQueen) {
                        tempPiece = (1ULL << 4) | (1ULL << 5) | (1ULL << 6);
                        if (!(tempPiece & AllBitBoard(Game)) && !(isSquareAttacked(4, Game, White) || isSquareAttacked(5, Game, White))) {
                            struct Move move = {3, 5, King};
                            move.score = 100;
                            newGame.game[color][piece] ^= 1ULL << 3;
                            newGame.game[color][piece] |= 1ULL << 5;
                            newGame.game[color][Rook] ^= 1ULL << 7;
                            newGame.game[color][Rook] |= 1ULL << 4;
                            if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                            else if (inCheck(&newGame, !color)) move.score += 200;
                            newGame = *Game;
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                    }
                    //check right castle
                    if (Game->WhiteCastle == WhiteBoth || Game->WhiteCastle == WhiteKing) {
                        tempPiece = (1ULL << 2) | (1ULL << 1);
                        if (!(tempPiece & AllBitBoard(Game)) && !(isSquareAttacked(2, Game, White) || isSquareAttacked(1, Game, White))){
                            struct Move move = {3, 1, King};
                            move.score = 100;
                            newGame.game[color][piece] ^= 1ULL << position;
                            newGame.game[color][piece] |= 1ULL << 1;
                            newGame.game[color][Rook] ^= 1ULL;
                            newGame.game[color][Rook] |= 1ULL << 2;
                            if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                            else if (inCheck(&newGame, !color)) move.score += 200;
                            newGame = *Game;
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                    }
                }
                else if (color == Black) {
                    //check left castle
                    if (Game->BlackCastle == BlackBoth || Game->BlackCastle == BlackQueen) {
                        tempPiece = (1ULL << 62) | (1ULL << 61) | (1ULL << 60);
                        if (!(tempPiece & AllBitBoard(Game)) && !(isSquareAttacked(60, Game, Black) || isSquareAttacked(61, Game, Black))){
                            struct Move move = {59, 61, King};
                            move.score = 100;
                            newGame.game[color][piece] ^= 1ULL << position;
                            newGame.game[color][piece] |= 1ULL << (61);
                            newGame.game[color][Rook] ^= 1ULL << 63;
                            newGame.game[color][Rook] |= 1ULL << 60;
                            if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                            else if (inCheck(&newGame, !color)) move.score += 200;
                            newGame = *Game;
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                    }
                    //check right castle
                    if (Game->BlackCastle == BlackBoth || Game->BlackCastle == BlackKing) {
                        tempPiece = (1ULL << 58) | (1ULL << 57);
                        if (!(tempPiece & AllBitBoard(Game)) && !(isSquareAttacked(58, Game, Black) || isSquareAttacked(57, Game, Black))){
                            struct Move move = {59, 57, King};
                            move.score = 100;
                            newGame.game[color][piece] ^= 1ULL << position;
                            newGame.game[color][piece] |= 1ULL << 57;
                            newGame.game[color][Rook] ^= 1ULL << 56;
                            newGame.game[color][Rook] |= 1ULL << 58;
                            if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                            else if (inCheck(&newGame, !color)) move.score += 200;
                            newGame = *Game;
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                    }
                }
                    
                
            }
        }
    }
}

int inCheck(struct gameBoard *Game, enum Color turn) {
    return isSquareAttacked(__builtin_ctzll(Game->game[turn][King]), Game, turn);
}

int isSquareAttacked(int position, struct gameBoard *Game, enum Color turn) //check if "turn" color is in check
{    
    //check for pawn attacks
    if (turn == White){
        if (position/8 < 6){
            long long int PossiblePawn = 0b0ULL;
            if (position % 8 > 0) PossiblePawn += (Game->game[turn][King] << 7);
            if (position % 8 < 7) PossiblePawn += (Game->game[turn][King] << 9);
            if (PossiblePawn & Game->game[!turn][Pawn]) return 1;
        }
    }
    else {
        if (position/8 > 1){
            long long int PossiblePawn = 0b0ULL;
            if (position % 8 > 0) PossiblePawn += (Game->game[turn][King] >> 7);
            if (position % 8 < 7) PossiblePawn += (Game->game[turn][King] >> 9);
            if (PossiblePawn & Game->game[!turn][Pawn]) return 1;
        }
    }
    //check for knight attakcs
    if (position/8 < 7) {
        long long int possibleKnight = 0b0ULL;
        if (position % 8 > 1) possibleKnight += (Game->game[turn][King] << 10);
        if (position % 8 < 6) possibleKnight += (Game->game[turn][King] << 6);
        if (position/8 < 6) {
            if (position % 8 > 0) possibleKnight += (Game->game[turn][King] << 17);
            if (position % 8 < 7) possibleKnight += (Game->game[turn][King] << 15);
        }
        if (possibleKnight & Game->game[!turn][Knight]) return 1;
    }
    if (position/8 > 0) {
        long long int possibleKnight = 0b0ULL;
        if (position % 8 > 1) possibleKnight += (Game->game[turn][King] >> 10);
        if (position % 8 < 6) possibleKnight += (Game->game[turn][King] >> 6);
        if (position/8 > 1){
            if (position % 8 > 0) possibleKnight += (Game->game[turn][King] >> 17);
            if (position % 8 < 7) possibleKnight += (Game->game[turn][King] >> 15);
        }
        if (possibleKnight & Game->game[!turn][Knight]) return 1;
    }
    //king attacks
    if (position/8 < 7) {
        if ((1ULL << (position + 8)) & Game->game[!turn][King]) return 1;
        if (position%8 < 7) {
            if ((1ULL << (position + 9)) & Game->game[!turn][King]) return 1;
        }
        if (position%8 > 0) {
            if ((1ULL << (position + 7)) & Game->game[!turn][King]) return 1;
        }
    }
    if (position/8 > 0) {
        if ((1ULL << (position - 8)) & Game->game[!turn][King]) return 1;
        if (position%8 < 7) {
            if ((1ULL << (position - 7)) & Game->game[!turn][King]) return 1;
        }
        if (position%8 > 0) {
            if ((1ULL << (position - 9)) & Game->game[!turn][King]) return 1;
        }
    }
    if (position % 8 > 0) {
        if ((1ULL << (position - 1)) & Game->game[!turn][King]) return 1;
    }
    if (position % 8 < 7) {
        if ((1ULL << (position + 1)) & Game->game[!turn][King]) return 1;
    }

    //Check Vertical Up
    for (long long int current = Game->game[turn][King] << 8; __builtin_ctzll(current)/8 < 8; current = current << 8) {
        if ((current & Game->game[!turn][Rook]) | (current & Game->game[!turn][Queen])) return 1;
        if (current & AllBitBoard(Game)) break;
    }

    //Check Vertival Down
    for (long long int current = Game->game[turn][King] >> 8; current != 0; current = current >> 8) {
        if ((current & Game->game[!turn][Rook]) | (current & Game->game[!turn][Queen])) return 1;
        if (current & AllBitBoard(Game)) break;
    }

    //Check Horizontal Left
    for (long long int current = Game->game[turn][King] << 1; __builtin_ctzll(current)%8 < 8 && __builtin_ctzll(current)%8 > 0; current = current << 1) {
        if ((current & Game->game[!turn][Rook]) | (current & Game->game[!turn][Queen])) return 1;
        if (current & AllBitBoard(Game)) break;
    }
    //Check Horizontal Right
    for (long long int current = Game->game[turn][King] >> 1; __builtin_ctzll(current)%8 >= 0 && current != 0 && __builtin_ctzll(current)%8 < 7; current = current >> 1) {
        if ((current & Game->game[!turn][Rook]) | (current & Game->game[!turn][Queen])) return 1;
        if (current & AllBitBoard(Game)) break;
    }

    //Check Diagonal Top left
    for (long long int current = Game->game[turn][King] << 9; __builtin_ctzll(current)%8 < 8 && __builtin_ctzll(current)%8 > 0 && __builtin_ctzll(current)/8 < 8; current = current << 9){
        if ((Game->game[!turn][Bishop] | Game->game[!turn][Queen]) & current) return 1;
        if (current & AllBitBoard(Game)) break; 
    }

    //Check Diagonal Top Right
    for (long long int current = Game->game[turn][King] << 7; __builtin_ctzll(current)%8 < 7 && __builtin_ctzll(current)/8 < 8; current = current << 7) {
        if ((Game->game[!turn][Bishop] | Game->game[!turn][Queen]) & current) return 1;
        if (current & AllBitBoard(Game)) break; 
    }

    //Check Diagonal Bottom Left
    for (long long int current = Game->game[turn][King] >> 7; __builtin_ctzll(current)%8 < 8 && __builtin_ctzll(current)%8 > 0 && current != 0; current = current >> 7){
        if ((Game->game[!turn][Bishop] | Game->game[!turn][Queen]) & current) return 1;
        if (current & AllBitBoard(Game)) break; 
    }

    //Check Diagonal Bottom Right
    for (long long int current = Game->game[turn][King] >> 9; __builtin_ctzll(current)%8 < 7 && current != 0; current = current >> 9){
        if ((Game->game[!turn][Bishop] | Game->game[!turn][Queen]) & current) return 1;
        if (current & AllBitBoard(Game)) break; 
    }
    return 0;    
}

int evaluate(struct gameBoard *Game, enum Color turn){
    /*int x = gameOver(turn, Game);
    if (x == Stalemate) return 0;
    if (x == Checkmate) {
        if (turn == White) return -10000000;
        else return 10000000;
    }*/
    
    int score = 0;
    int coord;
    unsigned long long int current;

    current = Game->game[White][Pawn];
    while (current){
        coord = __builtin_ctzll(current);
        current &= current -1;
        score = score + 100 + pawnPst[coord];
    }
    current = Game->game[White][Knight];
    while (current){
        coord = __builtin_ctzll(current);
        current &= current -1;
        score = score + 300 + knightPst[coord];
    }
    current = Game->game[White][Bishop];
    while (current){
        coord = __builtin_ctzll(current);
        current &= current -1;
        score = score + 300 + bishopPst[coord];
    }
    current = Game->game[White][Rook];
    while (current){
        coord = __builtin_ctzll(current);
        current &= current -1;
        score = score + 500 + rookPst[coord];
    }
    current = Game->game[White][Queen];
    while (current){
        coord = __builtin_ctzll(current);
        current &= current -1;
        score = score + 800 + queenPst[coord];
    }
    current = Game->game[White][King];
    while (current){
        coord = __builtin_ctzll(current);
        current &= current -1;
        score = score + 1000000 + kingPst[coord];
    }
    //Black
    current = Game->game[Black][Pawn];
    while (current){
        coord = __builtin_ctzll(current);
        current &= current -1;
        score = score - (100 + pawnPst[63 - coord]);
    }
    current = Game->game[Black][Knight];
    while (current){
        coord = __builtin_ctzll(current);
        current &= current -1;
        score = score - (300 + knightPst[63 - coord]);
    }
    current = Game->game[Black][Bishop];
    while (current){
        coord = __builtin_ctzll(current);
        current &= current -1;
        score = score - (300 + bishopPst[63 - coord]);
    }
    current = Game->game[Black][Rook];
    while (current){
        coord = __builtin_ctzll(current);
        current &= current -1;
        score = score - (500 + rookPst[63 - coord]);
    }
    current = Game->game[Black][Queen];
    while (current){
        coord = __builtin_ctzll(current);
        current &= current -1;
        score = score - (800 + queenPst[63 - coord]);
    }
    current = Game->game[Black][King];
    while (current){
        coord = __builtin_ctzll(current);
        current &= current -1;
        score = score - (1000000 + kingPst[63 - coord]);  
    }
    //if (score > 10000) printf("BLACKKING: %lld\n", Game->game[Black][King]);
    return score;
}

int MoreMoves(struct gameBoard *Game, enum Color color) {
    int position = 0;
    long long int currentPiece = 0;
    long long int tempPiece = 0;
    struct gameBoard copyGame = *Game;
    int reset = 0;
    for (int Piece = Queen; Piece >= King; --Piece){
        enum Piece piece = (enum Piece)Piece;
        if (piece == Pawn) {
            if (color == White) {
                currentPiece = Game->game[color][piece];
                while (currentPiece){
                    position = __builtin_ctzll(currentPiece);
                    currentPiece &= currentPiece - 1;
                    if (position/8 == 1 && !(((1ULL << (position + 8)) | (1ULL << (position + 16))) & AllBitBoard(Game))) { //pawn move 2 forward
                        tempPiece = Game->game[color][piece];
                        copyGame.game[color][piece] += (1ULL << position + 16) - (1ULL << position);
                        if (!inCheck(&copyGame, color)) {
                            return 1;
                        }
                        copyGame.game[color][piece] = tempPiece;
                    }
                    if (position/8 < 7 && !((1ULL << (position + 8)) & AllBitBoard(Game))) {
                        tempPiece = Game->game[color][piece];
                        copyGame.game[color][piece] += (1ULL << position + 8) - (1ULL << position);
                        if (!inCheck(&copyGame, color)) {
                            return 1;
                        }
                        copyGame.game[color][piece] = tempPiece;
                    }
                    if (position/8 < 7 && position % 8 > 0 && ((1ULL << (position + 9)) & ColorBitBoard(Game, !color))) {
                        tempPiece = Game->game[color][piece];
                        copyGame.game[color][piece] += (1ULL << position + 9) - (1ULL << position);
                        if (CheckCollision(1ULL << (position + 9), Game, &copyGame)) reset = 1;
                        if (!inCheck(&copyGame, color)) {
                            return 1;
                        }
                        if (reset) {
                            copyGame = *Game;
                            reset = 0;
                        }
                        else {
                            copyGame.game[color][piece] = tempPiece;
                        }
                    }
                    if (position/8 < 7 && position % 8 < 7 && ((1ULL << (position + 7)) & ColorBitBoard(Game, !color))) {
                        tempPiece = Game->game[color][piece];
                        copyGame.game[color][piece] += (1ULL << position + 7) - (1ULL << position);
                        if (CheckCollision(1ULL << (position + 7), Game, &copyGame)) reset = 1;
                        if (!inCheck(&copyGame, color)) {
                            return 1;
                        }
                        if (reset) {
                            copyGame = *Game;
                            reset = 0;
                        }
                        else {
                            copyGame.game[color][piece] = tempPiece;
                        }
                    }
                }
            }
            else {
                currentPiece = Game->game[color][piece];
                while (currentPiece) {
                    position = __builtin_ctzll(currentPiece);
                    currentPiece &= currentPiece - 1;
                    if (position/8 == 6 && !(((1ULL << (position - 8)) | (1ULL << (position - 16))) & AllBitBoard(Game))) {
                        tempPiece = Game->game[color][piece];
                        copyGame.game[color][piece] += (1ULL << position - 16) - (1ULL << position);
                        if (!inCheck(&copyGame, color)) {
                            return 1;
                        }
                        copyGame.game[color][piece] = tempPiece;
                    }
                    if (position/8 > 0 && !((1ULL << (position - 8)) & AllBitBoard(Game))) {
                        tempPiece = Game->game[color][piece];
                        copyGame.game[color][piece] += (1ULL << position - 8) - (1ULL << position);
                        if (!inCheck(&copyGame, color)) {
                            return 1;
                        }
                        copyGame.game[color][piece] = tempPiece;
                    }
                    if (position/8 > 0 && position % 8 > 0 && ((1ULL << position - 9) & ColorBitBoard(Game, !color))) {
                        tempPiece = Game->game[color][piece];
                        copyGame.game[color][piece] += (1ULL << position - 9) - (1ULL << position);
                        if (CheckCollision(1ULL << (position - 9), Game, &copyGame)) reset = 1;
                        if (!inCheck(&copyGame, color)) {
                            return 1;
                        }
                        if (reset) {
                            copyGame = *Game;
                            reset = 0;
                        }
                        else {
                            copyGame.game[color][piece] = tempPiece;
                        }
                    }
                    if (position/8 > 0 && position % 8 < 7 && ((1ULL << (position - 7) & ColorBitBoard(Game, !color)))) {
                        tempPiece = Game->game[color][piece];
                        copyGame.game[color][piece] += (1ULL << position - 7) - (1ULL << position);
                        if (CheckCollision(1ULL << (position - 7), Game, &copyGame)) reset = 1;
                        if (!inCheck(&copyGame, color)) {
                            return 1;
                        }
                        if (reset) {
                            copyGame = *Game;
                            reset = 0;
                        }
                        else {
                            copyGame.game[color][piece] = tempPiece;
                        }
                    }
                }
            }
        }
        if (piece == Knight) {
            currentPiece = Game->game[color][Knight];
            while (currentPiece) {
                position = __builtin_ctzll(currentPiece);
                currentPiece &= currentPiece - 1;
                if (position/8 < 7) {
                    if (position % 8 > 1 && !(ColorBitBoard(Game, color) & (1ULL << (position + 6)))) {
                        tempPiece = Game->game[color][Knight];
                        copyGame.game[color][piece] += (1ULL << position + 6) - (1ULL << position);
                        if (CheckCollision(1ULL << (position + 6), Game, &copyGame)) reset = 1;
                        if (!inCheck(&copyGame, color)) {
                            return 1;
                        }
                        if (reset) {
                            copyGame = *Game;
                            reset = 0;
                        }
                        else {
                            copyGame.game[color][Knight] = tempPiece;
                        }
                    }
                    if (position % 8 < 6 && !(ColorBitBoard(Game, color) & (1ULL << (position + 10)))) {
                        tempPiece = Game->game[color][Knight];
                        copyGame.game[color][piece] += (1ULL << position + 10) - (1ULL << position);
                        if (CheckCollision(1ULL << (position + 10), Game, &copyGame)) reset = 1;
                        if (!inCheck(&copyGame, color)) {
                            return 1;
                        }
                        if (reset) {
                            copyGame = *Game;
                            reset = 0;
                        }
                        else {
                            copyGame.game[color][Knight] = tempPiece;
                        }
                    }
                    if (position/8 < 6) {
                        if (position % 8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position + 15)))) {
                            tempPiece = Game->game[color][Knight];
                            copyGame.game[color][piece] += (1ULL << position + 15) - (1ULL << position);
                            if (CheckCollision(1ULL << (position + 15), Game, &copyGame)) reset = 1;
                            if (!inCheck(&copyGame, color)) {
                                return 1;
                            }
                            if (reset) {
                                copyGame = *Game;
                                reset = 0;
                            }
                            else {
                                copyGame.game[color][Knight] = tempPiece;
                            }
                        }
                        if (position % 8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position + 17)))) {
                            tempPiece = Game->game[color][Knight];
                            copyGame.game[color][piece] += (1ULL << position + 17) - (1ULL << position);
                            if (CheckCollision(1ULL << (position + 17), Game, &copyGame)) reset = 1;
                            if (!inCheck(&copyGame, color)) {
                                return 1;
                            }
                            if (reset) {
                                copyGame = *Game;
                                reset = 0;
                            }
                            else {
                                copyGame.game[color][Knight] = tempPiece;
                            }
                        }
                    }
                }
                if (position/8 > 0) {
                    if (position % 8 > 1 && !(ColorBitBoard(Game, color) & (1ULL << (position - 10)))) {
                        tempPiece = Game->game[color][Knight];
                        copyGame.game[color][piece] += (1ULL << position - 10) - (1ULL << position);
                        if (CheckCollision(1ULL << (position - 10), Game, &copyGame)) reset = 1;
                        if (!inCheck(&copyGame, color)) {
                            return 1;
                        }
                        if (reset) {
                            copyGame = *Game;
                            reset = 0;
                        }
                        else {
                            copyGame.game[color][Knight] = tempPiece;
                        }
                    }
                    if (position % 8 < 6 && !(ColorBitBoard(Game, color) & (1ULL << (position - 6)))) {
                        tempPiece = Game->game[color][Knight];
                        copyGame.game[color][piece] += (1ULL << position - 6) - (1ULL << position);
                        if (CheckCollision(1ULL << (position - 6), Game, &copyGame)) reset = 1;
                        if (!inCheck(&copyGame, color)) {
                            return 1;
                        }
                        if (reset) {
                            copyGame = *Game;
                            reset = 0;
                        }
                        else {
                            copyGame.game[color][Knight] = tempPiece;
                        }
                    }
                    if (position/8 > 1) {
                        if (position % 8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position - 17)))) {
                            tempPiece = Game->game[color][Knight];
                            copyGame.game[color][piece] += (1ULL << position - 17) - (1ULL << position);
                            if (CheckCollision(1ULL << (position - 17), Game, &copyGame)) reset = 1;
                            if (!inCheck(&copyGame, color)) {
                                return 1;
                            }
                            if (reset) {
                                copyGame = *Game;
                                reset = 0;
                            }
                            else {
                                copyGame.game[color][Knight] = tempPiece;
                            }
                        }
                        if (position % 8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position - 15)))) {
                            tempPiece = Game->game[color][Knight];
                            copyGame.game[color][piece] += (1ULL << position - 15) - (1ULL << position);
                            if (CheckCollision(1ULL << (position - 15), Game, &copyGame)) reset = 1;
                            if (!inCheck(&copyGame, color)) {
                                return 1;
                            }
                            if (reset) {
                                copyGame = *Game;
                                reset = 0;
                            }
                            else {
                                copyGame.game[color][Knight] = tempPiece;
                            }
                        }
                    }
                }
            }
        }
        if (piece == Rook || piece == Queen) {
            currentPiece = Game->game[color][Piece];
            while (currentPiece) {
                position = __builtin_ctzll(currentPiece);
                currentPiece &= currentPiece - 1;
                for (int x = position % 8,  y = position/8 + 1; y < 7 && !(ColorBitBoard(Game, color) & (1ULL << (8*y + x))); ++y) {
                    copyGame.game[color][piece] += (1ULL << 8*y + x) - (1ULL << position);
                    int t = CheckCollision(1ULL << (8*y + x), Game, &copyGame);
                    if (!inCheck(&copyGame, color)) return 1;
                    copyGame = *Game;
                    if (t) break;
                }
                for (int x = position % 8,  y = position/8 - 1; y > 0 && !(ColorBitBoard(Game, color) & (1ULL << (8*y + x))); --y) {
                    copyGame.game[color][piece] += (1ULL << 8*y + x) - (1ULL << position);
                    int t = CheckCollision(1ULL << (8*y + x), Game, &copyGame);
                    if (!inCheck(&copyGame, color)) return 1;
                    copyGame = *Game;
                    if (t) break;
                }
                for (int x = position % 8 - 1, y = position/8; x > 0 && !(ColorBitBoard(Game, color) & (1ULL << (8*y + x))); --x) {
                    copyGame.game[color][piece] += (1ULL << 8*y + x) - (1ULL << position);
                    int t = CheckCollision(1ULL << (8*y + x), Game, &copyGame);
                    if (!inCheck(&copyGame, color)) return 1;
                    copyGame = *Game;
                    if (t) break;
                }
                for (int x = position % 8 + 1, y = position/8; x < 7 && !(ColorBitBoard(Game, color) & (1ULL << (8*y + x))); --x) {
                    copyGame.game[color][piece] += (1ULL << 8*y + x) - (1ULL << position);
                    int t = CheckCollision(1ULL << (8*y + x), Game, &copyGame);
                    if (!inCheck(&copyGame, color)) return 1;
                    copyGame = *Game;
                    if (t) break;
                }
            }
        }
        if (piece == Bishop || piece == Queen || piece == King) {
            currentPiece = Game->game[color][piece];
            while (currentPiece) {
                position = __builtin_ctzll(currentPiece);
                currentPiece &= currentPiece - 1;
                for (int x = position % 8 + 1,  y = position/8 + 1; y < 7 && x < 7 && !(ColorBitBoard(Game, color) & (1ULL << (8*y + x))); ++y, ++x) {
                    copyGame.game[color][piece] += (1ULL << 8*y + x) - (1ULL << position);
                    int t = CheckCollision(1ULL << (8*y + x), Game, &copyGame);
                    if (!inCheck(&copyGame, color)) return 1;
                    copyGame = *Game;
                    if (t) break;
                }
                for (int x = position % 8 - 1,  y = position/8 + 1; y < 7 && x > 0 && !(ColorBitBoard(Game, color) & (1ULL << (8*y + x))); ++y, --x) {
                    copyGame.game[color][piece] += (1ULL << 8*y + x) - (1ULL << position);
                    int t = CheckCollision(1ULL << (8*y + x), Game, &copyGame);
                    if (!inCheck(&copyGame, color)) return 1;
                    copyGame = *Game;
                    if (t) break;
                }
                for (int x = position % 8 - 1,  y = position/8 - 1; y > 0 && x > 0 && !(ColorBitBoard(Game, color) & (1ULL << (8*y + x))); --y, --x) {
                    copyGame.game[color][piece] += (1ULL << 8*y + x) - (1ULL << position);
                    int t = CheckCollision(1ULL << (8*y + x), Game, &copyGame);
                    if (!inCheck(&copyGame, color)) return 1;
                    copyGame = *Game;
                    if (t) break;
                }
                for (int x = position % 8 + 1,  y = position/8 - 1; y > 0 && x < 7 && !(ColorBitBoard(Game, color) & (1ULL << (8*y + x))); --y, ++x) {
                    copyGame.game[color][piece] += (1ULL << 8*y + x) - (1ULL << position);
                    int t = CheckCollision(1ULL << (8*y + x), Game, &copyGame);
                    if (!inCheck(&copyGame, color)) return 1;
                    copyGame = *Game;
                    if (t) break;
                }
            }
        }
        if (piece == King) {
            position = __builtin_ctzll(Game->game[color][King]);
            if (position/8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position + 8)))) {
                copyGame.game[color][piece] += (1ULL << position + 8) - (1ULL << position);
                CheckCollision(1ULL << (position + 8), Game, &copyGame);
                if (!inCheck(&copyGame, color)) return 1;
                copyGame = *Game;
            }
            if (position/8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position - 8)))){
                copyGame.game[color][piece] += (1ULL << position - 8) - (1ULL << position);
                CheckCollision(1ULL << (position - 8), Game, &copyGame);
                if (!inCheck(&copyGame, color)) return 1;
                copyGame = *Game;
            }
            if (position % 8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position - 1)))){
                copyGame.game[color][piece] += (1ULL << position - 1) - (1ULL << position);
                CheckCollision(1ULL << (position - 1), Game, &copyGame);
                if (!inCheck(&copyGame, color)) return 1;
                copyGame = *Game;
            }
            if (position % 8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position + 1)))){     
                copyGame.game[color][piece] += (1ULL << position + 1) - (1ULL << position);
                CheckCollision(1ULL << (position + 1), Game, &copyGame);
                if (!inCheck(&copyGame, color)) return 1;
                copyGame = *Game;
            }
            if (position/8 < 7 && position % 8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position + 9)))){
                copyGame.game[color][piece] += (1ULL << position + 9) - (1ULL << position);
                CheckCollision(1ULL << (position + 9), Game, &copyGame);
                if (!inCheck(&copyGame, color)) return 1;
                copyGame = *Game;
            }
            if (position/8 < 7 && position % 8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position + 7)))){
                copyGame.game[color][piece] += (1ULL << position + 7) - (1ULL << position);
                CheckCollision(1ULL << (position + 7), Game, &copyGame);
                if (!inCheck(&copyGame, color)) return 1;
                copyGame = *Game;
            }
            if (position/8 > 0 && position % 8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position - 9)))){
                copyGame.game[color][piece] += (1ULL << position - 9) - (1ULL << position);
                CheckCollision(1ULL << (position - 9), Game, &copyGame);
                if (!inCheck(&copyGame, color)) return 1;
                copyGame = *Game;
            }
            if (position/8 > 0 && position % 8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position - 7)))){
                copyGame.game[color][piece] += (1ULL << position - 7) - (1ULL << position);
                CheckCollision(1ULL << (position - 7), Game, &copyGame);
                if (!inCheck(&copyGame, color)) return 1;
                copyGame = *Game;
            }
        }
    }
    return 0;
}\

int gameOver (enum Color turn, struct gameBoard *game) //check if "turn" color lost
{
    if (MoreMoves(game, turn)) return Play;
    if (inCheck(game, turn)) return Checkmate;
    return Stalemate;
}

//ASSUME ITS WHITE PLAYING AS MAXIMIZING
int alphabeta(int depth, struct gameBoard *Game, enum Color Turn, int alpha, int beta, int maximizingPlayer, struct Move *Move, int *nodes) {
    *nodes += 1;
    int x = gameOver(Turn, Game);
    if (x == Stalemate) return 0;
    else if (x == Checkmate) {
        if (Turn == White) return -10000000 + depth;
        else return 10000000 - depth;
    }
    if (depth == 0) return evaluate(Game, Turn);
    
    long long int TempPiece;
    int eval;

    struct MoveList moves;
    generateMoves(Game, &moves, Turn);
    InsertSort(moves.moves, moves.count);
    //if (depth == DEPTH) printMoves(&moves); // Debug
    
    //Maximizing Player
    if (maximizingPlayer) {
        int maxEval = -10000000;
        struct Move move;
        for (int i = 0; i < moves.count; ++i) {
            struct gameBoard newGame = *Game;
            move = moves.moves[i];
            CheckCollision((1ULL << move.end), Game, &newGame);
            newGame.game[Turn][move.piece] ^= (1ULL << move.start);
            newGame.game[Turn][move.piece] |= (1ULL << move.end);
            if (inCheck(&newGame, Turn)) continue;
            //check for promotion
            if (move.piece == Pawn && (move.end/8 == 7 - 7*Turn)) {
                newGame.game[Turn][Pawn] ^= (1ULL << move.end);
                newGame.game[Turn][move.promotion] |= (1ULL << move.end);
            }
            //check for castle
            if (move.piece == King && abs(move.start - move.end) == 2) {
                if (Turn == White) {
                    newGame.WhiteCastle = Neither;
                    if (move.end == 5) {
                        newGame.game[White][Rook] ^= (1ULL << 7);
                        newGame.game[White][Rook] |= (1ULL << 4);
                    }
                    else {
                        newGame.game[White][Rook] ^= (1ULL);
                        newGame.game[White][Rook] |= (1ULL << 2);
                    }
                }
                else {
                    newGame.BlackCastle = Neither;
                    if (move.end == 61) {
                        newGame.game[Black][Rook] ^= (1ULL << 63);
                        newGame.game[Black][Rook] |= (1ULL << 60);
                    }
                    else {
                        newGame.game[Black][Rook] ^= (1ULL << 56);
                        newGame.game[Black][Rook] |= (1ULL << 58);
                    }
                }
            }
            else if (move.piece == King) {
                if (Turn == White) newGame.WhiteCastle = Neither;
                else newGame.BlackCastle = Neither;
            }
            if (move.piece == Rook) {
                if (Turn == White && Game->WhiteCastle != Neither) {
                    if (move.start == 0) {
                        if (Game->WhiteCastle == WhiteBoth) newGame.WhiteCastle == WhiteQueen;
                        else newGame.WhiteCastle = Neither;
                    }
                    else if (move.start == 7) {
                        if (Game->WhiteCastle == WhiteBoth) newGame.WhiteCastle == WhiteKing;
                        else newGame.WhiteCastle = Neither;
                    }
                }
                else if (Turn == Black && Game->BlackCastle != Neither){
                    if (move.start == 63) {
                        if (Game->BlackCastle == BlackBoth) newGame.BlackCastle = BlackKing;
                        else newGame.BlackCastle = Neither;
                    }
                    else if (move.start == 56) {
                        if (Game->BlackCastle == BlackBoth) newGame.BlackCastle = BlackQueen;
                        else newGame.BlackCastle = Neither;
                    }
                } 
            }

            eval = alphabeta(depth-1, &newGame, !Turn, alpha, beta, 0, Move, nodes);
            if (eval > maxEval) {
                maxEval = eval;
                if (depth == DEPTH) *Move = move;
            }
            alpha = max(alpha, eval);
            if (beta <= alpha) break;
        }
        return maxEval;
    }
    else {
        int minEval = 10000000;
        struct Move move;
        for (int i = 0; i < moves.count; ++i){
            struct gameBoard newGame = *Game;
            move = moves.moves[i];
            if (move.start == 44 && move.end == 8 && depth == 8) printf("Explored at %d\n", depth);
            CheckCollision((1ULL << move.end), Game, &newGame);
            newGame.game[Turn][move.piece] ^= (1ULL << move.start);
            newGame.game[Turn][move.piece] |= (1ULL << move.end);
            if (inCheck(&newGame, Turn)) continue;
            //Check promotion
            if (move.piece == Pawn && (move.end/8 == 7 - 7*Turn)) {
                newGame.game[Turn][Pawn] ^= (1ULL << move.end);
                newGame.game[Turn][move.promotion] |= (1ULL << move.end);
            }
            //check for castle
            if (move.piece == King && abs(move.start - move.end) == 2) {
                if (Turn == White) {
                    newGame.WhiteCastle = Neither;
                    if (move.end = 5) {
                        newGame.game[White][Rook] ^= (1ULL << 7);
                        newGame.game[White][Rook] |= (1ULL << 4);
                    }
                    else {
                        newGame.game[White][Rook] ^= (1ULL);
                        newGame.game[White][Rook] |= (1ULL << 2);
                    }
                }
                else {
                    newGame.BlackCastle = Neither;
                    if (move.end == 61) {
                        newGame.game[Black][Rook] ^= (1ULL << 63);
                        newGame.game[Black][Rook] |= (1ULL << 60);
                    }
                    else {
                        newGame.game[Black][Rook] ^= (1ULL << 56);
                        newGame.game[Black][Rook] |= (1ULL << 58);
                    }
                }
            }
            else if (move.piece == King) {
                if (Turn == White) newGame.WhiteCastle = Neither;
                else newGame.BlackCastle = Neither;
            }
            if (move.piece == Rook) {
                if (Turn == White && Game->WhiteCastle != Neither) {
                    if (move.start == 0) {
                        if (Game->WhiteCastle == WhiteBoth) newGame.WhiteCastle == WhiteQueen;
                        else newGame.WhiteCastle = Neither;
                    }
                    else if (move.start == 7) {
                        if (Game->WhiteCastle == WhiteBoth) newGame.WhiteCastle == WhiteKing;
                        else newGame.WhiteCastle = Neither;
                    }
                }
                else if (Turn == Black && Game->BlackCastle != Neither){
                    if (move.start == 63) {
                        if (Game->BlackCastle == BlackBoth) newGame.BlackCastle = BlackKing;
                        else newGame.BlackCastle = Neither;
                    }
                    else if (move.start == 56) {
                        if (Game->BlackCastle == BlackBoth) newGame.BlackCastle = BlackQueen;
                        else newGame.BlackCastle = Neither;
                    }
                } 
            }
            eval = alphabeta(depth-1, &newGame, !Turn, alpha, beta, 1, Move, nodes);
            if (eval < minEval) {
                minEval = eval;
                if (depth == DEPTH) *Move = move;
            }
            beta = min(beta, eval);
            if (beta <= alpha) break;
        }
        return minEval;
    }
}