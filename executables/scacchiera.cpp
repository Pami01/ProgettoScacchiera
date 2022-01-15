#include <iostream>
#include "Board.h"
#include <vector>
#include <Windows.h>

void print(std::vector<Chess::Position> p){
	for(int i=0;i<p.size();i++){
		std::cout<<"("<<p[i].x<<", "<<p[i].y<<")";
	}
}

int main()
{
	Chess::Board b;

   Chess::Ending game_over = Chess::Ending::NONE;

   do {
      system("cls");
      std::cout << b << std::endl;
      
      std::string move;
      std::getline(std::cin, move);
      try {
         b.move(move.substr(0, 2), move.substr(3, 2));
      } catch(Chess::Board::IllegalMoveException e) {
         std:: cout << "Mossa non valida disabile!\n";
      }
   } while (!(game_over = b.is_game_over()));

   std::cout << b << std::endl;

   return 0;
}