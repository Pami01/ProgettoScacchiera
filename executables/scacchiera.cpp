#include <iostream>
#include <vector>
#include <fstream>
#include "Board.h"

#ifdef _WIN32
#include <Windows.h>
#define clear std::system("cls")
#endif

#ifdef linux
#include <cstdlib>
#define clear std::system("clear")
#endif

void print(std::vector<Chess::Position> p)
{
   for (int i = 0; i < p.size(); i++)
   {
      std::cout << "(" << p[i].x << ", " << p[i].y << ")";
   }
}

int main()
{
   Chess::Board b;

   Chess::Ending game_over;

   std::cout << "Inserisci il nome da dare a questa partita: ";
   std::string match_name;
   std::getline(std::cin, match_name);

   std::ofstream ofs(match_name + ".txt");

   do
   {
      std::cout << b << std::endl;

      std::string move;
      std::getline(std::cin, move);

      clear;

      if (move.size() != 5)
      {
         std::cout << "Mossa non valida\n\n";
         continue;
      }

      try
      {
         const Chess::Position from = move.substr(0, 2);
         const Chess::Position to = move.substr(3, 2);
         b.move(from, to);
         ofs << from << ' ' << to << std::endl;
      }
      catch (Chess::Board::IllegalMoveException e)
      {
         std::cout << "Mossa non valida\n\n";
      }
      catch (Chess::Position::InvalidPositionException e)
      {
         std::cout << "La mossa inserita non è valida. Formato accettato: 'xx xx'\n\n";
      }
   } while (!(game_over = b.is_game_over()));

   std::cout << b << std::endl;

   ofs.close();

   return 0;
}