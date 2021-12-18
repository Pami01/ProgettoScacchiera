#ifndef POSITION_H
#define POSITION_H

struct Position {
   int x, y; //(0,0) IN A1

   //operator +;
   //
};

Position operator+(const Position &p1, const Position &p2);
Position& operator+=(Position &p1, const Position &p2);
bool operator==(const Position &p1, const Position &p2);
bool operator!=(const Position &p1, const Position &p2);

#endif