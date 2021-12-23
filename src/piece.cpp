#ifndef PIECE_CPP
#define PIECE_CPP

#include "Piece.h"
#include "Position.h"
namespace Chess
{
   Piece::Piece(const Position position, const Side side, const PieceType type)
   {
      _position = position;
      _side = side;
      _type = type;
   }

   // Getter di _position
   Position Piece::position(void) const
   {
      return _position;
   }
   // Getter di _side
   Side Piece::side(void) const
   {
      return _side;
   }
   // Getter di _type
   PieceType Piece::type(void) const
   {
      return _type;
   }

   // Sposta il pezzo dalla posizione corrente a quella passata per parametro, senza eseguire controlli
   void Piece::move(const Position position)
   {
      _position = position;
   }

   // Ritorna tutte le posizioni possibili in cui il pezzo corrente si potrebbe muovere,
   //    senza considerare gli altri pezzi nella scacchiera
   std::vector<Position> *Piece::get_moves(void) const
   {
      std::vector<Position> *v = new std::vector<Position>();
      //Spezzare logiche in colonne-righe-diagonali
      switch (_type)
      {
      case KING:
         get_king_moves(v);
         break;
      case QUEEN:
         break;
      case ROOK:
         break;
      case BISHOP:
         break;
      case KNIGHT:
         break;
      case PAWN:
         break;
      }
      return v;
   };

   void Piece::get_king_moves(std::vector<Position> *p) const
   {
      for (int i = -1; i < 2; i++)
      {
         for (int j = -1; j < 2; j++)
         {
            if (i != 0 && i != 0)
               p->push_back(Position{_position.move(i, j)});
         }
      }
   }
}

#endif