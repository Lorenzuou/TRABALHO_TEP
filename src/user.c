#include "user.h"
#include "filme.h"
#include "util.h"
char *lerLinha()
{
    int caracter;
    size_t tamanhoChunk = TAM;
    size_t posicaoChunk = 0;

    char *string = malloc(TAM);

    if (string == NULL)
    {
        printf("Não há espaço para ser alocado em memória\n");
        exit(EXIT_FAILURE);
    }

    while ((caracter = fgetc(stdin)) != '\n' && caracter != '\r')
    {
        string[posicaoChunk++] = caracter;
        if (posicaoChunk == tamanhoChunk)
        {
            tamanhoChunk += TAM;

            string = realloc(string, tamanhoChunk);

            if (string == NULL)
            {
                printf("Não há mais espaço para ser alocado em memória\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    string[posicaoChunk] = 0;

    return string;
}

Usuario *carregarUsuarios()
{
    Usuario *user;
    user = (Usuario *)malloc(sizeof(Usuario) * TAM);
    qtdUsuarios = 0;

    FILE *file = fopen("data/usuarios.csv", "r");

    char linha[1024];

    while (fgets(linha, 1024, file))
    {
        if (qtdUsuarios + 1 == TAM)
        {
            user = realloc(user, sizeof(Usuario) * TAM * 2);
        }
        user[qtdUsuarios].nome = malloc(sizeof(char) * TAM);
        user[qtdUsuarios].senha = malloc(sizeof(char) * TAM);
        strcpy(user[qtdUsuarios].nome, strtok(linha, ","));
        strcpy(user[qtdUsuarios].senha, strtok(NULL, ","));

        // printf("1:%s, ", user[countUsuario].nome);
        // printf("2:%s\n", user[countUsuario].senha);

        qtdUsuarios++;
    };

    fclose(file);

    return user;
}

int realizarLogin(Usuario *usuario)
{
    Usuario *usuarios = carregarUsuarios();

    char *nome;
    char *senha;

    //system("clear");

    printf("-------------\n");
    printf("    LOGIN    \n");
    printf("-------------\n\n");

    printf("Usuario: ");
    getchar(); // pegar o enter do input de usuario
    nome = lerLinha();

    printf("\nSenha: ");
    senha = lerLinha();

    for (int i = 0; i < qtdUsuarios; i++)
    {
        if (!strcmp(nome, usuarios[i].nome)) // verifica se há um usuario com o que foi digitado
        {
            int retorno = 0;

            // printf("%s - %s\n", nome, usuarios[i].nome);
            // printf("%s - %s", senha, usuarios[i].senha);
            usuarios[i].senha[strcspn(usuarios[i].senha, "\n")] = 0; // Toma como nulo a posição da string que ocorrer um "\n"

            if (!strcmp(senha, usuarios[i].senha)) // verifica se a senha do usuario confere.
            {
                retorno = 1;
            

            }
            else
            {
                system("clear");
                printf("Senha incorreta.\n");

                retorno = 0;
            }

            free(usuarios);
            free(nome);
            free(senha);

            return retorno;
        }
    }

    system("clear");
    printf("Usuário não cadastrado.\n");

    free(usuarios);
    return 0;
}

int realizarCadastro()
{
    Usuario *usuarios = carregarUsuarios();

    Usuario novoUsuario;
    char *confSenha;

    system("clear");

    printf("------------\n");
    printf("  CADASTRO  \n");
    printf("------------\n\n");

    printf("Digite seu nome de usuario: ");
    getchar(); // pegar o enter do input de usuario
    novoUsuario.nome = lerLinha();

    printf("\nDigite sua senha: ");
    // pegar o enter do input de usuario
    novoUsuario.senha = lerLinha();

    printf("\nConfirme sua senha: ");
    confSenha = lerLinha();

    printf("%s\n", novoUsuario.nome);
    printf("%s\n", novoUsuario.senha);
    printf("%s\n", confSenha);

    for (int i = 0; i < qtdUsuarios; i++)
    {
        if (!strcmp(novoUsuario.nome, usuarios[i].nome)) // verifica se há um usuario com o que foi digitado
        {
            system("clear");
            printf("Usuário já cadastrado.\n");

            return 0;
        }
    }

    if (!strcmp(confSenha, novoUsuario.senha))
    {
        int posicao = 0;
        char caracter;

        while (caracter != '\n')
        {
            caracter = novoUsuario.senha[posicao];

            if (!isalnum(caracter))
            {
                system("clear");
                printf("Senha fora do padrão.\n");

                return 0;
            }

            printf("%c\n", caracter);

            posicao++;
        }

        FILE *file = fopen("data/usuarios.csv", "a");

        fprintf(file, "\n%s,%s", novoUsuario.nome, novoUsuario.senha);
        qtdUsuarios++;

        fclose(file);

        system("clear");
        printf("Usuário cadastrado com sucesso!\nInsira as informações para fazer o login:\n");

        return 1;
    }
    else
    {
        system("clear");
        printf("As senhas não conferem.\n");
    }

    return 0;
}

void perfilUsuario()
{

    system("clear");
    printf("D ou N - Historico ordenado por data ou por Nota\n");
    printf("2 - Excluir minha conta :(\n");
    printf("3 - Voltar\n");

    char c = getchar();

    switch (c)
    {
    case 'D':

        break;

    case 'N':

        break;
    case '2':

        break;
    case '3':

        break;

    default:
        break;
    }
}