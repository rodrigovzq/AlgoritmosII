#include "main.h" // No borrar

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int _hallar_candidato(int* arr, size_t inicio, size_t fin, int cand_der, int cand_izq)
{
    int contador_der = 0;
    int contador_izq = 0;
    for (size_t i = inicio; i <= fin; i++)
    {
        if(arr[i] == cand_der) contador_der++;
        if(arr[i] == cand_izq) contador_izq++;
    }
    if(contador_izq < contador_der)return cand_der;
    else return cand_izq;
}

int _mas_de_mitad(int* arr, size_t inicio, size_t fin)
{
    if(inicio == fin) return arr[inicio];
    size_t medio = (inicio + fin) / 2;
    int cand_der = _mas_de_mitad(arr, inicio, medio);
    int cand_izq = _mas_de_mitad(arr, medio + 1, fin);
    return _hallar_candidato(arr, inicio, fin, cand_der, cand_izq);
}

bool mas_de_mitad(int* arr, size_t n)
{
    int candidato = _mas_de_mitad(arr, 0, n - 1);
    int contador = 0;
    for (size_t i = 0; i < n; i++) if(arr[i] == candidato) contador++;
    return contador > (n / 2);
}
