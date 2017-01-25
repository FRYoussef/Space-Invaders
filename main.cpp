#include <allegro.h>
#include <stdlib.h>
#include <ctime>
#include "inicia.h"
#include "Nave.h"
#include "ListaEnemigos.h"
#include "ListaMuros.h"

int const NUM_ANIMACIONES_COR = 6;
int const TEMP_LATIDO = 2;
int const COL_NUMEROS = 3;
int const TEMP_COL_NUM = 10;
int const DIM_COR_X = 26;
int const DIM_COR_Y = 22;
int const DIM_NUM_X = 12;
int const DIM_NUM_Y = 20;

typedef struct {
    int animacionCor;
    int tempLatido;
    int colNum;
    int tempCol;
}tPantalla;

void motorDeImpactos(int &ptos, NAVE &nave,tEnemigos &listaE, tLMuros &listaM, BITMAP *buffer,
                     DATAFILE *imgsEnemigo);

void pintaCorazones(tPantalla &pantalla, int vidas, BITMAP *corazon, BITMAP *buffer);
bool temporizadorLatido(int &tempLatido);
void conversorNum(int num, int &x);
bool temporizadorColNumero(int &tempCol);
void pintaPuntos(int puntos, DATAFILE *numeros, BITMAP *buffer, tPantalla &pantalla);
void pintaPantalla(BITMAP *buffer, tEnemigos &listaE, NAVE &nave, DATAFILE *imgsNave,
                   DATAFILE *imgsEnemigo, BITMAP *corazon, BITMAP *fondo, tPantalla &pantalla
                   , tLMuros &listaM, DATAFILE *imgMuro, SAMPLE *disp, DATAFILE *ImgBala
                   , DATAFILE *numeros, int puntos);

int main(){
    NAVE nave (POS_X_INI, POS_Y_INI, VIDA_NAVE, 0);
	tEnemigos listaE;
	tLMuros listaM;
    bool gameOver = false;
    int puntos = 0;
    tPantalla pantalla;
    pantalla.animacionCor = 0;
    pantalla.tempLatido = 0;
    pantalla.colNum = 0;
    pantalla.tempCol = 0;

    srand(time(NULL));

    inicia_allegro(TAM_H, TAM_V);
    inicia_audio(600,600);
    BITMAP *buffer = create_bitmap(TAM_H, TAM_V);
    DATAFILE *imgsNave = load_datafile("Recursos/Nave/ImgNave.dat");
    DATAFILE *imgsEnemigo = load_datafile("Recursos/Enemigos/ImgEnemigo.dat");
    DATAFILE *imgMuro = load_datafile("Recursos/Muro/ImgMuro.dat");
    DATAFILE *ImgBala = load_datafile("Recursos/Bala/ImgBala.dat");
    DATAFILE *numeros = load_datafile("Recursos/Portada/ImgNumbers.dat");
    BITMAP *corazon = load_bitmap("Recursos/Corazon.bmp", NULL);
    BITMAP *fondo = load_bitmap("Recursos/Portada/fondo.bmp", NULL);
    BITMAP *GameOver = load_bitmap("Recursos/Portada/gameover.bmp", NULL);
    SAMPLE *musica = load_wav("Recursos/MusicaYSonidos/musica.wav");
    SAMPLE *disp = load_wav("Recursos/MusicaYSonidos/disparo.wav");

    inicializaListaEnemigos(listaE);
    incializaListaMuros(listaM);
	play_sample(musica, 100, 150, 1000, 1);
	pintaPantalla(buffer, listaE, nave, imgsNave, imgsEnemigo, corazon, fondo, pantalla,
                     listaM, imgMuro, disp, ImgBala, numeros, puntos);
	while(!gameOver){
       motorDeImpactos(puntos, nave, listaE, listaM, buffer, imgsEnemigo);
       pintaPantalla(buffer, listaE, nave, imgsNave, imgsEnemigo, corazon, fondo, pantalla,
                     listaM, imgMuro, disp, ImgBala, numeros, puntos);
       gameOver = nave.dameVidas() == 0 || key[KEY_ESC];
       rest(30);
	}
	draw_sprite(buffer, GameOver, TAM_HABIL_H - 415, TAM_HABIL_V - 300);
	blit(buffer, screen, 0,0,0,0, TAM_H, TAM_V);
	system("cls");
	destruyeListaBalas(nave.listaB);
	destruyeListaEnemigos(listaE);
	destruyeListaMuros(listaM);
	while(!key[KEY_ESC]){
        rest(40);
	}
    return 0;
}

END_OF_MAIN();


void pintaPantalla(BITMAP *buffer, tEnemigos &listaE, NAVE &nave, DATAFILE *imgsNave,
                   DATAFILE *imgsEnemigo, BITMAP *corazon, BITMAP *fondo, tPantalla &pantalla,
                   tLMuros &listaM, DATAFILE *imgMuro, SAMPLE *disp, DATAFILE *ImgBala
                   , DATAFILE *numeros, int puntos){
    clear(buffer);
    masked_blit(fondo, buffer, 0,0,0,0, 600, 600);
    int vidas = nave.dameVidas();
    pintaCorazones(pantalla, vidas, corazon, buffer);
    pintaListaMuros(listaM, buffer, imgMuro);
    mueveEnemigosYDispara(listaE, buffer, imgsEnemigo, ImgBala);
    nave.leeTecla(buffer, imgsNave, disp, ImgBala);
    pintaPuntos(puntos, numeros, buffer, pantalla);
    blit(buffer, screen, 0,0,0,0, TAM_H, TAM_V);
}

void motorDeImpactos(int &ptos, NAVE &nave, tEnemigos &listaE, tLMuros &listaM, BITMAP *buffer,
                     DATAFILE *imgsEnemigo){

    impactoBalaEnemigo(ptos, listaE, nave.listaB, buffer, imgsEnemigo);
    nave.impctoNaveBala(listaE.listaB);
    impactoBalaMuro(listaM, nave.listaB);
    impactoBalaMuro(listaM, listaE.listaB);
    colisionBalas(nave.listaB, listaE.listaB);
}

void pintaCorazones(tPantalla &pantalla, int vidas, BITMAP *corazon, BITMAP *buffer){
    if(temporizadorLatido(pantalla.tempLatido)) pantalla.animacionCor++;

    if(pantalla.animacionCor == NUM_ANIMACIONES_COR) pantalla.animacionCor = 0;

    BITMAP *cor = create_bitmap(DIM_COR_X, DIM_COR_Y);
    blit (corazon, cor, pantalla.animacionCor*DIM_COR_X, 0, 0, 0, DIM_COR_X, DIM_COR_Y);
    for(int i = 0; i < vidas; i++){
        draw_sprite(buffer, cor, (i*(DIM_COR_X + 7))+485, 45);
    }
    destroy_bitmap(cor);
}

bool temporizadorLatido(int &tempLatido){
    tempLatido++;
    if(tempLatido == TEMP_LATIDO){
        tempLatido = 0;
        return true;
    }
    return false;
}

void pintaPuntos(int puntos, DATAFILE *numeros, BITMAP *buffer, tPantalla &pantalla){
   if(temporizadorColNumero(pantalla.tempCol)) pantalla.colNum++;
   if(pantalla.colNum == COL_NUMEROS) pantalla.colNum = 0;

   bool terminado = false;
   int ptosAux = 0;
   int i = 0;
   while(!terminado){
        ptosAux = puntos % 10;
        puntos /= 10;
        int x = 0;
        conversorNum(ptosAux, x);
        if(!terminado){
            BITMAP *num = create_bitmap(DIM_NUM_X, DIM_NUM_Y);
            blit((BITMAP *)numeros[pantalla.colNum].dat, num, x, 0, 0, 0, DIM_NUM_X, DIM_NUM_Y);
            draw_sprite(buffer, num, 100 - (i*(DIM_NUM_X + 5)), 45);
            destroy_bitmap(num);
        }
        terminado = puntos == 0;
        i++;
   }
}

void conversorNum(int num, int &x){
    switch(num){
    case 1:
        x = DIM_NUM_X;
        break;
    case 2:
        x = 2*DIM_NUM_X;
        break;
    case 3:
        x = 3*DIM_NUM_X;
        break;
    case 4:
        x = 4*DIM_NUM_X;
        break;
    case 5:
        x = 5*DIM_NUM_X;
        break;
    case 6:
        x = 6*DIM_NUM_X;
        break;
    case 7:
        x = 7*DIM_NUM_X;
        break;
    case 8:
        x = 8*DIM_NUM_X;
        break;
    case 9:
        x = 9*DIM_NUM_X;
    }
}

bool temporizadorColNumero(int &tempCol){
    tempCol++;
    if(tempCol == TEMP_COL_NUM){
        tempCol = 0;
        return true;
    }
    return false;
}
