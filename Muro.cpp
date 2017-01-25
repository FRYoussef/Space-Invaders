#include "Muro.h"

void inicializaMuro(int x, int y, tMuro &listaL){
    listaL.cont = 0;
    insertaLadrillos(x, y, listaL);
}

void insertaLadrillos(int x, int y, tMuro &listaL){
    for(int i = 0; i < N_LADRILLOS; i++){
        int tipo;
        switch(i){
        case 0:
            tipo = 1;
            break;
        case 1:
            tipo = 0;
            break;
        case 2:
            tipo = 3;
            break;
        case 3:
            tipo = 4;
            break;
        case 4:
            tipo = 2;
        }
        LADRILLO ladrillo(x, y, MAX_VIDA_LADRILLO, 0,0, tipo);
        ladrillo.reColocaLadrillo();
        listaL.ladrillos[i] = new LADRILLO(ladrillo);
        listaL.cont++;
    }
}

void destruyeLadrillo(int pos, tMuro &listaL){
   for(int i = pos; i < listaL.cont - 1; i++){
        listaL.ladrillos[i] = listaL.ladrillos[i + 1];
    }
    delete listaL.ladrillos[listaL.cont-1];
    listaL.cont--;
}

void destruyeMuro(tMuro &listaL){
       for(int i =  0; i < listaL.cont; i++){
        delete listaL.ladrillos[i];
    }
    listaL.cont = 0;
}

void pintaMuro(tMuro &listaL, BITMAP *buffer, DATAFILE *imgMuro){
    for(int i = 0; i < listaL.cont; i++){
        if(listaL.ladrillos[i] -> dameVida() == 0)
            destruyeLadrillo(i, listaL);

        listaL.ladrillos[i] -> pinta(buffer, imgMuro);
    }
}

void impactoBalaLadrillo(tMuro &listaL, tBalas &listaB){
    int x, y;
    bool impacto;
    for(int i = 0; i < listaL.cont; i++){
        x = listaL.ladrillos[i] -> dameCoordX();
        y = listaL.ladrillos[i] -> dameCoordY();
        impacto = impactoObjeto(x, y, DIM_X_LADRILLO, DIM_Y_LADRILLO, listaB);
        if(impacto){
            if(listaL.ladrillos[i] -> dameVida() > 0){
                listaL.ladrillos[i] -> decrementaVida();
            }
        }
    }
}
