#include <stdlib.h>
#include "Board.h"
#include <stdio.h>

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
int whitePawnMoves[] = {8,16,7,9};
int blackPawnMoves[] = {-8,-16,-7,-9};
int knightMoves[] = {10,-6,6,-10,-17,-15,15,17,-17};
int kingMoves[] = {1,-1,8,9,7,-8,-7,-9};

int evaluate(struct gameBoard *game){
    /*
    takes in refrence to struct of current game -> evaluates advantage and returns a score 
    positive score = white advantage, negative score = black advantage, zero = no advantage
    */
    //check checkmate/stalemate
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



int alphabeta(int originalDepth, int depth, struct gameBoard *game, int turn, int alpha, int beta, int *totalMoves, int *start, int *end){
    *totalMoves += 1;
    if (!depth) return evaluate(game);
    long long unsigned int copyPiece,singlePiece;
    int position,newPosition,i;
    
    long long unsigned int (*teamBitboard)(struct gameBoard *);
    long long unsigned int (*opponentBitboard)(struct gameBoard *);

    long long unsigned int *currentPiece;
    long long unsigned int *newCurrentPiece;

    size_t size = 0;
    int *moves;

    int r,c;
    int dr, dc;
    int eval;
    int flip = 0;

    struct gameBoard newGame = *game;
    if (!turn) //computer turn
    {
        int maxEval = -1000000;
        for (i = 5; i >= 0; --i){
            if (flip) break;
            #ifdef SECOND
                switch(i){
                    case 0: 
                        currentPiece = &(game->whitePawns);
                        newCurrentPiece = &(newGame.whitePawns);
                        size = 4;
                        moves = malloc(size * sizeof(int));
                        for (int j = 0; j < size; ++j) moves[j] = whitePawnMoves[j];
                        break;
                    case 1: 
                        currentPiece = &(game->whiteKnights);
                        newCurrentPiece = &(newGame.whiteKnights);
                        size = 8;
                        moves = malloc(size * sizeof(int));
                        for (int j = 0; j < size; ++j) moves[j] = knightMoves[j];
                        break;
                    case 5: 
                        currentPiece = &(game->whiteKing);
                        newCurrentPiece = &(newGame.whiteKing);
                        size = 8;
                        moves = malloc(size * sizeof(int));
                        for (int j = 0; j < size; ++j) moves[j] = kingMoves[j];
                        break;
                    case 2: 
                        currentPiece = &(game->whiteBishops);
                        newCurrentPiece = &(newGame.whiteBishops);
                        break;
                    case 3: 
                        currentPiece = &(game->whiteRooks);
                        newCurrentPiece = &(newGame.whiteRooks);
                        break;
                    case 4: 
                        currentPiece = &(game->whiteQueen);
                        newCurrentPiece = &(newGame.whiteQueen);
                        break;
                }
                teamBitboard = whiteBitboard;
                opponentBitboard = blackBitBoard;
            #else
                switch(i){
                    case 0: 
                        currentPiece = &(game->blackPawns);
                        newCurrentPiece = &(newGame.blackPawns);
                        size = 4;
                        moves = malloc(size * sizeof(int));
                        for (int j = 0; j < size; ++j) moves[j] = blackPawnMoves[j];
                        break;
                    case 1: 
                        currentPiece = &(game->blackKnights);
                        newCurrentPiece = &(newGame.blackKnights);
                        size = 8;
                        moves = malloc(size * sizeof(int));
                        for (int j = 0; j < size; ++j) moves[j] = knightMoves[j];
                        break;
                    case 5: 
                        currentPiece = &(game->blackKing);
                        newCurrentPiece = &(newGame.blackKing);
                        size = 8;
                        moves = malloc(size * sizeof(int));
                        for (int j = 0; j < size; ++j) moves[j] = kingMoves[j];
                        break;
                    case 2: 
                        currentPiece = &(game->blackBishops);
                        newCurrentPiece = &(newGame.blackBishops);
                        break;    
                    case 3: 
                        currentPiece = &(game->whiteRooks);
                        newCurrentPiece = &(newGame.whiteRooks);
                        break;
                    case 4: 
                        currentPiece = &(game->blackQueen);
                        newCurrentPiece = &(newGame.blackQueen);
                        break;
                }
                teamBitboard = blackBitBoard;
                opponentBitboard = whiteBitboard;
            #endif
            copyPiece = *currentPiece;
            while (copyPiece){
                position = __builtin_ctzll(copyPiece);
                copyPiece &= copyPiece -1;
                if (i < 2 || i == 5){
                    for (int j = 0; j < size; ++j){
                        int x = position % 8;
                        int y = position/8;
                        x += moves[j]%8;
                        y += moves[j]/8;
                        newPosition = position + moves[j];
                        if (y <= 7 && y >= 0 && x <= 7 && x >= 0){
                            singlePiece = 1ULL << newPosition;
                            if (!(singlePiece & teamBitboard(game))){
                                if (!i) //pawn
                                {
                                    if (j == 0 && !(singlePiece & allBitboard(game))){
                                        *newCurrentPiece = *currentPiece - (1ULL << position) + (1ULL << newPosition);
                                        eval = alphabeta(originalDepth,depth-1,&newGame,1,alpha,beta,totalMoves,start,end);
                                        *newCurrentPiece = *currentPiece;
                                        if (eval > maxEval)
                                        { 
                                            maxEval = eval;
                                            if (depth == originalDepth){
                                            *start = position;
                                            *end = newPosition;
                                            }
                                        }
                                        if (eval > alpha) alpha = eval;
                                        if (beta <= alpha) {
                                            flip = 1;
                                            break;
                                        }
                                    }
                                    else if (j == 1 && position/8 == (int)(3.5 - 2.5 *(moves[1]/16)) && !(singlePiece & allBitboard(game))){
                                        *newCurrentPiece = *currentPiece - (1ULL << position) + (1ULL << newPosition);
                                        eval = alphabeta(originalDepth,depth-1,&newGame,1,alpha,beta,totalMoves,start,end);
                                        *newCurrentPiece = *currentPiece;
                                        if (eval > maxEval)
                                        { 
                                            maxEval = eval;
                                            if (depth == originalDepth){
                                            *start = position;
                                            *end = newPosition;
                                            }
                                        }
                                        if (eval > alpha) alpha = eval;
                                        if (beta <= alpha) {
                                            flip = 1;
                                            break;
                                        }
                                    }
                                    else if (j > 1 && singlePiece & opponentBitboard(game)) 
                                    {
                                        checkCollision(singlePiece, game, &newGame);
                                        *newCurrentPiece = *currentPiece - (1ULL << position) + (1ULL << newPosition);
                                        eval = alphabeta(originalDepth,depth-1,&newGame,1,alpha,beta,totalMoves,start,end);
                                        newGame = *game;
                                        if (eval > maxEval)
                                        { 
                                            maxEval = eval;
                                            if (depth == originalDepth){
                                            *start = position;
                                            *end = newPosition;
                                            }
                                        }
                                        if (eval > alpha) alpha = eval;
                                        if (beta <= alpha) {
                                            flip = 1;
                                            break;
                                        }
                                    }
                                }
                                else {
                                    checkCollision(singlePiece, game, &newGame);
                                    *newCurrentPiece = *currentPiece - (1ULL << position) + (1ULL << newPosition);
                                    eval = alphabeta(originalDepth,depth-1,&newGame,1,alpha,beta,totalMoves,start,end);
                                    newGame = *game;
                                    
                                    if (eval > maxEval)
                                    { 
                                        maxEval = eval;
                                        if (depth == originalDepth){
                                        *start = position;
                                        *end = newPosition;
                                        }
                                    }
                                    if (eval > alpha) alpha = eval;
                                    if (beta <= alpha) {
                                        flip = 1;
                                        break;
                                    }
                                }
                            }
                            else if (!i) ++j;
                        }
                    }
                    
                }
                else
                {
                    if (i != 3){
                        //all but rooks
                        dr = 1;
                        dc = 1;
                        for (r = position/8+ 1, c = position/8;1; r += dr, c += dc){
                            if (r > 7 || c > 7 || r < 0 || c < 0 || ((1ULL << (r*8 + c)) & teamBitboard(game))){
                                if (dr == 1 && dc == 1){
                                    r = position/8;
                                    c = position % 8;
                                    dr = -1;
                                    continue;
                                }
                                else if (dr == -1 && dc == 1){
                                    r = position/8;
                                    c = position % 8;
                                    dc = -1;
                                    continue;
                                }
                                else if (dr == -1 && dc == -1){
                                    r = position/8;
                                    c = position % 8;
                                    dr = 1;
                                    continue;
                                }
                                else if (dr == 1 && dc == -1)break;
                            }
                            newPosition = r*8 + c;
                            singlePiece = 1ULL << newPosition;
                            if (singlePiece && opponentBitboard(game)){
                                checkCollision(singlePiece, game, &newGame);
                                *newCurrentPiece = *currentPiece - (1ULL << position) + (1ULL << newPosition);
                                eval = alphabeta(originalDepth,depth-1,&newGame,1,alpha,beta,totalMoves,start,end);
                                newGame = *game;
                                if (eval > maxEval)
                                { 
                                    maxEval = eval;
                                    if (depth == originalDepth){
                                    *start = position;
                                    *end = newPosition;
                                    }
                                }
                                if (eval > alpha) alpha = eval;
                                if (beta <= alpha) {
                                    flip = 1;
                                }
                                
                                if (dr == 1 && dc == 1){
                                    r = position/8;
                                    c = position % 8;
                                    dr = -1;
                                    continue;
                                }
                                else if (dr == -1 && dc == 1){
                                    r = position/8;
                                    c = position % 8;
                                    dc = -1;
                                    continue;
                                }
                                else if (dr == -1 && dc == -1){
                                    r = position/8;
                                    c = position % 8;
                                    dr = 1;
                                    continue;
                                }
                                else if (dr == 1 && dc == -1)break;
                            }
                            else {
                                *newCurrentPiece = *currentPiece - (1ULL << position) + (1ULL << newPosition);
                                eval = alphabeta(originalDepth,depth-1,&newGame,1,alpha,beta,totalMoves,start,end);
                                newGame = *game;
                                if (eval > maxEval)
                                { 
                                    maxEval = eval;
                                    if (depth == originalDepth){
                                    *start = position;
                                    *end = newPosition;
                                    }
                                }
                                if (eval > alpha) alpha = eval;
                                if (beta <= alpha) {
                                    flip = 1;
                                    break;
                                }
                            }

                        }
                        if (flip) break;

                    }
                    if (i != 2){
                        
                        dr = 1;
                        dc = 0;
                        for (r = position/8+ 1, c = position %8;1; r += dr, c += dc){
                            if (r > 7 || c > 7 || r < 0 || c < 0 || ((1ULL << (r*8 + c)) & teamBitboard(game))){
                                if (dr == 1 && !dc){
                                    r = position/8;
                                    c = position % 8;
                                    dr = -1;
                                    continue;
                                }
                                else if (dr == -1 && !dc){
                                    r = position/8;
                                    c = position % 8;
                                    dr = 0;
                                    dc = -1;
                                    continue;
                                }
                                else if (!dr && dc == -1){
                                    r = position/8;
                                    c = position % 8;
                                    dc = 1;
                                    continue;
                                }
                                else if (!dr && dc == 1)break;
                            }
                            newPosition = r*8 + c;
                            singlePiece = 1ULL << newPosition;
                            if (singlePiece && opponentBitboard(game)){
                                checkCollision(singlePiece, game, &newGame);
                                *newCurrentPiece = *currentPiece - (1ULL << position) + (1ULL << newPosition);
                                eval = alphabeta(originalDepth,depth-1,&newGame,1,alpha,beta,totalMoves,start,end);
                                newGame = *game;
                                if (eval > maxEval)
                                { 
                                    maxEval = eval;
                                    if (depth == originalDepth){
                                    *start = position;
                                    *end = newPosition;
                                    }
                                }
                                if (eval > alpha) alpha = eval;
                                if (beta <= alpha) {
                                    flip = 1;
                                }

                                if (dr == 1 && !dc){
                                    r = position/8;
                                    c = position % 8;
                                    dr = -1;
                                    continue;
                                }
                                else if (dr == -1 && !dc){
                                    r = position/8;
                                    c = position % 8;
                                    dr = 0;
                                    dc = -1;
                                    continue;
                                }
                                else if (!dr && dc == -1){
                                    r = position/8;
                                    c = position % 8;
                                    dc = 1;
                                    continue;
                                }
                                else if (!dr && dc == 1)break;
                            }
                            else {
                                *newCurrentPiece = *currentPiece - (1ULL << position) + (1ULL << newPosition);
                                eval = alphabeta(originalDepth,depth-1,&newGame,1,alpha,beta,totalMoves,start,end);
                                newGame = *game;
                                if (eval > maxEval)
                                { 
                                    maxEval = eval;
                                    if (depth == originalDepth){
                                    *start = position;
                                    *end = newPosition;
                                    }
                                }
                                if (eval > alpha) alpha = eval;
                                if (beta <= alpha) {
                                    flip = 1;
                                    break;
                                }
                            }

                        }
                        if (flip) break;

                    }
                }
            }
            if (i < 2 || i == 5) free(moves);
        }
        return maxEval;
    }
    else 
    { //player turn
        int minEval = 1000000;
        for (i = 5; i >= 0; --i){
            if (flip) break;
            #ifdef SECOND 
                switch(i){
                    case 0: 
                        currentPiece = &(game->blackPawns);
                        newCurrentPiece = &(newGame.blackPawns);
                        size = 4;
                        moves = malloc(size * sizeof(int));
                        for (int j = 0; j < size; ++j) moves[j] = blackPawnMoves[j];
                        break;
                    case 1: 
                        currentPiece = &(game->blackKnights);
                        newCurrentPiece = &(newGame.blackPawns);
                        size = 8;
                        moves = malloc(size * sizeof(int));
                        for (int j = 0; j < size; ++j) moves[j] = knightMoves[j];
                        break;
                    case 5: 
                        currentPiece = &(game->blackKing);
                        newCurrentPiece = &(newGame.blackPawns);
                        size = 8;
                        moves = malloc(size * sizeof(int));
                        for (int j = 0; j < size; ++j) moves[j] = kingMoves[j];
                        break;
                    case 2: 
                        currentPiece = &(game->blackBishops);
                        newCurrentPiece = &(newGame.blackPawns);    
                        break;
                    case 3: 
                        currentPiece = &(game->whiteRooks);
                        newCurrentPiece = &(newGame.blackPawns);
                        break;
                    case 4: 
                        currentPiece = &(game->blackQueen);
                        newCurrentPiece = &(newGame.blackPawns);
                        break;
                }
                teamBitboard = blackBitBoard;
                opponentBitboard = whiteBitboard;
            #else
                switch(i){
                    case 0: 
                        currentPiece = &(game->whitePawns);
                        newCurrentPiece = &(newGame.whitePawns);
                        size = 4;
                        moves = malloc(size * sizeof(int));
                        for (int j = 0; j < size; ++j) moves[j] = whitePawnMoves[j];
                        break;
                    case 1: 
                        currentPiece = &(game->whiteKnights);
                        newCurrentPiece = &(newGame.whiteKnights);
                        size = 8;
                        moves = malloc(size * sizeof(int));
                        for (int j = 0; j < size; ++j) moves[j] = knightMoves[j];
                        break;
                    case 5: 
                        currentPiece = &(game->whiteKing);
                        newCurrentPiece = &(newGame.whiteKing);
                        size = 8;
                        moves = malloc(size * sizeof(int));
                        for (int j = 0; j < size; ++j) moves[j] = kingMoves[j];
                        break;
                    case 2: 
                        currentPiece = &(game->whiteBishops);
                        newCurrentPiece = &(newGame.whiteBishops);
                        break;
                    case 3: 
                        currentPiece = &(game->whiteRooks);
                        newCurrentPiece = &(newGame.whiteRooks);
                        break;
                    case 4: 
                        currentPiece = &(game->whiteQueen);
                        newCurrentPiece = &(newGame.whiteRooks);
                        break;
                }
                teamBitboard = whiteBitboard;
                opponentBitboard = blackBitBoard;
            #endif
            copyPiece = *currentPiece;
            while (copyPiece){
                position = __builtin_ctzll(copyPiece);
                copyPiece &= copyPiece -1;
                if (i < 2 || i == 5){
                    for (int j = 0; j < size; ++j){
                        newPosition = position + moves[j];
                        if (newPosition/8 <= 7 && newPosition/8 >= 0 && newPosition % 8 <= 7 && newPosition % 8 >= 0){
                            singlePiece = 1ULL << newPosition;
                            if (!(singlePiece & teamBitboard(game))){
                                if (!i) //pawn
                                {
                                    if (j == 0 && !(singlePiece & allBitboard(game))){
                                        *newCurrentPiece = *currentPiece - (1ULL << position) + (1ULL << newPosition);
                                        eval = alphabeta(originalDepth,depth-1,&newGame,0,alpha,beta,totalMoves,start,end);
                                        *newCurrentPiece = *currentPiece;
                                        if (eval < minEval) minEval = eval;
                                        if (eval < beta) beta = eval;
                                        if (beta <= alpha) {
                                            flip = 1;
                                            break;
                                        }
                                    }
                                    if (j == 1 && position/8 == (int)(3.5 - 2.5 *(moves[1]/16)) && !(singlePiece & allBitboard(game))){
                                        *newCurrentPiece = *currentPiece - (1ULL << position) + (1ULL << newPosition);
                                        eval = alphabeta(originalDepth,depth-1,&newGame,0,alpha,beta,totalMoves,start,end);
                                        *newCurrentPiece = *currentPiece;
                                        if (eval < minEval) minEval = eval;
                                        if (eval < beta) beta = eval;
                                        if (beta <= alpha) {
                                            flip = 1;
                                            break;
                                        }
                                    }
                                    else if (j > 1 && singlePiece & opponentBitboard(game)) 
                                    {
                                        checkCollision(singlePiece, game, &newGame);
                                        *newCurrentPiece = *currentPiece - (1ULL << position) + (1ULL << newPosition);
                                        eval = alphabeta(originalDepth,depth-1,&newGame,0,alpha,beta,totalMoves,start,end);
                                        newGame = *game;
                                        if (eval < minEval) minEval = eval;
                                        if (eval < beta) beta = eval;
                                        if (beta <= alpha) {
                                            flip = 1;
                                            break;
                                        }
                                    }
                                }
                                else {
                                    checkCollision(singlePiece, game, &newGame);
                                    *newCurrentPiece = *currentPiece - (1ULL << position) + (1ULL << newPosition);
                                    eval = alphabeta(originalDepth,depth-1,&newGame,0,alpha,beta,totalMoves,start,end);
                                    newGame = *game;
                                    if (eval < minEval) minEval = eval;
                                    if (eval < beta) beta = eval;
                                    if (beta <= alpha) {
                                        flip = 1;
                                        break;
                                    }
                                }
                            }
                            else if (!i) ++j;
                        }
                    }
                    
                }
                else
                {
                    if (i != 3){                        
                        dr = 1;
                        dc = 1;
                        for (r = position/8+ 1, c = position/8 + 1;1; r += dr, c += dc){
                            if (r > 7 || c > 7 || r < 0 || c < 0 || ((1ULL << (r*8 + c)) & teamBitboard(game))){
                                if (dr == 1 && dc == 1){
                                    r = position/8;
                                    c = position % 8;
                                    dr = -1;
                                    continue;
                                }
                                else if (dr == -1 && dc == 1){
                                    r = position/8;
                                    c = position % 8;
                                    dc = -1;
                                    continue;
                                }
                                else if (dr == -1 && dc == -1){
                                    r = position/8;
                                    c = position % 8;
                                    dr = 1;
                                    continue;
                                }
                                else if (dr == 1 && dc == -1)break;
                            }
                            newPosition = r*8 + c;
                            singlePiece = 1ULL << newPosition;
                            if (singlePiece && opponentBitboard(game)){
                                checkCollision(singlePiece, game, &newGame);
                                *newCurrentPiece = *currentPiece - (1ULL << position) + (1ULL << newPosition);
                                eval = alphabeta(originalDepth,depth-1,&newGame,0,alpha,beta,totalMoves,start,end);
                                newGame = *game;
                                if (eval < minEval) minEval = eval;
                                if (eval < beta) beta = eval;
                                if (beta <= alpha) {
                                    flip = 1;
                                }
                                if (dr == 1 && dc == 1){
                                    r = position/8;
                                    c = position % 8;
                                    dr = -1;
                                    continue;
                                }
                                else if (dr == -1 && dc == 1){
                                    r = position/8;
                                    c = position % 8;
                                    dc = -1;
                                    continue;
                                }
                                else if (dr == -1 && dc == -1){
                                    r = position/8;
                                    c = position % 8;
                                    dr = 1;
                                    continue;
                                }
                                else if (dr == 1 && dc == -1)break;
                            }
                            else {
                                *newCurrentPiece = *currentPiece - (1ULL << position) + (1ULL << newPosition);
                                eval = alphabeta(originalDepth,depth-1,&newGame,0,alpha,beta,totalMoves,start,end);
                                newGame = *game;
                                if (eval < minEval) minEval = eval;
                                if (eval < beta) beta = eval;
                                if (beta <= alpha) {
                                    flip = 1;
                                    break;
                                }
                            }

                        }
                        if (flip) break;

                    }
                    if (i != 2){
                        
                        dr = 1;
                        dc = 0;
                        for (r = position/8+ 1, c = position/8;1; r += dr, c += dc){
                            if (r > 7 || c > 7 || r < 0 || c < 0 || ((1ULL << (r*8 + c)) & teamBitboard(game))){
                                if (dr == 1 && !dc){
                                    r = position/8;
                                    c = position % 8;
                                    dr = -1;
                                    continue;
                                }
                                else if (dr == -1 && !dc){
                                    r = position/8;
                                    c = position % 8;
                                    dr = 0;
                                    dc = -1;
                                    continue;
                                }
                                else if (!dr && dc == -1){
                                    r = position/8;
                                    c = position % 8;
                                    dc = 1;
                                    continue;
                                }
                                else if (!dr && dc == 1)break;
                            }
                            newPosition = r*8 + c;
                            singlePiece = 1ULL << newPosition;
                            if (singlePiece && opponentBitboard(game)){
                                checkCollision(singlePiece, game, &newGame);
                                *newCurrentPiece = *currentPiece - (1ULL << position) + (1ULL << newPosition);
                                eval = alphabeta(originalDepth,depth-1,&newGame,0,alpha,beta,totalMoves,start,end);
                                newGame = *game;
                                if (eval < minEval) minEval = eval;
                                if (eval < beta) beta = eval;
                                if (beta <= alpha) {
                                    flip = 1;
                                }
                                if (dr == 1 && !dc){
                                    r = position/8;
                                    c = position % 8;
                                    dr = -1;
                                    continue;
                                }
                                else if (dr == -1 && !dc){
                                    r = position/8;
                                    c = position % 8;
                                    dr = 0;
                                    dc = -1;
                                    continue;
                                }
                                else if (!dr && dc == -1){
                                    r = position/8;
                                    c = position % 8;
                                    dc = 1;
                                    continue;
                                }
                                else if (!dr && dc == 1)break;
                            }
                            else {
                                *newCurrentPiece = *currentPiece - (1ULL << position) + (1ULL << newPosition);
                                eval = alphabeta(originalDepth,depth-1,&newGame,0,alpha,beta,totalMoves,start,end);
                                newGame = *game;
                                if (eval < minEval) minEval = eval;
                                if (eval < beta) beta = eval;
                                if (beta <= alpha) {
                                    flip = 1;
                                    break;
                                }
                            }

                        }
                        if (flip) break;

                    }
                }
            }
            if (i < 2 || i == 5) free(moves);
        }
        return minEval;
    }

}

