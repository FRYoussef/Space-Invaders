#ifndef PERSONAJES_H_INCLUDED
#define PERSONAJES_H_INCLUDED

#include "ListaBalas.h"

int const TAM_H = 600;
int const TAM_V = 600;
int const TAM_HABIL_H = 520;
int const TAM_HABIL_V = 500;

/*
 * Es una clase abstracta de la que derivará el resto
 */

class PERSONAJE{
protected:
	int x, y, vida;
public:
	PERSONAJE(int _x, int _y, int _vida) : x(_x), y(_y), vida(_vida){}
	virtual int dameCoordX() = 0;
	virtual int dameCoordY() = 0;
};

#endif // PERSONAJES_H_INCLUDED
