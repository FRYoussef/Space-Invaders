#include "ListaBalas.h"

void inicializaListaBalas(tBalas &listaB){
    listaB.cont = 0;
}

void destruyeBala(int pos, tBalas &listaB){
    for(int i = pos; i < listaB.cont - 1; i++){
        listaB.balas[i] = listaB.balas[i + 1];
    }
    delete listaB.balas[listaB.cont-1];
	listaB.cont--;
}

void destruyeListaBalas(tBalas &listaB){
    for(int i =  0; i < listaB.cont; i++){
        delete listaB.balas[i];
    }
    listaB.cont = 0;
}

void insertaBala(tBalas &listaB, BALA bala){
    for(int i = listaB.cont - 1; i >= 0; i--){
        listaB.balas[i + 1] = listaB.balas[i];
    }
    listaB.balas[0] = new BALA(bala);
    listaB.cont++;
}

void mueveBalas(bool arriba, tBalas &listaB, BITMAP *buffer, DATAFILE *ImgBala){
    for(int i =  0; i < listaB.cont; i++){
        listaB.balas[i] -> disparaBala(arriba, buffer, ImgBala);
        if(listaB.balas[listaB.cont - 1] -> limite(arriba)){
            destruyeBala(listaB.cont-1, listaB);
        }
    }
}

/*
 * En base a unas coord y unas dimensiones determina si alguna bala de la lista
 * ha impactado con el objeto.
 */

bool impactoObjeto(int _x, int _y, int _dimX, int _dimY, tBalas &listaB){
    bool impacto = false;

    for(int i = 0; i < listaB.cont && !impacto; i++){
        impacto = listaB.balas[i]->impactoBala(_x, _y, _dimX, _dimY);
        if(impacto){
            destruyeBala(i, listaB);
        }
    }
    return impacto;
}

void colisionBalas(tBalas &listaB1, tBalas &listaB2){
    for(int i = 0; i < listaB1.cont; i++){
        int x = listaB1.balas[i]->dameCoordX();
        int y = listaB1.balas[i]->dameCoordY();
        if(impactoObjeto(x, y, DIM_X_BALA, DIM_Y_BALA, listaB2))
            destruyeBala(i, listaB1);
    }
}

