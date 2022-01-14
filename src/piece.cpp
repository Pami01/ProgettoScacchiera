#ifndef PIECE_CPP
#define PIECE_CPP

#include "Piece.h"

namespace Chess
{


   // Overload operatore toggle per lo schieramento
   Side operator!(const Side &side)
   {
      return Side(!side);
   }
}

#endif