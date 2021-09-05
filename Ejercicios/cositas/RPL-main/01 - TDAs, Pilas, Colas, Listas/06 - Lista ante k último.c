#include "lista.h"
#include "lista_struct.h"

/* viborita */

void* lista_ante_k_ultimo(lista_t* lista, size_t k) {
    nodo_t *p1 = lista->primero;
    nodo_t *p2 = lista->primero;

    for (size_t i = 0; i < k; i++)
        p1 = p1->prox;

    while (p1) {
        p1 = p1->prox;
        p2 = p2->prox;
    }

    return p2->dato;
}
