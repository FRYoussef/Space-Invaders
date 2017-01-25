#include "Ladrillo.h"

void LADRILLO::pinta(BITMAP *buffer, DATAFILE *imgMuro){
    int x1 = 0;
    int y1 = 0;

    if(vida == 2) x1 = DIM_X_LADRILLO;
    else if(vida == 1) x1 = 2 * DIM_X_LADRILLO;

    if(tipo == 1) y1 = DIM_Y_LADRILLO;
    else if(tipo == 2) y1 = 2 * DIM_Y_LADRILLO;
    else if(tipo == 3) y1 = 3 * DIM_Y_LADRILLO;
    else if(tipo == 4) y1 = 4 * DIM_Y_LADRILLO;

    temporizadorCol();
    BITMAP *ladrillo = create_bitmap(DIM_X_LADRILLO, DIM_Y_LADRILLO);
    blit((BITMAP *)imgMuro[col].dat, ladrillo, x1, y1, 0,0, DIM_X_LADRILLO, DIM_Y_LADRILLO);
    draw_sprite(buffer, ladrillo, x, y + DIM_Y_LADRILLO);
    destroy_bitmap(ladrillo);
}

void LADRILLO::temporizadorCol(){
    tempCol++;
    if(tempCol == TEMP_COL_LADRILLO){
        tempCol = 0;
        col++;
        if(col == MAX_COL_LADRILLO) col = 0;
    }
}

void LADRILLO::reColocaLadrillo(){
    if(tipo == 0){
        y -= DIM_Y_LADRILLO;
    } else if(tipo == 3){
        x += 2 * DIM_X_LADRILLO;
    } else if(tipo == 4){
        x += DIM_X_LADRILLO;
        y -= DIM_Y_LADRILLO;
    } else if(tipo == 2){
        x += 2 * DIM_X_LADRILLO;
        y -= DIM_Y_LADRILLO;
    }
}
