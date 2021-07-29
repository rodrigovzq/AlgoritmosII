#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pila.h"
/*3
 Implementar una función int piso(int arreglo[], size_t largo, int n) que reciba
un arreglo ordenado de enteros, su largo y un entero N, y devuelva el piso de N en el
arreglo (es decir, el mayor número menor o igual a N que se encuentre en el arreglo) usando
la técnica de división y conquista. ¿Cuál es el orden del algoritmo? Justificar utilizando el
Teorema del Maestro. Ejemplos: 
*/
int _piso(int arreglo[], size_t inicio, size_t fin, int n)
{

    size_t m = (fin + inicio) / 2;
    if (inicio == m)
    {

        return arreglo[inicio];
    }
    if (arreglo[m] == n)
    {
        printf("%i=%i:", arreglo[m], n);
        return arreglo[m];
    }

    printf("%i<%i:", arreglo[m], n);
    if (arreglo[m] < n)

    {
        printf("si, busco de %zu a %zu \n", m, fin);
        return _piso(arreglo, m, fin, n);
    }
    else
    {
        printf("no, busco de %zu a %zu \n", inicio, m);
        return _piso(arreglo, inicio, m - 1, n);
    }
}
int piso(int arreglo[], size_t largo, int n)
{
    // if (n < arreglo[0])
    //     fprintf(stderr, "no hay piso\n");

    if (n > arreglo[largo - 1])
        return arreglo[largo - 1];
    return _piso(arreglo, 0, largo - 1, n);
}
/*4
Dadas dos pilas de enteros positivos (con posibles valores repetidos) cuyos elementos fueron
ingresados de menor a mayor, se pide implementar una función int* merge_pilas(pila*
pila_1, pila* pila_2) que devuelva un array ordenado de menor a mayor con todos los
valores de ambas pilas sin repeticiones. Detallar y justificar la complejidad del algoritmo
considerando que el tamaño de las pilas es N y M respectivamente.*/
int *merge_pilas(pila_t *pila_1, pila_t *pila_2)
{
    // las pilas sacan elementos de mayor a menor
    // voy desapilando y metiendo en una tercera pila
    pila_t *pila_merge = pila_crear();
    int *n1 = NULL;
    int *n2 = NULL;
    size_t count = 0;
    n1 = (int *)pila_desapilar(pila_1);
    n2 = (int *)pila_desapilar(pila_2);
    ;
    while (!pila_esta_vacia(pila_1) && !pila_esta_vacia(pila_2))
    {
        printf("n1: %i, n2: %i. %zu\n", *n1, *n2, count);
        if (*n1 == *n2)
        {
            pila_apilar(pila_merge, n1);
            count++;
            printf("apila iguales:%i\n", *n1);
            if (!pila_esta_vacia(pila_1))

                n1 = (int *)pila_desapilar(pila_1);
            if (!pila_esta_vacia(pila_2))

                n2 = (int *)pila_desapilar(pila_2);
        }
        while (*n1 > *n2 && !pila_esta_vacia(pila_1))
        {

            if (pila_ver_tope(pila_merge) == NULL || *n1 < *(int *)pila_ver_tope(pila_merge))
            {
                pila_apilar(pila_merge, n1);
                printf("apila n1:%i\n", *n1);
                count++;
            }
            if (!pila_esta_vacia(pila_1))
            {
                n1 = (int *)pila_desapilar(pila_1);
                //printf("desapila n1:%i\n", *n1);
            }
        }
        while (*n2 > *n1 && !pila_esta_vacia(pila_2))
        {
            if (pila_ver_tope(pila_merge) == NULL || *n2 < *(int *)pila_ver_tope(pila_merge))
            {
                pila_apilar(pila_merge, n2);
                printf("apila n2:%i\n", *n2);
                count++;
            }
            if (!pila_esta_vacia(pila_2))
                n2 = (int *)pila_desapilar(pila_2);
        }
    }

    // lleno la pila merge con lo que queda de las otras pilas
    if (pila_esta_vacia(pila_1))
    {
        pila_apilar(pila_merge, n1);
        printf("apila n1:%i\n", *n1);
        count++;
        // while (!pila_esta_vacia(pila_2))
        // {
        //     pila_apilar(pila_merge, pila_desapilar(pila_2));
        //     count++;
        // }
    }
    if (pila_esta_vacia(pila_2))
    {
        pila_apilar(pila_merge, n2);
        printf("apila n2:%i\n", *n2);
        // while (!pila_esta_vacia(pila_1))
        // {
        //     pila_apilar(pila_merge, pila_desapilar(pila_1));
        //     count++;
        // }
    }
    int *arr_ordenado = calloc(count, sizeof(int));
    for (size_t i = 0; i < count; i++)
    {
        arr_ordenado[i] = *(int *)pila_desapilar(pila_merge);
    }
    pila_destruir(pila_merge);
    return arr_ordenado;
}

int main(void)
{
    // int arreglo[10] = {1, 3, 4, 6, 7, 89};

    // int test = 5;
    // printf("floor de %i en el arreglo es %i\n", test, piso(arreglo, 6, test));
    pila_t *pila_1 = pila_crear();
    pila_t *pila_2 = pila_crear();
    size_t count = 0;
    int *aux = malloc(sizeof(int) * 9);
    for (int i = 1; i < 8; i = i + 2)
    {
        aux[count] = i;
        pila_apilar(pila_1, &aux[count]);
        count++;
    }
    for (int i = 2; i < 7; i++)
    {
        aux[count] = i;
        pila_apilar(pila_2, &aux[count]);
        count++;
    }
    int *arreglo = merge_pilas(pila_1, pila_2);
    printf("imprimo arreglo\n");
    for (size_t i = 0; i < count; i++)
        printf("%i\n", arreglo[i]);
}
