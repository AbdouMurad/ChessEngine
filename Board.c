#include <stdio.h>
#include "Board.h"

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
unsigned long long int blackBitBoard(struct gameBoard *game){//returns bit board of all opponent pieces
    return (*game).blackPawns | (*game).blackKnights | (*game).blackBishops | (*game).blackRooks | (*game).blackQueen | (*game).blackKing;
}
unsigned long long int whiteBitboard(struct gameBoard *game){ //return bit board of all player pieces
    return (*game).whitePawns | (*game).whiteKnights | (*game).whiteBishops | (*game).whiteRooks | (*game).whiteQueen | (*game).whiteKing;

}
unsigned long long int allBitboard(struct gameBoard *game){ //returns bit board will all pieces
    return blackBitBoard(game)| whiteBitboard(game);
}
void printBoard(struct gameBoard *game, int start, int end){
    long long unsigned int current = 1ULL << 63;
    int cur = 0;
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            cur = 63 - (i*8 + j);
            if (cur == start) setColour(YELLOW);
            else if (cur == end) setColour(GREEN); 
            if (current & allBitboard(game)){
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
void checkCollision(long long unsigned int singlePiece, struct gameBoard *game,struct gameBoard *newGame)
{ //check which pieces are colliding and remove the piece
    if (singlePiece & game->blackPawns) newGame->blackPawns ^= singlePiece;
    else if (singlePiece & game->blackKnights) newGame->blackKnights ^= singlePiece;
    else if (singlePiece & game->blackBishops) newGame->blackBishops ^= singlePiece;
    else if (singlePiece & game->blackRooks) newGame->blackRooks ^= singlePiece;
    else if (singlePiece & game->blackKing) newGame->blackKing ^= singlePiece;
    else if (singlePiece & game->whitePawns) newGame->whitePawns ^= singlePiece;
    else if (singlePiece & game->whiteKnights) newGame->whiteKnights ^= singlePiece;
    else if (singlePiece & game->whiteBishops) newGame->whiteBishops ^= singlePiece;
    else if (singlePiece & game->whiteRooks) newGame->whiteRooks ^= singlePiece;
    else if (singlePiece & game->whiteKing) newGame->whiteKing ^= singlePiece;


}
int makeMove(struct gameBoard *game, int start, int end){
    long long unsigned int singlePiece = 1ULL << start;
    long long unsigned int endPiece = 1ULL << end;
    int color = 0; //0 --> white else black
    if (blackBitBoard(game) & singlePiece) color = 1;
    if (!color){
        if (game->whitePawns & singlePiece){
            game->whitePawns -= singlePiece;
            game->whitePawns += (1ULL << end);
        }
        else if (game->whiteBishops & singlePiece){
            game->whiteBishops -= singlePiece;
            game->whiteBishops += (1ULL << end);
        }
        else if (game->whiteKnights & singlePiece){
            game->whiteKnights -= singlePiece;
            game->whiteKnights += (1ULL << end);
        }
        else if (game->whiteRooks & singlePiece){
            game->whiteRooks -= singlePiece;
            game->whiteRooks += (1ULL << end);
        }
        else if (game->whiteQueen & singlePiece){
            game->whiteQueen -= singlePiece;
            game->whiteQueen += (1ULL << end);
        }
        else if (game->whiteKing & singlePiece){
            game->whiteKing -= singlePiece;
            game->whiteKing += (1ULL << end);
        }
        game->blackPawns = game->blackPawns & ~endPiece;
        game->blackBishops = game->blackBishops & ~endPiece;
        game->blackKnights = game->blackKnights & ~endPiece;
        game->blackQueen = game->blackQueen & ~endPiece;
        game->blackRooks = game->blackRooks & ~endPiece;
        game->blackKing = game->blackKing & ~endPiece;
    }
    else{
        if (game->blackPawns & singlePiece){
            game->blackPawns -= singlePiece;
            game->blackPawns += (1ULL << end);
        }
        else if (game->blackBishops & singlePiece){
            game->blackBishops -= singlePiece;
            game->blackBishops += (1ULL << end);
        }
        else if (game->blackKnights & singlePiece){
            game->blackKnights -= singlePiece;
            game->blackKnights += (1ULL << end);
        }
        else if (game->blackRooks & singlePiece){
            game->blackRooks -= singlePiece;
            game->blackRooks += (1ULL << end);
        }
        else if (game->blackQueen & singlePiece){
            game->blackQueen -= singlePiece;
            game->blackQueen += (1ULL << end);
        }
        else if (game->blackKing & singlePiece){
            game->blackKing -= singlePiece;
            game->blackKing += (1ULL << end);
        }
        game->whitePawns = game->whitePawns & ~endPiece;
        game->whiteBishops = game->whiteBishops & ~endPiece;
        game->whiteKnights = game->whiteKnights & ~endPiece;
        game->whiteQueen = game->whiteQueen & ~endPiece;
        game->whiteRooks = game->whiteRooks & ~endPiece;
        game->whiteKing = game->whiteKing & ~endPiece;
    }
    return 0;
}
