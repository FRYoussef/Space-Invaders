#ifndef MURO_H_INCLUDED
#define MURO_H_INCLUDED

#include "Ladrillo.h"

int const N_LADRILLOS = 5;
int const MAX_VIDA_LADRILLO = 3;

typedef tLadrilloPtr tArrayL[N_LADRILLOS];

typedef struct{
    int cont;
    tArrayL ladrillos;
}tMuro;

void inicializaMuro(int x, int y, tMuro &listaL);
void insertaLadrillos(int x, int y, tMuro &listaL);
void destruyeLadrillo(int pos, tMuro &listaL);
void destruyeMuro(tMuro &listaL);
void pintaMuro(tMuro &listaL, BITMAP *buffer, DATAFILE *imgMuro);
void impactoBalaLadrillo(tMuro &listaL, tBalas &listaB);

typedef tMuro *tMuroPtr;

#endif // MURO_H_INCLUDED
