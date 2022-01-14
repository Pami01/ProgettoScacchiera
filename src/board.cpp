#ifndef BOARD_CPP
#define BOARD_CPP

#include <algorithm>
#include "Board.h"

namespace Chess
{
   /*       ECCEZIONI       */
   class Board::IllegalMoveException
   {
   };
   class Board::PieceNotFoundException
   {
   };
   class Board::WrongTurnException
   {
   };
   /*       COSTRUTTORI       */
   Board::Board()
       : _pieces(std::vector<Piece>())
   {
      _pieces.reserve(32);
      initialize();
   }
   Board::Board(const std::vector<Piece> &v)
       : _pieces(v) {}
   /*       METODI PRIVATI       */
   // TODO Testare la correttezza
   void Board::initialize(void)
   {
      // Pezzi del bianco
      _pieces.push_back(Piece{"A1", WHITE, ROOK});
      _pieces.push_back(Piece{"B1", WHITE, KNIGHT});
      _pieces.push_back(Piece{"C1", WHITE, BISHOP});
      _pieces.push_back(Piece{"D1", WHITE, QUEEN});
      _pieces.push_back(Piece{"E1", WHITE, KING});
      _pieces.push_back(Piece{"F1", WHITE, BISHOP});
      _pieces.push_back(Piece{"G1", WHITE, KNIGHT});
      _pieces.push_back(Piece{"H1", WHITE, ROOK});
      // Pedoni
      for (int i = 0; i < 8; i++)
      {
         std::string c = std::to_string('A' + i);
         _pieces.push_back(Piece{c + '2', WHITE, PAWN});
         _pieces.push_back(Piece{c + '7', BLACK, PAWN});
      }
      // Pezzi del nero
      _pieces.push_back(Piece{"A8", BLACK, ROOK});
      _pieces.push_back(Piece{"B8", BLACK, KNIGHT});
      _pieces.push_back(Piece{"C8", BLACK, BISHOP});
      _pieces.push_back(Piece{"D8", BLACK, QUEEN});
      _pieces.push_back(Piece{"E8", BLACK, KING});
      _pieces.push_back(Piece{"F8", BLACK, BISHOP});
      _pieces.push_back(Piece{"G8", BLACK, KNIGHT});
      _pieces.push_back(Piece{"H8", BLACK, ROOK});
   }
   // TODO Testare la correttezza
   void Board::toggle_turn(void)
   {
      _turn = !_turn;
   }
   // TODO Testare la correttezza
   Piece Board::find_piece(const Position &position) const
   {
      auto it = std::find_if(_pieces.begin(),
                             _pieces.end(),
                             [&position](const Piece &p)
                             {
                                return p.position() == position;
                             });
      if (it != _pieces.end())
         return *it;
      throw PieceNotFoundException();
   }
   /*       GETTERS       */
   // TODO Testare la correttezza
   void Board::get_pieces(Side side, std::vector<Piece> &output) const
   {
      // Inizializza vector output con size esatta di pezzi appertenente al side corrispondente
      output = std::vector<Piece>{};
      for (const Piece &p : _pieces)
      {
         if (p.side() == side)
            output.push_back(p);
      }
   }

   bool Board::is_check(const Side &side, const std::vector<Piece> &pieces) const
   {
      // Prendo il re dalla scacchiera (non serve controllare che ci sia il re perché ci deve essere, altrimenti la posizione sulla scacchiera non avrebbe senso)
      const Piece king = *std::find_if(pieces.begin(), pieces.end(),
                                       [&side](const Piece &p)
                                       {
                                          return p.type() == KING && p.side() == side;
                                       });
      for (const Piece &p : pieces)
      {
         // Ignoro i pezzi dello stesso schieramento del re
         if (p.side() == side)
            continue;
         // Controllo se la posizione del re è compresa tra quelle possibili del pezzo
         std::vector<Position> moves;
         p.get_moves(moves);

         auto it = std::find_if(moves.begin(), moves.end(),
                                [&king](const Position &pos)
                                {
                                   return king.position() == pos;
                                });

         if (it == moves.end())
            continue;
         // Se ho un pedone che è sulla stessa colonna del re, di sicuro non può scaccarlo
         if (p.type() == PAWN && p.position().x == king.position().x)
            continue;
         // Se la visione tra il pezzo e il re non è ostruita da altri pezzi (di qualsiasi schieramento), il re è sotto scacco
         if (!is_obstructed(p, king.position(), pieces))
            return true;
      }
      return false;
   }

   // TODO Testare la correttezza
   bool Board::is_obstructed(const Piece &p, const Position &to, const std::vector<Piece> &pieces) const
   {
      // Il cavallo non può avere il percorso ostruito
      if (p.type() == KNIGHT)
         return false;
      // Controllo se c'è qualche pezzo tra 'p.position()' e 'to' partendo dalla posizione precedente a 'to' e arrivando alla successiva di 'p.position()'
      short directionX = p.position().x > to.x ? 1 : (p.position().x < to.x ? -1 : 0),
            directionY = p.position().y > to.y ? 1 : (p.position().y < to.y ? -1 : 0);
      Position curr = to.move(directionX, directionY);

      while (p.position() != curr)
      {
         auto it = std::find_if(pieces.begin(), pieces.end(),
                                [&curr](const Piece &piece)
                                {
                                   return piece.position() == curr;
                                });
         // Se trovo un pezzo tra 'p.position()' e 'to' ritorno true (c'è qualcuno che blocca la vista di 'p' verso 'to')
         if (it != pieces.end())
            return true;
         // Incremento la posizione attuale
         curr = curr.move(directionX, directionY);
      }
      return false;
   }

   void Board::kill_piece(const Position &position)
   {
      _pieces.erase(std::find(_pieces.begin(), _pieces.end(), [&position](const Piece &p)
                              { return p.position() == position; }));
   }

   /*       OVERLOAD OPERATORI       */
   // TODO Testare la correttezza
   std::ostream &operator<<(std::ostream &os, const Board &b)
   {
      for (short i = 0; i < 8; i++)
      {
         os << 8 - i << ' ';
         for (short j = 0; j < 8; j++)
         {
            try
            {
               Piece p = b.find_piece({(short)(7 - i), j});
               os << (p.side() == WHITE ? (char)p.side() : (char)(p.side() + 32));
            }
            catch (Board::PieceNotFoundException e)
            {
               os << ' ';
            }
         }
         os << std::endl;
      }
      os << std::endl;
      os << "  ";
      for (char c = 'A'; c <= 'H'; c++)
         os << c;
      return os;
   }
   /*       FUNZIONALITA' DI GIOCO       */

   void Board::move(const Position from, const Position to)
   {
      // Lancia una 'PieceNotFoundException' se il pezzo non viene trovato
      const Piece p_from = find_piece(from);
      // Controlla se è il turno del pezzo selezionato
      if (p_from.side() != _turn)
         throw WrongTurnException();
      // Controlla se la posizione finale è tra quelle in cui si può muovere il pezzo selezionato
      std::vector<Position> moves;
      p_from.get_moves(moves);

      auto it =
          std::find_if(moves.begin(),
                       moves.end(),
                       [&to](const Position pos)
                       {
                          return pos == to;
                       });
      if (it == moves.end())
         throw IllegalMoveException();
      // Controlla se la casa di arrivo contiene un pezzo dello stesso schieramento di quello selezionato
      try
      {
         Piece p_to = find_piece(to);
         if (p_to.side() == p_from.side())
            throw IllegalMoveException();
         // Se è un pedone e si sta muovendo in avanti non può muoversi se c'è un pezzo in to
         if (p_from.type() == PAWN && from.x == to.x)
            throw IllegalMoveException();
         // Se è il re e sta cercando di arroccare non può se c'è un pezzo nella posizione finale
         if (p_from.type() == KING && abs(from.y - to.y) == 2)
            throw IllegalMoveException();
      }
      catch (PieceNotFoundException e)
      {
         // Si arriva qua se ci si sta muovendo in una casa vuota
         // Non si fa niente perché significa che il pezzo si potrebbe muovere in questa posizione
      }

      // Simulo il movimento del pezzo e controllo se è una mossa legale (cioè se mette in scacco il mio stesso re)
      std::vector<Piece> simulated_pieces;
      simulated_pieces.reserve(_pieces.size());
      for (const Piece &p : _pieces)
      {
         if (p.position() != from && p.position() != to)
            simulated_pieces.push_back(p);
      }
      simulated_pieces.push_back(Piece{to, p_from.side(), p_from.type()});

      if (is_check(p_from.side(), simulated_pieces))
         throw IllegalMoveException();

      // Movimento pedone
      if (p_from.type() == PAWN)
      {
         if (abs(from.y - to.y) == 2) // Sto cercando di avanzare un pedone di 2
         {
            // Non puoi muovere il pedone di 2 se non è nella posizione iniziale
            if ((p_from.side() == WHITE && from.y != 1) || (p_from.side() == BLACK && from.y != 6))
               throw IllegalMoveException();
            // Controllo che la casa subito davanti al pedone sia libera (la casa di arrivo è già stata controllata)
            try
            {
               find_piece(from.move(0, p_from.side() == WHITE ? 1 : -1));
               // Ho trovato un pezzo davanti al pedone quindi non si può muovere
               throw IllegalMoveException();
            }
            catch (PieceNotFoundException e)
            {
               // La casa davanti al pedone è libera. OK
            }
         }
         else if (from.x != to.x) // Sto mangiando in obliquo
         {
            try
            {
               find_piece(to);
               // Il caso in cui il pezzo di arrivo è dello stesso schieramento è già stato gestito
            }
            catch (PieceNotFoundException e)
            {
               // Per muoversi in diagonale il pedone deve mangiare
               if (!(_last_pawn_move == to.y && from.x == (p_from.side() == WHITE ? 4 : 3)))
                  throw IllegalMoveException();
            }
            // TODO Nella simulazione non è gestito lo scacco dopo aver mangiato per en passant
            // Mangio il pezzo in en passant
            kill_piece(Position{from.x, to.y});
         }
         // La spinta di 1 del pedone è già gestita
      }
      else if (p_from.type() == KING) /* Arrocco re */
      {
         if (abs(from.y - to.y) == 2)
         {
            short castle_direction = from.y < to.y ? 1 : -1;
            // Controllo che il re non abbia ancora perso il diritto ad arroccare
            if (p_from.side() == WHITE)
            {
               if (castle_direction > 0 && !_can_white_castle_right)
                  throw IllegalMoveException();
               if (castle_direction < 0 && !_can_white_castle_left)
                  throw IllegalMoveException();
            }
            else
            {
               if (castle_direction > 0 && !_can_black_castle_right)
                  throw IllegalMoveException();
               if (castle_direction < 0 && !_can_black_castle_left)
                  throw IllegalMoveException();
            }
            // Se al momento il re è sotto scacco non può arroccare
            if (is_check(p_from.side(), _pieces))
               throw IllegalMoveException();
            // Controllo se nella posizione intermedia (tra quella di arrocco e quella attuale) c'è un pezzo (quella finale è già controllata)
            try
            {
               find_piece({from.x, from.y + castle_direction});
               // Se c'è un pezzo, questo blocca l'arrocco
               throw IllegalMoveException();
            }
            catch (PieceNotFoundException e)
            {
               // OK, niente ferma l'arrocco
            }
            // Controllo se la posizione intermedia (tra quella di arrocco e quella attuale) mette sotto scacco il re
            std::vector<Piece> simulated_pieces;
            simulated_pieces.reserve(_pieces.size());
            for (const Piece &p : _pieces)
            {
               if (p.position() != from)
                  simulated_pieces.push_back(p);
            }
            simulated_pieces.push_back(Piece{{from.x, from.y + castle_direction}, p_from.side(), p_from.type()});

            if (is_check(p_from.side(), simulated_pieces))
               throw IllegalMoveException();

            // Elimino la torre con cui il re arrocca
            kill_piece(Position{from.x, castle_direction > 0 ? 7 : 0});
            // Rimetto la torre al posto giusto
            _pieces.push_back(Piece{Position{from.x, from.y + castle_direction}, p_from.side(), ROOK});
         }

         // Tolgo al re la possibilità di arroccare in futuro visto che si sta muovendo adesso
         if (p_from.side() == WHITE)
         {
            _can_white_castle_left = false;
            _can_white_castle_right = false;
         }
         else
         {
            _can_black_castle_left = false;
            _can_black_castle_right = false;
         }
      }
      else if (p_from.type() == ROOK) /* Tolgo la possibilità di arroccare al re se sto muovendo una torre */
      {
         if (p_from.side() == WHITE)
         {
            if (from.y == 7)
               _can_white_castle_right = false;
            else if (from.y == 0)
               _can_white_castle_left = false;
         }
         else
         {
            if (from.y == 7)
               _can_black_castle_right = false;
            else if (from.y == 0)
               _can_black_castle_left = false;
         }
      }

      // TODO Promozione

      // Elimino il pezzo nella posizione iniziale e in quella finale
      kill_piece(from);
      kill_piece(to);
      // Reinserisco il pezzo nella sua nuova posizione
      _pieces.push_back(Piece{to, p_from.side(), p_from.type()});
   }
}

#endif