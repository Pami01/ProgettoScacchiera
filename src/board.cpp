#ifndef BOARD_CPP
#define BOARD_CPP

#include <algorithm>
#include <memory>
#include "Board.h"

namespace Chess
{
   /*       ECCEZIONI       */
   class Board::InvalidMoveException
   {
   };
   class Board::PieceNotFoundException
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
   void Board::pieces(Side side, std::vector<Piece> &output) const
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
               Piece p = b.find_piece({7 - i, j});
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
   }
}

#endif