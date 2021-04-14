#include <stdio.h>
#include <stdlib.h>
#include "../include/user.h"
#include "../include/film.h"
#include "../include/util.h"

int main(int argc, char *argv[])

{
    Usuario usuarioLogado;
    int parar = 0;
    int logado = 0;
    int verbosidade = 0; //variável que irá controlar se os menus irão aparecer para o usuário ou não. 1 se sim | 0 se não

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
        logado = criarMenuLogin(&usuarioLogado, verbosidade); // roda enquanto o usuário ainda não estiver logado

        if (logado == 1)
        {
            parar = 0;
            while (parar == 0)
            {
                if (verbosidade)
                    system("clear");
                parar = criarMenuPrincipal(&usuarioLogado, verbosidade); // executa o menu enquanto parar == 0
            }
             free(usuarioLogado.nome);
            // free(usuarioLogado.senha);
        }
    }   
    

    return 0;   
}
