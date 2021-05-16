#include "lista.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
void pruebas_lista_vacia(void)
{
    printf("\n>>> Inicio prubeas de lista vacia<<<\n");
    lista_t *lista = lista_crear();
    print_test("Lista fue creada:", lista != NULL);
    print_test("Lista esta vacia:", lista_esta_vacia(lista));
    print_test("El primer elemento de la lista es NULL", lista_ver_primero(lista) == NULL);
    print_test("Eliminar primero de la lista esta restringido:", lista_borrar_primero(lista) == NULL);
    lista_destruir(lista, NULL);
    printf(">>> Fin de etapa <<<\n");
}
void pruebas_lista_elementos(void)
{
    printf("\n>>> Inicio prubeas de lista con algunos elementos<<<\n");
    lista_t *lista = lista_crear();
    int vec[3] = {5, 8, 13};

    // Agregar al final
    print_test("Lista fue creada:", lista != NULL);
    print_test("Agregar 5 al final:", lista_insertar_ultimo(lista, &vec[0]));
    print_test("Primer elemento es 5:", lista_ver_primero(lista) == &vec[0]);
    print_test("Agregar 8 al final:", lista_insertar_ultimo(lista, &vec[1]));
    print_test("Primer elemento continua siendo 5:", lista_ver_primero(lista) == &vec[0]);
    print_test("Agregar 13 al final:", lista_insertar_ultimo(lista, &vec[2]));
    print_test("Primer elemento continua siendo 5:", lista_ver_primero(lista) == &vec[0]);
    print_test("Agregar NULL es valido:", lista_insertar_ultimo(lista, NULL));
    print_test("Primer elemento continua siendo 5:", lista_ver_primero(lista) == &vec[0]);

    // Eliminar
    print_test("Eliminar 5:", lista_borrar_primero(lista) == &vec[0]);
    print_test("Primer elemento es 8:", lista_ver_primero(lista) == &vec[1]);
    print_test("Eliminar 8:", lista_borrar_primero(lista) == &vec[1]);
    print_test("Primer elemento es 13:", lista_ver_primero(lista) == &vec[2]);
    print_test("Eliminar 13:", lista_borrar_primero(lista) == &vec[2]);
    print_test("Primer elemento es NULL:", lista_ver_primero(lista) == NULL);
    print_test("Eliminar NULL:", lista_borrar_primero(lista) == NULL);

    // check vacio
    print_test("Lista esta vacia:", lista_esta_vacia(lista));

    // Agregar al principio
    print_test("Agregar 5 al principio:", lista_insertar_primero(lista, &vec[0]));
    print_test("Primer elemento es 5:", lista_ver_primero(lista) == &vec[0]);
    print_test("Agregar 8 al principio:", lista_insertar_primero(lista, &vec[1]));
    print_test("Primer elemento es 8:", lista_ver_primero(lista) == &vec[1]);
    print_test("Agregar 13 al principio:", lista_insertar_primero(lista, &vec[2]));
    print_test("Primer elemento es 13:", lista_ver_primero(lista) == &vec[2]);
    print_test("Agregar NULL es valido:", lista_insertar_primero(lista, NULL));
    print_test("Primer elemento es NULL:", lista_ver_primero(lista) == NULL);

    // Eliminar
    print_test("Eliminar NULL:", lista_borrar_primero(lista) == NULL);
    print_test("Primer elemento es 13:", lista_ver_primero(lista) == &vec[2]);
    print_test("Eliminar 13:", lista_borrar_primero(lista) == &vec[2]);
    print_test("Primer elemento es 8:", lista_ver_primero(lista) == &vec[1]);
    print_test("Eliminar 8:", lista_borrar_primero(lista) == &vec[1]);
    print_test("Primer elemento es 5:", lista_ver_primero(lista) == &vec[0]);
    print_test("Eliminar 5:", lista_borrar_primero(lista) == &vec[0]);
    // check vacio
    print_test("Lista esta vacia:", lista_esta_vacia(lista));
    lista_destruir(lista, NULL);
    printf(">>> Fin de etapa <<<\n");
}
void pruebas_lista_estudiante(void)
{
    pruebas_lista_vacia();
    pruebas_lista_elementos();
    // pruebas_lista_volumen_estatico();
    //pruebas_lista_volumen_dinamico();
    // pruebas_lista_destruccion();

    return;
}

#ifndef CORRECTOR

int main(void)
{
    pruebas_lista_estudiante();
    return failure_count() > 0; // Indica si falló alguna prueba.
}

#endif
