#ifndef LISTAENEMIGOS_H_INCLUDED
#define LISTAENEMIGOS_H_INCLUDED

#include <allegro.h>
#include "Enemigo.h"

int const N_ENEMIGOS = 44;
int const E_DISP = 2;
int const DIEZ_PTOS = 10;
int const QUINCE_PTOS = 15;
int const VEINTE_PTOS = 20;
int const TEMP_DISPARO_ENE = 4;

typedef tEnemigoPtr tArrayEnemigo[N_ENEMIGOS];

typedef struct {
    int cont;
    tArrayEnemigo enemigos;
    tBalas listaB;
    int tempDisparo;
}tEnemigos;

void inicializaListaEnemigos(tEnemigos &listaE);
void destruyeEnemigo(int pos, tEnemigos &listaE);
void destruyeListaEnemigos(tEnemigos &listaE);
void insertaEnemigos(tEnemigos &listaE);
void mueveEnemigosYDispara(tEnemigos &listaE, BITMAP *buffer, DATAFILE *imgsEnemigo, DATAFILE *ImgBala);
bool limiteMarco(const tEnemigos &listaE);
void impactoBalaEnemigo(int &puntos, tEnemigos &listaE, tBalas &listaB, BITMAP *buffer, DATAFILE *imgsEnemigo);
bool temporizador(tEnemigos &listaE);

#endif // LISTAENEMIGOS_H_INCLUDED
