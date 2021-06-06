#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include "strutil.h"
#include "pila.h"
#include "calc_helper.h"

#define MAX_LINE_SIZE 32
#define MSG_ERR "ERROR"

bool get_line(char *line, FILE *file);
bool parse_line(char **level, pilanum_t *stack, char **operators);
bool compute_line(pilanum_t *stack, char **operators);
int main(void)
{

    char *line = malloc(sizeof(char) * MAX_LINE_SIZE);

    FILE *fi = stdin;
    FILE *fo = stdout;
    calc_num result;
    pilanum_t *stack = pilanum_crear();
    //if (stack == NULL)
    //    return 1; //TODO: poner error
    //int i = 1;
    while (get_line(line, fi))
    {
        char **line_data = malloc(sizeof(char *) * MAX_LINE_SIZE);
        line_data = dc_split(line);
        char **operators = malloc(sizeof(char *) * MAX_LINE_SIZE);
        // lee linea, llena stack con operandos y arreglo con operadores
        parse_line(line_data, stack, operators);

        // el stack queda completo con los resultados

        if (compute_line(stack, operators))
        {
            desapilar_num(stack, &result);
            fprintf(fo, "%lli\n", result);
        }
        else
        {
            fprintf(fo, "%s\n", MSG_ERR);
        }
        //free(line);
        free_strv(line_data);
        //printf("cul\n");
        free_strv(operators);
    }
    pila_destruir(stack);
    return 0;
}

bool get_line(char *line, FILE *file)
{
    return fgets(line, MAX_LINE_SIZE, file) != NULL;
}

bool parse_line(char **level, pilanum_t *stack, char **operators)
{

    struct calc_token tok;
    size_t i = 0, j = 0;

    while (level[i] != NULL) // -> revisar condicion de paro
    {

        if (!calc_parse(level[i], &tok))
        {
            return false;
        }
        if (tok.type == TOK_NUM)
        {
            apilar_num(stack, tok.value);
        }

        if (tok.type == TOK_OPER)
        {
            operators[j] = calloc(4, sizeof(char));
            strcpy(operators[j++], level[i]);
            //printf("%s\n", operators[j - 1]);
        }
        i++;
    }

    operators[j] = NULL;
    return true;
}

bool compute_line(pilanum_t *stack, char **operators)
{

    size_t i = 0;
    calc_num x, y, z;

    while (operators[i] != NULL)
    {

        if (strcmp(operators[i], "+") == 0)
        {

            if (desapilar_num(stack, &x) && desapilar_num(stack, &y))
            {
                apilar_num(stack, y + x);
            }
            else
                return false;
        }
        else if (strcmp(operators[i], "-") == 0)
        {
            if (desapilar_num(stack, &x) && desapilar_num(stack, &y))
            {
                apilar_num(stack, y - x);
            }
            else
                return false;
        }
        else if (strcmp(operators[i], "*") == 0)
        {
            if (desapilar_num(stack, &x) && desapilar_num(stack, &y))
            {
                apilar_num(stack, y * x);
            }
            else
                return false;
        }
        else if (strcmp(operators[i], "/") == 0)
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
        else if (strcmp(operators[i], "^") == 0)
        {
            if (desapilar_num(stack, &x) && desapilar_num(stack, &y))
            {
                apilar_num(stack, (calc_num)pow(y, x));
            }
            else
                return false;
        }
        else if (strcmp(operators[i], "sqrt") == 0)
        {
            if (desapilar_num(stack, &x))
            {
                if (x > 0)
                {
                    apilar_num(stack, (calc_num)sqrt(x));
                }
                else
                    return false;
            }
        }
        else if (strcmp(operators[i], "log") == 0)
        {
            if (desapilar_num(stack, &x) && desapilar_num(stack, &y))
            {
                if (x >= 2)
                {
                    apilar_num(stack, (calc_num)(log(y) / log(x)));
                }
                else
                    return false;
            }
            else
                return false;
        }
        else if (strcmp(operators[i], "?") == 0)
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
        i++;
    }

    return true;
}
