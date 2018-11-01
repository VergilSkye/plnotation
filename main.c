
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "NPN.h"


int main()
{
    char *str;
    printf("Digite usa operação:\n");
    scanf("%s", str);


    if(validade_expression(str)){
    str = adicionarParenteses(str);

    char *NPN;
    NPN = infixToPrefix(str);
    printf("\n%s",NPN);
    printf("\nO resutado e %d\n", resolverNPN(NPN));
    }
    else{
    printf("\nA Expressao e invalida");
    }

    return (0);
}


