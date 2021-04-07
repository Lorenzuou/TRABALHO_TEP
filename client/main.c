#include <stdio.h>
#include <stdlib.h>
#include "../include/user.h"
#include "../include/filme.h"
#include "../include/util.h"

int main(int argc, char *argv[])

{
    Usuario usuarioLogado;
    int parar = 0;
    int resultado = 0;
    if (argc == 1 || atoi(argv[1]))
    {

        while (resultado == 0)
        {
            resultado = criarMenuLogin(&usuarioLogado);
        }

        if (resultado == 1)
        {
            while (parar == 0)
            {
                system("clear");
                parar = criarMenuPrincipal(&usuarioLogado);
            }
        }
    }
    else
    {
        printf("\nArgc");
    }
 
    return 0;
}
