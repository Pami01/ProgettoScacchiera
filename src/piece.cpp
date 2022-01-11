#ifndef PIECE_CPP
#define PIECE_CPP

#include "Piece.h"
#include "Position.h"
namespace Chess
{
   Piece::Piece(const Position position, const Side side, const PieceType type) : _position(position), _side(side), _type(type)
   {
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
   void Piece::get_moves(std::vector<Position> &v) const
   {
      //Spezzare logiche in colonne-righe-diagonali
      switch (_type)
      {
      case KING:
         get_king_moves(v);
         break;
      case QUEEN:
         get_queen_moves(v);
         break;
      case ROOK:
         get_rook_moves(v);
         break;
      case BISHOP:
         get_bishop_moves(v);
         break;
      case KNIGHT:
         get_knight_moves(v);
         break;
      case PAWN:
         get_pawn_moves(v);
         break;
      }
   };

   void Piece::get_king_moves(std::vector<Position> &v) const
   {
      for (int i = -1; i < 2; i++)
      {
         for (int j = -1; j < 2; j++)
         {
            if (i != 0 && j != 0)
               try
               {
                  v.push_back(_position.move(i, j));
               }
               catch (Position::InvalidPositionException e)
               {
               }
         }
      }
      for (int i = -2; i < 3; i++)
      {
         try
         {
            if (i != 0)
               v.push_back(_position.move(i, 0));
         }
         catch (Position::InvalidPositionException e)
         {
         }
      }
   }

   void Piece::get_bishop_moves(std::vector<Position> &v) const
   {
      bool ended = true;
      //diagonale primo quadrante
      int i = 1, j = 1;
      while (ended)
      {
         try
         {
            v.push_back(_position.move(i, j));
            i++;
            j++;
         }
         catch (Position::InvalidPositionException e)
         {
            ended = false;
         }
      }
      //diagonale 3° quadrante
      i = -1;
      j = -1;
      ended = true;
      while (ended)
      {
         try
         {
            v.push_back(_position.move(i, j));
            i--;
            j--;
         }
         catch (Position::InvalidPositionException e)
         {
            ended = false;
         }
      }
      //diagonale 4° quadrante
      i = 1;
      j = -1;
      ended = true;
      while (ended)
      {
         try
         {
            v.push_back(_position.move(i, j));
            i++;
            j--;
         }
         catch (Position::InvalidPositionException e)
         {
            ended = false;
         }
      }
      //diagonale 2° quadrante
      i = -1;
      j = 1;
      ended = true;
      while (ended)
      {
         try
         {
            v.push_back(_position.move(i, j));
            i--;
            j++;
         }
         catch (Position::InvalidPositionException e)
         {
            ended = false;
         }
      }
      return;
   }

   void Piece::get_rook_moves(std::vector<Position> &v) const
   {
      bool ended = true;
      //colonna verticale
      int i = 1, j = 0;
      while (ended)
      {
         try
         {
            v.push_back(_position.move(j, i));
            i += i;
            j += j;
         }
         catch (Position::InvalidPositionException e)
         {
            if (i == 1 && j == 0)
            {
               i = 0;
               j = 1;
            }
            else if (i == 0 && j == 1)
            {
               i = -1;
               j = 0;
            }
            else if (i == -1 && j == 0)
            {
               i = 0;
               j = -1;
            }
            else if (i == 0 && j == -1)
            {
               ended = false;
            }
         }
      }
      return;
   }

   void Piece::get_queen_moves(std::vector<Position> &v) const
   {
      get_rook_moves(v);
      get_bishop_moves(v);
      return;
   }

   void Piece::get_knight_moves(std::vector<Position> &v) const
   {
      int i = 1, j = 2;
      bool ended = true;
      while (ended)
      {
         try
         {
            v.push_back(_position.move(i, j));
         }
         catch (Position::InvalidPositionException e)
         {
         }
         if (i == 1 && j == 2)
         {
            i = 2;
            j = 1;
         }
         else if (i == 2 && j == 1)
         {
            j = -1;
         }
         else if (i == 2 && j == -1)
         {
            i = 1;
            j = -2;
         }
         else if (i == 1 && j == -2)
         {
            i = -1;
            j = 2;
         }
         else if (i == -1 && j == 2)
         {
            j = -2;
         }
         else if (i == -1 && j == -2)
         {
            i = -2;
            j = 1;
         }
         else if (i == -2 && j == 1)
         {
            j = -1;
         }
         else if (i == -2 && j == -1)
         {
            ended = false;
         }
      }
      return;
   }

   void Piece::get_pawn_moves(std::vector<Position> &v) const
   {
      int move = 0;
      if (_side)
      {
         move = 1;
         if (_position.y == 1)
         {
            v.push_back(_position.move(0, 2 * move));
         }
      }
      else
      {
         move = -1;
         if (_position.y == 6)
         {
            v.push_back(_position.move(0, -2 * move));
         }
      }
      for (int i = -1; i < 2; i++)
      {
         try
         {
            v.push_back(_position.move(i, move));
         }
         catch (Position::InvalidPositionException e)
         {
         }
      }
      return;
   }

}

#endif