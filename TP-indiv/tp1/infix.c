#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include "strutil.h"
#include "calc_helper.h"
#include "pila.h"
#include "cola.h"

#define MAX_LINE_SIZE 100000
#define MSG_ERR "ERROR"

bool get_line(char *line, FILE *file);
bool process_line(char **level, cola_t *queue);
bool get_line(char *line, FILE *file);
unsigned precedencia(char *op);

int main(void)
{
    FILE *fi = stdin;
    FILE *fo = stdout;
    cola_t *queue = cola_crear();
    char *line = malloc(sizeof(char) * MAX_LINE_SIZE);

    while (get_line(line, fi))
    {
        char **line_data = malloc(sizeof(char *) * MAX_LINE_SIZE);
        line_data = infix_split(line); //pide memeoria

        if (process_line(line_data, queue))
        {
            while (!cola_esta_vacia(queue))
            {
                fprintf(fo, "%s ", (char *)cola_desencolar(queue));
            }
            fprintf(fo, "\n");
        }
        else
        {
            fprintf(fo, "%s\n", MSG_ERR);
        }

        free_strv(line_data);
    }
    free(line);

    cola_destruir(queue, NULL);
    return 0;
}

bool get_line(char *line, FILE *file)
{
    return fgets(line, MAX_LINE_SIZE, file) != NULL;
}

bool process_line(char **level, cola_t *queue)
{
    pila_t *stack = pila_crear();
    struct calc_token tok;
    size_t i = 0;
    bool ok = true;
    while (level[i] != NULL && ok == true)
    {

        if (!calc_parse(level[i], &tok))
        {
            return false;
        }
        if (tok.type == TOK_NUM)
        {
            cola_encolar(queue, level[i]);
        }
        if (tok.type == TOK_LPAREN)
        {
            pila_apilar(stack, level[i]);
        }

        if (tok.type == TOK_OPER)
        {
            if (tok.oper.op != OP_POW)
            {
                while (!pila_esta_vacia(stack) && tok.oper.precedencia <= precedencia((char *)pila_ver_tope(stack)))
                {

                    ok &= cola_encolar(queue, pila_desapilar(stack));
                }
            }
            pila_apilar(stack, level[i]);
        }
        if (tok.type == TOK_RPAREN)
        {
            while (!pila_esta_vacia(stack) && *(char *)pila_ver_tope(stack) != '(')
            {
                ok &= cola_encolar(queue, pila_desapilar(stack));
            }
            pila_desapilar(stack); //desecho el (
        }
        i++;
    }
    while (!pila_esta_vacia(stack))
    {
        if (*(char *)pila_ver_tope(stack) != '(')
            ok &= cola_encolar(queue, pila_desapilar(stack));
        else
            pila_desapilar(stack);
    }
    pila_destruir(stack);
    return ok;
}
unsigned precedencia(char *op)
{
    char s = *op;
    if (s == '+')
        return 1;
    else if (s == '-')
        return 2;
    else if (s == '*')
        return 3;
    else if (s == '/')
        return 4;
    else if (s == '^')
        return 5;
    return 0;
}
