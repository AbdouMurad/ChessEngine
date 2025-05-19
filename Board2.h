#pragma once

void setColour(const char *colour);

enum Color {
    White, Black
};
enum Piece {
    King, Pawn, Knight, Bishop, Rook, Queen
};
enum GameState {
    Play, Stalemate, Checkmate
};
struct gameBoard {
    unsigned long long int game[2][6];
    int moveCount;
};

void setupBlankGame(struct gameBoard *Game);

void setupGame(struct gameBoard *Game);

unsigned long long int ColorBitBoard(struct gameBoard *Game, enum Color color);

unsigned long long int AllBitBoard(struct gameBoard *Game);

void CheckCollision(long long unsigned int singlePiece, struct gameBoard *Game,struct gameBoard *newGame);

void PrintBoard(struct gameBoard *Game, int start, int end);

int MakeMove(struct gameBoard *Game, int start, int end, enum Color color);