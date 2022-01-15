#ifndef POSITION_CPP
#define POSITION_CPP

#include "Position.h"

namespace Chess
{
   class Position::InvalidPositionException
   {
   };

   bool Position::is_valid(void) const
   {
      if (!((x < 0) || (x > 7)) && !((y < 0) || ((y > 7))))
         return true;

      return false;
   }

   void Position::decode_arithmetic_notation(const std::string &arithmetic_notation)
   {
      if (arithmetic_notation.size() != 2)
         throw InvalidPositionException();

      x = arithmetic_notation[1] - 49;
      y = std::tolower(arithmetic_notation[0]) - 97;

      if (!(is_valid()))
         throw InvalidPositionException();
   }

   Position::Position(const short x, const short y) : x(x), y(y)
   {
      if (!(is_valid()))
         throw InvalidPositionException();
   }

   Position::Position(const std::string arithmetic_notation)
   {
      decode_arithmetic_notation(arithmetic_notation);
   }

   Position::Position(const char *arithmetic_notation)
      : Position(std::string(arithmetic_notation))
   {
   }

   Position Position::move(const short x_increment, const short y_increment) const
   {
      short newX = x + x_increment;
      short newY = y + y_increment;

      return Position(newX, newY);
   }

   bool Position::operator==(const Position &other) const
   {
      if ((x == other.x) && (y == other.y))
         return true;
      return false;
   }

   bool Position::operator!=(const Position &other) const
   {
      return !(*this == other);
   }
}

#endif