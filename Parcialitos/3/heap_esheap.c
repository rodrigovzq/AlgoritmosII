/*

Implementar en lenguaje C una función recursiva con la firma bool
es_heap(int arr[], size_t n). Esta debe devolver true o false de acuerdo
a si el arreglo que recibe como parámetro cumple la propiedad de heap (de
mínimos).

Hacer el seguimiento de la función para el arreglo: [ 1, 7, 2, 8, 7, 6, 3, 3, 9, 10 ].

¿De qué orden es este algoritmo?

*/
/*

Invariantes de heap:
    - El padre debe ser mayor que los hijos
Casos base:
    - Una hoja es un heap

*/
#include <stdlib.h>
#include <stdbool.h>

bool _es_heap(int arr[], size_t pos_padre, size_t n)
{

    size_t pos_hizq = (2 * pos_padre) + 1;
    size_t pos_hder = (2 * pos_padre) + 2;

    if (pos_hizq > n && pos_hder > n)
        return true;
    if (pos_hizq <= n)
    {
        if (arr[pos_padre] > arr[pos_hizq])
            return false;
    }
    if (pos_hder <= n)
    {
        if (arr[pos_padre] > arr[pos_hder])
            return false;
    }
    if (pos_hizq <= n)
        if(!_es_heap(arr, pos_hizq, n))
            return false;
    if (pos_hder <= n)
        if(!_es_heap(arr, pos_hder, n))
            return false;
    return true;
}

bool es_heap(int arr[], size_t n)
{
    return _es_heap(arr, 0, n);
}

// Creo que si puedo aplicar teorema maestro, seria O( log n)