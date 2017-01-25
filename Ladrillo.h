#ifndef LADRILLO_H_INCLUDED
#define LADRILLO_H_INCLUDED

#include <allegro.h>
#include "Personajes.h"

int const DIM_X_LADRILLO = 20;
int const DIM_Y_LADRILLO = 16;
int const TEMP_COL_LADRILLO = 7;
int const MAX_COL_LADRILLO = 6;

class LADRILLO : public PERSONAJE{
    int tempCol;
    int col;
    int tipo;
public:
    LADRILLO(int x , int y, int vida, int _tempCol, int _col, int _tipo) :
        PERSONAJE(x, y, vida), tempCol(_tempCol), col (_col), tipo(_tipo){}
    void pinta(BITMAP *buffer, DATAFILE *imgMuro);
    int dameCoordX() {return x; };
    int dameCoordY() {return y; };
    int dameVida() { return vida; };
    void decrementaVida() { vida--; };
    void temporizadorCol();
    void reColocaLadrillo();
};

typedef LADRILLO *tLadrilloPtr;

#endif // LADRILLO_H_INCLUDED
