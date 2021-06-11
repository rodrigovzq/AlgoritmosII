#define _POSIX_C_SOURCE 200809L
#include "strutil.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define EOS '\0'

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
    char *end;
    char sep_str[2] = {sep, EOS};
    for (size_t i = 0; strv[i] != NULL; i++)
    {
        total_size = total_size + strlen(strv[i]) + 1;
        cant_str++;
    }

    char *string = calloc((1 + total_size + cant_str), sizeof(char));
    if (!string)
        return NULL;
    //string[0] = EOS; //para que ande stp en el principio
    end = string;
    size_t i = 0;
    while (i < cant_str)
    {
        if (i > 0)
            end = stpcpy(end, sep_str);

        end = stpcpy(end, strv[i]);

        i++;
        /* es lento
        strcat(string, strv[i]);
        if (i < cant_str - 1)
            strncat(string, &sep, 1);
        */
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
