#include "main.h" // No borrar

int primer_cero(int arr[], size_t n) {
    int izq = 0;
    int der = n - 1;
    
    int resultado = -1;

    while(der >= izq){
        int med = (der + izq) / 2;
        if(arr[med] == 0){
            der = med - 1;
            resultado = med;
        }
        else{
            izq = med + 1;
        }
    }
    return resultado;
}
