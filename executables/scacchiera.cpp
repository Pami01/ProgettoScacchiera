// @author: Pietro Bovolenta
// TODO Verificare passaggio promozione a file
#include <iostream>
#include <fstream>
#include <time.h>
#include "Board.h"
#include "Computer.h"

#ifdef _WIN32
#include <Windows.h>
#define clear std::system("cls")
#define wait Sleep(0.1)
#endif

#ifdef linux
#include <cstdlib>
#define clear std::system("clear")
#endif

Chess::Ending player_computer(Chess::Board &b, std::ostream &os);
Chess::Ending computer_computer(Chess::Board &b, std::ostream &os);
const char *ending(Chess::Ending e);

int main(int argc, char *argv[])
{
   if (argc < 2 || (std::string(argv[1]) != "pc" && std::string(argv[1]) != "cc"))
   {
      std::cout << "Devi passare come parametro 'pc' o 'cc' per giocare tra giocatore e computer o tra computer e computer\n";
      return -1;
   }

   srand(time(NULL));

   Chess::Board board;

   Chess::Ending game_over;

   std::cout << "Inserisci il nome da dare a questa partita: ";
   std::string match_name;
   std::getline(std::cin, match_name);

   std::ofstream ofs(match_name + ".txt");

   if (std::string(argv[1]) == "pc")
      game_over = player_computer(board, ofs);
   else
      game_over = computer_computer(board, ofs);

   ofs.close();

   std::cout << board << std::endl;

   std::cout << ending(game_over) << std::endl;

   return 0;
}

Chess::Ending player_computer(Chess::Board &board, std::ostream &os)
{
   Chess::Side player_side = Chess::Side(rand() % 2);
   Chess::Computer computer{board, !player_side};

   Chess::Ending game_over;

   do
   {
      std::cout << board << std::endl;

      if (board.turn() == player_side)
      {
         std::string move;
         std::getline(std::cin, move);

         if (move.size() != 5)
         {
            std::cout << "Mossa non valida\n\n";
            continue;
         }

         try
         {
            bool promotion = false;
            const Chess::Position from = move.substr(0, 2);
            const Chess::Position to = move.substr(3, 2);
            if (board.find_piece(from).type() == Chess::PAWN && to.y == (player_side == Chess::WHITE ? 7 : 0))
            {
               promotion = true;
            }
            board.move(from, to);
            os << from << ' ' << to;
            if (promotion)
               os << ' ' << (char)(board.find_piece(to).type());
            os << std::endl;
         }
         catch (Chess::Board::IllegalMoveException e)
         {
            std::cout << "Mossa non valida\n\n";
         }
         catch (Chess::Board::PieceNotFoundException e)
         {
            std::cout << "Non c'è un pezzo alla posizione iniziale\n\n";
         }
         catch (Chess::Position::InvalidPositionException e)
         {
            std::cout << "La mossa inserita non è valida. Formato accettato: 'xx xx'\n\n";
         }
      }
      else
      {
         computer.move(os);
      }

      clear;
   } while (!(game_over = board.is_game_over()));
   return game_over;
}

Chess::Ending computer_computer(Chess::Board &board, std::ostream &os)
{
   constexpr int MAX_MOVES = 120;

   Chess::Computer computer1{board, Chess::WHITE};
   Chess::Computer computer2{board, Chess::BLACK};

   Chess::Ending game_over;
   int moves = 0;
   do
   {
      std::cout << board << std::endl;

      wait;

      if (board.turn() == Chess::WHITE)
         computer1.move(os);
      else
      {
         computer2.move(os);
         moves++;
      }

      clear;
   } while (!(game_over = board.is_game_over()) && moves <= MAX_MOVES);
   return game_over;
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