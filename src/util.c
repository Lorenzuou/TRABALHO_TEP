#include "user.h"

int criarMenuLogin(Usuario *usuario)
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
        resultado = realizarLogin(usuario);
        break;
    case '2':
        if (realizarCadastro())
        {
            resultado = realizarLogin(usuario);
        }
        break;
    case '3':
        resultado = 2;
        break;
    }

    return resultado;
}

void criarMenuPrincipal()
{

    printf("\n**LOCADORA VIRTUAL**\n\n");
    printf("1.Listar filmes\n");
    printf("2.Meu perfil\n");
    printf("3.Pesquisar filme\n");
    printf("4.Sair\n\n");

    printf("Opção: ");
    char entrada;
    entrada = getchar();
    // scanf("%c", &entrada);

    switch (entrada)
    {
    case '1':
        listarFilmes(0);
        criarMenuPrincipal();
        break;
    case '2':
        perfilUsuario(); 
        break;
    case '3':

        break;
    case '4':

        break;

    default:

        break;
    }

    // system("clear");
    
}
