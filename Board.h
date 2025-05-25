#pragma once


enum Color {
    Black, White
};
enum Piece {
    King, Pawn, Knight, Bishop, Rook, Queen
};
enum GameState {
    Checkmate, Stalemate, Play
};

void setColour(const char *colour);

struct gameBoard {
    long long unsigned int whitePawns;
    long long unsigned int whiteBishops;
    long long unsigned int whiteKnights;
    long long unsigned int whiteRooks;
    long long unsigned int whiteQueen;
    long long unsigned int whiteKing;
    int whiteCastle;
    
    long long unsigned int blackPawns;
    long long unsigned int blackKnights;
    long long unsigned int blackBishops;
    long long unsigned int blackRooks;
    long long unsigned int blackQueen;
    long long unsigned int blackKing;
    int blackCastle; //1 - left : 2 - right : 3 - both

};

unsigned long long int blackBitBoard(struct gameBoard *game);

unsigned long long int whiteBitboard(struct gameBoard *game);

unsigned long long int allBitboard(struct gameBoard *game);

void checkCollision(long long unsigned int singlePiece, struct gameBoard *game,struct gameBoard *newGame);

void printBoard(struct gameBoard *game, int start, int end);

int makeMove(struct gameBoard *game, int start, int end);