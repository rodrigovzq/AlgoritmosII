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

#define MAX_LINE_SIZE 1000
#define MSG_ERR "ERROR"
#define ERR_NO_MEMORY "Memoria insuficiente\n"

bool get_line(char *line, FILE *file);
bool compute_line(char **level, pilanum_t *stack);
bool compute(pilanum_t *stack, char *operator);
bool read_line(char **line, FILE *file);
int main(void)
{

    char *line = malloc(sizeof(char) * MAX_LINE_SIZE);
    FILE *fi = stdin;
    FILE *fo = stdout;
    calc_num result, t;
    while (get_line(line, fi))
    {
        if (line[0] == '\n')
        {
            continue;
        }
        line[strlen(line) - 1] = '\0';

        pilanum_t *stack = pilanum_crear();
        if (stack == NULL)
        {
            fprintf(fo, ERR_NO_MEMORY);
            return 1;
        }
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
            }
        }
        else
        {
            fprintf(fo, "%s \n", MSG_ERR);
        }
        free_strv(line_data);
        while (!pila_esta_vacia(stack))
            desapilar_num(stack, &t);
        pila_destruir(stack);
    }
    free(line);
    return 0;
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
                return false;
        }
        i++;
    }
    if (level[i] != NULL)
        return false;
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
            if (x >= 0)
            {
                apilar_num(stack, pow((double)y, (double)x));
            }
            else
                return false;
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
        else
            return false;
    }
    else if (strcmp(operator, "log") == 0)
    {
        if (desapilar_num(stack, &x) && desapilar_num(stack, &y))
        {
            if (x > 0 && x != 1)
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
