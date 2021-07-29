#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*
1. Durante junio, un equipo de desarrolladores realizó muchos cambios en su proyecto, con la genial idea de ejecutar las pruebas recién el 30 de junio. Tuvieron la suerte que tan sólo una de las pruebas haya fallado (de las 10 millones de pruebas automáticas que tienen). El problema es que necesitan saber cuál cambio fue el que produjo el error. Lo que saben es que al
“día 0” (31 de mayo) todas las pruebas corrían correctamente. Algo en el medio tuvo que haberlo roto.
Implementarunalgoritmocambio_t* encontrar_causante(cambio_t** cambios, size_t n, bool (*prueba)(cambio_t**, size_t)) que reciba un arreglo de cambios (un TDA que es irrelevante como está implementado) y (por división y conquista) devuelva cuál fue el cambio exacto que rompió el test. La función prueba recibe un arreglo con cambios
y devuelve true si la prueba pasa correctamente, false en caso contrario. Es importante notar los cambios son secuencialmente dependientes (no puede pasar las pruebas el cambio número K sin pasar todos los los K-1 anteriores). Asumiendo que la ejecución de la prueba se realiza en tiempo lineal a la cantidad de cambios (pues hay que aplicarlos), el algoritmo a implementar debe ejecutar en tiempo lineal a la cantidad de cambios introducidos. Justificar la complejidad
del algoritmo implementado
*/
cambio_t *encontrar_causante(cambio_t **cambios, size_t n, bool (*prueba)(cambio_t **, size_t))
{
    if (prueba(cambios, n))
        return NULL;
    if (prueba(cambios, 1))
        return cambios[0];

    return _encontrar_causante(cambios, 0, n - 1, prueba);
}

cambio_t *_encontrar_causante(cambio_t **cambios, size_t i, size_t f, bool (*prueba)(cambio_t **, size_t))
{
    if (prueba(cambios, 1)) //el caso base es que la primera poscion del arreglo sea la falla
        return cambios[i];

    size_t medio = (f + i) / 2;
    //si el cambio no es el primero, me fijo en que mitad del arreglo se encuentra la falla
    // llamo recursivamente a para el sub arreglo donde este la falla
    if (!prueba(cambios, m))
        return _encontrar_causante(cambios, i, m, prueba );
    if (!prueba(&cambios[m], f - m))
        return _encontrar_causante(cambios, m + 1, f, prueba );
}
//ORDEN: Por teorema maestro: l
// - la cantidad de llamados recursivos a la vez es 1.
// - la cantidad de partes iguales en las que se divide el problema es 2.
// - el orden N^x de las operaciones fuera de las llamadas recursivas es la ejecucion de la funcion de prueba por lo que x=1 (lineal)
// -> Por lo tanto el orden del algoritmo es O(n) lineal con n siendo la cantidad de cambios en el arreglo.
/*

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
2. Dada una cola de enteros, escribir una funcion que determine si es piramidal. 
Una cola de enteros es piramidal si cada elemento es menor a su elemento siguiente 
(en el sentido que va desde el inicio de la cola hacia el otro extremo). La cola debe quedar en el mismo estado que antes de ejecutada la función.
Indicar el orden del algoritmo propuesto.
*/
bool es_piramidal(cola_t *cola)
{

    pila_t *pila = pila_crear();

    size_t *aux = cola_desencolar(cola);
    bool ok = true;
    while (!cola_esta_vacia(cola)) //desencola toda la cola
    {
        if (*aux >= cola_ver_tope(cola)) // en este caso la pila no es piramidal
        {
            ok &= false;
            break;
        }
        pila_apilar(pila, aux);
        aux = cola_desencolar(cola);
    }
    cola_encolar(cola, aux);
    while (!pila_esta_vacia(pila)) // la vuelve a armar
    {
        cola_encolar(cola, pila_desapilar(pila));
    }
    pila_destruir(pila);
    return ok;
}
// ORDEN: la cola se desarma y se vuelve a armar por completo en el peor de los casos de no piramidal, o cuando es piramidal.
//  En todo momento es linealmente dependietne con la cantidad de elementos del la cola, por lo tanto es O(n) con n la cantidad
// de elemento de la cola
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
3. Implementar el TDA Mamushka (matrioshka, o muñeca rusa), teniendo en cuenta que una Mamushka puede tener otra Mamushka dentro de si misma. Las primitivas deben ser:
mamushka_t* mamushka_crear(size_t tam, color_t color): Crea una mamushka con un tamaño y color definido. color_t mamushka_obtener_color(mamushka_t* mamushka): 
Obtiene el color de la Mamushka.
bool mamushka_guardar(mamushka_t* contenedora, mamushka_t* a_guardar): Intenta guardar la segunda ma- mushka en la primera. Si la primera ya tiene una mamushka guardada, 
entonces debe intentar guardar la mamushka a_guardar dentro de la mamushka que ya estaba guardada. La operación falla (y devuelve false) si en algún momento se intenta 
guardar una mamushka en otra de menor o igual tamaño. Por ejemplo: si tenemos una mamushka de tamaño 10 que dentro tiene una de tamaño 8, y se intenta guardar una de tamaño 5, 
ésta debe guardarse dentro de la de tamaño 8. Si, luego, se intentara guardar una de tamaño 6, la operación debe fallar dado que no se puede guardar una mamushka de tamaño 6 
dentro de una de tamaño 5.
mamushka_t* mamushka_obtener_guardada(mamushka_t*): Devuelve la mamushka guardada. NULL en caso de no tener ninguna guardada. En el ejemplo anterior, si utilizaremos esta 
primitiva con la Mamushka de tamaño 10, nos devolvería la Mamushka de tamaño 8 que guardamos (y que dentro tiene la de tamaño 5).
void mamushka_destruir(mamushka_t*): Destruye la mamushka (y todas las que se encuentren dentro).
Definir la estructura (struct) del TDA, y escribir estas 5 primitivas. Indicar el orden de cada una de ellas. Nota: color_t corresponde a un typedef enum color color_t, 
que está definido en algún lugar.
*/
typedef struct mamushka
{
    color_t color;
    size_t tam;
    struct mamushka *hija;
} mamushka_t;
//Crea una mamushka con un tamaño y color definido.
mamushka_t *mamushka_crear(size_t tam, color_t color)
{
    mamushka_t *m = malloc(sizeof(mamushka_t));
    if (!m)
        return NULL;
    m->color = color;
    m->tam = tam;
    m->hija = NULL;
    return m;
}
// Obtiene el color de la Mamushka.
color_t mamushka_obtener_color(mamushka_t *mamushka)
{
    return mamushka->color;
}
// Intenta guardar la segunda mamushka en la primera.Si la primera ya tiene una mamushka guardada,
// entonces debe intentar guardar la mamushka a_guardar dentro de la mamushka que ya estaba guardada.
// La operación falla(y devuelve false) si en algún momento se intenta guardar una mamushka en otra
// de menor o igual tamaño.Por ejemplo : si tenemos una mamushka de tamaño 10 que dentro tiene una
// de tamaño 8, y se intenta guardar una de tamaño 5, ésta debe guardarse dentro de la de tamaño 8.
// Si, luego, se intentara guardar una de tamaño 6, la operación debe fallar dado que no se puede
// guardar una mamushka de tamaño 6 dentro de una de tamaño 5.
bool mamushka_guardar(mamushka_t *contenedora, mamushka_t *a_guardar)
{
    if (contenedora->tam <= a_guardar->tam)
        return false;
    if (contenedora->hija == NULL)
    {
        contenedora->hija = a_guardar;
        return true;
    }
    else
    {
        return mamushka_guardar(contenedora->hija, a_guardar);
    }
}
// Devuelve la mamushka guardada.NULL en caso de no tener ninguna guardada.En el ejemplo anterior,
// si utilizaremos esta primitiva con la Mamushka de tamaño 10, nos devolvería la Mamushka de tamaño 8
// que guardamos(y que dentro tiene la de tamaño 5).
mamushka_t *mamushka_obtener_guardada(mamushka_t *mamushka)
{
    return (mamushka != NULL) ? mamushka->hija : NULL; // se crea con NULL si no tienen nada guardado
}
// Destruye la mamushka(y todas las que se encuentren dentro).
void mamushka_destruir(mamushka_t *mamushka)
{
    if (mamushka->hija != NULL)
        mamushka_destruir(mamushka->hija);
    free(mamushka);
}
