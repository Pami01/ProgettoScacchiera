#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <ostream>
#include "Position.h"
#include "Piece.h"

namespace Chess
{
   enum Ending
   {
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
      // Lancia una PieceNotFoundException se alla posizione inserita non c'è alcun pezzo
      Piece find_piece(const Position &position) const;
      // Ritorna true se il pezzo passato per parametro non può muoversi senza mettere sotto scacco il re
      bool is_pinned(const Piece &piece) const;
      // Ritrona true se un pezzo di 'side' controlla la posizione 'position'
      bool is_controlled(const Position &position, const Side &side) const;

   public:
      // Costruttore che inizializza una partita
      Board();
      // Costruttore che inizializza una partita da una specifica posizione
      Board(const std::vector<Piece> &pieces);

      // Eccezione per indicare una mossa invalida o illegale
      class IllegalMoveException;
      // Eccezione che viene lanciata quando non si è trovato un pezzo
      class PieceNotFoundException;
      // Eccezione che viene lanciata se si tenta di muovere un pezzo nel turno che non è il suo
      class WrongTurnException;

      // Getter per i pezzi di nero e bianco, in base al side passato
      // Copia i pezzi nel vector passato come output
      void get_pieces(Side side, std::vector<Piece> &output) const;

      // Sposta un pezzo dalla posizione 'from' alla posizione 'to'
      // Lancia una eccezione, se per qualche motivo la mossa non è valida
      void move(const Position from, const Position to);

      // Ritorna 'Ending::NONE = 0' se la partita non è finita, altrimenti ritorna il modo in cui è finita la partita
      Ending is_game_over(void) const;

      // Stampa la scacchiera
      friend std::ostream &operator<<(std::ostream &os, const Board &b);
   };
}

#endif