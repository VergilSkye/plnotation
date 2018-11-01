
#include <stdio.h>
#include <string.h>

#include "Utilidades.h"
#include "stack.h"
#define MAX_CHARS 10000

// safe_usub -- perform safe unsigned subtraction
size_t safe_usub(size_t x, size_t y)
{
    return x > y ? x - y : y - x;
}
//Reverter uma string;
char *strrev(const char *const str)
{
    if (!str)
    {
        return NULL;
    }

    size_t len = strnlen(str, MAX_CHARS);
    char *new = malloc(sizeof(char) * len);

    size_t i;
    for (i = 0; i < len; i++)
    {
        new[i] = str[safe_usub(i + 1, len)];
    }

    new[i] = 0;

    return new;
}
//Adiciona no final de um ponteiro de char um caracteer
void append(char *s, char c)
{
    int len = strlen(s);
    s[len] = c;
    s[len + 1] = '\0';
}

