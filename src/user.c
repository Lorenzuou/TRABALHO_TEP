#include "user.h"

Usuario *carregarUsuarios()
{

    Usuario *user;
    user = (Usuario *)malloc(sizeof(Usuario) * TAM);
    int countUsuario = 0;
    qtdUsuarios = 0;

    FILE *file = fopen("data/usuarios.csv", "r");

    char linha[1024];

    while (fgets(linha, 1024, file))
    {

        strcpy(user[countUsuario].nome, strtok(linha, ","));
        strcpy(user[countUsuario].senha, strtok(NULL, ","));

        // printf("1:%s, ", user[countUsuario].nome);
        // printf("2:%s\n", user[countUsuario].senha);

        qtdUsuarios++;
    };

    fclose(file);

    return user;
}

void realizarLogin()
{

    Usuario *usuarios = carregarUsuarios();

    char nome[TAM];
    char senha[TAM];

    printf("Usuario: ");
    scanf("%s", nome);
    printf("\nSenha: ");
    scanf("%s", senha);

    printf("%s", usuarios[0].nome);

    // for (int i = 0; i < qtdUsuarios; i++)
    // {

    //     if (strcmp(nome, usuarios[i].nome))
    //     {
    //         if(strcmp(senha, usuarios[i].senha)){
    //             printf("Usuário Logado com sucesso!");

    //         }
    //     }
    // }

    free(usuarios);
}

void realizarCadastro()
{
    Usuario novoUsuario;

    printf("Digite seu nome de usuario: ");
    scanf("%s", novoUsuario.nome);
    printf("\nDigite sua senha: ");
    scanf("%s", novoUsuario.senha);

    FILE *file = fopen("data/usuarios.csv", "a");

    fprintf(file, "\n%s,%s", novoUsuario.nome, novoUsuario.senha);
    qtdUsuarios++;

    fclose(file);
}
