#include "cola.h"
#include "cola_filtrar.h"
#include <stdlib.h>

void cola_filtrar(cola_t* cola, bool (*filtro)(void*)){
    cola_t* cola_aux = cola_crear();
    void* puntero_aux;
    while(!cola_esta_vacia(cola)){
        puntero_aux = cola_desencolar(cola);
        if(filtro(puntero_aux)){
            cola_encolar(cola_aux, puntero_aux);
        }
    }
    while(!cola_esta_vacia(cola_aux)){
        cola_encolar(cola, cola_desencolar(cola_aux));
    }
    cola_destruir(cola_aux, NULL);
}
