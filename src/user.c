#include "user.h"
#include "filme.h"
#include "util.h"

static Usuario usuarioLogado;

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

void criarMenuPrincipal(Usuario *usuario)
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

    char vetor[100];

    vetor[0] = 'a';
    vetor[1] = 'b';
    vetor[2] = 'c';
    vetor[3] = '\0';

    int listar = 1;
    int m = 0;
    switch (entrada)
    {
    case '1':

        while (listar)
        {

            listar = listarFilmes(m, usuario->nome);
            m += 10;
        }

        criarMenuPrincipal(&usuario);
        break;
    case '2':
        perfilUsuario(*usuario);
        getchar();
        criarMenuLogin(&usuario);
        break;
    case '3':

        printf("\n%d", allocString(vetor));
        break;
    case '4':

        break;

    default:

        break;
    }

    // system("clear");
}

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
                usuario->nome = malloc(sizeof(char) * TAM);
                strcpy(usuario->nome, usuarios[i].nome);

                usuarioLogado.nome = malloc(sizeof(char) * TAM);
                strcpy(usuario->nome, usuarios[i].nome);
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
        int i = 0;
        for (i = 0; i < strlen(novoUsuario.senha); i++)
        {
            if (!isalnum(novoUsuario.senha[i]))
            {
                //system("clear");
                printf("Senha fora do padrão.\n");

                return 0;
            }
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

void excluirConta(char *nome)
{
    Usuario *usuarios = carregarUsuarios();
    FILE *file = fopen("data/usuarios.csv", "w") ;

    printf("%d",qtdUsuarios);
    fclose(file);

    file  = fopen("data/historicos.csv", "a");

    for (int i = 0; i < qtdUsuarios; i++)
    {
         if (strcmp(usuarios[i].nome, nome))
         {
             fprintf("%s,%s",usuarios[i].nome,usuarios[i].senha);
         }else{ 
             fprintf("-%s,%s",usuarios[i].nome,usuarios[i].senha); // adiciona o marcador de conta suspensa
         }
    }
    fclose(file);
}

void verHistorico(Usuario usuario, int ordem)
{
    //  Filme *filmes = carregarHistoricos();

    // for(int i = 0; i<qtdFilmes; i++){
    //     if
    // }

    // if (ordem)
    // {

    //     int i, j;
    //     for (i = 0; i < n - 1; i++)

    //         // Last i elements are already in place
    //         for (j = 0; j < n - i - 1; j++)
    //             if (arr[j] > arr[j + 1])
    //             {
    //                 int temp = *xp;
    //                 *xp = *yp;
    //                 *yp = temp;
    //             }
    // }
}

void perfilUsuario(Usuario usuario)
{

    system("clear");
    printf("D ou N - Historico ordenado por data ou por Nota\n");
    printf("2 - Excluir minha conta :(\n");
    printf("3 - Voltar\n");
    getchar();
    char c = getchar();

    switch (c)
    {
    case 'D':
        verHistorico(usuario, 0);
        break;

    case 'N':
        verHistorico(usuario, 1);
        break;
    case '2':
        excluirConta(usuario.nome);
        system("clear");
        printf("\nConta excluida com sucesso!\n");

        break;
    case '3':

        break;

    default:
        break;
    }
}