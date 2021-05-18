#include "nodo.h"
#include <stdlib.h>
/* *****************************************************************
 *                        TDA NODO
 * *****************************************************************/
struct nodo
{
    void *dato;
    struct nodo *prox;
};
/* *****************************************************************
 *                    PRIMITIVAS NODO
 * *****************************************************************/

nodo_t *nodo_crear(void *dato)
{
    nodo_t *nodo = malloc(sizeof(nodo_t));

    if (nodo == NULL)
        return NULL;

    nodo->dato = dato;
    nodo->prox = NULL;
    return nodo;
}

void nodo_destruir(nodo_t *nodo)
{
    free(nodo);
}

void *nodo_ver_dato(nodo_t *nodo)
{
    return (nodo != NULL) ? nodo->dato : NULL;
}

nodo_t *nodo_proximo(nodo_t *nodo)
{
    return nodo->prox;
}

bool nodo_enlazar(nodo_t *nodo_anterior, nodo_t *nodo_siguiente)
{
    if (nodo_anterior == NULL)
        return false;
    nodo_anterior->prox = nodo_siguiente;
    return true;
}

bool nodo_al_final(nodo_t *nodo)
{
    return nodo == NULL;
}
