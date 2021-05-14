//Parcialito 1, Rodrigo Vazquez, 98934, Ejercicios: 3 4 8

/*3
 Implementar una función int piso(int arreglo[], size_t largo, int n) que reciba
un arreglo ordenado de enteros, su largo y un entero N, y devuelva el piso de N en el
arreglo (es decir, el mayor número menor o igual a N que se encuentre en el arreglo) usando
la técnica de división y conquista. ¿Cuál es el orden del algoritmo? Justificar utilizando el
Teorema del Maestro. Ejemplos: 
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int _piso(int arreglo[], size_t inicio, size_t fin, int n);
int piso(int arreglo[], size_t largo, int n)
{
    return _piso(arreglo, 0, largo - 1, n);
}
int _piso(int arreglo[], size_t inicio, size_t fin, int n)
{
    if (n >= arreglo[fin])
        return arreglo[fin]; //caso base

    size_t medio = (size_t)(inicio + fin) / 2;

    if (n > arreglo[medio] && n <= arreglo[fin])
        return _piso(arreglo, medio, fin, n);
    if (n > arreglo[inicio] && n <= arreglo[medio])
        return _piso(arreglo, inicio, medio, n);
}
// T(n)= A T(n/B)+O(n^c) con A=1, B=2, C=0 -> O(log n)

/*4
Dadas dos pilas de enteros positivos (con posibles valores repetidos) cuyos elementos fueron
ingresados de menor a mayor, se pide implementar una función int* merge_pilas(pila*
pila_1, pila* pila_2) que devuelva un array ordenado de menor a mayor con todos los
valores de ambas pilas sin repeticiones. Detallar y justificar la complejidad del algoritmo
considerando que el tamaño de las pilas es N y M respectivamente.*/

int *merge_pilas(pila_t *pila_1, pila_t *pila_2)
{
    pila_t *p = pila_crear();

    int *arreglo1;
    int *arreglo2;
    size_t n = 0;
    size_t m = 0;
    int x, y;

    while (!pila_esta_vacia(pila_1))
    {
        arreglo1[n++] = *pila_desapilar(pila_1);
    }
    while (!pila_esta_vacia(pila_2))
    {
        arreglo2[m++] = *pila_desapilar(pila_2);
    }
    size_t largo = m + n + 1;
    int arreglo[largo];
    size_t j = 0;                       // recorre arreglo2
    size_t k = 0;                       //recorre arreglo final
    int x;                              //canditato a ser agregado
    for (size_t i = 0; i < n && j < m;) // recorre primer arreglo y lo avanza solo si agrego un elemento del 1, sino avanza en el 2
    {

        if (arreglo1[i] < arreglo2[j]) //agrega el menor
        {
            x = arreglo1[i];
            i++;
        }
        if (arreglo1[i] == arreglo2[j])
        {
            x = arreglo2[j];
            j++;
            i++;
        }
        if (arreglo1[i] > arreglo2[j])
        {
            x = arreglo2[j];
            j++;
        }
        if (!esta_en_arreglo(arreglo, k + 1, x)) //solo agrego los que no estan
        {
            arreglo[k] = x;
            k++;
        }
    }
    return arreglo;
}
/*
En principio ambas pilas se recorren completamente y secuencialemten, esto es de orden O(2n)=O(n)
No ciclos anidados, entonces no se agregan recorridos de orden N .
El orden de al funcion es O(n)
*/
bool esta_en_arreglo(int arreglo[], size_t largo, int x)
{
    if (largo == 0)
        return false;
    for (size_t i = 0; i < largo; i++)
    {
        if (arreglo[i] == x)
            return true;
    }
    return false;
}
/* 8
Implementar función lista_t* reemplazar(lista_t* lista, int elemento, int
reemplazo) que recibe una lista enlazada enteros, un elemento a reemplazar y un elemento
de reemplazo, y devuelve una lista enlazada nueva con el reemplazo realizado en cada
aparición del elemento. La lista original no debe ser modificada. Detallar y justificar la
complejidad del algoritmo. Ejemplos: */

lista_t *reemplazar(lista_t *lista, int elemento, int reemplazo)
{
    lista_t *listanueva = lista_crear();
    lista_iter_t *iterador = lista_iter_crear(lista);
    for (size_t i = 0; i < lista_largo(lista); i++)
    {
        if (elemento == *lista_iter_ver_actual(iterador))
        {
            lista_insertar_ultimo(listanueva, &reemplazo);
        }
        else
        {
            lista_insertar_ultimo(listanueva, &elemento);
        }
        lista_iter_avanzar(iterador);
    }
    lista_iter_destruir(iterador);
    return listanueva;
}
/*
El iterador recorre siempre el total del largo de la lista dato, eso es de orden lineal.
La nueva lista se va creando al mismo ritmo que la primera esta siendo recorrida, es decir,
que no se agregan ordenes de magnitud de n.
El orden de la funcion es O(n)
*/
