#include <stdlib.h>
#include <stdbool.h>
// EJERICIO 3
// Implementar para un árbol binario una primitiva size_t ab_sin_hermanos(const ab_t *ab) que devuelva la cantidad
// de nodos en el árbol que no tienen hermanos.
// Se considera que un nodo no tiene hermano si su nodo padre no tiene otro
// hijo.Indicar y justificar la complejidad de la primitiva implementada,
// y el tipo de recorrido utilizado.A efectos del ejercicio,
// la estructura del árbol es:

typedef struct ab
{
    struct ab *izq;
    struct ab *der;
    void *dato;
} ab_t;

size_t abb_sin_hermanos(const ab_t *ab)
{
    if (ab->izq == NULL && ab->der == NULL)
        return 0; //verde

    if (ab->izq == NULL && ab->der != NULL)
        return _abb_sin_heramanos(ab->izq, true); // naranja
    if (ab->izq != NULL && ab->der == NULL)
        return _abb_sin_heramanos(ab->der, true); // naranja

    if (ab->izq != NULL && ab->der != NULL)
        return abb_sin_hermanos(ab->der) + abb_sin_hermanos(ab->izq); //rojo
}
size_t _abb_sin_heramanos(const ab_t *ab, bool posible)
{

    if (ab->izq == NULL && ab->der == NULL)
        return 1;
    else
        return 0;
}
// EJERICIO 4
// Implementar, para un Hash Cerrado, una primitiva que dado un Hash, un número k y una función
// bool debe_duplicar_dato(const char *clave), y suponiendo que en el Hash todos los datos guardados
//  son de tipo puntero a entero, duplique el valor del dato guardado para las primeras k claves para
// las que la función debe_duplicar_dato devuelva true.En caso de que el Hash tenga menos de k elementos,
// multiplicar por 2 el dato guardado de todas las claves para las que debe_duplicar_dato devuelva true.
// Indicar y justificar la complejidad de la primitiva implementada.La firma de la primitiva deberá ser :
// bool duplicar_selectivo(const hash_t *hash, int k, bool (*debe_duplicar_dato)(const char *clave))

bool duplicar_selectivo(const hash_t *hash, int k, bool (*debe_duplicar_dato)(const char *clave))
{
    hash_iter_t *iter = hash_iter_crear(hash);

    if (hash->cantidad < k)
        k = hash->cantidad;

    for (int i = 0; i < k; i++)
    {
        char *clave_actual = hash_iter_ver_actual(iter);
        if (debe_duplicar_dato(clave_actual))
        {
            int *dato_actual = hash_obtener(hash, clave_actual);
            int dato_duplicado = 2 * (*dato_actual);
            if (!hash_guardar(hash, clave_actual, dato_duplicado))
            {
                hash_iter_destruir(iter);
                return false;
            }
        }
        if (!hash_iter_avanzar(iter))
        {
            hash_iter_destruir(iter);
            return false;
        }
    }
    hash_iter_destruir(iter);
    return true;
}
// Complejidad
/*
Todas las primitivas de hash son O(1) salvo destruir que es O(N) pero aca no se utiliza
La funcion es un ciclo lineal que recorre la cantidad k o bien la cantidad total de elementos en el hash, 
siendo esta cantidad N, la complejidad de esta primitiva O(N)
*/
