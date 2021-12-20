#ifndef PIECE_H
#define PIECE_H

#include "Position.h"

enum Side
{
   WHITE = 1,
   BLACK = 0
};

class Piece
{
private:
   Position p;
   Side s;

public:
   virtual bool move();
};

#endif