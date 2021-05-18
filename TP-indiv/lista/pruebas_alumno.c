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
    print_test("El ultimo elemento de la lista es NULL", lista_ver_ultimo(lista) == NULL);
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
    print_test("Se puede guardar null", lista_insertar_primero(lista, NULL));
    print_test("El primer dato es null", lista_ver_primero(lista) == NULL);
    print_test("El largo de la lista es 1", lista_largo(lista) == 1);
    print_test("Al eliminar el priermo de la lista, retorna NULL", lista_borrar_primero(lista) == NULL);
    print_test("Lista esta vacia:", lista_esta_vacia(lista));
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
void pruebas_lista_volumen_estatico(void)
{
    printf("\n>>>Inicio de pruebas de volumen estatico<<<\n");

    lista_t *lista = lista_crear();
    print_test("Lista fue creada:", lista != NULL);

    const size_t tam = 27182;
    size_t vec[tam];
    for (size_t i = 0; i < tam; i++)
    {
        vec[i] = tam - i;
    }
    //Agregar al principio
    bool ok = true;
    for (size_t i = 0; i < tam; i++)
    {
        ok &= lista_insertar_primero(lista, &vec[i]);
    }
    print_test("Se pudieron guardar todos los elementos", ok);

    //Eliminar
    size_t *v;
    size_t *primero;
    bool ok_primero = true;
    for (size_t i = 0; i < tam; i++)
    {
        v = lista_borrar_primero(lista);
        ok &= *v == vec[tam - i - 1];
        primero = lista_ver_primero(lista);
        if (primero != NULL)
            ok_primero &= *primero == vec[tam - i - 2];
    }
    print_test("Se eliminaron todos los elementos", lista_esta_vacia(lista));
    print_test("Los elementos se eliminaron en el orden correcto", ok_primero);
    print_test("Se conservo la invariante de lista", ok);

    lista_destruir(lista, NULL);
    printf(">>> Fin de etapa <<<\n");
}
void pruebas_lista_volumen_dinamico(void)
{
    printf("\n>>>Inicio de pruebas de volumen dinamico<<<\n");

    lista_t *lista = lista_crear();
    print_test("Lista fue creada:", lista != NULL);
    //crea vector dinamico
    size_t tam = 100;
    int **vec = malloc(tam * sizeof(size_t *));
    for (size_t i = 0; i < tam; i++)
    {
        vec[i] = malloc(sizeof(size_t));
        *vec[i] = 5;
    }
    //Agregar al principio
    bool ok = true;
    for (size_t i = 0; i < tam; i++)
    {
        ok &= lista_insertar_primero(lista, vec[i]);
    }
    print_test("Se pudieron insertar todos los elementos al principio exitosamente", ok);

    lista_destruir(lista, free);
    free(vec);

    lista = lista_crear();
    print_test("Lista fue creada:", lista != NULL);
    //crea vector dinamico

    vec = malloc(tam * sizeof(size_t *));
    for (size_t i = 0; i < tam; i++)
    {
        vec[i] = malloc(sizeof(size_t));
        *vec[i] = 5;
    }
    //Agregar al final

    for (size_t i = 0; i < tam; i++)
    {
        ok &= lista_insertar_ultimo(lista, vec[i]);
    }
    print_test("Se pudieron insertar todos los elementos al final exitosamente", ok);

    lista_destruir(lista, free);
    free(vec);

    printf(">>> Fin de etapa <<<\n");
}
void pruebas_lista_iterador_externo(void)
{
    printf("\n>>>Inicio de pruebas de iterador externo<<<\n");

    lista_t *lista = lista_crear();
    print_test("Lista fue creada:", lista != NULL);
    lista_iter_t *iter = lista_iter_crear(lista);
    print_test("El iterador fue creado:", iter != NULL);
    int vec[3] = {5, 8, 13};

    // Al insertar un elemento en la posición en la que se crea el iterador, efectivamente se inserta al principio.
    print_test("Se inserto un 5 correctamente", lista_iter_insertar(iter, &vec[0]));
    int *primero = lista_ver_primero(lista);
    print_test("El elemento insertado esta al prinicipio", *primero == vec[0]);
    print_test("El largo de la lista es 1", lista_largo(lista) == 1);

    //- Insertar un elemento cuando el iterador está al final efectivamente es equivalente a insertar al final.
    lista_iter_avanzar(iter);
    print_test("Iterador al final", lista_iter_al_final(iter));
    print_test("Se inserto un 8 correctamente", lista_iter_insertar(iter, &vec[1]));
    print_test("El largo de la lista es 2", lista_largo(lista) == 2);
    int *ultimo = lista_ver_ultimo(lista);
    print_test("El ultimo de la lista es un 8", *ultimo == vec[1]);

    //- Insertar un elemento en el medio se hace en la posición correcta.
    print_test("Se inserto un 13 entre el 5 y el 8 ", lista_iter_insertar(iter, &vec[2]));
    int *actual = lista_iter_ver_actual(iter);
    print_test("El 13 esta en la posicion actual", *actual == vec[2]);
    print_test("El largo de la lista es 3", lista_largo(lista) == 3);
    primero = lista_ver_primero(lista);
    ultimo = lista_ver_ultimo(lista);
    print_test("El primero es el 5", *primero == vec[0]);
    print_test("El ultimo es el 8", *ultimo == vec[1]);

    //- Verificar que al remover un elemento del medio, este no está.
    actual = lista_iter_borrar(iter);
    print_test("Se removio el 13 correctamente", *actual == vec[2]);
    print_test("El largo de la lista es 2", lista_largo(lista) == 2);

    //- Al remover el elemento cuando se crea el iterador, cambia el primer elemento de la lista.
    lista_iter_t *itera2 = lista_iter_crear(lista);
    print_test("Nuevo iterador fue creado:", itera2 != NULL);
    actual = lista_iter_borrar(itera2);
    print_test("Se removio el primer elemento de la lista", *actual == vec[0]);
    print_test("El largo de la lista es 1", lista_largo(lista) == 1);

    //- Remover el último elemento con el iterador cambia el último de la lista.
    ultimo = lista_ver_ultimo(lista);
    actual = lista_iter_borrar(itera2);
    print_test("Se removio el ultimo elemento de la lista", *actual == *ultimo);
    print_test("La lista esta vacia", lista_largo(lista) == 0);

    //Destruccion
    lista_iter_destruir(iter);
    lista_iter_destruir(itera2);
    lista_destruir(lista, NULL);

    //Pruebas de recorrido
    lista = lista_crear();
    print_test("Lista fue creada:", lista != NULL);
    iter = lista_iter_crear(lista);
    print_test("El iterador fue creado:", iter != NULL);

    const size_t tam = 27182;
    size_t vec2[tam];
    bool ok_insertar = true;
    bool ok_largo = true;

    for (size_t i = 0; i < tam; i++)
    {
        vec2[i] = tam - i;
        ok_insertar &= lista_iter_insertar(iter, &vec2[i]);
        ok_largo &= lista_largo(lista) == i + 1;
    }
    print_test("Se insertaron todos los elementos de manera correcta", ok_insertar);
    print_test("El largo de la lista se actualizo correctamente", ok_largo);
    bool ok_avanzar = true;
    while (!lista_iter_al_final(iter))
    {

        ok_avanzar &= lista_iter_avanzar(iter);
    }
    print_test("El iterador recorre correctamente", ok_avanzar);
    print_test("El iterador esta al final de la lista", lista_iter_al_final(iter));

    //Destruccion
    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);
    printf(">>> Fin de etapa <<<\n");
}
bool ver_elemento_sin_corte(void *dato, void *extra)
{
    printf("%zu\n", *(size_t *)dato);
    return true;
}
bool ver_elemento_con_corte(void *dato, void *corte)
{
    if (*(size_t *)corte > 0)
    {
        printf("%zu:\t%zu\n", (*(size_t *)corte)--, *(size_t *)dato);

        return true;
    }
    else
    {
        return false;
    }
}
void pruebas_lista_iterador_interno(void)
{
    printf("\n>>>Inicio de pruebas de iterador externo<<<\n");
    lista_t *lista = lista_crear();
    print_test("Lista fue creada:", lista != NULL);
    lista_iter_t *iter = lista_iter_crear(lista);
    print_test("El iterador fue creado:", iter != NULL);

    const size_t tam = 27;
    size_t vec[tam];
    bool ok = true;
    for (size_t i = 0; i < tam; i++)
    {
        vec[i] = tam - i;
        ok &= lista_insertar_ultimo(lista, &vec[i]);
    }

    print_test("Se pudieron insertar todos los elementos al final exitosamente", ok);
    size_t corte = 5;

    lista_iterar(lista, ver_elemento_sin_corte, NULL);
    lista_iterar(lista, ver_elemento_con_corte, &corte);
    //Destruccion
    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);
    printf(">>> Fin de etapa <<<\n");
}
void pruebas_lista_estudiante(void)
{

    pruebas_lista_vacia();
    pruebas_lista_elementos();
    pruebas_lista_volumen_estatico();
    pruebas_lista_volumen_dinamico();
    pruebas_lista_iterador_externo();
    pruebas_lista_iterador_interno();

    return;
}

#ifndef CORRECTOR

int main(void)
{
    pruebas_lista_estudiante();
    return failure_count() > 0; // Indica si falló alguna prueba.
}

#endif
