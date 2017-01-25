#ifndef ENEMIGO_H_INCLUDED
#define ENEMIGO_H_INCLUDED

#include <allegro.h>
#include "Personajes.h"

int const TEMP_MOV_ENE = 22;
int const DIM_X_ENEM = 25;
int const DIM_Y_ENEM = 20;
int const DIM_X_EXP_ENE = 26;
int const DIM_Y_EXP_ENE = 16;
int const VIDA_ENEM = 1;
int const MAX_COL_ENE = 6;
int const TEMP_COL_ENE = 6;
int const TEMP_ANIMACION_ENE = 6;

class ENEMIGO : public PERSONAJE{
    int tempCol;
    int col;
    int iteracion;
    bool dir;
    int tipo;
    bool animacion;
    int tempAnimacion;
    bool explo;
public:
    ENEMIGO(int x, int y, int vida, int _iteracion, bool _dir, int _tipo, int _col, bool _animacion, int _tempAnimacion);
    void pinta(BITMAP *buffer, DATAFILE *imgsEnemigo, int x1, int y1)const;
    void mueveEnemigo(bool cambiaDir, BITMAP *buffer, DATAFILE *imgsEnemigo);
    int dameCoordX() { return x;};
    int dameCoordY(){return y;};
    int dameTipo(){ return tipo;};
    void posicionaBitmap(int &x1, int &y1);
    bool temporizador();
    void setExplo(bool _explo){explo = _explo;};
    void setVida(int _vida){ vida -= _vida;}
    int dameVida(){return vida;}
};

typedef ENEMIGO *tEnemigoPtr;

#endif // ENEMIGO_H_INCLUDED
