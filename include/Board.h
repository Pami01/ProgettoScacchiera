#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include <iostream>
#include <vector>


class Board {
   private:
      //TODO Controllare presenza pezzi nella scacchiera 
      std::vector<Piece> pieces;
      //TODO Verificare efficenza booleano per turno 
      Side turn;
   public:

      Board();
      Board(std::vector<Piece> v);

      void move();
};

#endif