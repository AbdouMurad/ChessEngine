#define MAX_MOVES 128
#define DEPTH 7
#define TT_SIZE (1 << 22)

struct Move {
    int start;
    int end;
    enum Piece piece;
    enum Piece promotion; //when promotion occurs this occurs what the new move is
    int score; //score used to evaluate the move in order to prioritize better moves
};

struct TTEntry {
    unsigned long long int key;
    int score;
    int depth;
    int flag; 
    struct Move BestMove;
};
enum flag {
    EXACT, LOWERBOUND, HIGHERBOUND
};

struct TTEntry *probe(long long unsigned int key, struct TTEntry *table);

void store(long long unsigned int key, int depth, int score, int flag, struct Move BestMove, struct TTEntry *table);

struct MoveList {
    struct Move moves[MAX_MOVES];
    int count;
};
int abs(int a);

void InsertSort(struct Move *moves, int count);

int inCheck(struct gameBoard *game, enum Color col); // check if color is in check

int isSquareAttacked(int position, struct gameBoard *game, enum Color col); //check if square for color is being attacked

int evaluate(struct gameBoard *Game, enum Color turn);

void printMoves(struct MoveList *moves);

void generateMoves(struct gameBoard *Game, struct MoveList *moves, enum Color color);

int MoreMoves(struct gameBoard *Game, enum Color color);

int gameOver(enum Color turn, struct gameBoard *game);

int alphabeta(int depth, struct gameBoard *game, enum Color Turn, int alpha, int beta, int maximizingPlayer, struct Move *move, struct TTEntry *table, int *ndoes);