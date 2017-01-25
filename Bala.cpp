#include "Bala.h"

void BALA::pinta(BITMAP *buffer, DATAFILE *ImgBala) const{

    BITMAP *bala = create_bitmap(DIM_X_BALA, DIM_Y_BALA);
    int tipo = dameTipo();
    blit((BITMAP *)ImgBala[tipo].dat, bala, 0, 0, 0, 0, DIM_X_BALA, DIM_Y_BALA);
    draw_sprite(buffer, bala, x, y + DIM_Y_BALA);
    destroy_bitmap(bala);
}

void BALA::disparaBala(bool arriba, BITMAP *buffer, DATAFILE *ImgBala){
   if(arriba && !limite(arriba) && temporizador()){
      y -= DIM_Y_BALA;
   }else if (!arriba && !limite(arriba) && temporizador()){
      y += DIM_Y_BALA;
   }
   pinta(buffer, ImgBala);
}

/*
 * Se pasan como parametros las coord del objeto, y las dimensiones de este,
 * ej: cuanto hacia la derecha se extiende el objeto.
 * Devuelve si ha impactado con el objeto
 */

bool BALA::impactoBala(int _x, int _y, int _dimX, int _dimY){
    return (_x <= x + DIM_X_BALA) && (x <= _x + _dimX) && (_y <= y + DIM_Y_BALA) && (y <= _y + _dimY);
}

bool BALA::limite(bool arriba){
    bool alcanzado = true;
    if(arriba){
        if(y > TAM_V1 - LIM_TABLERO_V1 + DIM_Y_BALA) alcanzado = false;
    }else {
        if(y < LIM_TABLERO_V1 + DIM_Y_BALA) alcanzado = false;
    }
    return alcanzado;
}

bool BALA::temporizador(){
    iteracion++;
    if(iteracion == TIEMPO_BALA){
        iteracion = 0;
        return true;
    }
    return false;
}
