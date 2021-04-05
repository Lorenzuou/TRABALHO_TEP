#include <stdio.h>
#include <stdlib.h>
#include "../include/user.h"
#include "../include/filme.h"
#include "../include/util.h"




int main(int argc, char *argv[])
 
{
    Usuario usuarioLogado;
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
