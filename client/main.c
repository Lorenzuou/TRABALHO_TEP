#include <stdio.h>
#include <stdlib.h>

void criarMenu()
{
    char entrada;
    scanf("%c", &entrada);
    switch (entrada)
    {
    case '1':
        realizarLogin();
        break;
    case '2':
        realizarCadastro();
        break;
    case '3':
        procurarFilme();
        break;
    case '4':

        break;

    default:
        break;
    }
}

int main()
{

    printf("Hello Henrick Bengolo");


    criarMenu(); 

    return 0;
}