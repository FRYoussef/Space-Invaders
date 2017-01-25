#ifndef NAVE_H_INCLUDED
#define NAVE_H_INCLUDED

#include <allegro.h>
#include "Personajes.h"

int const POS_X_INI = TAM_HABIL_H / 2;
int const POS_Y_INI = TAM_HABIL_V - 18;
int const VIDA_NAVE = 3;
int const DIM_X_NAVE = 30;
int const DIM_Y_NAVE = 31;
int const NUM_BALAS_NAVE = 2;
int const MAX_COL_NAVE = 6;
int const ANIMACIONES_NAVE = 3;
int const TEMP_COL_NAVE = 5;
int const TEMP_DISPARO_NAVE = 4;
int const TEMP_ANIMACION_NAVE = 5;

class NAVE : public PERSONAJE{
    int col;
    int tempCol;
    int tempDisparo;
    int animacion;
    int tempAnimacion;

    // solo si vulnerable = 1, se le resta vida a la nave
    bool vulnerable;
public:
    tBalas listaB;

	NAVE(int _x, int _y, int vida, int _col);
	void pinta(BITMAP *buffer, DATAFILE *imgsNave);
	void leeTecla(BITMAP *buffer, DATAFILE *imgsNave, SAMPLE *disp, DATAFILE *ImgBala);
	int dameCoordX() {return x; };
	int dameCoordY() { return y; };
	int dameVidas() { return vida; };
	void impctoNaveBala(tBalas &listaB);
	void temporizador();
	bool temporizadorTempDisparo();
	//void impactoNaveEnemigo();
};

#endif // NAVE_H_INCLUDED
