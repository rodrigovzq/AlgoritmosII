#include <stddef.h> 
#include "invertir_arreglo.h"
#include "pila.h"
#include <stdlib.h>


void invertir_arreglo(void** arreglo, size_t n) {
    pila_t* pila = pila_crear();

    for(int i = 0; i < n; i++){
        pila_apilar(pila, arreglo[i]);
    }

    for(int i = 0; i < n; i++){
        arreglo[i] = pila_desapilar(pila);
    }

}
