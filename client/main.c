#include <stdio.h>
#include <stdlib.h>
#include "../include/user.h"
#include "../include/filme.h"
#include "../include/util.h"

int main(int argc, char *argv[])

{
    Usuario usuarioLogado;
    int parar = 0;
    int logado = 0;
    int verbosidade = 0;

    if (argc == 2)
    {
        verbosidade = atoi(argv[1]);
    }
    else
    {
        verbosidade = 1;
    }

    // meuPrintf(verbosidade,"tranquilo como um %s com %d baseados", "esquilo", 4);

    while (logado == 0)
    {
        logado = criarMenuLogin(&usuarioLogado, verbosidade);

        if (logado == 1)
        {
            parar = 0;
            while (parar == 0)
            {
                system("clear");
                parar = criarMenuPrincipal(&usuarioLogado, verbosidade);
                logado = 0;
            }
        free(usuarioLogado.nome);
        }
        
    }
    
    

    return 0;
}
