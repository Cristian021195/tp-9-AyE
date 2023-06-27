#include <stdio.h>
#include <stdlib.h>
#define INDEF -9999;


typedef int ITEM;
typedef struct ELEMENTO{
    ITEM dato;
    struct ELEMENTO * siguiente;
}ELEMENTO;

typedef struct FILA{
    struct ELEMENTO * frente;
    struct ELEMENTO * final;
    int longitud;
}FILA;


// OPERACIONES
FILA FILAVACIA(); // FILA *F
FILA ENFILA(FILA F, ITEM I);
FILA PUSHF(FILA F, ITEM I);
ITEM FRENTE(FILA F);
ITEM FONDO(FILA F);
ITEM TOP(FILA F);
FILA POP(FILA F);
FILA DEFILA(FILA *F);
FILA DEFILAX(FILA *F, ITEM I);
//int ESSIMETRICA(FILA F);
FILA INVERTIRLISTA(FILA F); // como usuario
int INCLUIDA(FILA P1, FILA P2); // como usuario
int ESFILAVACIA(FILA F);
void MOSTRAR(FILA F);
int LONGITUD(FILA F);
int PERTENECE(FILA F, ITEM I);
int IGUALF(FILA F1, FILA F2);
FILA CONCATN(FILA F1, FILA *F2, int n);
void DEFILAV(FILA *F);

int IGUALF(FILA F1, FILA F2){
    if(F1.frente != NULL && F2.frente != NULL){
        if(LONGITUD(F1) != LONGITUD(F2)){
            return 1;
        }else{
            printf("sx");
            return 0;
        }
    }else{
        printf("s");
        return 0;
    }
}

int PERTENECE(FILA F, ITEM I){

    while (F.frente != NULL){
        if(F.frente->dato == I){
            return 0;
        }
        F.frente = F.frente->siguiente;
    }
    return 1;
}

int LONGITUD(FILA F){
    int cont = 0;

    while (F.frente != NULL){
        cont ++;
        F.frente = F.frente->siguiente;
    }
    return cont;
}


// SEMANTICA
int ESFILAVACIA(FILA F){
    return F.frente == NULL;// ? 1 : 0;
}

void MOSTRAR(FILA F){
    printf("\n");
    while (F.frente != NULL)
    {
        printf("[%d]", F.frente->dato);
        F.frente = F.frente->siguiente;
    }
    
}

int INCLUIDA(FILA P1, FILA P2){
    int respuesta = 1;
    
    while (ESFILAVACIA(P2) != 1){
        if (TOP(P1) == TOP(P2)){
            P1 = POP(P1);
            P2 = POP(P2);
            respuesta = 0;
        }else{
            respuesta = 1;
            P2 = POP(P2);
        }
    }

    if(ESFILAVACIA(P1) != 1){
        return 1;
    }
    

    return respuesta;
}

FILA INVERTIRLISTA(FILA F){ // recibe una lista enlazada y, con la ayuda de una pila auxiliar, retorna la lista construida en orden inverso. 
    FILA PAUX = FILAVACIA();

    while (ESFILAVACIA(F) != 1)
    {
        PAUX = ENFILA(PAUX, TOP(F));
        F = POP(F);
    }   

    return PAUX;

}

FILA CONCATN(FILA F1, FILA *F2, int n){
    int aux = F2->longitud;
    while (n > 0){ // && n < LONGITUD(*F2)
        //printf("|| %d ||", FRENTE(*F2));
        F1 = ENFILA(F1, FRENTE(*F2));
        DEFILAV(F2);
        n --; aux --;
        if(aux == 0){
            break;
        }
    }
    return F1;
}

FILA POP(FILA F){
    ELEMENTO *AUX;
    
    AUX = F.frente;
    F.frente = F.frente->siguiente;
    free(AUX);
    return F;
}

/*int ESSIMETRICA(FILA F){
    return 1;
}*/

FILA DEFILA(FILA *F){
    ELEMENTO * AUX, *ANT;
    AUX = F->frente;
    while (AUX->siguiente != NULL){
        ANT = AUX;
        AUX = ANT->siguiente;
    }
    ANT->siguiente = NULL;
    free(AUX);
    return *F;
}

void DEFILAV(FILA *F){
    ELEMENTO * AUX;
    if(F->frente != NULL){
        AUX = F->frente;
        F->frente = F->frente->siguiente;

        AUX->siguiente = NULL;
        F->longitud = F->longitud - 1;
        free(AUX);        
    }
}

FILA DEFILAX(FILA *F, ITEM I){
    ELEMENTO * ACT, *ANT;
    FILA NF = FILAVACIA();
    ACT = F->frente;
    while (ACT != NULL) {
        //printf("\n(%d)\n", ACT->dato);
        if (ACT->dato != I) {            
            NF = ENFILA(NF, ACT->dato);
        }
        ANT = ACT;
        ACT = ANT->siguiente;
    }
    //free(F); 
    *F = NF;
    /*while (ACT != NULL) {
        if (ACT->dato == I) {
            if (ANT == NULL) {
                F->frente = ACT->siguiente;
                ANT = ACT->siguiente;
            } else {
                ANT->siguiente = ACT->siguiente;
            }
            free(ACT);
            ACT = ANT->siguiente;
        } else {
            ANT = ACT;
            ACT = ACT->siguiente;
        }
    }*/
    //free(F);

    return *F;
}

ITEM TOP(FILA F){
    return F.frente->dato;
}

ITEM FRENTE(FILA F){
    if(F.longitud > 0){
        return F.frente->dato;
    }
    return INDEF;
}
ITEM FONDO(FILA F){
    if(F.longitud > 0){
        return F.final->dato;
    }
    return INDEF;
}

FILA ENFILA(FILA F, ITEM I){
    ELEMENTO * N = (ELEMENTO *) malloc(sizeof(ELEMENTO));
    N->dato = I;
    N->siguiente = NULL;

    if(F.longitud == 0){
        F.final = N;
        F.frente = N;
        F.longitud = F.longitud + 1;
    }else{
        F.final->siguiente = N;
        F.final = N; // paso necesario, sino la fila nunca se altera
        F.longitud = F.longitud + 1;
    }
    return F;
}
FILA PUSHF(FILA F, ITEM I){
    ELEMENTO * AUX, *ANT;
    ELEMENTO * N = (ELEMENTO *) malloc(sizeof(ELEMENTO));
    N->siguiente = NULL; N->dato = I;
    AUX = F.frente;
    while (AUX->siguiente != NULL){
        ANT = AUX;
        AUX = ANT->siguiente;
    }
    //ANT->siguiente = NULL;
    AUX->siguiente = N;
    return F;
}

FILA FILAVACIA(){
    FILA F;
    F.frente = NULL;
    F.final = NULL;
    F.longitud = 0;    
    return F;
}



