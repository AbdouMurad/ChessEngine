#define MAX_MOVES 256
#define DEPTH 7

struct Move {
    int start;
    int end;
    enum Piece piece;
    enum Piece promotion; //when promotion occurs this occurs what the new move is
};

struct MoveList {
    struct Move moves[MAX_MOVES];
    int count;
};

int inCheck(struct gameBoard *game, enum Color col); // check if color is in check

int isSquareAttacked(int position, struct gameBoard *game, enum Color col); //check if square for color is being attacked

int evaluate(struct gameBoard *Game, enum Color turn);

void printMoves(struct MoveList *moves);

void generateMoves(struct gameBoard *Game, struct MoveList *moves, enum Color color);

int MoreMoves(struct gameBoard *Game, enum Color color);

int gameOver(enum Color turn, struct gameBoard *game);

int alphabeta(int depth, struct gameBoard *game, enum Color Turn, int alpha, int beta, int maximizingPlayer, struct Move *move);