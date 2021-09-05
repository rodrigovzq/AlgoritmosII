#include <stdlib.h>
#include <stdio.h> // sprintf
#include "fraccion.h"

struct fraccion{
    int denom;
    int numer;
};

int mcd(int i, int j)
{
    // euclides algorithm
    if (j == 0) return i;
    return mcd(j, i % j);
}

fraccion_t* fraccion_crear(int numerador, int denominador) {
    if(denominador==0) return NULL; // 0 is not allowed doh...
    int divisorComun = mcd(numerador,denominador);
    fraccion_t *f1;
    if( !(f1=(fraccion_t*)malloc(sizeof(fraccion_t))) )
    {
        return NULL;
    }
    if( (numerador%divisorComun)==0)
    {
        // 15/3 = 5 ; numerador=5 denominador=1
        numerador=numerador/divisorComun;
        denominador=denominador/divisorComun;
    }
    f1->numer = numerador;
    f1->denom = denominador;
    return f1;
}

void fraccion_destruir(fraccion_t* fraccion) {
    if(fraccion) free(fraccion);
}

fraccion_t* fraccion_sumar(fraccion_t* f1, fraccion_t* f2) {
    
    fraccion_t *f;
    int numerador = (f1->numer*f2->denom) + (f2->numer*f1->denom);
    int denominador = f1->denom*f2->denom;
    if( (numerador%denominador)==0)
    {
        // 15/3 = 5 ; numerador=5 denominador=1
        numerador=numerador/denominador;
        denominador=1;
    }
    
    if( !(f=fraccion_crear(numerador,denominador)) )
    {
        fprintf(stderr,"%s\n","Could not allocate memory for fraccion.");
        return NULL;
    }
    fraccion_destruir(f1);
    fraccion_destruir(f2);
    return f;
}

fraccion_t* fraccion_mul(fraccion_t* f1, fraccion_t* f2) {
    fraccion_t *f;

    if( (f=fraccion_crear(f1->numer * f2->numer,f1->denom * f2->denom))==NULL )
    {
        fprintf(stderr,"%s\n","Could not allocate memory for fraccion.");
        return NULL;
    }
    fraccion_destruir(f1);
    fraccion_destruir(f2);
    return f;
    
}

int fraccion_parte_entera(fraccion_t* fraccion) {
    // as numer and denom are ints the division is made int and such a cast may be not needed
    return (int)(fraccion->numer/fraccion->denom);
}

char* fraccion_representacion(fraccion_t* fraccion) {
    char *buffer = (char*)malloc( (sizeof(char)*100));
    if((fraccion->numer%fraccion->denom)==0)
        sprintf(buffer, "%d", fraccion->numer/fraccion->denom);
    else sprintf(buffer, "%d/%d", fraccion->numer, fraccion->denom);
    return buffer;
}
