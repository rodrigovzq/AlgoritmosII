#include "testing.h"
#include "strutil.h"
#include <stdio.h>
#include <stdlib.h>
void pruebas_split(void)
{
    char *test = "hola,como,estas";
    print_test("caso 1", true);
    char **splitted = split(test, ',');
    for (size_t i = 0; i < 3; i++)
    {
        printf(">> %s\n", splitted[i]);
    }
    free_strv(splitted);

    print_test("caso 2", true);
    splitted = split("hola,,como", ',');
    for (size_t i = 0; i < 3; i++)
    {
        printf(">> %s\n", splitted[i]);
    }
    free_strv(splitted);

    print_test("caso 3", true);
    splitted = split("hola,como,", ',');
    for (size_t i = 0; i < 3; i++)
    {
        printf(">> %s\n", splitted[i]);
    }
    free_strv(splitted);

    print_test("caso 4", true);
    splitted = split(",hola,como", ',');
    for (size_t i = 0; i < 3; i++)
    {
        printf(">> %s\n", splitted[i]);
    }
    free_strv(splitted);

    print_test("caso 5", true);
    splitted = split("hola", ',');
    printf(">> %s\n", splitted[0]);
    free_strv(splitted);

    print_test("caso 6", true);
    splitted = split("", ',');
    printf(">> %s\n", splitted[0]);
    free_strv(splitted);

    print_test("caso 7", true);
    splitted = split("", ',');

    for (size_t i = 0; i < 1; i++)
    {
        printf(">> %s\n", splitted[i]);
    }

    free_strv(splitted);
}

void pruebas_join(void)
{
    char *test = "Hola Mundo";
    char **strv = split(test, ' ');
    //printf("%s\n%s\n%s\n", strv[0], strv[1], strv[2]);
    char *resultado = join(strv, ';'); // "abc;def;ghi"
    printf("original: %s, nuevo: %s\n", test, resultado);
    free_strv(strv);
    free(resultado);

    test = "";
    strv = split(test, ',');

    resultado = join(strv, ','); // "Hola,mundo
    printf("original %s\n", test);
    printf("nuevo %s\n", resultado);
    free_strv(strv);
    free(resultado);
}

void pruebas_string_estudiante(void)
{
    //pruebas_split();
    pruebas_join();

    return;
}
#ifndef CORRECTOR

int main(void)
{
    pruebas_string_estudiante();
    return failure_count() > 0; // Indica si falló alguna prueba.
}

#endif
