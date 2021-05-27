#include "lista.h"
/*******************************************************************
 *               		     TP Lista                              *
 *		 Facultad de Ingenieria de la Universidad de Buenos Aires  *
 *												Vazquez, Rodrigo   *
 ******************************************************************/
#include <stdlib.h>
#include <stdbool.h>
/* *****************************************************************
 *                         TDA LISTA
 * *****************************************************************/
struct lista
{
    nodo_t *primero;
    nodo_t *ultimo;
    size_t largo;
};
struct nodo
{
    void *dato;
    struct nodo *prox;
};

/* *****************************************************************
 *                       TDA ITERADOR EXTERNO
 * *****************************************************************/

struct lista_iter
{
    lista_t *lista;
    nodo_t *actual;
    nodo_t *anterior;
};

/* *****************************************************************
 *                    PRIMITIVAS LISTA
 * *****************************************************************/

lista_t *lista_crear(void)
{
    lista_t *lista = malloc(sizeof(lista_t));

    if (lista == NULL)
        return NULL;

    lista->primero = NULL;
    lista->ultimo = NULL;
    lista->largo = 0;
    return lista;
}

bool lista_esta_vacia(const lista_t *lista)
{
    return lista_largo(lista) == 0;
}

bool lista_insertar_primero(lista_t *lista, void *dato)
{
    nodo_t *nuevo_primero = nodo_crear(dato);
    if (nuevo_primero == NULL)
        return false;
    if (lista_esta_vacia(lista))
    {
        lista->ultimo = nuevo_primero;
    }
    else
    {
        nodo_enlazar(nuevo_primero, lista->primero);
    }
    lista->primero = nuevo_primero;
    lista->largo++;
    return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato)
{
    nodo_t *nuevo_ultimo = nodo_crear(dato);
    if (nuevo_ultimo == NULL)
        return false;
    if (lista_esta_vacia(lista))
    {
        lista->primero = nuevo_ultimo;
    }
    else
    {
        nodo_enlazar(lista->ultimo, nuevo_ultimo);
    }
    lista->ultimo = nuevo_ultimo;
    lista->largo++;
    return true;
}

void *lista_borrar_primero(lista_t *lista)
{
    if (lista_esta_vacia(lista))
        return NULL;
    nodo_t *nuevo_primero = nodo_proximo(lista->primero);
    void *dato = lista->primero->dato;
    nodo_destruir(lista->primero);
    lista->primero = nuevo_primero;
    if (lista_esta_vacia(lista))
        lista->ultimo = NULL;
    lista->largo--;
    return dato;
}

void *lista_ver_primero(const lista_t *lista)
{
    return (!lista_esta_vacia(lista)) ? lista->primero->dato : NULL;
}

void *lista_ver_ultimo(const lista_t *lista)
{
    return (!lista_esta_vacia(lista)) ? lista->ultimo->dato : NULL;
}

size_t lista_largo(const lista_t *lista)
{
    return lista->largo;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *))
{
    while (!lista_esta_vacia(lista))
    {
        void *dato = lista_ver_primero(lista);
        if (destruir_dato)
            destruir_dato(dato);
        lista_borrar_primero(lista);
    }
    free(lista);
}

/* *****************************************************************
 *                  PRIMITIVAS ITERADOR EXTERNO
 * *****************************************************************/

lista_iter_t *lista_iter_crear(lista_t *lista)
{

    lista_iter_t *iterador = malloc(sizeof(lista_iter_t));

    if (iterador == NULL)
        return NULL;

    iterador->lista = lista;
    iterador->actual = lista->primero;
    iterador->anterior = NULL;
    return iterador;
}

bool lista_iter_avanzar(lista_iter_t *iter)
{
    if (lista_iter_al_final(iter))
        return false;
    nodo_t *nuevo_actual = nodo_proximo(iter->actual);
    iter->anterior = iter->actual;
    iter->actual = nuevo_actual;

    return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter)
{
    return (!lista_esta_vacia(iter->lista)) ? iter->actual->dato : NULL;
}

bool lista_iter_al_final(const lista_iter_t *iter)
{
    return iter->actual == NULL;
}

void lista_iter_destruir(lista_iter_t *iter)
{
    free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato)
{
    if (iter->anterior == NULL) //iterador al principio
    {

        lista_insertar_primero(iter->lista, dato);
        iter->actual = iter->lista->primero;
    }
    else if (iter->actual == NULL) // iterador al final
    {
        iter->anterior = iter->lista->ultimo;
        lista_insertar_ultimo(iter->lista, dato);
        iter->actual = iter->lista->ultimo;
    }
    else
    {
        nodo_t *nuevo_nodo = nodo_crear(dato);
        if (nuevo_nodo == NULL)
            return false;

        nodo_enlazar(iter->anterior, nuevo_nodo);
        nodo_enlazar(nuevo_nodo, iter->actual);
        iter->actual = nuevo_nodo;
        iter->lista->largo++;
    }

    return true;
}

void *lista_iter_borrar(lista_iter_t *iter)
{

    if (lista_esta_vacia(iter->lista))
        return NULL;

    nodo_t *supr = iter->actual;

    if (lista_largo(iter->lista) == 1)
    {

        iter->lista->primero = NULL;
        iter->lista->ultimo = NULL;
    }
    else if (iter->anterior == NULL) // iterador al principio y el actual no es null
    {
        iter->lista->primero = nodo_proximo(supr);
    }
    else
    {
        nodo_enlazar(iter->anterior, nodo_proximo(supr));
    }
    void *dato = supr->dato;
    iter->actual = nodo_proximo(iter->actual);
    nodo_destruir(supr);
    iter->lista->largo--;
    if (lista_iter_al_final(iter))
        iter->lista->ultimo = iter->anterior;
    return dato;
}

/* *****************************************************************
 *                 PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra)
{

    nodo_t *item = lista->primero;
    bool sigue = true;

    while (!nodo_al_final(item) && sigue)
    {
        sigue = visitar(item->dato, extra);
        item = nodo_proximo(item);
    }
}
/* *****************************************************************
 *                    Funciones NODO
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


nodo_t *nodo_proximo(nodo_t *nodo)
{

    return (nodo != NULL) ? nodo->prox : NULL;
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
