#pragma oncels


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

enum Castle {
    WhiteBoth, WhiteQueen, WhiteKing, BlackBoth, BlackQueen, BlackKing, Neither
};
struct gameBoard {
    unsigned long long int game[2][6];
    int moveCount;
    enum Castle WhiteCastle;
    enum Castle BlackCastle;
    int enPassant[2];
    
};

int fen(struct gameBoard *Game, char *fen);

void setupBlankGame(struct gameBoard *Game);

void setupGame(struct gameBoard *Game);

unsigned long long int ColorBitBoard(struct gameBoard *Game, enum Color color);

unsigned long long int AllBitBoard(struct gameBoard *Game);

//int CheckCollision(long long unsigned int singlePiece, struct gameBoard *Game,struct gameBoard *newGame);

int CheckCollision(long long unsigned int singlePiece, struct gameBoard *Game,  struct gameBoard *newGame, enum Color Turn);

void PrintBoard(struct gameBoard *Game, int start, int end);

int MakeMove(struct gameBoard *Game, int start, int end, enum Color color);