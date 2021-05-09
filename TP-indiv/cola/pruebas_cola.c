#include "cola.h"
#include "testing.h"
#include <stdio.h>
void pruebas_cola_vacia(void)
{
    printf("\n>>> Inicio prubeas de cola vacia<<<\n");
    cola_t *c = cola_crear();
    print_test("Cola fue creada:", c != NULL);
    print_test("Cola esta vacia:", cola_esta_vacia(c));
    print_test("El primer elemento de la cola es NULL", cola_ver_primero(c) == NULL);
    print_test("Desencolar esta restringido:", cola_desencolar(c) == NULL);
    cola_destruir(c, NULL);
    printf(">>> Fin de etapa <<<\n");
}

void pruebas_cola_elementos(void)
{
    printf("\n>>> Inicio prubeas de cola con algunos elementos<<<\n");
    cola_t *c = cola_crear();
    int vec[3] = {5, 8, 13};

    // encolar
    print_test("Cola fue creada:", c != NULL);
    print_test("Encolar 5:", cola_encolar(c, &vec[0]));
    print_test("Primer elemento es 5:", cola_ver_primero(c) == &vec[0]);
    print_test("Encolar 8:", cola_encolar(c, &vec[1]));
    print_test("Primer elemento continua siendo 5:", cola_ver_primero(c) == &vec[0]);
    print_test("Enocolar 13:", cola_encolar(c, &vec[2]));
    print_test("Primero elemento continua siendo 5:", cola_ver_primero(c) == &vec[0]);
    print_test("Encolamiento de NULL es valido:", cola_encolar(c, NULL));

    // desencolar
    print_test("Desencolar 5:", cola_desencolar(c) == &vec[0]);
    print_test("Primer elemento es 8:", cola_ver_primero(c) == &vec[1]);
    print_test("Desencolar 8:", cola_desencolar(c) == &vec[1]);
    print_test("Primer elemento es 13:", cola_ver_primero(c) == &vec[2]);
    print_test("Desencolar 13:", cola_desencolar(c) == &vec[2]);
    print_test("Primer elemento es NULL:", cola_ver_primero(c) == NULL);
    print_test("Desencolar NULL:", cola_desencolar(c) == NULL);

    // check vacio
    print_test("Cola esta vacia:", cola_esta_vacia(c));
    cola_destruir(c, NULL);
    printf(">>> Fin de etapa <<<\n");
}
void pruebas_cola_volumen(void)
{
    printf("\n>>>Inicio de pruebas de volumen<<<\n");
    cola_t *c = cola_crear();
    print_test("La cola fue creada:", c != NULL);

    const size_t tam = 27800;
    size_t vec[tam];
    for (size_t i = 0; i < tam; i++)
    {
        vec[i] = tam - i;
    }
    // Encolar
    bool ok = true;
    for (size_t i = 0; i < tam; i++)
    {
        ok &= cola_encolar(c, &vec[i]);
    }
    print_test("Se pudieron guardar todos los elementos", ok);

    // Desencolar
    size_t *v;
    size_t *primero;
    bool ok_primero = true;
    for (size_t i = 0; i < tam; i++)
    {
        v = cola_desencolar(c);
        ok &= *v == vec[i];
        primero = cola_ver_primero(c);
        if (primero != NULL)
            ok_primero &= *primero == vec[i + 1];
    }
    print_test("Se desencolaron todos los elementos", cola_esta_vacia(c));
    print_test("Todos los elementos desencolados fueron correctos", ok_primero);
    print_test("Se conservo la invariante de cola", ok);

    cola_destruir(c, NULL);
    printf(">>> Fin de etapa <<<\n");
}
void pruebas_cola_estudiante(void)
{
    pruebas_cola_vacia();
    pruebas_cola_elementos();
    pruebas_cola_volumen();

    return;
}

#ifndef CORRECTOR

int main(void)
{
    pruebas_cola_estudiante();
    return failure_count() > 0; // Indica si falló alguna prueba.
}

#endif
