#ifndef BALA_H_INCLUDED
#define BALA_H_INCLUDED

#include <allegro.h>

char const DISPARO = 194;
int const TIEMPO_BALA = 1;
int const DIM_X_BALA = 6;
int const DIM_Y_BALA = 12;
int const LIM_TABLERO_V1 = 500;
int const LIM_TABLERO_H1 = 520;
int const TAM_V1 = 600;
int const TAM_H1 = 600;
int const TIPO1 = 0;
int const TIPO2 = 1;
int const TIPO3 = 2;

class BALA{
   int x, y;
   int iteracion;
   int tipo;
   int damage;
public:
   BALA (int _x, int _y, int _tipo, int _damage) : x(_x), y(_y),
            tipo(_tipo), damage(_damage){iteracion = 0;}
   void pinta(BITMAP *buffer, DATAFILE *ImgBala) const;
   void disparaBala(bool arriba, BITMAP *buffer, DATAFILE *ImgBala);
   bool impactoBala(int _x, int _y, int dimX, int dimY);
   bool limite(bool arriba);
   bool temporizador();
   int dameCoordX()const {return x;}
   int dameCoordY()const {return y;}
   int dameDamage()const{return damage;}
   int dameTipo()const {return tipo;}
};

typedef BALA *tBALAptr;

#endif // BALA_H_INCLUDED
