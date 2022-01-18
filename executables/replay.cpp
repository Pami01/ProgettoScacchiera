//@author: Lorenzo Pamio
#include <iostream>
#include <fstream>
#include "Board.h"

#ifdef _WIN32
#include <Windows.h>
#define clear std::system("cls")
#define space "\r\n"
#define wait Sleep(10)
#endif

#ifdef linux
#include <cstdlib>
#define clear std::system("clear")
#define space "\n"
#endif

const char *ending(Chess::Ending e);
const bool is_read_legal(std::string line);

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
      int line_counter = 0;
      //Leggo finche il file non è terminato
      while (!file.eof())
      {
         std::string line;
         std::getline(file, line);
         line_counter++;
         if (!is_read_legal(line))
         {
            std::cout << "Trovata stringa non valida:" << line << "alla riga numero: " << line_counter << std::endl;
            std::cout << "Continuo saltando la riga corrente?:S/N" << std::endl
                      << "NOTA(Potrebbe generare problemi!)";
            std::cin >> line;
            if (std::toupper(line[0]) == 'S')
               continue;
            break;
         }
         wait;
         clear;
         try
         {
            std::string promotionType = "K";
            if (line.size() == 7)
               promotionType = line.substr(6, 1);
            b.move(line.substr(0, 2), line.substr(3, 2), Chess::PieceType(promotionType[0]));
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
      std::fstream fileIn{argv[2]};
      std::ofstream fileOut{argv[3]};
      fileOut << b << std::endl;
      int line_counter = 0;
      while (!fileIn.eof())
      {
         std::string line;
         std::getline(fileIn, line);
         line_counter++;
         fileOut << "-------------" << space;
         if (!is_read_legal(line))
         {
            std::cout << "Trovata stringa non valida:" << line << "alla riga numero: " << line_counter << std::endl;
            std::cout << "Continuo saltando la riga corrente?:S/N" << std::endl
                      << "NOTA(Potrebbe generare problemi!)";
            std::cin >> line;
            if (std::toupper(line[0]) == 'S')
               continue;
            break;
         }
         try
         {
            std::string promotionType = "K";
            if (line.size() == 7)
               promotionType = line.substr(6, 1);
            b.move(line.substr(0, 2), line.substr(3, 2), Chess::PieceType(promotionType[0]));
            fileOut << b << std::endl;
         }
         catch (Chess::Board::IllegalMoveException e)
         {
            std::cout << "Errore irreversibile board, rilevata mossa non valida:" << line << std::endl;
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

const bool is_read_legal(std::string line)
{
   int size = line.size();
   //verifico innanzitutto se lo standard è rispettato e rispetta la nomenclatura "LN LN" || "LN LN L" (L=lettera N=numero)
   //controllo se la stringa ha 5 o 7 caratteri
   if (size == 5 || size == 7)
   {
      if (std::isalpha(line[0]) && std::isdigit(line[1]) && std::isalpha(line[3]) && std::isdigit(line[4]))
      {
         //se sono nel caso 5 caratteri, ho finito, la nomenclatura è legale
         if (size == 5)
            return true;
         //verifico ultimo carattere, se è alfabetico sono apposto
         return std::isalpha(line[6]);
      }
   }
   return false;
}