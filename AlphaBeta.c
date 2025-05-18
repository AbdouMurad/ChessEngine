#include "Board.h"

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

int evaluate(struct gameBoard *game){
    /*
    takes in pointer to struct of current game -> evaluates advantage and returns a score 
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
    if (!turn)//computer turn
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
                        if (!(allBitboard(game) & singlePiece)) {
                            
                            newPiece = game->whitePawns - (1ULL << position) + (1ULL << position + 16);
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
                                flip = 1;
                                break;
                            }
                            
                        }
                    }
                    
                    //pawn move 1 forward
                    singlePiece = (1ULL << position + 8);
                    if ( (position/8 < 7) && !(allBitboard(game) & singlePiece)) { //pawn move 1 square

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
        
        for (i = 5; i >= 0; --i){
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
                        if (!(allBitboard(game) & singlePiece)) {
                            
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
                    if ( (position/8 > 0) && !(allBitboard(game) & singlePiece)) { //pawn move 1 square

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