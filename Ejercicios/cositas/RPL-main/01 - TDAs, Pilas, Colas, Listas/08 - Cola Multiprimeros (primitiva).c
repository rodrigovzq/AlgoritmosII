#include "cola.h"
#include "cola_struct.h"

void** cola_multiprimeros(const cola_t* cola, size_t k) {
    void **primeros = calloc(k, sizeof(void*));
    if (!primeros) return NULL;
    nodo_t* actual = cola->prim;
    for (int i = 0; i<k && actual != NULL; i++) {
        primeros[i] = actual->dato;
        actual = actual->sig;
    }
    return primeros;
}
