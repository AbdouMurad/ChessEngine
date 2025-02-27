#include <stdio.h>
#include <stdlib.h>

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
        score = score + kingPst[coord];
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
        score = score - kingPst[63 - coord];  
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

int alphabeta(int depth, struct gameBoard *game, int turn, int alpha, int beta, int *moves){
    *moves += 1;
    if (depth == 0){ //check for stalemate and checkmate as well
        return evaluate(game);
    }

    struct gameBoard newGame = (*game);
    int eval;
    int maxEval;
    int position;

    int i;
    int flip;

    unsigned long long int copyPiece;
    unsigned long long int newPiece;

    unsigned long long int singlePiece; //contains single piece
    //assume computer is always white
    if (!turn){ //computer turn
        maxEval = -1000000;
        //generate positions
        
        for (i = 0, flip = 1; i < 5 && flip; ++i){
            if (i == 0) copyPiece = (*game).whitePawns;
            else if (i == 1) copyPiece = (*game).whiteKnights;
            else if (i == 2) copyPiece = (*game).whiteBishops;
            else if (i == 3) copyPiece = (*game).whiteRooks;
            else if (i == 4) copyPiece = (*game).whiteQueen;
            while (flip && copyPiece){
                position = __builtin_ctzll(copyPiece);
                copyPiece &= copyPiece -1;
                if (i == 0) //pawn
                {
                    //pawn move 2 forward
                    if (flip && position/8 == 1){
                        singlePiece = (1ULL << position + 16);
                        if (!(allBitBoard(game) & singlePiece)) {
                            
                            newPiece = (*game).whitePawns - (1ULL << position) + (1ULL << position + 16);
                            newGame.whitePawns = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame.whitePawns = (*game).whitePawns;
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d - %d 1\n",newPiece,eval,maxEval); 
                        }
                    }
                    //pawn move 1 forward
                    singlePiece = (1ULL << position + 8);
                    if (flip && (position/8 < 7) && !(allBitBoard(game) & singlePiece)) { //pawn move 1 square

                        newPiece = (*game).whitePawns - (1ULL << position) + singlePiece;
                        newGame.whitePawns = newPiece;
                        eval = alphabeta(depth-1, &newGame,1,alpha,beta,moves);
                        newGame.whitePawns = (*game).whitePawns;
                        if (eval > maxEval) maxEval = eval;
                        if (eval > alpha) alpha = eval;
                        if (beta <= alpha) flip = 0;
                        printf("%llu - %d -- %d 2\n",newPiece,eval,maxEval);
                    }

                    //check diagonal pawn attack - left
                    singlePiece = 1ULL << (position + 9);
                    if (flip && (position % 8 != 7) && (position/8 < 7) && !(whiteBitboard(game) & singlePiece) && (blackBitBoard(game) & singlePiece) ) {
                        newPiece = (*game).whitePawns - (1ULL << position) + singlePiece;
                        
                        //check which black piece is attacked
                        if (newPiece & (*game).blackPawns) newGame.blackPawns -= singlePiece;
                        else if (newPiece & (*game).blackKnights) newGame.blackKnights -= singlePiece;
                        else if (newPiece & (*game).blackBishops) newGame.blackBishops -= singlePiece;
                        else if (newPiece & (*game).blackRooks) newGame.blackRooks -= singlePiece;
                        else if (newPiece & (*game).blackQueen) newGame.blackQueen -= singlePiece;

                        newGame.whitePawns = newPiece;
                        eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                        newGame = (*game);
                        if (eval > maxEval) maxEval = eval;
                        if (eval > alpha) alpha = eval;
                        if (beta <= alpha) flip = 0;
                        printf("%llu - %d -- %d 3\n",newPiece,eval,maxEval);
                    }
                    //check diagonal pawn attack - right
                    singlePiece = 1ULL << (position + 7);
                    if (flip && (position/8 < 7) && (position % 8) && !(whiteBitboard(game) & singlePiece) && (blackBitBoard(game) & singlePiece)) {
                        
                        newPiece = (*game).whitePawns - (1ULL << position) + singlePiece;
                        //check which black piece is attacked
                        if (newPiece & (*game).blackPawns) newGame.blackPawns -= singlePiece;
                        else if (newPiece & (*game).blackKnights) newGame.blackKnights -= singlePiece;
                        else if (newPiece & (*game).blackBishops) newGame.blackBishops -= singlePiece;
                        else if (newPiece & (*game).blackRooks) newGame.blackRooks -= singlePiece;
                        else if (newPiece & (*game).blackQueen) newGame.blackQueen -= singlePiece;
                        
                        newGame.whitePawns = newPiece;
                        eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                        newGame = (*game);
                        if (eval > maxEval) maxEval = eval;
                        if (eval > alpha) alpha = eval;
                        if (beta <= alpha) flip = 0;
                        printf("%llu - %d -- %d 4\n",newPiece,eval,maxEval);
                    }
                }
                else if (i == 1)//knight
                {
                    //left up
                    singlePiece = 1ULL << (position + 10);
                    if (flip && (position % 8 < 6) && (position/8 < 7) && !(whiteBitboard(game) & singlePiece)) {
                        newPiece = (*game).whiteKnights - (1ULL << position) + singlePiece;
                        if (newPiece & (*game).blackPawns) newGame.blackPawns -= singlePiece;
                        else if (newPiece & (*game).blackKnights) newGame.blackKnights -= singlePiece;
                        else if (newPiece & (*game).blackBishops) newGame.blackBishops -= singlePiece;
                        else if (newPiece & (*game).blackRooks) newGame.blackRooks -= singlePiece;
                        else if (newPiece & (*game).blackQueen) newGame.blackQueen -= singlePiece;

                        newGame.whiteKnights = newPiece;
                        eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                        newGame = (*game);
                        if (eval > maxEval) maxEval = eval;
                        if (eval > alpha) alpha = eval;
                        if (beta <= alpha) flip = 0;
                        printf("%llu - %d -- %d 5\n",newPiece,eval,maxEval);
                    }

                    //left down
                    singlePiece = 1ULL << (position - 6);
                    if (flip && (position % 8 < 6) && (position/8 > 0) && !(whiteBitboard(game) & singlePiece)) {
                        newPiece = (*game).whiteKnights - (1ULL << position) + singlePiece;
                        if (newPiece & (*game).blackPawns) newGame.blackPawns -= singlePiece;
                        else if (newPiece & (*game).blackKnights) newGame.blackKnights -= singlePiece;
                        else if (newPiece & (*game).blackBishops) newGame.blackBishops -= singlePiece;
                        else if (newPiece & (*game).blackRooks) newGame.blackRooks -= singlePiece;
                        else if (newPiece & (*game).blackQueen) newGame.blackQueen -= singlePiece;

                        newGame.whiteKnights = newPiece;
                        eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                        newGame = (*game);
                        if (eval > maxEval) maxEval = eval;
                        if (eval > alpha) alpha = eval;
                        if (beta <= alpha) flip = 0;
                        printf("%llu - %d -- %d 6\n",newPiece,eval,maxEval);
                    }
                    //right up
                    singlePiece = 1ULL << (position + 6);
                    if (flip && (position % 8 > 1) && (position/8 < 7) && !(whiteBitboard(game) & singlePiece)) {
                        newPiece = (*game).whiteKnights - (1ULL << position) + singlePiece;
                        if (newPiece & (*game).blackPawns) newGame.blackPawns -= singlePiece;
                        else if (newPiece & (*game).blackKnights) newGame.blackKnights -= singlePiece;
                        else if (newPiece & (*game).blackBishops) newGame.blackBishops -= singlePiece;
                        else if (newPiece & (*game).blackRooks) newGame.blackRooks -= singlePiece;
                        else if (newPiece & (*game).blackQueen) newGame.blackQueen -= singlePiece;

                        newGame.whiteKnights = newPiece;
                        eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                        newGame = (*game);
                        if (eval > maxEval) maxEval = eval;
                        if (eval > alpha) alpha = eval;
                        if (beta <= alpha) flip = 0;
                        printf("%llu - %d -- %d 7\n",newPiece,eval,maxEval);
                    }
                    //right down
                    singlePiece = 1ULL << (position - 10);
                    if (flip && (position % 8 > 1) && (position/8 > 0) && !(whiteBitboard(game) & singlePiece)) {
                        newPiece = (*game).whiteKnights - (1ULL << position) + singlePiece;
                        if (newPiece & (*game).blackPawns) newGame.blackPawns -= singlePiece;
                        else if (newPiece & (*game).blackKnights) newGame.blackKnights -= singlePiece;
                        else if (newPiece & (*game).blackBishops) newGame.blackBishops -= singlePiece;
                        else if (newPiece & (*game).blackRooks) newGame.blackRooks -= singlePiece;
                        else if (newPiece & (*game).blackQueen) newGame.blackQueen -= singlePiece;

                        newGame.whiteKnights = newPiece;
                        eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                        newGame = (*game);
                        if (eval > maxEval) maxEval = eval;
                        if (eval > alpha) alpha = eval;
                        if (beta <= alpha) flip = 0;
                        printf("%llu - %d -- %d 8\n",newPiece,eval,maxEval);
                    }
                    //down right
                    singlePiece = 1ULL << (position - 17);
                    if (flip && (position % 8 > 0) && (position/8 > 1) && !(whiteBitboard(game) & singlePiece)) {
                        newPiece = (*game).whiteKnights - (1ULL << position) + singlePiece;
                        if (newPiece & (*game).blackPawns) newGame.blackPawns -= singlePiece;
                        else if (newPiece & (*game).blackKnights) newGame.blackKnights -= singlePiece;
                        else if (newPiece & (*game).blackBishops) newGame.blackBishops -= singlePiece;
                        else if (newPiece & (*game).blackRooks) newGame.blackRooks -= singlePiece;
                        else if (newPiece & (*game).blackQueen) newGame.blackQueen -= singlePiece;

                        newGame.whiteKnights = newPiece;
                        eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                        newGame = (*game);
                        if (eval > maxEval) maxEval = eval;
                        if (eval > alpha) alpha = eval;
                        if (beta <= alpha) flip = 0;
                        printf("%llu - %d -- %d 9\n",newPiece,eval,maxEval);
                    }
                    //down left
                    singlePiece = 1ULL << (position - 15);
                    if (flip && (position % 8 < 7) && (position/8 > 1) && !(whiteBitboard(game) & singlePiece)) {
                        newPiece = (*game).whiteKnights - (1ULL << position) + singlePiece;
                        if (newPiece & (*game).blackPawns) newGame.blackPawns -= singlePiece;
                        else if (newPiece & (*game).blackKnights) newGame.blackKnights -= singlePiece;
                        else if (newPiece & (*game).blackBishops) newGame.blackBishops -= singlePiece;
                        else if (newPiece & (*game).blackRooks) newGame.blackRooks -= singlePiece;
                        else if (newPiece & (*game).blackQueen) newGame.blackQueen -= singlePiece;

                        newGame.whiteKnights = newPiece;
                        eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                        newGame = (*game);
                        if (eval > maxEval) maxEval = eval;
                        if (eval > alpha) alpha = eval;
                        if (beta <= alpha) flip = 0;
                        printf("%llu - %d -- %d 10\n",newPiece,eval,maxEval);
                    }
                    //up right
                    singlePiece = 1ULL << (position + 15);
                    if (flip && (position % 8 > 0) && (position/8 < 6) && !(whiteBitboard(game) & singlePiece)) {
                        newPiece = (*game).whiteKnights - (1ULL << position) + singlePiece;
                        if (newPiece & (*game).blackPawns) newGame.blackPawns -= singlePiece;
                        else if (newPiece & (*game).blackKnights) newGame.blackKnights -= singlePiece;
                        else if (newPiece & (*game).blackBishops) newGame.blackBishops -= singlePiece;
                        else if (newPiece & (*game).blackRooks) newGame.blackRooks -= singlePiece;
                        else if (newPiece & (*game).blackQueen) newGame.blackQueen -= singlePiece;

                        newGame.whiteKnights = newPiece;
                        eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                        newGame = (*game);
                        if (eval > maxEval) maxEval = eval;
                        if (eval > alpha) alpha = eval;
                        if (beta <= alpha) flip = 0;
                        printf("%llu - %d -- %d 11\n",newPiece,eval,maxEval);
                    }
                    //up left
                    singlePiece = 1ULL << (position + 17);
                    if (flip && (position % 8 < 7) && (position/8 < 6) && !(whiteBitboard(game) & singlePiece)) {
                        newPiece = (*game).whiteKnights - (1ULL << position) + singlePiece;
                        if (newPiece & (*game).blackPawns) newGame.blackPawns -= singlePiece;
                        else if (newPiece & (*game).blackKnights) newGame.blackKnights -= singlePiece;
                        else if (newPiece & (*game).blackBishops) newGame.blackBishops -= singlePiece;
                        else if (newPiece & (*game).blackRooks) newGame.blackRooks -= singlePiece;
                        else if (newPiece & (*game).blackQueen) newGame.blackQueen -= singlePiece;

                        newGame.whiteKnights = newPiece;
                        eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                        newGame = (*game);
                        if (eval > maxEval) maxEval = eval;
                        if (eval > alpha) alpha = eval;
                        if (beta <= alpha) flip = 0;
                        printf("%llu - %d -- %d 12\n",newPiece,eval,maxEval);
                    }
                }
                else if (i == 2)//bishop
                {
                    int r;
                    int c;
                    int k; // 0 - blocker found
                    //top left
                    for (r = position/8 + 1, c = position % 8 + 1, k = 1; k && r < 8 && c < 8; ++r, ++c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = (*game).whiteBishops - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) k = 0;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns -= singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights -= singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops -= singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks -= singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen -= singlePiece;
                            newGame.whiteBishops = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d tly\n",newPiece,eval,maxEval);
                            k = 0;
                        }
                        else {
                            newGame.whiteBishops = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d tln\n",newPiece,eval,maxEval);
                        }
                    }
                    //top right
                    for (r = position/8 + 1, c = position % 8 - 1, k = 1; k && r < 8 && c >= 0; ++r, --c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = (*game).whiteBishops - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) k = 0;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns -= singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights -= singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops -= singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks -= singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen -= singlePiece;
                            newGame.whiteBishops = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d try\n",newPiece,eval,maxEval);
                            k = 0;
                        }
                        else {
                            newGame.whiteBishops = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d trn\n",newPiece,eval,maxEval);
                        }
                    }
                    //bottom left
                    for (r = position/8 - 1, c = position % 8 + 1, k = 1; k && r >= 0 && c < 8; --r, ++c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = (*game).whiteBishops - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) k = 0;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns -= singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights -= singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops -= singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks -= singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen -= singlePiece;
                            newGame.whiteBishops = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d bly\n",newPiece,eval,maxEval);
                            k = 0;
                        }
                        else {
                            newGame.whiteBishops = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d bln\n",newPiece,eval,maxEval);
                        }
                    }
                    //bottom right
                    for (r = position/8 - 1, c = position % 8 - 1, k = 1; k && r >= 0 && c >= 0; --r, --c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = (*game).whiteBishops - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) k = 0;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns -= singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights -= singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops -= singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks -= singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen -= singlePiece;
                            newGame.whiteBishops = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d bry\n",newPiece,eval,maxEval);
                            k = 0;
                        }
                        else {
                            newGame.whiteBishops = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d brn\n",newPiece,eval,maxEval);
                        }
                    }
                }
                else if (i == 3) //rook
                {
                    printf("here\n");
                    int r;
                    int c;
                    int k; // 0 - blocker found
                    //up
                    for (r = position/8 + 1, c = position % 8, k = 1; k && r < 8; ++r){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = game->whiteRooks - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) k = 0;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns -= singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights -= singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops -= singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks -= singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen -= singlePiece;
                            newGame.whiteRooks = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d ty\n",newPiece,eval,maxEval);
                            k = 0;
                        }
                        else {
                            newGame.whiteRooks = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d tn\n",newPiece,eval,maxEval);
                        }
                    }
                    //down
                    for (r = position/8 - 1, c = position % 8, k = 1; k && r >= 0; --r){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = game->whiteRooks - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) k = 0;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns -= singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights -= singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops -= singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks -= singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen -= singlePiece;
                            newGame.whiteRooks = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d by\n",newPiece,eval,maxEval);
                            k = 0;
                        }
                        else {
                            newGame.whiteRooks = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d bn\n",newPiece,eval,maxEval);
                        }
                    }
                    //left
                    for (r = position/8, c = position % 8 + 1, k = 1; k && c < 8; ++c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = game->whiteRooks - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) k = 0;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns -= singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights -= singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops -= singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks -= singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen -= singlePiece;
                            newGame.whiteRooks = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d ly\n",newPiece,eval,maxEval);
                            k = 0;
                        }
                        else {
                            newGame.whiteRooks = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d ln\n",newPiece,eval,maxEval);
                        }
                    }
                    //right
                    for (r = position/8, c = position % 8 -1, k = 1; k && c >= 0; --c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = game->whiteRooks - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) k = 0;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns -= singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights -= singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops -= singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks -= singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen -= singlePiece;
                            newGame.whiteRooks = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d ry\n",newPiece,eval,maxEval);
                            k = 0;
                        }
                        else {
                            newGame.whiteRooks = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d rn\n",newPiece,eval,maxEval);
                        }
                    }
                }    
                else if (i == 4) //queen
                {
                    int r;
                    int c;
                    int k; // 0 - blocker found
                    //top left
                    for (r = position/8 + 1, c = position % 8 + 1, k = 1; k && r < 8 && c < 8; ++r, ++c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = (*game).whiteQueen - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) k = 0;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns -= singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights -= singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops -= singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks -= singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen -= singlePiece;
                            newGame.whiteQueen = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d tly\n",newPiece,eval,maxEval);
                            k = 0;
                        }
                        else {
                            newGame.whiteQueen = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d tln\n",newPiece,eval,maxEval);
                        }
                    }
                    //top right
                    for (r = position/8 + 1, c = position % 8 - 1, k = 1; k && r < 8 && c >= 0; ++r, --c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = (*game).whiteQueen - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) k = 0;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns -= singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights -= singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops -= singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks -= singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen -= singlePiece;
                            newGame.whiteQueen = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d try\n",newPiece,eval,maxEval);
                            k = 0;
                        }
                        else {
                            newGame.whiteQueen = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d trn\n",newPiece,eval,maxEval);
                        }
                    }
                    //bottom left
                    for (r = position/8 - 1, c = position % 8 + 1, k = 1; k && r >= 0 && c < 8; --r, ++c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = (*game).whiteQueen - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) k = 0;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns -= singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights -= singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops -= singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks -= singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen -= singlePiece;
                            newGame.whiteQueen = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d bly\n",newPiece,eval,maxEval);
                            k = 0;
                        }
                        else {
                            newGame.whiteQueen = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d bln\n",newPiece,eval,maxEval);
                        }
                    }
                    //bottom right
                    for (r = position/8 - 1, c = position % 8 - 1, k = 1; k && r >= 0 && c >= 0; --r, --c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = (*game).whiteQueen - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) k = 0;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns -= singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights -= singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops -= singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks -= singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen -= singlePiece;
                            newGame.whiteQueen = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d bry\n",newPiece,eval,maxEval);
                            k = 0;
                        }
                        else {
                            newGame.whiteQueen = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d brn\n",newPiece,eval,maxEval);
                        }
                    }
                    //up
                    for (r = position/8 + 1, c = position % 8, k = 1; k && r < 8; ++r){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = game->whiteQueen - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) k = 0;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns -= singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights -= singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops -= singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks -= singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen -= singlePiece;
                            newGame.whiteQueen = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d ty\n",newPiece,eval,maxEval);
                            k = 0;
                        }
                        else {
                            newGame.whiteQueen = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d tn\n",newPiece,eval,maxEval);
                        }
                    }
                    //down
                    for (r = position/8 - 1, c = position % 8, k = 1; k && r >= 0; --r){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = game->whiteQueen - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) k = 0;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns -= singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights -= singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops -= singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks -= singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen -= singlePiece;
                            newGame.whiteQueen = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d by\n",newPiece,eval,maxEval);
                            k = 0;
                        }
                        else {
                            newGame.whiteQueen = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d bn\n",newPiece,eval,maxEval);
                        }
                    }
                    //left
                    for (r = position/8, c = position % 8 + 1, k = 1; k && c < 8; ++c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = game->whiteQueen - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) k = 0;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns -= singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights -= singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops -= singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks -= singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen -= singlePiece;
                            newGame.whiteQueen = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d ly\n",newPiece,eval,maxEval);
                            k = 0;
                        }
                        else {
                            newGame.whiteQueen = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d ln\n",newPiece,eval,maxEval);
                        }
                    }
                    //right
                    for (r = position/8, c = position % 8 -1, k = 1; k && c >= 0; --c){
                        singlePiece = 1ULL << (r*8 + c);
                        newPiece = game->whiteQueen - (1ULL << position) + singlePiece;
                        if (singlePiece & whiteBitboard(game)) k = 0;
                        else if (singlePiece & blackBitBoard(game)){
                            //check which black piece is attacked
                            if (newPiece & (*game).blackPawns) newGame.blackPawns -= singlePiece;
                            else if (newPiece & (*game).blackKnights) newGame.blackKnights -= singlePiece;
                            else if (newPiece & (*game).blackBishops) newGame.blackBishops -= singlePiece;
                            else if (newPiece & (*game).blackRooks) newGame.blackRooks -= singlePiece;
                            else if (newPiece & (*game).blackQueen) newGame.blackQueen -= singlePiece;
                            newGame.whiteQueen = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d ry\n",newPiece,eval,maxEval);
                            k = 0;
                        }
                        else {
                            newGame.whiteQueen = newPiece;
                            eval = alphabeta(depth -1,&newGame,1,alpha,beta,moves);
                            newGame = (*game);
                            if (eval > maxEval) maxEval = eval;
                            if (eval > alpha) alpha = eval;
                            if (beta <= alpha) flip = 0;
                            printf("%llu - %d -- %d rn\n",newPiece,eval,maxEval);
                        }
                    }
                }
            }
        }
        return maxEval;



    }




}

void setupBlankGame(struct gameBoard *game){
    (*game).whitePawns = 0b000000000000000000000000000000000000000000000000000000000000000;
    (*game).whiteKnights = 0b0000000000000000000000000000000000000000000000000000000000000000;
    (*game).whiteBishops = 0b0000000000000000000000000000000000000000000000000000000000000000;
    (*game).whiteRooks = 0b0000000000000000000000000000000000000000000000000000000000000000;
    (*game).whiteQueen = 0b1000000000000000000000000000000000000000000000000000000000000000;
    (*game).whiteKing = 0b0000000000000000000000000000000000000000000000000000000000000000;
    (*game).whiteCastle = 3;

    (*game).blackPawns = 0b0000000000000000000000000000000000000000000000000000000000000000;
    (*game).blackKnights = 0b0000000000000000000000000000000000000000000000000000000000000000;
    (*game).blackBishops = 0b0000000000000000000000000000000000000000000000000000000000000000;
    (*game).blackRooks = 0b0000000000000000000000000000000000000000000000000000000000000000;
    (*game).blackQueen = 0b0000000000000000000000000000000000000000000000000000000000000000;
    (*game).blackKing = 0b0000000000000000000000000000000000000000000000000000000000000000;
    (*game).blackCastle = 3;
};
void setupGame(struct gameBoard *game){
    (*game).whitePawns = 0b0000000000000000000000000000000000000000000000001111111100000000;
    (*game).whiteKnights = 0b0000000000000000000000000000000000000000000000000000000001000010;
    (*game).whiteBishops = 0b0000000000000000000000000000000000000000000000000000000000100100;
    (*game).whiteRooks = 0b0000000000000000000000000000000000000000000000000000000010000001;
    (*game).whiteQueen = 0b0000000000000000000000000000000000000000000000000000000000010000;
    (*game).whiteKing = 0b0000000000000000000000000000000000000000000000000000000000001000;
    (*game).whiteCastle = 3;

    (*game).blackPawns = 0b0000000011111111000000000000000000000000000000000000000000000000;
    (*game).blackKnights = 0b0100001000000000000000000000000000000000000000000000000000000000;
    (*game).blackBishops = 0b0010010000000000000000000000000000000000000000000000000000000000;
    (*game).blackRooks = 0b1000000100000000000000000000000000000000000000000000000000000000;
    (*game).blackQueen = 0b0000100000000000000000000000000000000000000000000000000000000000;
    (*game).blackKing = 0b0001000000000000000000000000000000000000000000000000000000000000;
    (*game).blackCastle = 3;}
int main(){


    //assume computer is white for now

    int moves = 0;
    int turn = 0; //0 - white / 1 - black 


    struct gameBoard game;
    setupGame(&game);
    //setupBlankGame(&game);
    int score = evaluate(&game);
    printf("SCORE: %d\n",score);
    int newScore = alphabeta(1,&game,0,-10000000,1000000, &moves);
    //printf("%d\n",score);
    printf("newScore %d - score %d\n",newScore,score);
    printf("moves: %d\n", moves);

}