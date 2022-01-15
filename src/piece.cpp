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
   bool is_valid_piece_type(const PieceType &type)
   {
      switch (type)
      {
      case PAWN:
      case KNIGHT:
      case BISHOP:
      case ROOK:
      case QUEEN:
      case KING:
         return true;
      default:
         return false;
      }
   }

}

#endif