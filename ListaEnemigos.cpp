#include <stdlib.h>
#include <ctime>
#include "ListaEnemigos.h"

/*
 * Hay que mejorar esta función
 */
void insertaEnemigos(tEnemigos &listaE){
    int x = TAM_H - TAM_HABIL_H + 1;
    int y = ( TAM_V - TAM_HABIL_V) + 1;
    int lin = N_ENEMIGOS / 11;
    int cont = 0;
    int tipo = 0;
    for(int i = 0; i < lin; i++){
        for(int j = 0; j < (N_ENEMIGOS / lin); j++){

            // el incremento de x es para tener espaciado entre los enemigos
            ENEMIGO enemigo((x + ((DIM_X_ENEM + 5) * j)), y, VIDA_ENEM, 0, true, tipo, 0, false, 0);
            listaE.enemigos[cont] = new ENEMIGO(enemigo);
            listaE.cont++;
            cont++;
        }
        if(tipo == 2) tipo = 0;

        tipo++;
        y += DIM_Y_ENEM + 5;
    }
}

void inicializaListaEnemigos(tEnemigos &listaE){
    listaE.cont = 0;
    listaE.tempDisparo = 0;
    insertaEnemigos(listaE);
    inicializaListaBalas(listaE.listaB);
}

void destruyeEnemigo(int pos, tEnemigos &listaE){
   for(int i = pos; i < listaE.cont - 1; i++){
        listaE.enemigos[i] = listaE.enemigos[i + 1];
    }
    delete listaE.enemigos[listaE.cont];
    listaE.cont--;
}

void destruyeListaEnemigos(tEnemigos &listaE){
    destruyeListaBalas(listaE.listaB);
    for(int i =  0; i < listaE.cont; i++){
        delete listaE.enemigos[i];
    }
    listaE.cont = 0;
}

void mueveEnemigosYDispara(tEnemigos &listaE, BITMAP *buffer, DATAFILE *imgsEnemigo, DATAFILE *ImgBala){
    mueveBalas(false, listaE.listaB, buffer, ImgBala);
    bool limite = limiteMarco(listaE);
    for(int i =  0; i < listaE.cont; i++){
        listaE.enemigos[i] -> mueveEnemigo(limite, buffer, imgsEnemigo);
        if(listaE.enemigos[i]->dameVida() == 0){
            destruyeEnemigo(i, listaE);
            i--;
        }
    }
    if(temporizador(listaE) && listaE.listaB.cont < E_DISP && listaE.cont > 0){
        int pos = rand() % listaE.cont;
        int x = listaE.enemigos[pos]->dameCoordX() + (DIM_X_ENEM / 2);
        int y = listaE.enemigos[pos]->dameCoordY() + DIM_Y_ENEM + 1;
        BALA bala(x, y, TIPO2, 1);
        insertaBala(listaE.listaB, bala);
    }
}

bool limiteMarco(const tEnemigos &listaE){
    for(int i =  0; i < listaE.cont; i++){
        int x = listaE.enemigos[i] -> dameCoordX();
        if((x <= TAM_H - TAM_HABIL_H) || (x + DIM_X_ENEM >= TAM_HABIL_H)){
            return true;
        }
    }
    return false;
}

void impactoBalaEnemigo(int &puntos, tEnemigos &listaE, tBalas &listaB, BITMAP *buffer, DATAFILE *imgsEnemigo){
    int x, y;
    bool impacto = false;
    for(int i =  0; i < listaE.cont; i++){
        x = listaE.enemigos[i]->dameCoordX();
        y = listaE.enemigos[i]->dameCoordY();
        impacto = impactoObjeto(x, y, DIM_X_ENEM, DIM_Y_ENEM, listaB);
        if(impacto){
            int damage = listaB.balas[0]->dameDamage();
            listaE.enemigos[i]->setVida(damage);
            if(listaE.enemigos[i]->dameVida() == 0){
                listaE.enemigos[i] ->setExplo(true);

                switch(listaE.enemigos[i] -> dameTipo()){
                    case 0:
                        puntos += DIEZ_PTOS;
                        break;
                    case 1:
                        puntos += QUINCE_PTOS;
                        break;
                    case 2:
                        puntos += VEINTE_PTOS;
                }
            }
        }
    }
}

bool temporizador(tEnemigos &listaE){
    listaE.tempDisparo++;
    if(listaE.tempDisparo == TEMP_DISPARO_ENE){
        listaE.tempDisparo = 0;
        return true;
    }
    return false;
}

