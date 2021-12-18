

struct Position{
   int x,y; //(0,0) IN A1

   //operator +;
   //
};

enum Deployment{
   BIANCO=1, NERO=0
};


class Piece{
   private:
      Position p;
      Deployment s;
   public:
      virtual bool move() = 0;

};