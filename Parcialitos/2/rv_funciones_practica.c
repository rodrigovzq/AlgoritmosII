#include <stdlib.h>
#include <stdbool.h>
#include "hash.h"
#include "lista.h"
// Escribir una primita recrusiva que invierta el arbol binario pasado por parametro,
// de manera tal qu e los hijos izquierdos de cada nodo se conviertan en hijos derechos.

typedef struct arbol
{
    struct arbol *izq;
    struct arbol *der;

} arbol_t;

void arbol_invertir(arbol_t *ab)
{
    if (!ab)
        return;
    arbol_t *aux = ab->der;
    ab->der = ab->izq;
    ab->izq = aux;

    arbol_invertir(ab->der);
    arbol_invertir(ab->der);
}
// Complejidad: Teorema maestro
/*
A = 2 ; cantidad de llamados recursivos simultaneos
B = 2 ; proporcion del tamaño original que se llama recursivamente
C = 0 ; orden n^c del costo de las operaciones aparte de lo recursivo (lineas 13 a 17)
log_b(A) = log_2(2) = 1 > 0 = C => O(n^mayor) => *** O(n) *** 
*/
// Es PRE ORDER porque se realizan primer acciones sobre el nodo actual y luego sobre los hijos
// (POST ORDER es cuando las acciones son primero sobre los hijos y luego sobre el padre y IN ORDER es izq, padre, der)
//**************************************************************************************//

// Implementar una funcion de orden O(N), que reciba un arreglo y su largo y que devuelva true o false
// de acuerdo a si existe algun elemento que aparezca mas de la mitad de las veces. Justificar orden.

bool repetidos(void *arreglo[], size_t n)
{
    // Crear hash
    // Por cada elemento del arreglo:
    // si el elemento no esta en el hash, lo guardamos con 1 como valor (valor es las aparciciones)
    // Si el elemento esta en el hash, incrementamos en valor actal.
    // Si el elemento tiene valor mayor a n/2 return true.
    //devolver false

    hash_t *hash = hash_crear(NULL);
    for (size_t i = 0; i < n; i++)
    {
        if (!hash_pertenece(hash, arreglo[i]))
        {
            hash_guardar(hash, arreglo[i], &1);
        }
        else
        {
            size_t *apariciones = hash_obtener(hash, arreglo[i]);
            *apariciones++;
            hash_guardar(hash, arreglo[i], apariciones);
            if (*apariciones > n / 2)
            {
                return true;
                hash_destruir(hash);
            }
        }
    }
    hash_destruir(hash);
    return false;
}
bool repetidos_enclase(void *arreglo[], size_t n)
{
    // libertad de consideracion para lo que devuelve hash_obtener, y que le puedo guardar

    hash_t *hash = hash_crear(NULL);
    for (size_t i = 0; i < n; i++)
    {
        size_t apariciones = (!hash_pertenece(hash, arreglo[i])) ? 1 : hash_obtener(hash, arreglo[i]) + 1; //consi
        hash_guardar(hash, arreglo[i], apariciones);
    }
    if (apariciones > n / 2)
    {
        hash_destruir(hash);
        return true;
    }
    hash_destruir(hash);
    return false;
}
// Complejidad:
/*
Todas las primitivas de hash son O(1) salvo destruir que es O(N) pero se ejecuta una sola vez
el for es O(N)
La funcion es O(N)
*/
//**************************************************************************************//
// Ejercico 4: Implementar una primitva para el ABB, que devuelva una lista con las claves del mismo,
// ordenadas tal que si insertaramos las claves en un ABB vacio, dicho ABB tendria la misma estructura que el arbol
// original

// --> usar preorder para cummplir lo ultimo

void _obtener_claves(nodo_t *actual, lista_t *lista)
{
    if (!nodo)
        return;

    lista_insertar_ultimo(lista, nodo->clave);

    _obtener_claves(nodo->izq, lista);
    _obtener_clave(nodo->der, lista);
}
lista_t *obtener_claves(abb_t *arbol)
{
    lista_t *lista = lista_crear();
    _obtener_claves(arbol->raiz, lista);
    return lista;
}
// Complejidad: O(N) con N la cantidad de nodos porque los tiene que recorrer todos.

//**************************************************************************************//

// Ordenamientos no comparativos

// Muestre paso a paso como ordenar el siguiente arreglo de numeros
// con counting sort [1,4,1,2,7,5,2,1,9] . De que orden es el algoritmo?

// Counting sort -> cuando los elementos estan en un rango acotado y son elementos contables (enteros)

// 1- calcular el rango rg{entre el minimo y el maximo}
// 2-  Crear un arreglo nuevo que tenga max-min elementos
// Lo hice en Notability
