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
int min(int a, int b) {
    return a < b ? a : b;
}

void printMoves(struct MoveList *moves) {
    printf("Moves: %d \n", moves->count);
    for (int i = 0; i < moves->count; ++i) {
        if (i % 10 == 0) printf("\n");
        printf("[%d : %d - %d] ", moves->moves[i].start, moves->moves[i].end, moves->moves[i].piece);
    }
    printf("\n");
}

//for debug
void printPieceMoves(struct MoveList *moves, enum Color piece) {
    for (int i = 0; i < moves->count; ++i) {
        if (moves->moves[i].piece == piece) printf("[%d : %d - %d]\n", moves->moves[i].start, moves->moves[i].end, moves->moves[i].piece);
    }
}

void generateMoves(struct gameBoard *Game, struct MoveList *moves, enum Color color) {
    moves->count = 0;
    int position = 0;
    long long int currentPiece = 0;
    long long int tempPiece = 0;
    for (int Piece = Queen; Piece >= King; --Piece){
        enum Piece piece = (enum Piece)Piece;
        if (piece == Pawn) {
            if (color == White) {
                currentPiece = Game->game[color][piece];
                while (currentPiece){
                    position = __builtin_ctzll(currentPiece);
                    currentPiece &= currentPiece - 1;
                    if (position/8 == 1 && !(((1ULL << (position + 8)) | (1ULL << (position + 16))) & AllBitBoard(Game))) { //pawn move 2 forward
                        struct Move move = {position, position + 16, piece};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    if (position/8 < 7 && !((1ULL << (position + 8)) & AllBitBoard(Game))) {
                        struct Move move = {position, position + 8, Pawn};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    if (position/8 < 7 && position % 8 > 0 && ((1ULL << (position + 9)) & ColorBitBoard(Game, !color))) {
                        struct Move move = {position, position + 9, Pawn};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    if (position/8 < 7 && position % 8 < 7 && ((1ULL << (position + 7)) & ColorBitBoard(Game, !color))) {
                        struct Move move = {position, position + 7, Pawn};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                }
            }
            else {
                currentPiece = Game->game[color][Pawn];
                while (currentPiece) {
                    position = __builtin_ctzll(currentPiece);
                    currentPiece &= currentPiece - 1;
                    if (position/8 == 6 && !(((1ULL << (position - 8)) | (1ULL << (position - 16))) & AllBitBoard(Game))) {
                        struct Move move = {position , position - 16, piece};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    if (position/8 > 0 && !((1ULL << (position - 8)) & AllBitBoard(Game))) {
                        struct Move move = {position, position - 8, piece};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    if (position/8 > 0 && position % 8 > 0 && ((1ULL << position - 9) & ColorBitBoard(Game, !color))) {
                        struct Move move = {position, position -9, piece};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    if (position/8 > 0 && position % 8 < 7 && ((1ULL << (position - 7) & ColorBitBoard(Game, !color)))) {
                        struct Move move = {position, position - 7, piece};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
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
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    if (position % 8 < 6 && !(ColorBitBoard(Game, color) & (1ULL << (position + 10)))) {
                        struct Move move = {position, position + 10, Knight};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    if (position/8 < 6) {
                        if (position % 8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position + 15)))) {
                            struct Move move = {position , position + 15, Knight};
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                        if (position % 8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position + 17)))) {
                            struct Move move = {position, position + 17, Knight};
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                    }
                }
                if (position/8 > 0) {
                    if (position % 8 > 1 && !(ColorBitBoard(Game, color) & (1ULL << (position - 10)))) {
                        struct Move move = {position, position - 10, Knight};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    if (position % 8 < 6 && !(ColorBitBoard(Game, color) & (1ULL << (position - 6)))) {
                        struct Move move = {position, position - 6, Knight};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    if (position/8 > 1) {
                        if (position % 8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position - 17)))) {
                            struct Move move = {position , position - 17, Knight};
                            moves->moves[moves->count] = move;
                            moves->count += 1;
                        }
                        if (position % 8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position - 15)))) {
                            struct Move move = {position, position - 15, Knight};
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
                    moves->moves[moves->count] = move;
                    moves->count += 1;
                    if (ColorBitBoard(Game, !color) & (1ULL << (position % 8 + 8*y))) break;
                }
                for (int y = position/8 - 1; y >= 0; --y) {
                    if (ColorBitBoard(Game, color) & (1ULL << (position % 8 + 8*y))) break;
                    struct Move move = {position, position % 8 + 8*y, piece};
                    moves->moves[moves->count] = move;
                    moves->count += 1;
                    if (ColorBitBoard(Game, !color) & (1ULL << (position % 8 + 8*y))) break;
                }
                for (int x = position % 8 + 1; x <= 7; ++x) {
                    if (ColorBitBoard(Game, color) & (1ULL << ((position/8) *8 + x))) break;
                    struct Move move = {position, (position/8) *8 + x, piece};
                    moves->moves[moves->count] = move;
                    moves->count += 1;
                    if (ColorBitBoard(Game, !color) & (1ULL << ((position/8) *8 + x))) break;
                }
                for (int x = position % 8 -1; x >= 0; --x) {
                    if (ColorBitBoard(Game, color) & (1ULL << ((position/8) *8 + x))) break;
                    struct Move move = {position, (position/8) *8 + x, piece};
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
                    moves->moves[moves->count] = move;
                    moves->count += 1;
                    if (ColorBitBoard(Game, !color) & (1ULL << (8*y + x))) break;
                }
                for (int y = position/8 + 1, x = position % 8 - 1; x >= 0 && y <= 7; --x, ++y) {
                    if (ColorBitBoard(Game, color) & (1ULL << (8*y + x))) break;
                    struct Move move = {position, 8*y + x, piece};
                    moves->moves[moves->count] = move;
                    moves->count += 1;
                    if (ColorBitBoard(Game, !color) & (1ULL << (8*y + x))) break;
                }
                for (int y = position/8 -1, x = position % 8 - 1; x >= 0 && y >= 0; --x, --y) {
                    if (ColorBitBoard(Game, color) & (1ULL << (8*y + x))) break;
                    struct Move move = {position, 8*y + x, piece};
                    moves->moves[moves->count] = move;
                    moves->count += 1;
                    if (ColorBitBoard(Game, !color) & (1ULL << (8*y + x))) break;
                }
                for (int y = position/8 - 1, x = position % 8 + 1; x <= 7 && y >= 0; ++x, --y) {
                    if (ColorBitBoard(Game, color) & (1ULL << (8*y + x))) break;
                    struct Move move = {position, 8*y + x, piece};
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
                //printf("ERROR - NO KING %d\n", position);
                continue;
            }
            if (position/8 < 7) {
                if (!(ColorBitBoard(Game, color) & (1ULL << (position + 8)))) {
                    Game->game[color][King] = 1ULL << (position + 8);
                    if (!inCheck(Game, color)) {
                        struct Move move = {position, position + 8, King};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    Game->game[color][King] = tempPiece;
                }
                if (position % 8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position + 7)))) {
                    Game->game[color][King] = 1ULL << (position + 7);
                    if (!inCheck(Game, color)) {
                        struct Move move = {position, position + 7, King};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    Game->game[color][King] = tempPiece;
                }
                if (position % 8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position + 9)))) {
                    Game->game[color][King] = 1ULL << (position + 9);
                    if (!inCheck(Game, color)) {
                        struct Move move = {position, position + 9, King};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    Game->game[color][King] = tempPiece;
                }
            }
            if (position/8 > 0) {
                if (!(ColorBitBoard(Game, color) & (1ULL << (position - 8)))) {
                    Game->game[color][King] = 1ULL << (position - 8);
                    if (!inCheck(Game, color)) {
                        struct Move move = {position, position - 8, King};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    Game->game[color][King] = tempPiece;
                }
                if (position % 8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position - 9)))) {
                    Game->game[color][King] = 1ULL << (position - 9);
                    if (!inCheck(Game, color)) {
                        struct Move move = {position, position - 9, King};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    Game->game[color][King] = tempPiece;
                }
                if (position % 8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position - 7)))) {
                    Game->game[color][King] = 1ULL << (position - 7);
                    if (!inCheck(Game, color)) {
                        struct Move move = {position, position - 7, King};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    Game->game[color][King] = tempPiece;
                }
            }
            if (position % 8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position - 1)))) {
                    Game->game[color][King] = 1ULL << (position - 1);
                    if (!inCheck(Game, color)) {
                        struct Move move = {position, position - 1, King};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    Game->game[color][King] = tempPiece;
            }
            if (position % 8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position + 1)))) {
                    Game->game[color][King] = 1ULL << (position + 1);
                    if (!inCheck(Game, color)) {
                        struct Move move = {position, position + 1, King};
                        moves->moves[moves->count] = move;
                        moves->count += 1;
                    }
                    Game->game[color][King] = tempPiece;
            }
        }
    }
}

int inCheck(struct gameBoard *Game, enum Color turn) //check if "turn" color is in check
{
    int position = __builtin_ctzll(Game->game[turn][King]);      
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

int evaluate(struct gameBoard *Game, enum Color turn, struct MoveList *moves){
    int x = gameOver(turn, Game, moves);
    if (x == Stalemate) return 0;
    if (x == Checkmate) {
        if (turn == White) return -10000000;
        else return 10000000;
    }
    
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
        if (piece == Rook || piece == Queen || piece == King) {
            currentPiece = Game->game[color][Piece];
            while (currentPiece) {
                position = __builtin_ctzll(currentPiece);
                currentPiece &= currentPiece - 1;
                if (position/8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position + 8)))) {
                        tempPiece = Game->game[color][piece];
                        copyGame.game[color][piece] += (1ULL << position + 8) - (1ULL << position);
                        if (CheckCollision(1ULL << (position + 8), Game, &copyGame)) reset = 1;
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
                if (position/8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position - 8)))){
                    tempPiece = Game->game[color][piece];
                    copyGame.game[color][piece] += (1ULL << position - 8) - (1ULL << position);
                    if (CheckCollision(1ULL << (position - 8), Game, &copyGame)) reset = 1;
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
                if (position % 8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position - 1)))){
                    tempPiece = Game->game[color][piece];
                    copyGame.game[color][piece] += (1ULL << position - 1) - (1ULL << position);
                    if (CheckCollision(1ULL << (position - 1), Game, &copyGame)) reset = 1;
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
                if (position/8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position + 1)))){
                    tempPiece = Game->game[color][piece];
                    copyGame.game[color][piece] += (1ULL << position + 1) - (1ULL << position);
                    if (CheckCollision(1ULL << (position + 1), Game, &copyGame)) reset = 1;
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
        if (piece == Bishop || piece == Queen || piece == King) {
            currentPiece = Game->game[color][piece];
            while (currentPiece) {
                position = __builtin_ctzll(currentPiece);
                currentPiece &= currentPiece - 1;
                if (position/8 < 7 && position % 8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position + 9)))){
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
                if (position/8 < 7 && position % 8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position + 7)))){
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
                if (position/8 > 0 && position % 8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position - 9)))){
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
                if (position/8 > 0 && position % 8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position - 7)))){
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
    return 0;
}


int gameOver (enum Color turn, struct gameBoard *game, struct MoveList *moves) //check if "turn" color lost
{
    if (moves->count > 0) return Play;
    if (inCheck(game, turn)) return Checkmate;
    return Stalemate;
}

//ASSUME ITS WHITE PLAYING AS MAXIMIZING
int alphabeta(int depth, struct gameBoard *Game, enum Color Turn, int alpha, int beta, int maximizingPlayer, struct Move *Move) {
    struct MoveList moves;
    generateMoves(Game, &moves, Turn);
    if (depth == 0 || gameOver(Turn, Game, &moves)) return evaluate(Game, Turn, &moves);
    long long int TempPiece;
    int eval;
    //printKingMoves(&moves);
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
            eval = alphabeta(depth-1, &newGame, !Turn, alpha, beta, 0, Move);
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
            CheckCollision((1ULL << move.end), Game, &newGame);
            newGame.game[Turn][move.piece] ^= (1ULL << move.start);
            newGame.game[Turn][move.piece] |= (1ULL << move.end);
            if (inCheck(&newGame, Turn)) continue;
            eval = alphabeta(depth-1, &newGame, !Turn, alpha, beta, 1, Move);
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