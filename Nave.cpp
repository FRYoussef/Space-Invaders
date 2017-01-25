#include "Nave.h"

 NAVE::NAVE(int _x, int _y, int vida, int _col): PERSONAJE (_x, _y, vida){
    col = _col;
    tempCol = 0;
    tempDisparo = 0;
    vulnerable = true;
    animacion = 0;
    tempAnimacion = 0;
    inicializaListaBalas(listaB);
}

void NAVE::pinta(BITMAP *buffer, DATAFILE *imgsNave){
    int x1 = 0;

    temporizador();
    if(animacion == 1) x1 = DIM_X_NAVE;
    else if (animacion == 2) x1 = 2 * DIM_X_NAVE;
    else if (animacion == 3) x1 = 3 * DIM_X_NAVE;

	BITMAP *nave = create_bitmap(DIM_X_NAVE, DIM_Y_NAVE);
    blit((BITMAP *) imgsNave[col].dat, nave, x1, 0, 0, 0, DIM_X_NAVE, DIM_Y_NAVE);
    draw_sprite(buffer, nave, x, y + DIM_Y_NAVE);
    destroy_bitmap(nave);
}

void NAVE::leeTecla(BITMAP *buffer, DATAFILE *imgsNave, SAMPLE *disp, DATAFILE *ImgBala){
    if(vulnerable){
        if(key[KEY_A] && (x >= TAM_H - TAM_HABIL_H)){
            x -= 10;
        } else if(key[KEY_D] && (x + DIM_X_NAVE <= TAM_HABIL_H)){
            x += 10;
        } if(temporizadorTempDisparo() && key[KEY_SPACE] && listaB.cont < NUM_BALAS_NAVE){
            tempDisparo = 0;
            play_sample(disp, 100, 150, 1000, 0);
            BALA bala(x + (DIM_X_NAVE / 2) - 1, y + DIM_Y_NAVE + 1, TIPO1, 1);
            insertaBala(listaB, bala);
        }
    }
    pinta(buffer, imgsNave);
    mueveBalas(true, listaB, buffer, ImgBala);
}

void NAVE::impctoNaveBala(tBalas &listaB){
    if(vulnerable && impactoObjeto(x, y, DIM_X_NAVE, DIM_Y_NAVE, listaB)){
        vida--;
        vulnerable = false;
    }
}

void NAVE::temporizador(){
    tempCol++;
    if(tempCol == TEMP_COL_NAVE){
        tempCol = 0;
        col++;
        if(col == MAX_COL_NAVE){
            col = 0;
        }
    }
    if(!vulnerable){
    tempAnimacion++;
        if(tempAnimacion == TEMP_ANIMACION_NAVE){
            tempAnimacion = 0;
            animacion++;
            if(animacion == ANIMACIONES_NAVE){
                animacion = 0;
                x = POS_X_INI;
                y = POS_Y_INI;
                vulnerable = true;
            }
        }
    }
}

bool NAVE::temporizadorTempDisparo(){
    if(tempDisparo < TEMP_DISPARO_NAVE) tempDisparo++;

    if(tempDisparo == TEMP_DISPARO_NAVE) return true;

    return false;
}
