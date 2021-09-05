#include "cola.h"
#include "cola_multi.h"
#include <stdlib.h>

void** cola_multiprimeros(cola_t* cola, size_t k) {
    void** arr = calloc(k, sizeof(void*));
    if (!arr) return NULL;

    cola_t* aux = cola_crear();
    if (!aux){
        free(arr);
        return NULL;
    }
    int contador = 0;

    while (!cola_esta_vacia(cola)){
        if (contador < k){
            arr[contador] = cola_ver_primero(cola);
        }
    
        cola_encolar(aux, cola_desencolar(cola));  
        contador++;          
    }
    
    while (!cola_esta_vacia(aux)){
        cola_encolar(cola, cola_desencolar(aux));
    }
    return arr;
}
