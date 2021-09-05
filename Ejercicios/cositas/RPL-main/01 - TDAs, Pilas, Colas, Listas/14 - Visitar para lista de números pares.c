#include "lista.h"

bool visitar_suma_pares(void* dato, void* extra) {
    int* dato_ = dato;
    int* extra_ = extra;
    if (*dato_ % 2 == 0) {
        *extra_ += *dato_;
    }
    if (*dato_ < 0) {
        *extra_ = 0;
    }
    return true;
}
