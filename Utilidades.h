#ifndef UTILIDADES_H_INCLUDED
#define UTILIDADES_H_INCLUDED


//Subtração segura, faz uma subtração para tipo unsigned, positivo
size_t safe_usub(size_t x, size_t y);

//Implementação do função de reverter string
char *strrev(const char *const str);

//Operação para simular a concatenação de um ponteiro de char com um char (char* + char)
void append(char *s, char c);

#endif
