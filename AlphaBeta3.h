#define MAX_MOVES 256
#define DEPTH 7

struct Move {
    int start;
    int end;
    enum Piece piece;
};

struct MoveList {
    struct Move moves[MAX_MOVES];
    int count;
};

int inCheck(struct gameBoard *game, enum Color col);

int evaluate(struct gameBoard *Game, enum Color turn, struct MoveList *moves);

void printMoves(struct MoveList *moves);

void generateMoves(struct gameBoard *Game, struct MoveList *moves, enum Color color);

int gameOver(enum Color turn, struct gameBoard *game, struct MoveList *moves);

int alphabeta(int depth, struct gameBoard *game, enum Color Turn, int alpha, int beta, int maximizingPlayer, struct Move *move);