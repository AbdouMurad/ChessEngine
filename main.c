#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const char * const GREEN = "\x1b[32m";
const char * const YELLOW = "\x1b[33m";
const char * const WHITE = "\x1b[0m";
const char * const BLACK = "\x1b[90m";

const char * current = WHITE;

void setColour(const char *colour) {
  if (current == colour) return;
  printf("%s", colour);
  current = colour;
}

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
    -30, -40, -40, -50, -50, -40, -40, -30,};

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

unsigned long long int blackBitBoard(struct gameBoard *game){//returns bit board of all opponent pieces
    return (*game).blackPawns | (*game).blackKnights | (*game).blackBishops | (*game).blackRooks | (*game).blackQueen | (*game).blackKing;
}
unsigned long long int whiteBitboard(struct gameBoard *game){ //return bit board of all player pieces
    return (*game).whitePawns | (*game).whiteKnights | (*game).whiteBishops | (*game).whiteRooks | (*game).whiteQueen | (*game).whiteKing;

}
unsigned long long int allBitBoard(struct gameBoard *game){ //returns bit board will all pieces
    return blackBitBoard(game)| whiteBitboard(game);
}
void printBoard(struct gameBoard *game, int start, int end){
    long long unsigned int current = 1ULL << 63;
    int cur = 0;
    int i,j;
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            cur = 63 - (i*8 + j);
            if (cur == start) setColour(YELLOW);
            else if (cur == end) setColour(GREEN); 
            if (current & allBitBoard(game)){
                if (cur != start && cur != end) setColour(WHITE);
                if (current & game->whitePawns){
                    printf("P ");
                }
                else if (current & game->whiteBishops) {
                    printf("B ");
                }
                else if (current & game->whiteKnights) {
                    printf("k ");
                }
                else if (current & game->whiteRooks) {
                    printf("R ");
                }
                else if (current & game->whiteQueen) {
                    printf("Q ");
                }
                else if (current & game->whiteKing) {
                    printf("K ");
                }
                if (cur != start && cur != end) setColour(BLACK);
                if (current & game->blackPawns){
                    printf("P ");
                }
                else if (current & game->blackBishops) {
                    printf("B ");
                }
                else if (current & game->blackKnights) {
                    printf("k ");
                }
                else if (current & game->blackRooks) {
                    printf("R ");
                }
                else if (current & game->blackQueen) {
                    printf("Q ");
                }
                else if (current & game->blackKing) {
                    printf("K ");
                }
            }
            else {
                if (cur != start && cur != end) setColour(WHITE);
                printf("0 ");
            }
            current = current >> 1;
        }
        setColour(WHITE);
        printf("%d  \n",(7-i)*8);
    }
    printf("\n");
    setColour(WHITE);
}
int alphabeta(int originalDepth, int depth, struct gameBoard *game, int turn, int alpha, int beta, int *moves, int *start, int *end){
    *moves += 1;
    if (depth == 0){ //check for stalemate and checkmate as well
        return evaluate(game);
    }

    struct gameBoard newGame = (*game);
    int eval;
    
    int position;

    unsigned long long int copyPiece;
    unsigned long long int newPiece;

    unsigned long long int singlePiece; //contains single piece

    int c,r,i,flip;
    flip = 0;
    //assume computer is always white
    if (!turn) //computer turn
    { 
        int maxEval = -1000000;
        //generate positions
        
        for (i = 5; i >= 0; --i){
            if (flip) break;
            if (i == 0) copyPiece = (*game).whitePawns;
            else if (i == 1) copyPiece = (*game).whiteKnights;
            else if (i == 2) copyPiece = (*game).whiteBishops;
            else if (i == 3) copyPiece = (*game).whiteRooks;
            else if (i == 4) copyPiece = (*game).whiteQueen;
            else if (i == 5) copyPiece = (*game).whiteKing;
            while (copyPiece){
                position = __builtin_ctzll(copyPiece);
                copyPiece &= copyPiece -1;
                if (i == 0) //pawn
                {
                    //pawn move 2 forward
                    if (position/8 == 1){
                        singlePiece = (1ULL << position + 16);
                        if (!(allBitBoard(game) & singlePiece)) {
                            
                            newPiece = (*game).whitePawns - (1ULL << position) + (1ULL << position + 16);
                            newGame.whitePawns = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame.whitePawns = (*game).whitePawns;
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                *start = position;
                                *end = position + 16;
                                }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                break;
                            }
                            
                        }
                    }
                    
                    //pawn move 1 forward
                    singlePiece = (1ULL << position + 8);
                    if ( (position/8 < 7) && !(allBitBoard(game) & singlePiece)) { //pawn move 1 square

                        newPiece = (*game).whitePawns - (1ULL << position) + singlePiece;
                        newGame.whitePawns = newPiece;
                        eval =alphabeta(originalDepth,depth-1, &newGame,1,alpha,beta,moves,start,end);
                        newGame.whitePawns = (*game).whitePawns;
                        if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = position + 8;
                                    }
                            }
                        if (eval > alpha) alpha = eval;
                        if (beta <= alpha) {
                                flip = 1;
                                break;
                            }
                    }
                    

                    //check diagonal pawn attack - left
                    singlePiece = 1ULL << (position + 9);
                    if ((position % 8 != 7) && (position/8 < 7) && (blackBitBoard(game) & singlePiece) ) {
                        newPiece = (*game).whitePawns - (1ULL << position) + singlePiece;
                        
                        //check which black piece is attacked
                        if (newPiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                        else if (newPiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                        else if (newPiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                        else if (newPiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                        else if (newPiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                        else if (newPiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;

                        newGame.whitePawns = newPiece;
                        eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                        newGame = (*game);
                        if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = position + 9;
                                    }
                            }
                        if (eval > alpha) alpha = eval;
                        if (beta <= alpha){
                                flip = 1;
                                break;
                            }
                    }
                    //check diagonal pawn attack - right
                    singlePiece = 1ULL << (position + 7);
                    if ((position/8 < 7) && (position % 8) && (blackBitBoard(game) & singlePiece)) {
                        
                        newPiece = (*game).whitePawns - (1ULL << position) + singlePiece;
                        //check which black piece is attacked
                        if (newPiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                        else if (newPiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                        else if (newPiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                        else if (newPiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                        else if (newPiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                        else if (newPiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                        
                        newGame.whitePawns = newPiece;
                        eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                        newGame = (*game);
                        if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = position + 7;
                                    }
                            }
                        if (eval > alpha) alpha = eval;
                        if (beta <= alpha) {
                            flip = 1;
                            break;
                        }
                    }

                    //PROMOTION - to be completed
                }            
                else if (i == 1)//knight
                {
                    //left up
                    singlePiece = 1ULL << (position + 10);
                    if ((position % 8 < 6) && (position/8 < 7) && !(whiteBitboard(game) & singlePiece)) {
                        newPiece = (*game).whiteKnights - (1ULL << position) + singlePiece;
                        if (newPiece & blackBitBoard(game)){
                            if (newPiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (newPiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                        }
                        newGame.whiteKnights = newPiece;
                        eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                        newGame = (*game);
                        if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = position + 10;
                                    }
                            }
                        if (eval > alpha) alpha = eval;
                        if (beta <= alpha) {
                                flip = 1;
                                break;
                            }
                    }

                    //left down
                    singlePiece = 1ULL << (position - 6);
                    if ((position % 8 < 6) && (position/8 > 0) && !(whiteBitboard(game) & singlePiece)) {
                        newPiece = (*game).whiteKnights - (1ULL << position) + singlePiece;
                        if (newPiece & blackBitBoard(game)){
                            if (newPiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (newPiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                        }

                        newGame.whiteKnights = newPiece;
                        eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                        newGame = (*game);
                        if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = position - 6;
                                    }
                            }
                        if (eval > alpha) alpha = eval;
                        if (beta <= alpha) {
                                flip = 1;
                                break;
                            }
                    }
                    //right up
                    singlePiece = 1ULL << (position + 6);
                    if ((position % 8 > 1) && (position/8 < 7) && !(whiteBitboard(game) & singlePiece)) {
                        newPiece = (*game).whiteKnights - (1ULL << position) + singlePiece;
                        if (newPiece & blackBitBoard(game)){
                            if (newPiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (newPiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                        }

                        newGame.whiteKnights = newPiece;
                        eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                        newGame = (*game);
                        if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = position + 6;
                                    }
                            }
                        if (eval > alpha) alpha = eval;
                        if (beta <= alpha) {
                                flip = 1;
                                break;
                            }
                    }
                    //right down
                    singlePiece = 1ULL << (position - 10);
                    if ((position % 8 > 1) && (position/8 > 0) && !(whiteBitboard(game) & singlePiece)) {
                        newPiece = (*game).whiteKnights - (1ULL << position) + singlePiece;
                        if (newPiece & blackBitBoard(game)){
                            if (newPiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (newPiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                        }

                        newGame.whiteKnights = newPiece;
                        eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                        newGame = (*game);
                        if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = position -10;
                                    }
                            }
                        if (eval > alpha) alpha = eval;
                        if (beta <= alpha) {
                                flip = 1;
                                break;
                            }
                    }
                    //down right
                    singlePiece = 1ULL << (position - 17);
                    if ((position % 8 > 0) && (position/8 > 1) && !(whiteBitboard(game) & singlePiece)) {
                        newPiece = (*game).whiteKnights - (1ULL << position) + singlePiece;
                        if (newPiece & blackBitBoard(game)){
                            if (newPiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (newPiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                        }

                        newGame.whiteKnights = newPiece;
                        eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                        newGame = (*game);
                        if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = position - 17;
                                    }
                            }
                        if (eval > alpha) alpha = eval;
                        if (beta <= alpha) {
                                flip = 1;
                                break;
                            }
                    }
                    //down left
                    singlePiece = 1ULL << (position - 15);
                    if ((position % 8 < 7) && (position/8 > 1) && !(whiteBitboard(game) & singlePiece)) {
                        newPiece = (*game).whiteKnights - (1ULL << position) + singlePiece;
                        if (newPiece & blackBitBoard(game)){
                            if (newPiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (newPiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                        }

                        newGame.whiteKnights = newPiece;
                        eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                        newGame = (*game);
                        if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = position - 15;
                                    }
                            }
                        if (eval > alpha) alpha = eval;
                        if (beta <= alpha) {
                                flip = 1;
                                break;
                            }
                    }
                    //up right
                    singlePiece = 1ULL << (position + 15);
                    if ((position % 8 > 0) && (position/8 < 6) && !(whiteBitboard(game) & singlePiece)) {
                        newPiece = (*game).whiteKnights - (1ULL << position) + singlePiece;
                        if (newPiece & blackBitBoard(game)){
                            if (newPiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (newPiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                        }

                        newGame.whiteKnights = newPiece;
                        eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                        newGame = (*game);
                        if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = position + 15;
                                    }
                            }
                        if (eval > alpha) alpha = eval;
                        if (beta <= alpha) {
                                flip = 1;
                                break;
                            }
                    }
                    //up left
                    singlePiece = 1ULL << (position + 17);
                    if ((position % 8 < 7) && (position/8 < 6) && !(whiteBitboard(game) & singlePiece)) {
                        newPiece = (*game).whiteKnights - (1ULL << position) + singlePiece;
                        if (newPiece & blackBitBoard(game)){
                            if (newPiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (newPiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                        }

                        newGame.whiteKnights = newPiece;
                        eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                        newGame = (*game);
                        if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = position + 17;
                                    }
                            }
                        if (eval > alpha) alpha = eval;
                        if (beta <= alpha) {
                                flip = 1;
                                break;
                            }
                    }
                }
                else if (i == 2)//bishop
                {
                    //top left
                    for (r = position/8 + 1, c = position % 8 + 1; r < 8 && c < 8; ++r, ++c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = (*game).whiteBishops - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) break;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (newPiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                            newGame.whiteBishops = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.whiteBishops = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                        }
                    }
                    if (flip) break;
                    //top right
                    for (r = position/8 + 1, c = position % 8 - 1;r < 8 && c >= 0; ++r, --c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = (*game).whiteBishops - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) break;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (newPiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                            newGame.whiteBishops = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.whiteBishops = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                        }
                    }
                    if (flip) break;
                    //bottom left
                    for (r = position/8 - 1, c = position % 8 + 1; r >= 0 && c < 8; --r, ++c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = (*game).whiteBishops - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) break;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (newPiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                            newGame.whiteBishops = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.whiteBishops = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                        }
                    }
                    if (flip) break;
                    //bottom right
                    for (r = position/8 - 1, c = position % 8 - 1;r >= 0 && c >= 0; --r, --c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = (*game).whiteBishops - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) break;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (newPiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                            newGame.whiteBishops = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.whiteBishops = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                        }
                    }
                    if (flip) break;
                }
                else if (i == 3) //rook
                {
                    //up
                    for (r = position/8 + 1, c = position % 8;  r < 8; ++r){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = game->whiteRooks - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) break;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (newPiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                            newGame.whiteRooks = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.whiteRooks = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                        }
                    }
                    if (flip) break;
                    //down
                    for (r = position/8 - 1, c = position % 8;r >= 0; --r){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = game->whiteRooks - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) break;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (newPiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                            newGame.whiteRooks = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.whiteRooks = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
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
                    //left
                    for (r = position/8, c = position % 8 + 1;c < 8; ++c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = game->whiteRooks - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) break;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (newPiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                            newGame.whiteRooks = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.whiteRooks = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                        }
                    }
                    if (flip) break;
                    //right
                    for (r = position/8, c = position % 8 -1; c >= 0; --c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = game->whiteRooks - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) break;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (newPiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                            newGame.whiteRooks = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.whiteRooks = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                        }
                    }
                    if (flip) break;
                }    
                else if (i == 4) //queen - 
                {
                    //top left
                    for (r = position/8 + 1, c = position % 8 + 1; r < 8 && c < 8; ++r, ++c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = (*game).whiteQueen - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) break;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (newPiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                            newGame.whiteQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.whiteQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                        }
                    }
                    if (flip) break;
                    //top right
                    for (r = position/8 + 1, c = position % 8 - 1;r < 8 && c >= 0; ++r, --c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = (*game).whiteQueen - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) break;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (newPiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                            newGame.whiteQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.whiteQueen = newPiece;
                            eval = alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                        }
                    }
                    if (flip) break;
                    //bottom left
                    for (r = position/8 - 1, c = position % 8 + 1; r >= 0 && c < 8; --r, ++c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = (*game).whiteQueen - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) break;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (newPiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                            newGame.whiteQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.whiteQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
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
                    //bottom right
                    for (r = position/8 - 1, c = position % 8 - 1;r >= 0 && c >= 0; --r, --c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = (*game).whiteQueen - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) break;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (newPiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                            newGame.whiteQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.whiteQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                        }
                    }
                    if (flip) break;
                    //up
                    for (r = position/8 + 1, c = position % 8;r < 8; ++r){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = game->whiteQueen - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) break;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (newPiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                            newGame.whiteQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.whiteQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                        }
                    }
                    if (flip) break;
                    //down
                    for (r = position/8 - 1, c = position % 8;r >= 0; --r){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = game->whiteQueen - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) break;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (newPiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                            newGame.whiteQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.whiteQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                        }
                    }
                    if (flip) break;
                    //left
                    for (r = position/8, c = position % 8 + 1; c < 8; ++c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = game->whiteQueen - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) break;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (newPiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                            newGame.whiteQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.whiteQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                        }
                    }
                    if (flip) break;
                    //right
                    for (r = position/8, c = position % 8 -1; c >= 0; --c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = game->whiteQueen - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) break;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (newPiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                            newGame.whiteQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.whiteQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                        }
                    }
                    if (flip) break;
                }
                else if (i == 5) //king
                {   
                    //up
                    singlePiece = 1ULL << position + 8;
                    if ( position/8 < 7 && !(singlePiece & whiteBitboard(game))) {
                        if (singlePiece & blackBitBoard(game)){
                            if (singlePiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (singlePiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (singlePiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (singlePiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (singlePiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (singlePiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                        }
                            newGame.whiteKing = singlePiece;
                            eval =alphabeta(originalDepth,depth-1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }

                        
                    }
                    //left 
                    singlePiece = 1ULL << position + 1;
                    if ( position %8 < 7 && !(singlePiece & whiteBitboard(game))) {
                        if (singlePiece & blackBitBoard(game)){
                            if (singlePiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (singlePiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (singlePiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (singlePiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (singlePiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (singlePiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                        }

                            newGame.whiteKing = singlePiece;
                            eval =alphabeta(originalDepth,depth-1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                    
                            
                    }
                    //right 
                    singlePiece = 1ULL << position - 1;
                    if ( position %8 > 0 && !(singlePiece & whiteBitboard(game))) {
                        if (singlePiece & blackBitBoard(game)){
                            if (singlePiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (singlePiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (singlePiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (singlePiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (singlePiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (singlePiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                        }

                            newGame.whiteKing = singlePiece;
                            eval =alphabeta(originalDepth,depth-1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = r*8 +c;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                    
                            
                    }
                    //down 
                    singlePiece = 1ULL << position - 8;
                    if ( position/8 > 0 && !(singlePiece & whiteBitboard(game))) {
                        if (singlePiece & blackBitBoard(game)){
                            if (singlePiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (singlePiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (singlePiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (singlePiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (singlePiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (singlePiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                        }

                            newGame.whiteKing = singlePiece;
                            eval =alphabeta(originalDepth,depth-1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = position -8;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                    
                            
                    }
                    //up left 
                    singlePiece = 1ULL << position + 9;
                    if ( position %8 < 7 && position/8 < 7 && !(singlePiece & whiteBitboard(game))) {
                        if (singlePiece & blackBitBoard(game)){
                            if (singlePiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (singlePiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (singlePiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (singlePiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (singlePiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (singlePiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                        }

                            newGame.whiteKing = singlePiece;
                            eval =alphabeta(originalDepth,depth-1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = position +9;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                    
                            
                    }
                    //up right 
                    singlePiece = 1ULL << position + 7;
                    if ( position %8 > 0 && position/8 < 7 && !(singlePiece & whiteBitboard(game))) {
                        if (singlePiece & blackBitBoard(game)){
                            if (singlePiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (singlePiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (singlePiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (singlePiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (singlePiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (singlePiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                        }

                            newGame.whiteKing = singlePiece;
                            eval =alphabeta(originalDepth,depth-1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = position +7;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                    
                            
                    }
                    //down left 
                    singlePiece = 1ULL << position - 7;
                    if ( position %8 < 7 && position/8 > 0 && !(singlePiece & whiteBitboard(game))) {
                        if (singlePiece & blackBitBoard(game)){
                            if (singlePiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (singlePiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (singlePiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (singlePiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (singlePiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (singlePiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                        }

                            newGame.whiteKing = singlePiece;
                            eval =alphabeta(originalDepth,depth-1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = position -7;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                    
                            
                    }
                    //down right 
                    singlePiece = 1ULL << position - 9;
                    if ( position %8 > 0 && position/8 > 0 && !(singlePiece & whiteBitboard(game))) {
                        if (singlePiece & blackBitBoard(game)){
                            if (singlePiece & (*game).blackPawns) newGame.blackPawns =newGame.blackPawns ^ singlePiece;
                            else if (singlePiece & (*game).blackKnights) newGame.blackKnights =newGame.blackKnights ^ singlePiece;
                            else if (singlePiece & (*game).blackBishops) newGame.blackBishops =newGame.blackBishops ^ singlePiece;
                            else if (singlePiece & (*game).blackRooks) newGame.blackRooks = newGame.blackRooks ^ singlePiece;
                            else if (singlePiece & (*game).blackQueen) newGame.blackQueen = newGame.blackQueen ^ singlePiece;
                            else if (singlePiece & (*game).blackKing) newGame.blackKing = newGame.blackKing ^ singlePiece;
                        }

                            newGame.whiteKing = singlePiece;
                            eval =alphabeta(originalDepth,depth-1,&newGame,1,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval > maxEval)
                            { 
                                maxEval = eval;
                                if (depth == originalDepth){
                                    *start = position;
                                    *end = position -9;
                                    }
                            }
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                    
                            
                    }
                    //CASTLE
                }
                }
        }
    
        return maxEval;
    }
    else //Player turnn
    { 
        int minEval = 1000000;
        //generate positions
        
        for (i = 0; i <= 5; ++i){
            if (flip) break;
            if (i == 0) copyPiece = (*game).blackPawns;
            else if (i == 1) copyPiece = (*game).blackKnights;
            else if (i == 2) copyPiece = (*game).blackBishops;
            else if (i == 3) copyPiece = (*game).blackRooks;
            else if (i == 4) copyPiece = (*game).blackQueen;
            else if (i == 5) copyPiece = (*game).blackKing;
            while ( copyPiece){
                position = __builtin_ctzll(copyPiece);
                copyPiece &= copyPiece -1;
                if (i == 0) //pawn
                {
                    //pawn move 2 forward
                    if ( position/8 == 6){
                        singlePiece = (1ULL << position - 16);
                        if (!(allBitBoard(game) & singlePiece)) {
                            
                            newPiece = (*game).blackPawns - (1ULL << position) + (1ULL << position - 16);
                            newGame.blackPawns = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame.blackPawns = (*game).blackPawns;
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                        }
                    }
                    //pawn move 1 forward
                    singlePiece = (1ULL << position - 8);
                    if ( (position/8 > 0) && !(allBitBoard(game) & singlePiece)) { //pawn move 1 square

                        newPiece = (*game).blackPawns - (1ULL << position) + singlePiece;
                        newGame.blackPawns = newPiece;
                        eval =alphabeta(originalDepth,depth-1, &newGame,0,alpha,beta,moves,start,end);
                        newGame.blackPawns = (*game).blackPawns;
                        if (eval < minEval) minEval = eval;
                        if (eval < beta) beta = eval; 
                        if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                    }

                    //check diagonal pawn attack - left
                    singlePiece = 1ULL << (position - 7);
                    if ( (position % 8 < 7) && (position/8 > 0) && (whiteBitboard(game) & singlePiece) ) {
                        newPiece = (*game).blackPawns - (1ULL << position) + singlePiece;
                        
                        //check which black piece is attacked
                        if (newPiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                        else if (newPiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                        else if (newPiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                        else if (newPiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                        else if (newPiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                        else if (newPiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;

                        newGame.blackPawns = newPiece;
                        eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                        newGame = (*game);
                        if (eval < minEval) minEval = eval;
                        if (eval < beta) beta = eval; 
                        if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                    }
                    //check diagonal pawn attack - right
                    singlePiece = 1ULL << (position - 9);
                    if ( (position/8 > 0) && (position % 8 > 0) && (whiteBitboard(game) & singlePiece)) {
                        
                        newPiece = (*game).blackPawns - (1ULL << position) + singlePiece;
                        //check which black piece is attacked
                        if (newPiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                        else if (newPiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                        else if (newPiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                        else if (newPiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                        else if (newPiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                        else if (newPiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                        
                        newGame.blackPawns = newPiece;
                        eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                        newGame = (*game);
                        if (eval < minEval) minEval = eval;
                        if (eval < beta) beta = eval; 
                        if (beta <= alpha) {
                                flip = 1;
                                break;
                            }
                    }
                    //PROMOTION - to be completed
                }            
                else if (i == 1)//knight
                {
                    //left up
                    singlePiece = 1ULL << (position + 10);
                    if ((position % 8 < 6) && (position/8 < 7) && !(blackBitBoard(game) & singlePiece)) {
                        newPiece = (*game).blackKnights - (1ULL << position) + singlePiece;
                        if (newPiece & whiteBitboard(game)){
                            if (newPiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                            else if (newPiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                            else if (newPiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                            else if (newPiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                            else if (newPiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                            else if (newPiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                    }

                        newGame.blackKnights = newPiece;
                        eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                        newGame = (*game);
                        if (eval < minEval) minEval = eval;
                        if (eval < beta) beta = eval; 
                        if (beta <= alpha) {
                                flip = 1;
                                break;
                            }
                    }

                    //left down
                    singlePiece = 1ULL << (position - 6);
                    if ( (position % 8 < 6) && (position/8 > 0) && !(blackBitBoard(game) & singlePiece)) {
                        newPiece = (*game).blackKnights - (1ULL << position) + singlePiece;
                        if (newPiece & whiteBitboard(game)){
                            if (newPiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                            else if (newPiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                            else if (newPiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                            else if (newPiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                            else if (newPiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                            else if (newPiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                    }

                        newGame.blackKnights = newPiece;
                        eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                        newGame = (*game);
                        if (eval < minEval) minEval = eval;
                        if (eval < beta) beta = eval; 
                        if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                    }
                    //right up
                    singlePiece = 1ULL << (position + 6);
                    if ( (position % 8 > 1) && (position/8 < 7) && !(blackBitBoard(game) & singlePiece)) {
                        newPiece = (*game).blackKnights - (1ULL << position) + singlePiece;
                        if (newPiece & whiteBitboard(game)){
                            if (newPiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                            else if (newPiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                            else if (newPiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                            else if (newPiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                            else if (newPiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                            else if (newPiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                    }

                        newGame.blackKnights = newPiece;
                        eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                        newGame = (*game);
                        if (eval < minEval) minEval = eval;
                        if (eval < beta) beta = eval; 
                        if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                    }
                    //right down
                    singlePiece = 1ULL << (position - 10);
                    if ( (position % 8 > 1) && (position/8 > 0) && !(blackBitBoard(game) & singlePiece)) {
                        newPiece = (*game).blackKnights - (1ULL << position) + singlePiece;
                        if (newPiece & whiteBitboard(game)){
                            if (newPiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                            else if (newPiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                            else if (newPiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                            else if (newPiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                            else if (newPiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                            else if (newPiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                    }

                        newGame.blackKnights = newPiece;
                        eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                        newGame = (*game);
                        if (eval < minEval) minEval = eval;
                        if (eval < beta) beta = eval; 
                        if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                    }
                    //down right
                    singlePiece = 1ULL << (position - 17);
                    if ( (position % 8 > 0) && (position/8 > 1) && !(blackBitBoard(game) & singlePiece)) {
                        newPiece = (*game).blackKnights - (1ULL << position) + singlePiece;
                        if (newPiece & whiteBitboard(game)){
                            if (newPiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                            else if (newPiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                            else if (newPiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                            else if (newPiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                            else if (newPiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                            else if (newPiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                    }

                        newGame.blackKnights = newPiece;
                        eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                        newGame = (*game);
                        if (eval < minEval) minEval = eval;
                        if (eval < beta) beta = eval; 
                        if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                    }
                    //down left
                    singlePiece = 1ULL << (position - 15);
                    if ( (position % 8 < 7) && (position/8 > 1) && !(blackBitBoard(game) & singlePiece)) {
                        newPiece = (*game).blackKnights - (1ULL << position) + singlePiece;
                        if (newPiece & whiteBitboard(game)){
                            if (newPiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                            else if (newPiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                            else if (newPiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                            else if (newPiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                            else if (newPiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                            else if (newPiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                    }

                        newGame.blackKnights = newPiece;
                        eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                        newGame = (*game);
                        if (eval < minEval) minEval = eval;
                        if (eval < beta) beta = eval; 
                        if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                    }
                    //up right
                    singlePiece = 1ULL << (position + 15);
                    if ( (position % 8 > 0) && (position/8 < 6) && !(blackBitBoard(game) & singlePiece)) {
                        newPiece = (*game).blackKnights - (1ULL << position) + singlePiece;
                        if (newPiece & whiteBitboard(game)){
                            if (newPiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                            else if (newPiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                            else if (newPiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                            else if (newPiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                            else if (newPiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                            else if (newPiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                    }

                        newGame.blackKnights = newPiece;
                        eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                        newGame = (*game);
                        if (eval < minEval) minEval = eval;
                        if (eval < beta) beta = eval; 
                        if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                    }
                    //up left
                    singlePiece = 1ULL << (position + 17);
                    if ( (position % 8 < 7) && (position/8 < 6) && !(whiteBitboard(game) & singlePiece)) {
                        newPiece = (*game).blackKnights - (1ULL << position) + singlePiece;
                        if (newPiece & whiteBitboard(game)){
                            if (newPiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                            else if (newPiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                            else if (newPiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                            else if (newPiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                            else if (newPiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                            else if (newPiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                    }

                        newGame.blackKnights = newPiece;
                        eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                        newGame = (*game);
                        if (eval < minEval) minEval = eval;
                        if (eval < beta) beta = eval; 
                        if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                    }
                }
                else if (i == 2)//bishop
                {
                    //top left
                    for (r = position/8 + 1, c = position % 8 + 1; r < 8 && c < 8; ++r, ++c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = (*game).blackBishops - (1ULL << position) + singlePiece;
                        if (singlePiece & blackBitBoard(game)) break;
                        else if (singlePiece & whiteBitboard(game)){
                            //check which black piece is attacked
                        if (newPiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                        else if (newPiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                        else if (newPiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                        else if (newPiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                        else if (newPiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                        else if (newPiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                            newGame.blackBishops = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.blackBishops = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                        }
                    }
                    if (flip) break;
                    //top right
                    for (r = position/8 + 1, c = position % 8 - 1; r < 8 && c >= 0; ++r, --c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = (*game).blackBishops - (1ULL << position) + singlePiece;
                        if (singlePiece & blackBitBoard(game)) break;
                        else if (singlePiece & whiteBitboard(game)){
                            //check which black piece is attacked
                        if (newPiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                        else if (newPiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                        else if (newPiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                        else if (newPiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                        else if (newPiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                        else if (newPiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                            newGame.blackBishops = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.blackBishops = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                                break;    
                            }
                            
                        }
                    }
                    if (flip) break;
                    //bottom left
                    for (r = position/8 - 1, c = position % 8 + 1; r >= 0 && c < 8; --r, ++c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = (*game).blackBishops - (1ULL << position) + singlePiece;
                        if (singlePiece & blackBitBoard(game)) break;
                        else if (singlePiece & whiteBitboard(game)){
                            //check which black piece is attacked
                        if (newPiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                        else if (newPiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                        else if (newPiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                        else if (newPiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                        else if (newPiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                        else if (newPiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                            newGame.blackBishops = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.blackBishops = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                        }
                    }
                    if (flip) break;
                    //bottom right
                    for (r = position/8 - 1, c = position % 8 - 1; r >= 0 && c >= 0; --r, --c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = (*game).blackBishops - (1ULL << position) + singlePiece;
                        if (singlePiece & blackBitBoard(game)) break;
                        else if (singlePiece & whiteBitboard(game)){
                            //check which black piece is attacked
                        if (newPiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                        else if (newPiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                        else if (newPiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                        else if (newPiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                        else if (newPiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                        else if (newPiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                            newGame.blackBishops = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.blackBishops = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                        }
                    }
                    if (flip) break;
                }
                else if (i == 3) //rook
                {
                    //up
                    for (r = position/8 + 1, c = position % 8; r < 8; ++r){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = game->blackRooks - (1ULL << position) + singlePiece;
                        if (singlePiece & blackBitBoard(game)) break;
                        else if (singlePiece & whiteBitboard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                            else if (newPiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                            else if (newPiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                            else if (newPiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                            else if (newPiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                            else if (newPiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                            newGame.blackRooks = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.blackRooks = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                                break;
                            }
                            
                        }
                    }
                    if (flip) break;
                    //down
                    for (r = position/8 - 1, c = position % 8; r >= 0; --r){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = game->blackRooks - (1ULL << position) + singlePiece;
                        if (singlePiece & blackBitBoard(game)) break;
                        else if (singlePiece & whiteBitboard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                            else if (newPiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                            else if (newPiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                            else if (newPiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                            else if (newPiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                            else if (newPiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                            newGame.blackRooks = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.blackRooks = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                                break;
                            }
                            
                        }
                    }
                    if (flip) break;
                    //left
                    for (r = position/8, c = position % 8 + 1; c < 8; ++c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = game->blackRooks - (1ULL << position) + singlePiece;
                        if (singlePiece & blackBitBoard(game)) break;
                        else if (singlePiece & whiteBitboard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                            else if (newPiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                            else if (newPiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                            else if (newPiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                            else if (newPiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                            else if (newPiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                            newGame.blackRooks = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.blackRooks = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                                break;
                            }
                            
                        }
                    }
                    if (flip) break;
                    //right
                    for (r = position/8, c = position % 8 - 1; c >= 0; --c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = game->blackRooks - (1ULL << position) + singlePiece;
                        if (singlePiece & blackBitBoard(game)) break;
                        else if (singlePiece & whiteBitboard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                            else if (newPiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                            else if (newPiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                            else if (newPiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                            else if (newPiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                            else if (newPiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                            newGame.blackRooks = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.blackRooks = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
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
                else if (i == 4) //queen
                {
                    //top left
                    for (r = position/8 + 1, c = position % 8 + 1; r < 8 && c < 8; ++r, ++c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = (*game).blackQueen - (1ULL << position) + singlePiece;
                        if (singlePiece & blackBitBoard(game)) break;
                        else if (singlePiece & whiteBitboard(game)){
                            //check which black piece is attacked
                        if (newPiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                        else if (newPiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                        else if (newPiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                        else if (newPiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                        else if (newPiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                        else if (newPiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                            newGame.blackQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.blackQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                                break;
                            }
                        }
                    }
                    if (flip) break;
                    //top right
                    for (r = position/8 + 1, c = position % 8 - 1; r < 8 && c >= 0; ++r, --c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = (*game).blackQueen - (1ULL << position) + singlePiece;
                        if (singlePiece & blackBitBoard(game)) break;
                        else if (singlePiece & whiteBitboard(game)){
                            //check which black piece is attacked
                        if (newPiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                        else if (newPiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                        else if (newPiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                        else if (newPiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                        else if (newPiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                        else if (newPiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                            newGame.blackQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.blackQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                        }
                    }
                    if (flip) break;
                    //bottom left
                    for (r = position/8 - 1, c = position % 8 + 1; r >= 0 && c < 8; --r, ++c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = (*game).blackQueen - (1ULL << position) + singlePiece;
                        if (singlePiece & blackBitBoard(game)) break;
                        else if (singlePiece & whiteBitboard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                            else if (newPiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                            else if (newPiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                            else if (newPiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                            else if (newPiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                            else if (newPiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                            newGame.blackQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.blackQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                        }
                    }
                    if (flip) break;
                    //bottom right
                    for (r = position/8 - 1, c = position % 8 - 1; r >= 0 && c >= 0; --r, --c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = (*game).blackQueen - (1ULL << position) + singlePiece;
                        if (singlePiece & blackBitBoard(game)) break;
                        else if (singlePiece & whiteBitboard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                            else if (newPiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                            else if (newPiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                            else if (newPiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                            else if (newPiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                            else if (newPiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                            newGame.blackQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.blackQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                        }
                    }
                    if (flip) break;
                    //up
                    for (r = position/8 + 1, c = position % 8; r < 8; ++r){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = (*game).blackQueen - (1ULL << position) + singlePiece;
                        if (singlePiece & blackBitBoard(game)) break;
                        else if (singlePiece & whiteBitboard(game)){
                            //check which black piece is attacked
                        if (newPiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                        else if (newPiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                        else if (newPiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                        else if (newPiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                        else if (newPiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                        else if (newPiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                            newGame.blackQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.blackQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                        }
                    }
                    if (flip) break;
                    //down
                    for (r = position/8 - 1, c = position % 8; r >= 0; --r){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = (*game).blackQueen - (1ULL << position) + singlePiece;
                        if (singlePiece & blackBitBoard(game)) break;
                        else if (singlePiece & whiteBitboard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                            else if (newPiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                            else if (newPiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                            else if (newPiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                            else if (newPiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                            else if (newPiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                            newGame.blackQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.blackQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                        }
                    }
                    if (flip) break;
                    //left
                    for (r = position/8, c = position % 8 + 1; c < 8; ++c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = (*game).blackQueen - (1ULL << position) + singlePiece;
                        if (singlePiece & blackBitBoard(game)) break;
                        else if (singlePiece & whiteBitboard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                            else if (newPiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                            else if (newPiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                            else if (newPiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                            else if (newPiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                            else if (newPiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                            newGame.blackQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.blackQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                        }
                    }
                    if (flip) break;
                    //right
                    for (r = position/8, c = position % 8 -1;c >= 0; --c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = (*game).blackQueen - (1ULL << position) + singlePiece;
                        if (singlePiece & blackBitBoard(game)) break;
                        else if (singlePiece & whiteBitboard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                            else if (newPiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                            else if (newPiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                            else if (newPiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                            else if (newPiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                            else if (newPiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                            newGame.blackQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                            }
                            break;
                        }
                        else {
                            newGame.blackQueen = newPiece;
                            eval =alphabeta(originalDepth,depth -1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                        }
                    }
                    if (flip) break;
                }
                else if (i == 5) //king
                {   
                    //up
                    singlePiece = 1ULL << position + 8;
                    if ( position/8 < 7 && !(singlePiece & blackBitBoard(game))) {
                        if (singlePiece & whiteBitboard(game)){
                            if (singlePiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                            else if (singlePiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                            else if (singlePiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                            else if (singlePiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                            else if (singlePiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                            else if (singlePiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                        }
                            newGame.blackKing = singlePiece;
                            eval =alphabeta(originalDepth,depth-1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                    }
                    //left 
                    singlePiece = 1ULL << position + 1;
                    if ( position %8 < 7 && !(singlePiece & blackBitBoard(game))) {
                        if (singlePiece & whiteBitboard(game)){
                        if (singlePiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                        else if (singlePiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                        else if (singlePiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                        else if (singlePiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                        else if (singlePiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                        else if (singlePiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                        }
                            newGame.blackKing = singlePiece;
                            eval =alphabeta(originalDepth,depth-1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                    }
                    //right 
                    singlePiece = 1ULL << position - 1;
                    if ( position %8 > 0 && !(singlePiece & blackBitBoard(game))) {
                        if (singlePiece & whiteBitboard(game)){
                        if (singlePiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                        else if (singlePiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                        else if (singlePiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                        else if (singlePiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                        else if (singlePiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                        else if (singlePiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                        }
                            newGame.blackKing = singlePiece;
                            eval =alphabeta(originalDepth,depth-1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                    }
                    //down 
                    singlePiece = 1ULL << position - 8;
                    if ( position /8 > 0 && !(singlePiece & blackBitBoard(game))) {
                        if (singlePiece & whiteBitboard(game)){
                        if (singlePiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                        else if (singlePiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                        else if (singlePiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                        else if (singlePiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                        else if (singlePiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                        else if (singlePiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                        }
                            newGame.blackKing = singlePiece;
                            eval =alphabeta(originalDepth,depth-1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                    }
                    //up left 
                    singlePiece = 1ULL << position + 9;
                    if ( position %8 < 7 && position/8 < 7 && !(singlePiece & blackBitBoard(game))) {
                        if (singlePiece & whiteBitboard(game)){
                        if (singlePiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                        else if (singlePiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                        else if (singlePiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                        else if (singlePiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                        else if (singlePiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                        else if (singlePiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                        }
                            newGame.blackKing = singlePiece;
                            eval =alphabeta(originalDepth,depth-1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                    }
                    //up right 
                    singlePiece = 1ULL << position + 7;
                    if ( position %8 > 0 && position/8 < 7 && !(singlePiece & blackBitBoard(game))) {
                        if (singlePiece & whiteBitboard(game)){
                        if (singlePiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                        else if (singlePiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                        else if (singlePiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                        else if (singlePiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                        else if (singlePiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                        else if (singlePiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                        }
                            newGame.blackKing = singlePiece;
                            eval =alphabeta(originalDepth,depth-1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                    }
                    //down left 
                    singlePiece = 1ULL << position - 7;
                    if ( position %8 < 7 && position/8 > 0 && !(singlePiece & blackBitBoard(game))) {
                        if (singlePiece & whiteBitboard(game)){
                        if (singlePiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                        else if (singlePiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                        else if (singlePiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                        else if (singlePiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                        else if (singlePiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                        else if (singlePiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                        }
                            newGame.blackKing = singlePiece;
                            eval =alphabeta(originalDepth,depth-1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                    }
                    //down right 
                    singlePiece = 1ULL << position - 9;
                    if ( position %8 > 0 && position/8 > 0 && !(singlePiece & blackBitBoard(game))) {
                        if (singlePiece & whiteBitboard(game)){
                        if (singlePiece & (*game).whitePawns) newGame.whitePawns = newGame.whitePawns ^ singlePiece;
                        else if (singlePiece & (*game).whiteKnights) newGame.whiteKnights = newGame.whiteKnights ^ singlePiece;
                        else if (singlePiece & (*game).whiteBishops) newGame.whiteBishops = newGame.whiteBishops ^ singlePiece;
                        else if (singlePiece & (*game).whiteRooks) newGame.whiteRooks = newGame.whiteRooks ^ singlePiece;
                        else if (singlePiece & (*game).whiteQueen) newGame.whiteQueen = newGame.whiteQueen ^ singlePiece;
                        else if (singlePiece & (*game).whiteKing) newGame.whiteKing = newGame.whiteKing ^ singlePiece;
                        }
                            newGame.blackKing = singlePiece;
                            eval =alphabeta(originalDepth,depth-1,&newGame,0,alpha,beta,moves,start,end);
                            newGame = (*game);
                            if (eval < minEval) minEval = eval;
                            if (eval < beta) beta = eval; 
                            if (beta <= alpha) {
                                flip = 1;
                                break ;
                            }
                    }
                    //CASTLE
                }
                }
        }
    
        return minEval;
    }
        
    
}
void makeMove(struct gameBoard *game){
    int start,end;
    printf("Which piece to move?\n");
    scanf("%d",&start);
    printf("Where to?\n");
    scanf("%d",&end);

    long long unsigned int startPiece = 1ULL << start;
    long long unsigned int endPiece = 1ULL << end;
    if (game->blackPawns & startPiece){
        game->blackPawns = game->blackPawns - startPiece + endPiece;
    }
    else if (game->blackKnights & startPiece){
        game->blackKnights = game->blackKnights - startPiece + endPiece;
    }
    else if (game->blackBishops & startPiece){
        game->blackBishops = game->blackBishops - startPiece + endPiece;
    }
    else if (game->blackRooks & startPiece){
        game->blackRooks = game->blackRooks - startPiece + endPiece;
    }
    else if (game->blackQueen & startPiece){
        game->blackQueen = game->blackQueen - startPiece + endPiece;
    }
    else if (game->blackKing & startPiece){
        game->blackKing = game->blackKing - startPiece + endPiece;
    }
    if (game->whitePawns & endPiece){
        game->whitePawns -= endPiece;
    }
    else if (game->whiteKnights & endPiece){
        game->whiteKnights -= endPiece;
    }
    else if (game->whiteBishops & endPiece){
        game->whiteBishops -= endPiece;
    }
    else if (game->whiteRooks & endPiece){
        game->whiteRooks -= endPiece;
    }
    else if (game->whiteQueen & endPiece){
        game->whiteQueen -= endPiece;
    }
    else if (game->whiteKing & endPiece){
        game->whiteKing -= endPiece;
    }
    printBoard(game,start,end);
}
void computerMakeMove(int start, int end,struct gameBoard *game){
    long long unsigned int startPiece = 1ULL << start;
    long long unsigned int endPiece = 1ULL << end;
    if (game->whitePawns & startPiece){
        game->whitePawns = game->whitePawns - startPiece + endPiece;
    }
    else if (game->whiteKnights & startPiece){
        game->whiteKnights = game->whiteKnights - startPiece + endPiece;
    }
    else if (game->whiteBishops & startPiece){
        game->whiteBishops = game->whiteBishops - startPiece + endPiece;
    }
    else if (game->whiteRooks & startPiece){
        game->whiteRooks = game->whiteRooks - startPiece + endPiece;
    }
    else if (game->whiteQueen & startPiece){
        game->whiteQueen = game->whiteQueen - startPiece + endPiece;
    }
    else if (game->whiteKing & startPiece){
        game->whiteKing = game->whiteKing - startPiece + endPiece;
    }
    if (game->blackPawns & endPiece){
        game->blackPawns -= endPiece;
    }
    else if (game->blackKnights & endPiece){
        game->blackKnights -= endPiece;
    }
    else if (game->blackBishops & endPiece){
        game->blackBishops -= endPiece;
    }
    else if (game->blackRooks & endPiece){
        game->blackRooks -= endPiece;
    }
    else if (game->blackQueen & endPiece){
        game->blackQueen -= endPiece;
    }
    else if (game->blackKing & endPiece){
        game->blackKing -= endPiece;
    }
    printBoard(game, start, end);
}


void setupBlankGame(struct gameBoard *game)
{
    // White Pieces
    (*game).whitePawns =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b0000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8
    (*game).whiteKnights =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x42, for knights on b1 & g1)
    0b00000000ULL;         // Row 8
    (*game).whiteBishops =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x24, for bishops on c1 & f1)
    0b00000000ULL;         // Row 8
    (*game).whiteRooks =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x81, for rooks on a1 & h1)
    0b11111111ULL;         // Row 8

    (*game).whiteQueen =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x10)
    0b00000000ULL;         // Row 8

    (*game).whiteKing =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x08)
    0b00000000ULL;         // Row 8

    (*game).whiteCastle = 3;

    // Black Pieces

    (*game).blackPawns =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8

    (*game).blackKnights =
    0b00000000ULL << 56 |  // Row 1 (0x42)
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8

    (*game).blackBishops =
    0b00000000ULL << 56 |  // Row 1 (0x24)
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8

    (*game).blackRooks =
    0b11111111ULL << 56 |  // Row 1 (0x81)
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8

    (*game).blackQueen =
    0b00000000ULL << 56 |  // Row 1 (0x08)
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8

    (*game).blackKing =
    0b00000000ULL << 56 |  // Row 1 (0x10)
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8

    (*game).blackCastle = 3;

};
void setupGame(struct gameBoard *game){
    // White Pieces
    (*game).whitePawns =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b11111111ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8
    (*game).whiteKnights =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x42, for knights on b1 & g1)
    0b01000010ULL;         // Row 8
    (*game).whiteBishops =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x24, for bishops on c1 & f1)
    0b00100100ULL;         // Row 8
    (*game).whiteRooks =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x81, for rooks on a1 & h1)
    0b10000001ULL;         // Row 8

    (*game).whiteQueen =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x10)
    0b00010000ULL;         // Row 8

    (*game).whiteKing =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x08)
    0b00001000ULL;         // Row 8

    (*game).whiteCastle = 3;

    // Black Pieces

    (*game).blackPawns =
    0b00000000ULL << 56 |  // Row 1
    0b11111111ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8

    (*game).blackKnights =
    0b01000010ULL << 56 |  // Row 1 (0x42)
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8

    (*game).blackBishops =
    0b00100100ULL << 56 |  // Row 1 (0x24)
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8

    (*game).blackRooks =
    0b10000001ULL << 56 |  // Row 1 (0x81)
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8

    (*game).blackQueen =
    0b00010000ULL << 56 |  // Row 1 (0x08)
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8

    (*game).blackKing =
    0b00001000ULL << 56 |  // Row 1 (0x10)
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8

    (*game).blackCastle = 1;
}
int main(){
    //assume computer is white for now

    int moves = 0;
    int turn = 0; //0 - white / 1 - black 

    struct gameBoard game;
    setupGame(&game);
    //setupBlankGame(&game);
    while(1){
    int depth = 5;
    int score = evaluate(&game);
    printf("SCORE: %d\n",score);
    int start, end; //start position and end position of most optimal move
    int newScore =alphabeta(depth,depth,&game,0,-10000000,1000000, &moves,&start,&end);
    printf("newScore: %d  score: %d\n",newScore,score);
    printf("moves: %d Depth: %d\n", moves,depth);
    printf("Starting Move: %d End Move: %d\n\n\n",start,end);
    computerMakeMove(start,end,&game);
    makeMove(&game);
    }
}