#include "composicion_funciones.h"
#include <stdlib.h>
#include "pila.h"

typedef struct composicion{
    pila_t* funciones;
}composicion_t;

typedef double (*funcion_t)(double x);

composicion_t* composicion_crear(){
    composicion_t* composicion = malloc(sizeof(composicion_t));
    if(!composicion) return NULL;

    composicion->funciones = pila_crear();
    if(!composicion->funciones){
        free(composicion);
        return NULL;
    }

    return composicion;
}

void composicion_destruir(composicion_t* composicion){
    free(composicion->funciones);
    free(composicion);
}

bool composicion_agregar_funcion(composicion_t* composicion, funcion_t funcion_nueva){
    return pila_apilar(composicion->funciones, (void*)funcion_nueva);
}

double composicion_aplicar(composicion_t* composicion, double x){
    if(pila_esta_vacia(composicion->funciones)) return x;

    funcion_t funcion_aplicar = pila_desapilar(composicion->funciones);
    double res = funcion_aplicar(x);

    return composicion_aplicar(composicion, res);
}
