#include "cola.h"
/*******************************************************************
 *               		     TP Cola                               *
 *		 Facultad de Ingenieria de la Universidad de Buenos Aires  *
 *												Vazquez, Rodrigo   *
 ******************************************************************/

#include <stdlib.h>

typedef struct nodo
{
    void *dato;
    struct nodo *sig;
} nodo_t;

struct cola
{
    nodo_t *primero;
    nodo_t *ultimo;
};

cola_t *cola_crear(void) //LISTO
{
    cola_t *cola = malloc(sizeof(cola_t));
    if (cola == NULL)
        return NULL;
    cola->primero = NULL;
    cola->ultimo = NULL;
    return cola;
}

void cola_destruir(cola_t *cola, void (*destruir_dato)(void *))
{
    while (cola->primero)
    {
        void *dato = cola_desencolar(cola);
        if (destruir_dato)
        {
            destruir_dato(dato);
        }
    }
    free(cola);
}

bool cola_esta_vacia(const cola_t *cola) //LISTO
{
    return !cola->primero;
}

bool cola_encolar(cola_t *cola, void *valor) //LISTO
{
    nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
    if (nuevo_nodo == NULL)
        return false;
    nuevo_nodo->sig = NULL;
    nuevo_nodo->dato = valor;
    if (cola_esta_vacia(cola))
    {
        cola->primero = nuevo_nodo;
    }
    else
    {
        cola->ultimo->sig = nuevo_nodo;
    }
    cola->ultimo = nuevo_nodo;
    return true;
}

void *cola_ver_primero(const cola_t *cola) //LISTO
{
    if (cola_esta_vacia(cola))
        return NULL;
    return cola->primero->dato;
}

void *cola_desencolar(cola_t *cola)
{
    if (cola_esta_vacia(cola))
        return NULL;
    void *dato = cola->primero->dato; //rescata dato a devolver
    nodo_t *nuevo_primero = cola->primero->sig;
    free(cola->primero);
    cola->primero = nuevo_primero;

    return dato;
}
