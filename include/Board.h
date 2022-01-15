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

      // Variabili logiche
      // controlli arrocco
      bool _can_white_castle_left{true};
      bool _can_white_castle_right{true};
      bool _can_black_castle_left{true};
      bool _can_black_castle_right{true};
      // ultima colonna pedone (solo per en passant)
      short _last_pawn_move{-1};

   private:
      // Prepara la posizione iniziale riempiendo il vector _pieces
      void initialize(void);
      // Cambia il turno
      void toggle_turn(void);
      // Cerca il pezzo ad una certa posizione e lo ritorna
      // Lancia una PieceNotFoundException se alla posizione inserita non c'è alcun pezzo
      Piece find_piece(const Position &position) const;
      // Ritorna true se la posizione corrente ha generato uno scacco al re dello schieramento side
      bool is_check(const Side &side, const std::vector<Piece> &pieces) const;
      // Ritorna true se il pezzo di partenza è ostruito da un altro pezzo cercando di arrivare alla posizione to
      bool is_obstructed(const Piece &p, const Position &to, const std::vector<Piece> &pieces) const;
      // Metodo che elimina il pezzo alla posizione indicata dal vettore _pieces
      void kill_piece(const Position &position);
      // Ritorna true il pezzo alla posizione from si può muovere nella posizione to, false altrimenti
      bool can_move(const Piece &p_from, const Position &to) const;

   public:
      // Costruttore che inizializza una partita
      Board();
      // Costruttore che inizializza una partita da una specifica posizione
      Board(const std::vector<Piece> &pieces);

      // Eccezione per indicare una mossa invalida o illegale
      class IllegalMoveException;
      // Eccezione che viene lanciata quando non si è trovato un pezzo
      class PieceNotFoundException;

      // Getter per i pezzi di nero e bianco, in base al side passato
      // Copia i pezzi nel vector passato come output
      void get_pieces(Side side, std::vector<Piece> &output) const;

      // Sposta un pezzo dalla posizione 'from' alla posizione 'to'
      // Lancia una eccezione, se per qualche motivo la mossa non è valida
      void move(const Position from, const Position to, const PieceType promotion_type = PieceType::UNSELECTED);

      // Ritorna 'Ending::NONE = 0' se la partita non è finita, altrimenti ritorna il modo in cui è finita la partita
      Ending is_game_over(void) const;

      // Stampa la scacchiera
      friend std::ostream &operator<<(std::ostream &os, const Board &b);
   };
}

#endif