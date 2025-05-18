int evaluate(struct gameBoard *game);

int alphabeta(int originalDepth, int depth, struct gameBoard *game, int turn, int alpha, int beta, int *moves, int *start, int *end);