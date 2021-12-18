#ifndef PIECE_H
#define PIECE_H



enum Side {
   BIANCO=1, NERO=0
};


class Piece {
   private:
      Position p;
      Side s;
   public:
      virtual bool move() = 0;

};

#endif