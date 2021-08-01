#define _POSIX_C_SOURCE 200809L
#include "heap.h"
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define HEAP_INIT_SIZE 10
#define HEAP_RESIZE_FACTOR 2

/*******************************************************************
 *               		        HEAP                               *
 *		 Facultad de Ingenieria de la Universidad de Buenos Aires  *
 *												Vazquez, Rodrigo   *
 *												Vidal, Manuel      *
 ******************************************************************/
// Invariante / condicion de heap -> padre >= hijos -> heap de maximos

struct heap
{
    void **datos;
    size_t cantidad;
    size_t capacidad;
    cmp_func_t cmp;
};

/* *****************************************************************
 *                           AUXILIARES HEAP                       *
 * *****************************************************************/

static size_t calcular_pos_padre(size_t pos_hijo)
{
    return (pos_hijo - 1) / 2;
}
//Pre: validar que haya no se vaya del rango
static size_t calcular_pos_hizq(size_t pos_padre)
{
    return 2 * pos_padre + 1;
}
static size_t calcular_pos_hder(size_t pos_padre)
{
    return 2 * pos_padre + 2;
}
static void swap(void **x, void **y)
{
    void *aux = *x;
    *x = *y;
    *y = aux;
}

static bool heap_redimensionar(heap_t *heap, size_t nueva_capacidad)
{
    void **datos_nuevo = realloc(heap->datos, nueva_capacidad * sizeof(void *));

    if (nueva_capacidad > 0 && !datos_nuevo)
        return false;

    heap->datos = datos_nuevo;
    heap->capacidad = nueva_capacidad;
    return true;
}

static void upheap(void **datos, size_t pos_hijo, cmp_func_t cmp)
{
    if (pos_hijo == 0)
        return;

    void *hijo = datos[pos_hijo];

    size_t pos_padre = calcular_pos_padre(pos_hijo);

    void *padre = datos[pos_padre];

    if (cmp(padre, hijo) < 0)
    {
        swap(&datos[pos_padre], &datos[pos_hijo]);
        upheap(datos, pos_padre, cmp);
    }
}

static size_t maximo(void **datos, cmp_func_t cmp, size_t pos_padre, size_t pos_hder, size_t pos_hizq, size_t cant)
{

    size_t pos_max = pos_padre;

    if (pos_hizq < cant && cmp(datos[pos_padre], datos[pos_hizq]) < 0)
        pos_max = pos_hizq;

    if (pos_hder < cant && cmp(datos[pos_max], datos[pos_hder]) < 0)
        pos_max = pos_hder;

    return pos_max;
}

static void downheap(void **datos, const size_t cant, size_t pos_padre, cmp_func_t cmp)
{
    if (pos_padre >= cant)
        return;

    size_t pos_hder = calcular_pos_hder(pos_padre);
    size_t pos_hizq = calcular_pos_hizq(pos_padre);

    size_t pos_max = maximo(datos, cmp, pos_padre, pos_hder, pos_hizq, cant);

    if (pos_max != pos_padre)
    {
        swap(&datos[pos_padre], &datos[pos_max]);
        downheap(datos, cant, pos_max, cmp);
    }
}

static void heapify(void **datos, size_t cant, cmp_func_t cmp)
{
    for (size_t i = cant / 2; i > 0; i--)
    {
        downheap(datos, cant, i - 1, cmp);
    }
}
/* *****************************************************************
 *                        PRIMITIVAS HEAP                          *
 * *****************************************************************/
heap_t *heap_crear(cmp_func_t cmp)
{
    if (!cmp)
        return NULL;
    heap_t *heap = malloc(sizeof(heap_t));
    if (!heap)
        return NULL;
    heap->datos = malloc(HEAP_INIT_SIZE * sizeof(void *));
    if (!heap->datos)
    {
        free(heap);
        return NULL;
    }
    heap->cantidad = 0;
    heap->capacidad = HEAP_INIT_SIZE;
    heap->cmp = cmp;
    return heap;
}

void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e))
{
    size_t i = 0;
    while (i < heap->cantidad && destruir_elemento)
    {
        destruir_elemento(heap->datos[i]);
        i++;
    }
    free(heap->datos);
    free(heap);
}

size_t heap_cantidad(const heap_t *heap)
{
    return heap->cantidad;
}

void *heap_ver_max(const heap_t *heap)
{
    return (!heap_esta_vacio(heap)) ? heap->datos[0] : NULL;
}

bool heap_esta_vacio(const heap_t *heap)
{
    return heap->cantidad == 0;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp)
{
    if (!cmp)
        return NULL;
    heap_t *heap = malloc(sizeof(heap_t));
    if (!heap)
        return NULL;
    heap->datos = malloc(sizeof(void *) * n);
    if (!heap->datos)
    {
        free(heap);
        return NULL;
    }

    memcpy(heap->datos, arreglo, n * sizeof(void *));
    heapify(heap->datos, n, cmp);

    heap->cantidad = n;
    heap->capacidad = n;
    heap->cmp = cmp;
    return heap;
}

bool heap_encolar(heap_t *heap, void *elem)
{
    if (heap->cantidad == heap->capacidad)
    {
        if (!heap_redimensionar(heap, heap->capacidad * HEAP_RESIZE_FACTOR))
            return false;
    }
    heap->datos[heap->cantidad++] = elem;
    upheap(heap->datos, heap->cantidad - 1, heap->cmp);

    return true;
}

void *heap_desencolar(heap_t *heap)
{
    if (heap_esta_vacio(heap))
        return NULL;

    void *dato = heap->datos[0];

    heap->cantidad--;

    if (heap->cantidad > 0)
    {
        swap(&heap->datos[0], &heap->datos[(heap->cantidad)]);
        downheap(heap->datos, heap->cantidad, 0, heap->cmp);
    }

    if (heap->cantidad < heap->capacidad / HEAP_RESIZE_FACTOR && heap->capacidad > HEAP_INIT_SIZE)
    {
        if (!heap_redimensionar(heap, heap->capacidad / HEAP_RESIZE_FACTOR))
            return false;
    }

    return dato;
}

/// HEAP SORT////
// para ordenar de menor a mayor, necesito un heap de maximos
void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp)
{

    if (!elementos || cant < 2)
        return;

    heapify(elementos, cant, cmp);

    for (size_t ultimo_relativo = cant - 1; ultimo_relativo > 0; ultimo_relativo--)
    {
        swap(&elementos[0], &elementos[ultimo_relativo]);
        downheap(elementos, ultimo_relativo, 0, cmp);
    }
}
