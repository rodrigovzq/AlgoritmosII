#include "main.h" // No borrar

size_t posicion_pico(int v[], size_t ini, size_t fin) {
    // Completar
    if (ini >= fin) return ini;
    if (fin - ini == 1) {
        if (v[ini] > v[fin]) return ini;
        return fin;
    }
    size_t medio = ini + (fin - ini) / 2;
    size_t izq = posicion_pico(v, ini, medio);
    size_t der = posicion_pico(v, medio, fin);
    if (izq != medio) return izq;
    if (der) return der;
    return fin;
}
