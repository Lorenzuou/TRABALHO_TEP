#include "user.h"

Usuario* carregarUsuarios()
{

    Usuario *user;
    user = (Usuario *)malloc(sizeof(Usuario) * TAM);
    int countUsuario = 0;

    FILE *file = fopen("data/usuarios.csv", "r");

    char linha[1024];

    while (fgets(linha, 1024, file))
    {

        strcpy(user[countUsuario].nome, strtok(linha, ","));
        strcpy(user[countUsuario].senha, strtok(NULL, ","));

        printf("1:%s, ", user[countUsuario].nome);
        printf("2:%s\n", user[countUsuario].senha);

        countUsuario++;
    };

    fclose(file);

   
    
    return user;
}

void realizarLogin()
{
    Usuario *usuarios = carregarUsuarios();
    
    
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
    Usuario novoUsuario; 


    printf("Digite seu nome de usuario: ");
    scanf("%s",novoUsuario.nome); 
    printf("\nDigite sua senha: ");
    scanf("%s",novoUsuario.senha); 

    FILE *file = fopen("data/usuarios.csv", "a");

    fprintf(file,"\n%s,%s",novoUsuario.nome,novoUsuario.senha);

    fclose(file);

}
