#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <inttypes.h>
#include "strutil.h"
#include "pila.h"
#include "calc_helper.h"

#define MAX_LINE_SIZE 32
#define MSG_ERR "ERROR"
#define ERR_NO_MEMORY "Memoria insuficiente\n"

bool get_line(char *line, FILE *file);
bool compute_line(char **level, pilanum_t *stack);
bool compute(pilanum_t *stack, char *operator);
bool read_line(char **line, FILE *file);
int main(void)
{

    char *line = malloc(sizeof(char) * MAX_LINE_SIZE);
    //char *line = NULL;
    FILE *fi = stdin;
    FILE *fo = stdout;
    calc_num result;
    while (get_line(line, fi))
    {
        pilanum_t *stack = pilanum_crear();
        if (stack == NULL)
        {
            fprintf(stderr, ERR_NO_MEMORY);
            return 1;
        }
        if (strtok(line, "\n"))

        {
            char **line_data = malloc(sizeof(char *) * MAX_LINE_SIZE);

            line_data = dc_split(line); //pide memeoria

            if (compute_line(line_data, stack))
            {
                desapilar_num(stack, &result);
                if (pila_esta_vacia(stack))
                {
                    fprintf(fo, "%" PRId64 "\n", result);
                }
                else
                {
                    fprintf(fo, "%s\n", MSG_ERR);
                    pila_destruir(stack);
                    stack = pilanum_crear();
                }
            }
            else
            {
                fprintf(fo, "%s \n", MSG_ERR);
                pila_destruir(stack);
                stack = pilanum_crear();
            }

            free_strv(line_data);
        }
        pila_destruir(stack);
    }
    free(line);
    return 0;
}
bool read_line(char **line, FILE *file)
{
    char *aux;
    size_t len = 0;
    size_t read;
    read = getline(&aux, &len, file);
    if (read < 0)
    {
        return false;
    }
    if (aux[read - 1] == '\n')
    {
        aux[read - 1] = '\0';
        return true;
    }
    *line = aux;
    return true;
}
bool get_line(char *line, FILE *file)
{

    return fgets(line, MAX_LINE_SIZE, file) != NULL;
}

bool compute_line(char **level, pilanum_t *stack)
{

    struct calc_token tok;
    size_t i = 0;
    bool ok = true;

    while (level[i] != NULL && ok == true)
    {

        if (strcmp(level[i], "\n") != 0 && !calc_parse(level[i], &tok))
        {
            return false;
        }
        if (tok.type == TOK_NUM)
        {
            apilar_num(stack, tok.value);
        }

        if (tok.type == TOK_OPER)
        {
            ok &= compute(stack, level[i]);
            if (!ok)
                return ok;
        }
        i++;
    }

    return ok;
}

bool compute(pilanum_t *stack, char *operator)
{

    calc_num x, y, z;

    if (strcmp(operator, "+") == 0)
    {

        if (desapilar_num(stack, &x) && desapilar_num(stack, &y))
        {
            apilar_num(stack, y + x);
        }
        else
            return false;
    }
    else if (strcmp(operator, "-") == 0)
    {
        if (desapilar_num(stack, &x) && desapilar_num(stack, &y))
        {
            apilar_num(stack, y - x);
        }
        else
            return false;
    }
    else if (strcmp(operator, "*") == 0)
    {
        if (desapilar_num(stack, &x) && desapilar_num(stack, &y))
        {
            apilar_num(stack, y * x);
        }
        else
            return false;
    }
    else if (strcmp(operator, "/") == 0)
    {
        if (desapilar_num(stack, &x) && desapilar_num(stack, &y))
        {
            if (x != 0)
            {
                apilar_num(stack, y / x);
            }
            else
                return false;
        }
        else
            return false;
    }
    else if (strcmp(operator, "^") == 0)
    {
        if (desapilar_num(stack, &x) && desapilar_num(stack, &y))
        {
            apilar_num(stack, pow((double)y, (double)x));
        }
        else
            return false;
    }
    else if (strcmp(operator, "sqrt") == 0)
    {
        if (desapilar_num(stack, &x))
        {
            if (x >= 0)
            {
                apilar_num(stack, sqrt((double)x));
            }
            else
                return false;
        }
    }
    else if (strcmp(operator, "log") == 0)
    {
        if (desapilar_num(stack, &x) && desapilar_num(stack, &y))
        {
            if (x >= 2)
            {
                apilar_num(stack, (log((double)y) / log((double)x)));
            }
            else
                return false;
        }
        else
            return false;
    }
    else if (strcmp(operator, "?") == 0)
    {
        if (desapilar_num(stack, &x) && desapilar_num(stack, &y) && desapilar_num(stack, &z))
        {
            apilar_num(stack, (z) ? y : x);
        }
        else
            return false;
    }
    else
    {

        return false;
    }

    return true;
}
