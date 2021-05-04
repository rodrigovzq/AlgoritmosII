#include "pila.h"
#include "testing.h"
#include <stdio.h>

static void prueba_pila_vacia(void)
{
    printf(">>>Inicio de pruebas con pila de tamaño 0<<<\n");

    pila_t *p = pila_crear();

    print_test("la pila fue creada:", p != NULL);
    print_test("largo de la pila es 0:", pila_esta_vacia(p) == true);
    print_test("ver tope devuelve puntero nulo:", pila_ver_tope(p) == NULL);
    print_test("restringir desapilar", pila_desapilar(p) == NULL);
    pila_destruir(p);
}

static void prueba_pila_elementos(void)
{
    printf(">>>Inicio de pruebas con pila de tamaño 4<<<\n");

    pila_t *p = pila_crear();

    int vec[3] = {5, 8, 13};
    // apilamiento
    print_test("la pila fue creada:", p != NULL);
    print_test("apilar 5:", pila_apilar(p, &vec[0]) == true);
    print_test("tope es 5:", pila_ver_tope(p) == &vec[0]);
    print_test("apilar 8:", pila_apilar(p, &vec[1]) == true);
    print_test("tope es 8:", pila_ver_tope(p) == &vec[1]);
    print_test("apilar 13:", pila_apilar(p, &vec[2]) == true);
    print_test("tope es 13:", pila_ver_tope(p) == &vec[2]);
    print_test("apilamiento de NULL es valido:", pila_apilar(p, NULL) == true);

    //desapilamiento
    print_test("desapilar NULL:", pila_desapilar(p) == NULL);
    print_test("desapilar 13:", pila_desapilar(p) == &vec[2]);
    print_test("tope es 8:", pila_ver_tope(p) == &vec[1]);
    print_test("desapilar 8:", pila_desapilar(p) == &vec[1]);
    print_test("tope es 5:", pila_ver_tope(p) == &vec[0]);
    print_test("desapilar 5:", pila_desapilar(p) == &vec[0]);

    //check vacio
    print_test("pila esta vacia:", pila_esta_vacia(p) == true);
    pila_destruir(p);
}

static void prueba_pila_volumen(void)
{
    size_t tam = 27182;
    printf(">>>Inicio de pruebas de volumen<<<\n");
    //creo pila
    pila_t *p = pila_crear();
    print_test("la pila fue creada:", p != NULL);

    size_t vec[tam];
    for (size_t i = 0; i < tam; i++)
    {
        vec[i] = tam - i;
    }
    // prueba de apilar
    bool ok = true;
    bool ok_tope = true;
    size_t *tope;
    for (size_t i = 0; i < tam; i++)
    {
        ok &= pila_apilar(p, &vec[i]);
        tope = pila_ver_tope(p);
        ok_tope &= *tope == vec[i];
    }
    print_test("se pudieron guardar todos los elementos", ok);
    print_test("todos los elementos guardados fueron correctos", ok_tope);

    // prueba desapilar
    size_t *v;
    for (size_t i = 0; i < tam; i++)
    {

        v = pila_desapilar(p);
        ok &= *v == vec[tam - i - 1];
        tope = pila_ver_tope(p);
        if (tope != NULL)
            ok_tope &= *tope == vec[tam - i - 2];
    }
    print_test("se desapilaron todos los elementos", pila_esta_vacia(p) == true);
    print_test("todos los elementos desapilados fueron correctos", ok_tope);
    print_test("se conservo la invariante de pila", ok);
    pila_destruir(p);
}

void pruebas_pila_estudiante()
{
    prueba_pila_vacia();
    prueba_pila_elementos();
    prueba_pila_volumen();
}

/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR // Para que no dé conflicto con el main() del corrector.

int main(void)
{
    pruebas_pila_estudiante();
    return failure_count() > 0; // Indica si falló alguna prueba.
}

#endif
