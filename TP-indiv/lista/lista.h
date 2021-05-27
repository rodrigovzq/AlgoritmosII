#ifndef _LISTA_H
#define _LISTA_H
#include <stdlib.h>
#include <stdbool.h>
/* *****************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/
struct lista;
typedef struct lista lista_t;
struct lista_iter;
typedef struct lista_iter lista_iter_t;
/* *****************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void);
// Devuelve verdadero si la lista no tiene elementos adentro, falso en caso contrario.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);
// Inserta un nuevo elemento al principio de la lista.
// Pre: la lista fue creada.
// Post: un nodo se agrego al principio de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);
// Inserta un nuevo elemento al final de la lista.
// Pre: la lista fue creada.
// Post: un nodo se agrego al final de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);
// Devuelve y elimina el primer elemento de la lista.
// Pre: la lista fue creada.
// Post: un nodo se elimino del principio de la lista.
void *lista_borrar_primero(lista_t *lista);
// Devuelve el dato almacenado al principio de la lista
// Pre: la lista fue creada
void *lista_ver_primero(const lista_t *lista);
// Devuelve el dato almacenado al final de la lista
// Pre: la lista fue creada
void *lista_ver_ultimo(const lista_t *lista);
// Devuelve la cantidad de elementos almacenados en la lista.
// Pre: la lista fue creada.
size_t lista_largo(const lista_t *lista);
// Destruye el contenido de la lista y sus datos almacenados.
// Pre: la lista fue creada.
// Post: la lista fue destruida.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

/* *****************************************************************
 *                 PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

// TODO: Documentacion iterador externo
// Crea iterador.
// Post: devuelve puntero a iterador o NULL en caso de no poder crearse
lista_iter_t *lista_iter_crear(lista_t *lista);
// Avanza el iterador a la siguiente posicicion.
// Pre: el iterador fue creado.
// Post: el iterador se encuentra en la siguiente posicion de la lista o en el mismo lugar si estaba al final.
bool lista_iter_avanzar(lista_iter_t *iter);
// Permite ver el dato del item actual de la lista donde se encuentra el iterador.
// Pre: el iterador fue creado.
void *lista_iter_ver_actual(const lista_iter_t *iter);
// Verifica que si el iterador esta al final de la lista.
// Pre: el iterador fue creado.
bool lista_iter_al_final(const lista_iter_t *iter);
// Destruye el iterador
// Pre: el iterador fue creado.
// Post: el iterador fue destruido.
void lista_iter_destruir(lista_iter_t *iter);
// Inserta un dato en la posicion actual del iterador.
// Pre: el iterador fue creado.
// Post: la lista tiene un elemento mas,insertado en la posicion actual del iterador.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);
// Elimina un dato en la posicion actual del iterador.
// Pre: el iterador fue creado.
// Post: la lista tiene un elemento menos, quitado de la posicion actual del iterador.
void *lista_iter_borrar(lista_iter_t *iter);

/* *****************************************************************
 *                 PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

// TODO: Documentacion iterador interno
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

typedef struct nodo nodo_t;

/* *****************************************************************
 *                    Funciones NODO
 * *****************************************************************/

// Crea nodo
// Post: Nodo creado con dato guardado y posicion proxima en NULL. Devuelve NULL en caso de falla.
nodo_t *nodo_crear(void *dato);
// Elimina el nodo
// Pre: Nodo fue creado
// Post: Nodo eliminado
void nodo_destruir(nodo_t *nodo);
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
