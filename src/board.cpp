#ifndef BOARD_CPP
#define BOARD_CPP

#include "Board.h"

namespace Chess
{
   Board::Board() : pieces(std::vector<Piece>()), turn(WHITE)
   {
   }

}

#endif