#ifndef _NODO_H
#define _NODO_H
#include <stdbool.h>

/* *****************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/
typedef struct nodo nodo_t;

/* *****************************************************************
 *                    PRIMITIVAS NODO
 * *****************************************************************/

// Crea nodo
// Post: Nodo creado con dato guardado y posicion proxima en NULL. Devuelve NULL en caso de falla.
nodo_t *nodo_crear(void *dato);
// Elimina el nodo
// Pre: Nodo fue creado
// Post: Nodo eliminado
void nodo_destruir(nodo_t *nodo);
// Devuelve puntero al dato del nodo argumento
// Pre: Nodo fue creado
void *nodo_ver_dato(nodo_t *nodo);
// Devuelve puntero al siguiente nodo del argumento.
// Pre: Nodo fue creado
nodo_t *nodo_proximo(nodo_t *nodo);
//Enlaza unidireccionalmente los nodos, en el orden de los argumentos.
// Post el primer nodo ahora tiene un puntero al siguiente en su campo prox
bool nodo_enlazar(nodo_t *nodo_anterior, nodo_t *nodo_siguiente);
// Verifica que si el nodo esta al final de la lista.
// Pre: el nodo fue creado.
bool nodo_al_final(nodo_t *nodo);

#endif
