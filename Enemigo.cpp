#include "Enemigo.h"

ENEMIGO::ENEMIGO(int x, int y, int vida, int _iteracion, bool _dir, int _tipo, int _col, bool _animacion, int _tempAnimacion)
    : PERSONAJE(x, y, vida)
{
    iteracion = _iteracion;
    dir = _dir;
    tipo = _tipo;
    col = _col;
    animacion = _animacion;
    tempAnimacion = _tempAnimacion;
    tempCol = 0;
    explo = false;
}

void ENEMIGO::pinta(BITMAP *buffer, DATAFILE *imgsEnemigo, int x1, int y1)const{
    int imagen = 2 * col;
    int dimX = DIM_X_ENEM;
    int dimY = DIM_Y_ENEM;
    if(explo){
     imagen = 2 * col + 1;
     dimX = DIM_X_EXP_ENE;
     dimY = DIM_Y_EXP_ENE;
    }

    BITMAP *enemigo = create_bitmap(dimX, dimY);
    blit((BITMAP *) imgsEnemigo[imagen].dat, enemigo, x1, y1, 0, 0, dimX, dimY);
    draw_sprite(buffer, enemigo, x, y + dimY);
    destroy_bitmap(enemigo);
}

void ENEMIGO::mueveEnemigo(bool cambiaDir, BITMAP *buffer, DATAFILE *imgsEnemigo){
   if(temporizador()){

        // si ha alcanzado los lim del marco cambia el sentido y baja una linea
        if(cambiaDir){
            dir = !dir;
            y += DIM_Y_ENEM;
        }
        if(dir){
            x += DIM_X_ENEM;
        } else {
            x -= DIM_X_ENEM;
        }
    }
    int x1, y1;
    posicionaBitmap(x1, y1);
    pinta(buffer, imgsEnemigo, x1, y1);
}

bool ENEMIGO::temporizador(){
    iteracion++;
    tempCol++;
    tempAnimacion++;
    if(tempAnimacion == TEMP_ANIMACION_ENE){
        tempAnimacion = 0;
        animacion = !animacion;
    }
    if(tempCol == TEMP_COL_ENE){
        tempCol = 0;
        col++;
        if(col == MAX_COL_ENE){
            col = 0;
        }
    }
    if(iteracion == TEMP_MOV_ENE){
        iteracion = 0;
        return true;
    }
    return false;
}

void ENEMIGO::posicionaBitmap(int &x1, int &y1){
    if(!explo){
        if(!animacion){
            x1 = 0;
        } else {
            x1 = DIM_X_ENEM;
        }
        if(tipo == 0){
            y1 = 0;
        } else if(tipo == 2){
            y1 = 2*DIM_Y_ENEM;
        } else {
            y1 = DIM_Y_ENEM;
        }
    } else {
        x1 = 0;
        y1 = 0;
    }
}
