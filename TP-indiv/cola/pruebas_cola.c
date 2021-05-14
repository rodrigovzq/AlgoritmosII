#include "cola.h"
#include "testing.h"
#include <stdio.h>
#include "vector.h"
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
void pruebas_cola_volumen_estatico(void)
{
    printf("\n>>>Inicio de pruebas de volumen<<<\n");
    cola_t *c = cola_crear();
    print_test("La cola fue creada:", c != NULL);

    const size_t tam = 27182;
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
vector_t *crear_vector_prueba(const size_t tam)
{
    vector_t *vec = vector_crear(tam);
    size_t i;
    for (i = 0; i < tam; i++)
    {
        vector_guardar(vec, i, (int)i);
    }
    return vec;
}
void pruebas_cola_volumen_dinamico()
{
    printf("\n>>>Inicio de pruebas de volumen dinamico<<<\n");
    cola_t *c = cola_crear();
    print_test("La cola fue creada:", c != NULL);
    const size_t tam = 35813;
    vector_t *vec = crear_vector_prueba(tam);

    // Encolar
    bool ok = true;
    int valor;
    for (size_t i = 0; i < tam; i++)
    {
        vector_obtener(vec, i, &valor);
        ok &= cola_encolar(c, &valor);
    }
    print_test("Se pudieron guardar todos los elementos", ok);
    // Desencolar
    int *v;
    size_t *primero;
    bool ok_primero = true;
    for (size_t i = 0; i < tam; i++)
    {
        v = cola_desencolar(c);
        vector_obtener(vec, i, &valor);
        ok &= valor == *v;
        primero = cola_ver_primero(c);
        if (primero != NULL)
        {
            vector_obtener(vec, i + 2, &valor);
            ok_primero &= (int)*primero == valor;
        }
    }
    print_test("Se desencolaron todos los elementos", cola_esta_vacia(c));
    print_test("Todos los elementos desencolados fueron correctos", ok_primero);
    print_test("Se conservo la invariante de cola", ok);

    cola_destruir(c, free);
    vector_destruir(vec);
    printf(">>> Fin de etapa <<<\n");
}
void pruebas_cola_destruccion()
{
    printf("\n>>>Inicio de pruebas de volumen: destruccion con elementos dentro<<<\n");
    cola_t *cola = cola_crear();
    size_t tam = 100;
    int **vec = malloc(tam * sizeof(int *));
    print_test("La cola fue creada:", cola != NULL);
    for (size_t i = 0; i < tam; i++)
    {
        vec[i] = malloc(sizeof(int));
        *vec[i] = 5;
    }
    // Encolar
    bool ok = true;
    for (size_t i = 0; i < tam; i++)
    {
        ok &= cola_encolar(cola, vec[i]);
    }

    print_test("Se pudieron guardar todos los elementos", ok);

    cola_destruir(cola, free);
    free(vec);
    printf(">>> Fin de etapa <<<\n");
}

void pruebas_cola_estudiante(void)
{
    pruebas_cola_vacia();
    pruebas_cola_elementos();
    pruebas_cola_volumen_estatico();
    pruebas_cola_volumen_dinamico();
    pruebas_cola_destruccion();

    return;
}

#ifndef CORRECTOR

int main(void)
{
    pruebas_cola_estudiante();
    return failure_count() > 0; // Indica si falló alguna prueba.
}

#endif
