#include <stdio.h>
#include "Board.h"
const char * const GREEN = "\x1b[32m";
const char * const YELLOW = "\x1b[33m";
const char * const WHITE = "\x1b[0m";
const char * const BLACK = "\x1b[90m";

const char *current = WHITE;

int fen(struct gameBoard *Game, char *fen) {
    // Clear board
    for (int color = 0; color < 2; color++) {
        for (int piece = 0; piece < 6; piece++) {
            Game->game[color][piece] = 0ULL;
        }
    }

    Game->WhiteCastle = Neither;
    Game->BlackCastle = Neither;
    Game->enPassant[White] = 8;
    Game->enPassant[Black] = 8;

    int pos = 63;
    int i = 0;

    // Piece placement
    for (char c; pos >= 0; ++i) {
        c = fen[i];
        if (c >= '1' && c <= '8') {
            pos -= (c - '0');
        } else if (c == '/') {
            continue;
        } else {
            int color = (c >= 'A' && c <= 'Z') ? White : Black;
            int type;
            switch (c | 32) { // normalize to lowercase
                case 'p': type = Pawn; break;
                case 'r': type = Rook; break;
                case 'n': type = Knight; break;
                case 'b': type = Bishop; break;
                case 'q': type = Queen; break;
                case 'k': type = King; break;
                default: continue;
            }
            Game->game[color][type] |= 1ULL << pos;
            pos--;
        }
    }

    // Side to move
    i++; // skip space
    int turn = fen[i] == 'w' ? White : Black;
    i += 2;

    // Castling rights
    if (fen[i] == '-') {
        i++;
    } else {
        while (fen[i] != ' ') {
            switch (fen[i]) {
                case 'K': Game->WhiteCastle = Game->WhiteCastle == WhiteQueen ? WhiteBoth : WhiteKing; break;
                case 'Q': Game->WhiteCastle = Game->WhiteCastle == WhiteKing ? WhiteBoth : WhiteQueen; break;
                case 'k': Game->BlackCastle = Game->BlackCastle == BlackQueen ? BlackBoth : BlackKing; break;
                case 'q': Game->BlackCastle = Game->BlackCastle == BlackKing ? BlackBoth : BlackQueen; break;
            }
            i++;
        }
    }

    i++; // skip space to en passant square

    // En passant square
    if (fen[i] == '-') {
        Game->enPassant[White] = 8;
        Game->enPassant[Black] = 8;
        i++;
    } else {
        int file = fen[i] - 'a';
        int rank = fen[i + 1] - '1';

        if (rank == 2) { // en passant available for black
            Game->enPassant[Black] = file;
            Game->enPassant[White] = 8;
        } else if (rank == 5) { // en passant available for white
            Game->enPassant[White] = file;
            Game->enPassant[Black] = 8;
        } else {
            Game->enPassant[White] = 8;
            Game->enPassant[Black] = 8;
        }

        i += 2;
    }

    return turn;
}

void setupGame(struct gameBoard *Game)
{
    Game->enPassant[White] = 8;
    Game->enPassant[Black] = 8;
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
//debug setup (should keep setupGame() as default game board)
void setupBlankGame(struct gameBoard *Game)
{
    Game->WhiteCastle = WhiteBoth;
    Game->BlackCastle = BlackBoth;
    Game->enPassant[White] = 8;
    Game->enPassant[Black] = 8;
    // White Pieces
    Game->game[White][Pawn] =
    0b00000000ULL << 56 |  // Row 8
    0b00000000ULL << 48 |  // Row 7
    0b00000000ULL << 40 |  // Row 6
    0b00000000ULL << 32 |  // Row 5
    0b00010000ULL << 24 |  // Row 4
    0b00001000ULL << 16 |  // Row 3
    0b11100111ULL << 8  |  // Row 2
    0b00000000ULL;         // Row 1
    Game->game[White][Knight] =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00001000ULL << 8  |  // Row 7 (0x42, for knights on b1 & g1)
    0b00000000ULL;         // Row 8
    Game->game[White][Bishop] =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00000000ULL << 40 |  // Row 3
    0b00000000ULL << 32 |  // Row 4
    0b10000000ULL << 24 |  // Row 5
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
    0b00000100ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7 (0x10)
    0b00000000ULL;         // Row 8

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
    0b00101110ULL << 48 |  // Row 2
    0b00000001ULL << 40 |  // Row 3
    0b01010000ULL << 32 |  // Row 4
    0b00000000ULL << 24 |  // Row 5
    0b00000000ULL << 16 |  // Row 6
    0b00000000ULL << 8  |  // Row 7
    0b00000000ULL;         // Row 8
    Game->game[Black][Knight] =
    0b00000000ULL << 56 |  // Row 1
    0b00000000ULL << 48 |  // Row 2
    0b00100100ULL << 40 |  // Row 3
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
    0b00000000ULL << 56 |  // Row 1
    0b00010000ULL << 48 |  // Row 2
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

//check if collision exist on Turn color with singlePiece in Game, apply change in newGame (remove collision)
int CheckCollision(long long unsigned int singlePiece, struct gameBoard *Game,  struct gameBoard *newGame, enum Color Turn) {
    for (int j = 0; j < 6; ++j) {
      if (singlePiece & Game->game[Turn][j]) {
        newGame->game[Turn][j] ^= singlePiece;
        return j+1;
      }
    }
  return 0;
}

void PrintBoard(struct gameBoard *Game, int start, int end) {
  long long unsigned int current = 1ULL << 63;
  int cur = 0;
  for (int i = 0; i < 8; ++i) {
    setColour(WHITE);
    printf("DEBUG: %d",(8-i));
    printf("|");
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
    printf("\n");
  }
  setColour(WHITE);
  printf("DEBUG: X|---------------\n");
  printf("DEBUG:   a b c d e f g h\n");
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