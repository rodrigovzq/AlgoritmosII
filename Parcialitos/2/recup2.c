#include "abb.h"
#include "heap.h"
#include "lista.h"
#include "hash.h"
// 1. Se tiene un árbol binario de búsqueda con cadenas como claves y una función de comparación
// strcmp.Implementar una primitiva lista_t *abb_mayores(const abb_t *abb, const char *cadena)
//que dado un ABB y una cadena, devuelva una lista ordenada que contenga las claves del árbol
// que sean mayores a la cadena recibida por parámetro(que no necesariamente está en el árbol).
// Indicar y justificar cual es la complejidad del algoritmo.Suponer que la estructura del TDA es :

//Aclaración : se debe realizar la menor cantidad posible de comparaciones.

typedef struct abb
{
    const char *clave;
    struct abb *izq;
    struct abb *der;
} abb_t;

lista_t *abb_mayores(const abb_t *abb, const char *cadena)
{

    lista_t *lista = lista_crear();
    heap_t *heap = heap_crear(strcmp); //heap de maximos

    llenar_con_mayores(abb, cadena, heap);
    while (heap_cantidad(heap) > 0)
    {
        lista_insertar_primero(lista, heap_desencolar(heap)); //al insertar primero desde maxim a minimo, se ordena la lista de menor a mayor
    }
    heap_destruir(heap, NULL);
    return lista;
}

void llenar_con_mayores(abb_t *abb, char *cadena, heap_t *heap)
{
    if (abb == NULL)
        return;
    int compare = strcmp(abb->clave, cadena);
    if (compare == 0)
        heap_encolar(heap, abb->clave);
    else if (compare < 0)
        llenar_con_mayores(abb->der, cadena, heap);
    heap_encolar(heap, abb->clave);
    if (abb->izq != NULL && strcmp(abb->izq->clave, cadena) >= 0)
        llenar_con_mayores(abb->izq, cadena, heap);
    if (abb->der != NULL)
        llenar_con_mayores(abb->der, cadena, heap) return
}
// La funcion llenar_con_mayores es la que hace el recorrido del arbol de manera pre order.
// Como debe recorrer siempre por lo menos un sub arbol entero, por la estructura binaria del ABB, el orden es generalmente
//O(logN) y en el pero de los casos es O(N) con N siendo la cantidad de nodos que hay en el abb .
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 2. Una fábrica de pastas de Lanús le pide a alumnos de Algoritmos y Programación II que le solucionen un problema :
//  sus dos distribuidoras de materias primas le enviaron un hash cada una, dónde sus claves son los nombres de los
//  productos, y sus valores asociados, sus precios.La fábrica de pastas le pide a los alumnos que le implementen una
//  función que le devuelva un nuevo hash con la unión de todos esos productos, y en caso de que una misma materia prima
//   se encuentre en ambos hashes, elegir la que tenga el precio más barato.Indicar y justificar el orden del algoritmo.
void *minimo(void *a, void *b)
{
    if ((size_t)*a < (size_t)*b)
        return a;
    return b;
}

hash_t *merge_hash(hash_t *hash1, hash_t *hash2)
{
    hash_t *merged = hash_crear(free);
    hash_t *primero = NULL, *segundo = NULL;
    if (hash_cantidad(hash1) > hash_cantidad(hash2))
    {
        primero = hash1;
        segundo = hash2;
    }
    else
    {
        primero = hash2;
        segundo = hash1;
    }
    hash_iter_t *iter = hash_iter_crear(primero);
    size_t *precio = 0;
    while (!hash_iter_al_final(iter))
    {
        char *producto = hash_iter_ver_actual(iter);
        precio = (size_t *)hash_obtener(primero, producto);
        hash_guardar(merged, producto, precio);
        hash_iter_avanzar(iter);
    } //llena el hash con los contenidos del hash con mas elementos.
    hash_iter_destruir(iter);
    iter = hash_iter_crear(segundo);
    while (!hash_iter_al_final(iter))
    {
        char *producto = hash_iter_ver_actual(iter);
        precio = (size_t *)hash_obtener(primero, producto);
        if (hash_pertenece(primero, producto))
        {
            precio = (size_t *)minimo(hash_obtener(primero, producto), hash_obtener(segundo, producto));
        }
        hash_guardar(merged, producto, precio);
        hash_iter_avanzar(iter);
    }
    hash_iter_destruir(iter);
    return merged;
}

// Este algoritmo recorre enteramente ambos hashes, el resto de primitivas usadas son de tiempo constante
// por lo que orden de este algoritmo es O(N + M), siendo N y M la cantidad de elementos en los hash1 y hash2 respectivamente.
