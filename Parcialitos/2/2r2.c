#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"

// 2. Se tiene un hash abierto implementado con la siguiente estructura :

typedef struct hash
{
    lista_t **tabla;
    size_t m;
} hash_t;
typedef struct campo
{
    const char *clave;
    void *dato;
} campo_t;

// Implementar la primitiva bool hash_contiene_valor(const hash_t *, void *) que devuelva verdadero o falso de acuerdo
//  a si el hash almacena alguna clave con el valor pasado por parámetro(sin usar iteradores del hash, ya que se trata de
//  una primitiva), sabiendo que : El miembro tabla del hash es un arreglo de tamaño m de listas enlazadas.Cada lista
//  contiene elementos de tipo campo_t *.

bool hash_contiene_valor(const hash_t *hash, void *dato)
{
    //quiero ver si el dato esta asociado a alguna clave del hash

    for (size_t i = 0; i < hash->m; i++)
    {
        lista_iter_t *iter = lista_iter_crear(hash->tabla[i]);
        while (!lista_iter_al_final(iter)) // en el caso de que no haya lista en ese campo asumo que lista_iter_al_final devolvera true
        {
            campo_t *campo = lista_iter_ver_actual(iter);
            if (campo->dato == dato)
            {
                lista_iter_destruir(iter);
                return true;
            }
            lista_iter_avanzar(iter);
        }
        lista_iter_destruir(iter);
    }
    return false;
}
// Esta primitiva debe recorrer (en el pero de los casos, todos) los elementos del hash.
// El orden es O(n) siendo n la cantidad de elementos almacenados en el hash.
