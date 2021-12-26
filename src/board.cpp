#ifndef BOARD_CPP
#define BOARD_CPP

#include <algorithm>
#include <memory>
#include "Board.h"

namespace Chess
{
   /*       ECCEZIONI       */
   class Board::IllegalMoveException
   {
   };
   class Board::PieceNotFoundException
   {
   };
   class Board::WrongTurnException
   {
   };
   /*       COSTRUTTORI       */
   Board::Board()
       : _pieces(std::vector<Piece>())
   {
      _pieces.reserve(32);
      initialize();
   }
   Board::Board(const std::vector<Piece> &v)
       : _pieces(v) {}
   /*       METODI PRIVATI       */
   // TODO Testare la correttezza
   void Board::initialize(void)
   {
      // Pezzi del bianco
      _pieces.push_back(Piece{"A1", WHITE, ROOK});
      _pieces.push_back(Piece{"B1", WHITE, KNIGHT});
      _pieces.push_back(Piece{"C1", WHITE, BISHOP});
      _pieces.push_back(Piece{"D1", WHITE, QUEEN});
      _pieces.push_back(Piece{"E1", WHITE, KING});
      _pieces.push_back(Piece{"F1", WHITE, BISHOP});
      _pieces.push_back(Piece{"G1", WHITE, KNIGHT});
      _pieces.push_back(Piece{"H1", WHITE, ROOK});
      // Pedoni
      for (int i = 0; i < 8; i++)
      {
         std::string c = std::to_string('A' + i);
         _pieces.push_back(Piece{c + '2', WHITE, PAWN});
         _pieces.push_back(Piece{c + '7', BLACK, PAWN});
      }
      // Pezzi del nero
      _pieces.push_back(Piece{"A8", BLACK, ROOK});
      _pieces.push_back(Piece{"B8", BLACK, KNIGHT});
      _pieces.push_back(Piece{"C8", BLACK, BISHOP});
      _pieces.push_back(Piece{"D8", BLACK, QUEEN});
      _pieces.push_back(Piece{"E8", BLACK, KING});
      _pieces.push_back(Piece{"F8", BLACK, BISHOP});
      _pieces.push_back(Piece{"G8", BLACK, KNIGHT});
      _pieces.push_back(Piece{"H8", BLACK, ROOK});
   }
   // TODO Testare la correttezza
   void Board::toggle_turn(void)
   {
      _turn = Side(!_turn);
   }
   // TODO Testare la correttezza
   Piece Board::find_piece(const Position &position) const
   {
      auto it = std::find_if(_pieces.begin(),
                             _pieces.end(),
                             [position](const Piece &p)
                             {
                                return p.position() == position;
                             });
      if (it != _pieces.end())
         return *it;
      throw PieceNotFoundException();
   }
   /*       GETTERS       */
   // TODO Testare la correttezza
   void Board::get_pieces(Side side, std::vector<Piece> &output) const
   {
      output.reserve(_pieces.size());
      std::copy_if(_pieces.begin(),
                   _pieces.end(),
                   output.begin(),
                   [side](const Piece &p)
                   {
                      return p.side() == side;
                   });
   }

   bool Board::is_controlled(const Position &position, const Side &side) const
   {
   }

   bool Board::is_pinned(const Piece &piece) const
   {
      // Prendo tutti i pezzi che potrebbero causare il 'pin'
      std::vector<Piece> possible_pinning_pieces;
      possible_pinning_pieces.reserve(_pieces.size());
      std::copy_if(_pieces.begin(),
                   _pieces.end(),
                   possible_pinning_pieces.begin(),
                   [piece](const Piece &p)
                   {
                      // Gli unici pezzi che possono pinnare sono alfiere, regina e torre
                      return p.side() != piece.side() &&
                             (p.type() == BISHOP || p.type() == QUEEN || p.type() == ROOK);
                   });
      // Ciclo i pezzi e vedo se qualcuno 'pinna'
      for (const Piece &p : possible_pinning_pieces)
      {
         std::vector<Position> moves;
         p.get_moves(moves);
         // TODO Controlla tutti i pezzi se 'pinnano' piece e ritorna true in caso favorevole
      }
      return false;
   }
   /*       OVERLOAD OPERATORI       */
   // TODO Testare la correttezza
   std::ostream &operator<<(std::ostream &os, const Board &b)
   {
      for (short i = 0; i < 8; i++)
      {
         os << 8 - i << ' ';
         for (short j = 0; j < 8; j++)
         {
            try
            {
               Piece p = b.find_piece({(short)(7 - i), j});
               os << (p.side() == WHITE ? (char)p.side() : (char)(p.side() + 32));
            }
            catch (Board::PieceNotFoundException e)
            {
               os << ' ';
            }
         }
         os << std::endl;
      }
      os << std::endl;
      os << "  ";
      for (char c = 'A'; c <= 'H'; c++)
         os << c;
      return os;
   }
   /*       FUNZIONALITA' DI GIOCO       */

   void Board::move(const Position from, const Position to)
   {
      // Lancia una 'PieceNotFoundException' se il pezzo non viene trovato
      Piece p_from = find_piece(from);
      // Controlla se è il turno del pezzo selezionato
      if (p_from.side() != _turn)
         throw WrongTurnException();
      // Controlla se la posizione finale è tra quelle in cui si può muovere il pezzo selezionato
      std::vector<Position> moves;
      p_from.get_moves(moves);

      auto it =
          std::find_if(moves.begin(),
                       moves.end(),
                       [to](const Position pos)
                       {
                          return pos == to;
                       });
      if (it == moves.end())
         throw IllegalMoveException();
      // Controlla se la casa di arrivo contiene un pezzo dello stesso schieramento di quello selezionato
      try
      {
         Piece p_to = find_piece(to);
         if (p_to.side() == p_from.side())
            throw IllegalMoveException();
      }
      catch (PieceNotFoundException e)
      {
         // Si arriva qua se ci si sta muovendo in una casa vuota
         // Non si fa niente perché significa che il pezzo si potrebbe muovere in questa posizione
      }

      // TODO Controllo interazioni con gli altri pezzi
      // Controllo 'pin'
      if (is_pinned(p_from))
         throw IllegalMoveException();
      // Controllo se il re si può muovere senza finire sotto scacco
      if (p_from.type() == KING && is_controlled(to, Side(!p_from.side())))
         throw IllegalMoveException();
      // TODO Controllo pedone
   }
}

#endif