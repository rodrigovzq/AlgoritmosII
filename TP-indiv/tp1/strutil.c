#include "strutil.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define EOS '\0'
#define _POSIX_C_SOURCE 200809L

char *substr(const char *str, size_t n)
{
    char *substr = malloc(sizeof(char *));

    if (substr == NULL)
        return NULL;

    if (n != 0)
        strncpy(substr, str, n);
    substr[n] = EOS;

    return substr;
}

char **split(const char *str, char sep)
{
    size_t f = 0, i = 0;
    size_t strcount = 0;
    char *aux[strlen(str)];
    while (str[f] != EOS)
    {
        if (str[f] == sep)
        {
            aux[strcount++] = substr(str + i, f - i);
            i = ++f;
        }
        else
            f++;
    }
    printf("i=%zu\n", i);
    aux[strcount++] = substr(str + i, f - i);
    printf("cantidad de palabras luego de split %zu \n", strcount);
    char **spltstr = malloc(strcount * sizeof(char *) + 1);
    for (i = 0; i < strcount; i++)
    {
        spltstr[i] = aux[i];
    }

    return spltstr;
}

char *join(char **strv, char sep)
{

    size_t total_size = 0;
    size_t cant_str = 0;
    for (size_t i = 0; strv[i] != NULL; i++)
    {
        total_size = total_size + strlen(strv[i]);
        //printf("total size %zu es %zu\n", i, total_size);
        cant_str++;
    }

    //printf("Join: cantidad de palabras %zu\n", cant_str);
    char *string = calloc((total_size + cant_str), sizeof(char));
    //printf("Join: allocated %zu\n", total_size + cant_str);

    for (size_t i = 0; i < cant_str; i++)
    {
        //printf("%s\t", strv[i]);
        strcat(string, strv[i]);
        if (i < cant_str - 1) //pone separador en todas las intersecciones menos la ultima
            strncat(string, &sep, 1);
        //printf("%s\n", string);
    }
    //printf("%s\n", string);
    //printf("Join: cant de caracteres %zu\n", strlen(string));
    return string;
}
void free_strv(char *strv[])
{

    for (size_t i = 0; strv[i] != NULL; i++)
    {
        printf("liberando %s\n", strv[i]);
        free(strv[i]);
    }
    printf("libero puntero\n");
    free(strv);
}
