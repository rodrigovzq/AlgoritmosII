#include "lista.h"
#include "lista_struct.h"

void lista_invertir(lista_t* lista) {
    nodo_t* actual = lista->primero;
    nodo_t* anterior = NULL;
    nodo_t* siguiente = actual ? actual->prox: NULL;
    lista->ultimo = lista->primero;
    while (actual) {
        actual->prox = anterior;
        anterior = actual;
        actual = siguiente;
        siguiente = actual ? actual->prox : NULL;
    }
    lista->primero = anterior;
}
