#ifndef LISTAMUROS_H_INCLUDED
#define LISTAMUROS_H_INCLUDED

#include "Muro.h"

int const N_MUROS = 5;

typedef tMuroPtr tArrayM[N_MUROS];

typedef struct{
    int cont;
    tArrayM muros;
}tLMuros;

void incializaListaMuros(tLMuros &listaM);
void destruyeListaMuros(tLMuros &listaM);
void insertaMuros(tLMuros &listaM);
void pintaListaMuros(tLMuros &listaM, BITMAP *buffer, DATAFILE *imgMuro);
void impactoBalaMuro(tLMuros &listaM, tBalas &listaB);
void destruyeUnMuro(int pos, tLMuros &listaM);

#endif // LISTAMUROS_H_INCLUDED
