#include <stdio.h>
#include <stdlib.h>
#include "../include/user.h"










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
        // procurarFilme();
        break;
    case '4':

        break;

    default:
        break;
    }
}

int main()
{



    criarMenu(); 

    return 0;
}