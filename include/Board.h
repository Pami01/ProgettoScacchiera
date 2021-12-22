#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <ostream>
#include "Position.h"
#include "Piece.h"

namespace Chess
{
   class Board
   {
   private:
      std::vector<Piece> _pieces;
      Side _turn;

   private:
      // Prepara la posizione iniziale riempiendo il vector _pieces
      void initialize(void);

   public:
      // Costruttore che inizializza una partita
      Board();
      // Costruttore che inizializza una partita da una specifica posizione
      Board(const std::vector<Piece> &pieces);

      // Eccezione per indicare una mossa invalida o illegale
      class InvalidMoveException;

      // Sposta un pezzo dalla posizione 'from' alla posizione 'to'
      // Lancia una 'InvalidMoveException', se per qualche motivo la mossa non è valida
      void move(const Position &from, const Position &to);

      // Stampa la scacchiera
      friend std::ostream &operator<<(std::ostream &os, const Board &b);
   };
}

#endif