// 2 4 7

#include <stdlib.h>
#include <stdbool.h>

/*
2- Dado un juego de 2 jugadores, donde cada jugador tiene N cartas y se juega a K rondas. En
cada ronda los jugadores juegan la carta más grande, y gana quien tenga la mayor, luego los
jugadores descartan la carta jugada. Al finalizar las K rondas, el ganador es el jugador que
haya ganado más rondas. Se desea implementar una función:
int obtener_ganador(int* cartas_1, int* cartas_2, size_t n, size_t k);
Donde cartas_1 representa un array con los valores de las cartas del jugador 1, cartas_2
representa un array con los valores de las cartas del jugador 2, n es la cantidad de cartas de
cada jugador y k es la cantidad de rondas. La función debe devolver 1 si gana el jugador 1, -1
si pierde el jugador 1 o 0 en caso de empate.
Dar y justificar la complejidad, no puede ser mayor a O(n + k log n)
*/
int obtener_ganador(int *cartas_1, int *cartas_2, size_t n, size_t k)
{

    size_t puntos1 = 0, puntos2 = 0; //1 por ronda ganada

    heap_t *h1 = heap_crear(comparar_enteros); //uso heap de maximos
    heap_t *h2 = heap_crear(comparar_enteros);

    for (size_t i = 0; i < n; i++)
    {
        heap_encolar(h1, cartas_1[i]);
        heap_encolar(h2, cartas_2[i]);
    } // ORDEN -> O(n)

    for (size_t i = 0; i < k && i < n; i++)
    {
        // O(log n)
        int jugada = comparar_enteros(*heap_desencolar(h1), *heap_desencolar(h2)); //siempre descartan la carta jugada
        if (jugada > 0)
            puntos1++;
        else if (jugada < 0)
            puntos2++;
    } // ORDEN -> O(k log n)

    heap_destruir(h1);
    heap_destruir(h2);

    return comparar_enteros(puntos1, puntos2);
}
// El orden del algoritmo es O(n + klog n) porque al encolar en el heap los n elementos de los arreglos, es de orden O(n)
// Luego se desencola con orden O(log n) dentro de un ciclo de k repeticiones. Por lo que en total resultaria O(n+ klog n)
int comparar_enteros(int a, int b)
{

    if (a > b)
        return 1;
    if (a < b)
        return -1;
    return 0;
}
