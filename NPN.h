#ifndef NPN_H_INCLUDED
#define NPN_H_INCLUDED

#include <stdlib.h>


//Caso seja um operador retorna 1 se não retorna 0
int isOperator(char c);

//Prioridade de operações
int getPriority(char c);

//tranformas uma equação infixa para uma equação pósfixa
char *infixToPostfix(char *infix);

//Transforma um equação infixa para uma equação prefixa, utilizando a função infixToPostFix
char *infixToPrefix(char *infix);

//Adiciona parentese na frente a atras de um ponteiro de char;
char *adicionarParenteses(char *str);

//Resolver notação polonesa normal
int resolverNPN(char *str);

// Retorna 1 caso a expressão tenha os parênteses balanceados
int validade_expression(char *exp);
#endif
