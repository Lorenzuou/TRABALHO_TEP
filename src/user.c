#include "user.h"

void carregarUsuarios()
{

    Usuario *user;
    user = (Usuario*)malloc(sizeof(Usuario) * TAM);
    int countUsuario = 0;

    FILE *file = fopen("data/usuarios.csv", "r");

    char linha[1024];
    while (fgets(linha, 1024, file))
    {

         strcpy( user[countUsuario].nome,strtok(linha, ",") );
         strcpy( user[countUsuario].nome,strtok(linha, ",") );

        // *user.nome =  strtok(linha, ",");
        // user.senha = *strtok(NULL, ",");
        printf("%s",user[countUsuario].nome);
        printf("%s",user[countUsuario].senha);

        fclose(file);
        countUsuario++;
    };
}
void realizarLogin()
{
    carregarUsuarios();
    // char *usuarios;

    // char *nome[TAM];
    // char *senha[TAM];

    // printf("Usuario: ");
    // scanf("%s", *nome);
    // printf("\nSenha: ");
    // scanf("%s", *senha);
}

void realizarCadastro()
{
}
