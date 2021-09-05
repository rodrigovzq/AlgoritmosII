#include "main.h" // No borrar

size_t raiz_entera2(size_t n, size_t i) {
    if (n / i == 1 ) return i;
    if (n < i) return ++i;
    i++;
    if (n % (i-1) == 0) return raiz_entera2(n/(i-1), i);
    return raiz_entera2(n/i, i);

}

size_t raiz_entera(size_t n) {
    // Completar
    if (n == 0) return 0;
    return raiz_entera2(n, 1);
}
