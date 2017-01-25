#include "ListaMuros.h"

void incializaListaMuros(tLMuros &listaM){
    listaM.cont = 0;
    insertaMuros(listaM);
}

void destruyeListaMuros(tLMuros &listaM){
    for(int i = 0; i < listaM.cont; i++){
        destruyeMuro(*listaM.muros[i]);
    }
    listaM.cont = 0;
}

void insertaMuros(tLMuros &listaM){
    int x = (TAM_H - TAM_HABIL_H) - 8;
    int y = TAM_HABIL_V - 50;
    int incremetoX = DIM_X_LADRILLO * 3 + 35;
    for(int i = 0; i < N_MUROS; i++){
        tMuro muro;
        inicializaMuro((x + (incremetoX * i)), y, muro);
        listaM.muros[i] = new tMuro(muro);
        listaM.cont++;
    }
}

void pintaListaMuros(tLMuros &listaM, BITMAP *buffer, DATAFILE *imgMuro){
    for(int i = 0; i < listaM.cont; i++){
        if(listaM.muros[i] -> cont == 0)
            destruyeUnMuro(i, listaM);

        pintaMuro(*listaM.muros[i], buffer, imgMuro);
    }
}

void impactoBalaMuro(tLMuros &listaM, tBalas &listaB){
    for(int i = 0; i < listaM.cont; i++){
        impactoBalaLadrillo(*listaM.muros[i], listaB);
    }
}

void destruyeUnMuro(int pos, tLMuros &listaM){
   for(int i = pos; i < listaM.cont - 1; i++){
        *listaM.muros[i] = *listaM.muros[i + 1];
    }
    delete listaM.muros[listaM.cont-1];
    listaM.cont--;
}
