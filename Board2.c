#include <stdio.h>
#include "Board2.h"
const char * const GREEN = "\x1b[32m";
const char * const YELLOW = "\x1b[33m";
const char * const WHITE = "\x1b[0m";
const char * const BLACK = "\x1b[90m";

const char * current = WHITE;

void setupGame(struct gameBoard *Game)
{
    // White Pieces
    Game->game[White][Pawn] =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b11111111ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8
    Game->game[White][Knight] =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x42, for knights on b1 & g1)
    0b01000010ULL;         // Row 8
    Game->game[White][Bishop] =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x24, for bishops on c1 & f1)
    0b00100100ULL;         // Row 8
    Game->game[White][Rook] =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x81, for rooks on a1 & h1)
    0b10000001ULL;         // Row 8

    Game->game[White][Queen] =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x10)
    0b00010000ULL;         // Row 8

    Game->game[White][King] =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x08)
    0b00001000ULL;         // Row 8

    Game->WhiteCastle = WhiteBoth;
    // Black Pieces

    Game->game[Black][Pawn] =
    0b00000000ULL << 56 |  // Row 1
    0b11111111ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8
    Game->game[Black][Knight] =
    0b01000010ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x42, for knights on b1 & g1)
    0b00000000ULL;         // Row 8
    Game->game[Black][Bishop] =
    0b00100100ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x24, for bishops on c1 & f1)
    0b00000000ULL;         // Row 8
    Game->game[Black][Rook] =
    0b10000001ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x81, for rooks on a1 & h1)
    0b00000000ULL;         // Row 8

    Game->game[Black][Queen] =
    0b00010000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x10)
    0b00000000ULL;         // Row 8

    Game->game[Black][King] =
    0b00001000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x08)
    0b00000000ULL;         // Row 8

    Game->BlackCastle = BlackBoth;
}

void setupBlankGame(struct gameBoard *Game)
{
    Game->WhiteCastle = WhiteBoth;
    Game->BlackCastle = BlackBoth;
    // White Pieces
    Game->game[White][Pawn] =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00010000ULL << 24 |  // Row 5
    0b00000001ULL << 16 |  // Row 6
    0b11100110ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8
    Game->game[White][Knight] =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00100100ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x42, for knights on b1 & g1)
    0b00000000ULL;         // Row 8
    Game->game[White][Bishop] =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x24, for bishops on c1 & f1)
    0b00100000ULL;         // Row 8
    Game->game[White][Rook] =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x81, for rooks on a1 & h1)
    0b10000001ULL;         // Row 8

    Game->game[White][Queen] =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x10)
    0b00010000ULL;         // Row 8

    Game->game[White][King] =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x08)
    0b00001000ULL;         // Row 8

    // Black Pieces

    Game->game[Black][Pawn] =
    0b00000000ULL << 56 |  // Row 1
    0b11100111ULL << 48 |  // Row 2
    0b00001000ULL << 40 |  // Row 3
    0b00010000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8
    Game->game[Black][Knight] =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000100ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x42, for knights on b1 & g1)
    0b00000000ULL;         // Row 8
    Game->game[Black][Bishop] =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00110000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x24, for bishops on c1 & f1)
    0b00000000ULL;         // Row 8
    Game->game[Black][Rook] =
    0b10000001ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000001ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x81, for rooks on a1 & h1)
    0b00000000ULL;         // Row 8

    Game->game[Black][Queen] =
    0b00010000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x10)
    0b00000000ULL;         // Row 8

    Game->game[Black][King] =
    0b00001000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x08)
    0b00000000ULL;         // Row 8
}

void setColour(const char *colour) {
  if (current == colour) return;
  printf("%s", colour);
  current = colour;
}

unsigned long long int ColorBitBoard(struct gameBoard *Game, enum Color color){//returns bit board of all opponent pieces
    return Game->game[color][Pawn] | Game->game[color][Knight] | Game->game[color][Bishop] | Game->game[color][Rook] | Game->game[color][Queen] | Game->game[color][King];
}

unsigned long long int AllBitBoard(struct gameBoard *Game) {
  return ColorBitBoard(Game, White) | ColorBitBoard(Game, Black);
}

int CheckCollision(long long unsigned int singlePiece, struct gameBoard *Game,  struct gameBoard *newGame) {
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 6; ++j) {
      if (singlePiece & Game->game[i][j]) {
        newGame->game[i][j] ^= singlePiece;
        return j+1;
      }
    }
  }
  return 0;
}

void PrintBoard(struct gameBoard *Game, int start, int end) {
  long long unsigned int current = 1ULL << 63;
  int cur = 0;
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      cur = 63 - (i*8 + j);
      if (cur == start) setColour(YELLOW);
      else if (cur == end) setColour(GREEN);
      if (current & AllBitBoard(Game)) {
        if (cur != start && cur != end) setColour(WHITE);
        if (current & Game->game[White][Pawn]) printf("P ");
        else if (current & Game->game[White][Bishop]) printf("B ");
        else if (current & Game->game[White][Knight]) printf("k ");
        else if (current & Game->game[White][Rook]) printf("R ");
        else if (current & Game->game[White][Queen]) printf("Q ");
        else if (current & Game->game[White][King]) printf("K ");
        if (cur != start && cur != end) setColour(BLACK);
        if (current & Game->game[Black][Pawn]) printf("P ");
        else if (current & Game->game[Black][Bishop]) printf("B ");
        else if (current & Game->game[Black][Knight]) printf("k ");
        else if (current & Game->game[Black][Rook]) printf("R ");
        else if (current & Game->game[Black][Queen]) printf("Q ");
        else if (current & Game->game[Black][King]) printf("K ");  
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

int MakeMove(struct gameBoard *Game, int start, int end, enum Color color) {
  long long unsigned int singlePiece = 1ULL << start;
  long long unsigned int endPiece = 1ULL << end;
  if (Game->game[color][Pawn] & singlePiece) Game->game[color][Pawn] = Game->game[color][Pawn] - singlePiece + endPiece;
  else if (Game->game[color][Knight] & singlePiece) Game->game[color][Knight] = Game->game[color][Knight] - singlePiece + endPiece;
  else if (Game->game[color][Bishop] & singlePiece) Game->game[color][Bishop] = Game->game[color][Bishop] - singlePiece + endPiece;
  else if (Game->game[color][Rook] & singlePiece) Game->game[color][Rook] = Game->game[color][Rook] - singlePiece + endPiece;
  else if (Game->game[color][Queen] & singlePiece) Game->game[color][Queen] = Game->game[color][Queen] - singlePiece + endPiece;
  else if (Game->game[color][King] & singlePiece) Game->game[color][King] = Game->game[color][King] - singlePiece + endPiece;
}