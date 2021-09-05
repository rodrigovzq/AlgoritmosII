#include "main.h" // No borrar

int elemento_desordenado2(int arr[], size_t inicio, size_t fin) {
    if (inicio >= fin) {
        return false;
    }
    if ((fin - inicio) == 1) {
        int ordenado = (arr[fin] >= arr[inicio]) ? false : arr[inicio];
        return ordenado;
    }
    size_t medio = inicio + (fin - inicio) / 2;
    int izquierda = elemento_desordenado2(arr, inicio, medio);
    int derecha = elemento_desordenado2(arr, medio, fin);
    if (izquierda) return izquierda;
    if (derecha) return derecha;
    return false;
}

int elemento_desordenado(int arr[], size_t n) {
    // Completar
    if (n == 0) return -1;
    return elemento_desordenado2(arr, 0, n-1);
}
