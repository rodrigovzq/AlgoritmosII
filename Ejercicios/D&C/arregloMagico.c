#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "testing.h"

bool _arreglo_es_magico(int arr[], size_t inicio, size_t fin);
bool arreglo_es_magico(int arr[], size_t n);

int main(void)
{

    int A[6] = {-3, 0, 1, 3, 7, 9};
    int B[6] = {1, 2, 4, 6, 7, 9};

    print_test("El arreglo A es magico:", arreglo_es_magico(A, 6));
    print_test("El arreglo B no es magico", !arreglo_es_magico(B, 6));
}

bool arreglo_es_magico(int arr[], size_t n)
{
    return _arreglo_es_magico(arr, 0, n - 1);
}

bool _arreglo_es_magico(int arr[], size_t inicio, size_t fin)
{
    //Caso base
    if (inicio > fin)
        return false;

    size_t medio = (size_t)(inicio + fin) / 2;

    // Si siguio buscando sin exito, medio diverge hacia algun extremo
    if (medio == fin || medio == inicio)
        return false;
    if (arr[medio] == medio)
        return true;
    else if (arr[medio] > medio)
        return _arreglo_es_magico(arr, inicio, medio);
    else
        return _arreglo_es_magico(arr, medio, fin);
}
