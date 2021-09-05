#include "pila.h"

/* viborita */

void ordenar_pila(pila_t* pila) {
    pila_t *pilaTemp = pila_crear();


    while (!pila_esta_vacia(pila)) {
        int *temp = pila_desapilar(pila);
        
        while (!pila_esta_vacia(pilaTemp) && *(int *)pila_ver_tope(pilaTemp) < *temp) 
            pila_apilar(pila, pila_desapilar(pilaTemp));
        pila_apilar(pilaTemp, temp);
    }

    while(!pila_esta_vacia(pilaTemp))
        pila_apilar(pila, pila_desapilar(pilaTemp));

    pila_destruir(pilaTemp);
}
