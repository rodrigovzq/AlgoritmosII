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

    int a = 8, b = 2, c = 1, d = 5, e = 10, f = 6, g = 14;
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
