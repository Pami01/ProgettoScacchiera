#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <ostream>
#include "Position.h"
#include "Piece.h"

namespace Chess
{
   enum Ending {
      // false se non è finita la partita
      NONE = 0,
      // patte (1 - 5)
      STALEMATE = 1,
      _50_MOVE_RULE,
      INSUFFICIENT_MATERIAL,
      REPETITION,
      AGREEMENT,
      // Vittorie (10 - 11)
      // Il bianco ha mattato
      WHITE_CHECKMATE = 10,
      // Il nero ha mattato
      BLACK_CHECKMATE
   };

   class Board
   {
   private:
      std::vector<Piece> _pieces;
      Side _turn;

   private:
      // Prepara la posizione iniziale riempiendo il vector _pieces
      void initialize(void);
      // Cambia il turno
      void toggle_turn(void);
      // Cerca il pezzo ad una certa posizione e lo ritorna
      Piece find_piece(const Position &position);

   public:
      // Costruttore che inizializza una partita
      Board();
      // Costruttore che inizializza una partita da una specifica posizione
      Board(const std::vector<Piece> &pieces);

      // Eccezione per indicare una mossa invalida o illegale
      class InvalidMoveException;

      // Getter per i pezzi del bianco
      std::vector<Piece> pieces_white(void) const;
      // Getter per i pezzi del nero
      std::vector<Piece> pieces_black(void) const;

      // Sposta un pezzo dalla posizione 'from' alla posizione 'to'
      // Lancia una 'InvalidMoveException', se per qualche motivo la mossa non è valida
      void move(const Position &from, const Position &to);

      // Ritorna 'Ending::NONE = 0' se la partita non è finita, altrimenti ritorna il modo in cui è finita la partita
      Ending is_game_over(void) const;

      // Stampa la scacchiera
      friend std::ostream &operator<<(std::ostream &os, const Board &b);
   };
}

#endif