#include "strutil.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define EOS '\0'
#define _POSIX_C_SOURCE 200809L

char *substr(const char *str, size_t n)
{
    char *substr = malloc(sizeof(char *) * (n + 1));

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
    char **spltstr = malloc((strlen(str) + 2) * sizeof(char *));

    while (str[f] != EOS)
    {
        if (str[f] == sep)
        {
            spltstr[strcount++] = substr(str + i, f - i);
            i = ++f;
        }
        else
            f++;
    }
    spltstr[strcount++] = substr(str + i, f - i);
    spltstr[strcount] = NULL;

    return spltstr;
}

char *join(char **strv, char sep)
{

    size_t total_size = 0;
    size_t cant_str = 0;
    for (size_t i = 0; strv[i] != NULL; i++)
    {
        total_size = total_size + strlen(strv[i]);
        cant_str++;
    }

    char *string = calloc((total_size + cant_str), sizeof(char));

    for (size_t i = 0; i < cant_str; i++)
    {
        strcat(string, strv[i]);
        if (i < cant_str - 1)
            strncat(string, &sep, 1);
    }

    return string;
}
void free_strv(char *strv[])
{
    for (size_t i = 0; strv[i] != NULL; i++)
    {
        free(strv[i]);
    }

    free(strv);
}
