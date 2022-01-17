//@Author: Lorenzo Pamio
#ifndef COMPUTER_CPP
#define COMPUTER_CPP

#include <vector>
#include <exception>
#include "Computer.h"

namespace Chess
{
   Computer::Computer(Board &board, const Side side)
       : _board(board), _side(side)
   {
   }

   std::string Computer::move(void) const
   {
      std::vector<Piece> pieces;
      // Prendo pezzi dello schieramento attuale del bot
      _board.get_pieces(_side, pieces);
      // Scelgo un pezzo casuale del quale effettuare una mossa
      while (_side == _board.turn())
      {
         int piece = rand() % pieces.size();
         // Controllo se il pezzo può muoversi
         std::vector<Position> moves;
         pieces[piece].get_moves(moves);
         if (moves.size() != 0)
         {
            // Estraggo una posizione random di quelle "legali" nella quale spostarmi
            int position = rand() % moves.size();
            try
            {
               // Tento lo spostamento. Se la mossa non è legale ricomincio il ciclo ed estraggo un altro pezzo
               // Passo ad ogni mossa una eventuale promozione
               _board.move(pieces[piece].position(), moves[position], get_random_promotion());
               return pieces[piece].position().to_string() + " " + moves[position].to_string();
            }
            catch (Board::IllegalMoveException e)
            {
            }
         }
      }
      throw std::exception();
   }

   PieceType Computer::get_random_promotion() const
   {
      switch (rand() % 4)
      {
      case 0:
         return QUEEN;
      case 1:
         return BISHOP;
      case 2:
         return ROOK;
      case 3:
         return KNIGHT;
      }
      throw std::exception();
   }

}

#endif