#include "heap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For size_t in Linux.

int cmp_int(const void *a, const void *b)
{
    if (*(int *)a > *(int *)b)
        return 1;
    if (*(int *)a == *(int *)b)
        return 0;
    return -1;
}
int main(void)
{

    int a = 1, b = 8, c = 5, d = 2, e = 5, f = 7, g = 6;
    void *arr[] = {&a, &b, &c, &d, &e, &f, &g};
    for (int i = 0; i < 7; i++)
        printf("%i ", *(int *)arr[i]);
    printf("\n");
    heap_sort(arr, 7, (cmp_func_t)cmp_int);
    for (size_t i = 0; i < 7; i++)
    {
        printf("%i ", *(int *)arr[i]);
    }
    printf("\n");

    // heap_destruir(heap, free);
}
