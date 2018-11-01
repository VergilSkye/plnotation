#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "stack.h"
#include "alloc.h"
#include "Utilidades.h"


void destructor_char(void *data)
{
    free(data);
}

void *constructor_char(void *data)
{
    void *ptr = mallocx(sizeof(char));
    memcpy(ptr, data, sizeof(char));
    return ptr;
}

void destructor_int(void *data)
{
    free(data);
}

void *constructor_int(void *data)
{
    void *ptr = mallocx(sizeof(int));
    memcpy(ptr, data, sizeof(int));
    return ptr;
}

int isOperator(char c)
{
    int aux = 1;
    if (c == '(' || c == ')')
    {
        aux = 0;
    }
    return (!isalpha(c) && !isdigit(c) && aux);
}

int getPriority(char c)
{

    if (c == '-' || c == '+')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '^')
        return 3;
    return 0;
}

char *infixToPostfix(char *infix)
{

    int l = strlen(infix);
    stack_t *char_stack;
    stack_initialize(&char_stack, constructor_char, destructor_char);
    char *output = malloc(l *sizeof(char));
    memset(output, '\0', sizeof(output));
    int contador = 0;
    char aux;

    for (int i = 0; i < l; i++)
    {
        //Caso seja um numero coloque direto na variavel outpur
        if (isdigit(infix[i]) || isalpha(infix[i]))
        {
            aux = infix[i];
            append(output, aux);
            contador++;
        }
        //Caso seja um Parenteses direito adiciona a pilha de operandos
        else if (infix[i] == '(')
        {

            stack_push(char_stack, &infix[i]);

        }
        //Caso seja um Parenteses esquerdo, ')', vá retirando os operandos
        //até encontra um Parenteses direito, '(', retirando ele também.
        else if (infix[i] == ')')
        {

            aux = *(char*)stack_top(char_stack);

            while (aux != '(')
            {
                append(output, aux);
                contador++;
                stack_pop(char_stack);
                aux = *(char *)stack_top(char_stack);
            }
            stack_pop(char_stack);

        }
        // Caso seja um operador
        else
        {

            aux = *(char *)stack_top(char_stack);
            //Existe algum operador na pilha? se sim entra no if
            if (isOperator(aux))
            {
                //O operador na pilha, aux, tem maior prioridade?
                // Se sim retira da pilha e coloca no output
                while (getPriority(infix[i]) <= getPriority(aux))
                {

                    append(output, aux);
                    contador++;
                    stack_pop(char_stack);
                    aux = *(char *)stack_top(char_stack);
                }
            }

            stack_push(char_stack, &infix[i]);

        }
    }


//Retorna string da notação polonesa reversa
    return output;
}

char *infixToPrefix(char *infix)
{
    //Tamanho da string recebida
    int l = strlen(infix);
    //Inverte a string recebida
    infix = strrev(infix);

    //Arruma os parenteses que estão errados
    //depois da operação de reversão
    for (int i = 0; i < l; i++)
    {
        if (infix[i] == '(')
        {
            infix[i] = ')';
            continue;
        }
        else if (infix[i] == ')')
        {
            infix[i] = '(';
            continue;
        }
    }

    char *prefix = infixToPostfix(infix);
    prefix = strrev(prefix);

    return prefix;
}
char *adicionarParenteses(char *str)
{
    size_t len = strlen(str);

    char *p1 = ")";
    char *str2 = malloc(len + 2 + 2);
    str2[0] = '(';
    str2[1] = '\0';
    strcat(str2, str);
    strcat(str2, p1);
    return str2;
}
int resolverNPN(char *str){

    char *eq = strrev(str);
    int l = strlen(str);
    // temporario que armazena a conversão do caracter para o numero tipo inteiro
    int tmp;
    // variaveis utiliza para as operações matematicas
    int x, y, result;

    stack_t *int_stack;
    stack_initialize(&int_stack, constructor_int, destructor_int);

    for (int i = 0; i < l; i++){
        if(isdigit(eq[i])){

            tmp =  eq[i]-'0';
            stack_push(int_stack,&tmp);
        }
        if(eq[i]=='+'){

            x = *(int*)stack_top(int_stack);
            stack_pop(int_stack);
            y = *(int*)stack_top(int_stack);;
            stack_pop(int_stack);
            result = x+y;
            stack_push(int_stack,&result);
        }
        if(eq[i]=='-'){

            x = *(int*)stack_top(int_stack);
            stack_pop(int_stack);
            y = *(int*)stack_top(int_stack);;
            stack_pop(int_stack);
            result = x-y;
            stack_push(int_stack,&result);
        }
        if(eq[i]=='*'){

            x = *(int*)stack_top(int_stack);
            stack_pop(int_stack);
            y = *(int*)stack_top(int_stack);;
            stack_pop(int_stack);
            result = x*y;
            stack_push(int_stack,&result);
        }
        if(eq[i]=='/'){

            x = *(int*)stack_top(int_stack);
            stack_pop(int_stack);
            y = *(int*)stack_top(int_stack);;
            stack_pop(int_stack);
            result = x/y;
            stack_push(int_stack,&result);
        }
    }
    return *(int*)stack_top(int_stack);
}

int validade_expression(char *str)
{
    int i;
    char * tmp = malloc(1+strlen(str));
    strcpy(tmp,str);


    int res = 1;
    stack_t* pilha;
    stack_initialize(&pilha,constructor_char,destructor_char);
    for(i=0; i<strlen(tmp); i++)
    {
        char c = tmp[i];
        if(c=='(')
        {
            stack_push(pilha,&c);
        }
        else if(c==')')
        {
            if(stack_empty(pilha))
            {
                res = 0;
                break;
            }
            else
            {
                stack_pop(pilha);
            }
        }
    }
    if(!stack_empty(pilha)){
    res =0;
    }
    stack_delete(&pilha);
    free(tmp);


    return res;

}
