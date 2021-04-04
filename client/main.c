#include <stdio.h>
#include <stdlib.h>
#include "../include/user.h"

int criarMenuLogin();

int main(int argc, char *argv[])
{
    if (argc == 1 || atoi(argv[1]))
    {
        int resultado = 0;
        while (resultado == 0)
        {
            resultado = criarMenuLogin();
        }

        if (resultado == 1)
        {
            system("clear");
            criarMenuPrincipal();
        }
    }
    else
    {
        printf("\nArgc");
    }

    return 0;
}

int criarMenuLogin()
{
    int resultado = 0; // 0 = não logado | 1 = logado | 2 = sair
    char entrada;

    printf("\n**LOCADORA VIRTUAL**\n\n");
    printf("1.Login\n");
    printf("2.Cadastro\n");
    printf("3.Sair\n\n");

    printf("Opção: ");
    scanf("%c", &entrada);

    switch (entrada)
    {
    case '1':
        resultado = realizarLogin();
        break;
    case '2':
        if (realizarCadastro())
        {
            resultado = realizarLogin();
        }
        break;
    case '3':
        resultado = 2;
        break;
    }

    return resultado;
}

int criarMenuPrincipal()
{
    char entrada;

    printf("\n**LOCADORA VIRTUAL**\n\n");
    printf("1.Listar filmes\n");
    printf("2.Meu perfil\n");
    printf("3.Pesquisar filme\n");
    printf("4.Sair\n\n");

    printf("Opção: ");
    scanf("%c", &entrada);

    switch (entrada)
    {
    case '1':

        break;
    case '2':

        break;
    case '3':

        break;
    case '4':

        break;

    default:

        break;
    }

    // system("clear");
    return 0;
}
