#include <stdio.h>
#include <math.h>
#include "./headers/fila.h"

FILA RADIX_SORT_MSD(FILA F, int N, int D);

int main(){
    FILA NUMEROS, RESULTADOS;
    NUMEROS = FILAVACIA(); RESULTADOS = FILAVACIA();

    NUMEROS = ENFILA(NUMEROS, 342); /*FTE*/
    NUMEROS = ENFILA(NUMEROS, 123);    NUMEROS = ENFILA(NUMEROS, 30);
    NUMEROS = ENFILA(NUMEROS, 410);    NUMEROS = ENFILA(NUMEROS, 34);
    NUMEROS = ENFILA(NUMEROS, 242);    NUMEROS = ENFILA(NUMEROS, 341);
    NUMEROS = ENFILA(NUMEROS, 42);    NUMEROS = ENFILA(NUMEROS, 111); NUMEROS = ENFILA(NUMEROS, 11);
    NUMEROS = ENFILA(NUMEROS, 314); /*FIN*/

    RESULTADOS = RADIX_SORT_MSD(NUMEROS, 11, 3);
    MOSTRAR(RESULTADOS);
    return 0;
}

FILA RADIX_SORT_MSD(FILA F, int N, int D){
    FILA F_ARR[11];
    int CURR_F_LENGTH = F.longitud;

    if (ESFILAVACIA(F) || CURR_F_LENGTH==1){
        return F;
    }
    for (int i = 0; i < N; i++){
        F_ARR[i] = FILAVACIA();
    }

    for(int i = 0; i < N; i++){
        int index = ((int)(FRENTE(F) / pow(10, D-1)) % 10);
        F_ARR[index] = ENFILA(F_ARR[index], FRENTE(F));
        DEFILAV(&F);
    }

    for (int i = 0; i < N; i++){
        if (!ESFILAVACIA(F_ARR[i]) && F_ARR[i].longitud > 1 && D != 0){
            F_ARR[i] = RADIX_SORT_MSD(F_ARR[i], N, D - 1);
        }
    }

    for (int i = 0; i < N; i++){
        F = CONCATN(F, &F_ARR[i], F_ARR[i].longitud);
    }
    return F;
}