#ifndef POSITION_H
#define POSITION_H

#include <string>

namespace Chess
{
   struct Position
   {
   private:
      short _x, _y;

   private:
      // Controlla se l'oggetto è valido (x e y compresi tra 0 e 7)
      bool is_valid(void) const;
      // Converte la notazione aritmetica (A1, B7, H6, ...) e inizializza le variabili private
      //    alle coordinate corrette ({0, 0}, {1, 6}, {7, 5}, ...)
      // Lancia una 'InvalidPositionException' se la posizione inserita non è valida
      void decode_arithmetic_notation(const std::string &arithmetic_notation);

   public:
      // Costruttore privato (serve solo per il metodo move, interno alla classe)
      // Inizializza l'oggetto controllando la validità delle coordinate
      Position(const short x, const short y);
      // Inizializza l'oggetto tramite il metodo privato 'decode_arithmetic_notation'
      Position(const std::string arithmetic_notation);
      // Inizializza l'oggetto tramite il metodo privato 'decode_arithmetic_notation'
      // Passo un 'const char *' per avere una conversione implicita che con una stringa non avrei
      Position(const char *arithmetic_notation);

      // Eccezione che indica che la posizione non è valida
      class InvalidPositionException;

      // Ritorna una nuova posizione data dall'incremento di quella corrente
      //    con le coordinate passate per parametro
      Position move(const short x_increment, const short y_increment) const;

      // Operatore di uguaglianza
      bool operator==(const Position &other);
      // Operatore di disuguaglianza
      bool operator!=(const Position &other);
   };
}

#endif