//@author: Lorenzo Pamio
#include <iostream>
#include <fstream>
#include "Board.h"

#ifdef _WIN32
#include <Windows.h>
#define clear std::system("cls")
#define wait Sleep(1000)
#endif

#ifdef linux
#include <cstdlib>
#define clear std::system("clear")
#endif

const char *ending(Chess::Ending e);

int main(int argc, char *argv[])
{
   //Inizio verificando gli argomenti passati al replay
   if (argc <= 1 || argc > 4)
   {
      std::cout << "Inserisci un numero valido di argomenti";
      return -1;
   }
   //Controllo che il primo argomento inserito sia uguale a v o f (Per avviare una delle funzioni previste dal programma replay)
   if (!(*argv[1] == 'v' || *argv[1] == 'f'))
   {
      std::cout << "Inserisci degli argomenti validi";
      return -1;
   }
   if (*argv[1] == 'v')
   {
      //Creo la board e la mostro per la prima volta
      Chess::Board b;
      std::cout << b << std::endl;
      std::fstream file{argv[2]};
      while (!file.eof())
      {
         std::string line;
         std::getline(file, line);
         wait;
         try
         {

            b.move(line.substr(0, 2), line.substr(3, 2));
            std::cout << b << std::endl;
         }
         catch (Chess::Board::IllegalMoveException e)
         {
            std::cout << "Errore irreversibile board, rilevata mossa non valida:" << line;
         }
      }
      std::cout << ending(b.is_game_over());
   }
   else
   {
      Chess::Board b;
      std::cout << b << std::endl;
      std::fstream fileIn{argv[2]};
      std::ofstream fileOut{argv[3]};
      std::cout << fileOut.is_open() << std::endl;
      while (!fileIn.eof())
      {
         std::string line;
         std::getline(fileIn, line);
         try
         {

            b.move(line.substr(0, 2), line.substr(3, 2));
            fileOut << b << std::endl;
         }
         catch (Chess::Board::IllegalMoveException e)
         {
            std::cout << "Errore irreversibile board, rilevata mossa non valida:" << line;
         }
      }

      fileOut << ending(b.is_game_over());
      fileOut.close();
   }
   return 0;
}

const char *ending(Chess::Ending e)
{
   switch (e)
   {
   case Chess::STALEMATE:
      return "Stallo";
   case Chess::_50_MOVE_RULE:
      return "Regola delle 50 mosse";
   case Chess::INSUFFICIENT_MATERIAL:
      return "Materiale insufficiente";
   case Chess::REPETITION:
      return "Ripetizione di mosse";
   case Chess::WHITE_CHECKMATE:
      return "SCACCOMATTO! Vince il bianco";
   case Chess::BLACK_CHECKMATE:
      return "SCACCOMATTO! Vince il nero";
   default:
      return "La partita non e' finita";
   }
}