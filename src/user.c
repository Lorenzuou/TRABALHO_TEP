#include "user.h"
#include "filme.h"
#include "util.h"

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

int criarMenuPrincipal(Usuario *usuario)
{

    printf("\n**LOCADORA VIRTUAL**\n\n");
    printf("1.Listar filmes\n");
    printf("2.Meu perfil\n");
    printf("3.Pesquisar filme\n");
    printf("4.Sair\n\n");

   
    char entrada;
    entrada = getchar();
    // scanf("%c", &entrada);

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
        getchar();

        criarMenuPrincipal(&usuario);
        break;
    case '2':
        perfilUsuario(usuario->id);
        getchar();
        criarMenuPrincipal(&usuario);
        break;
    case '3':
        procurarFilme(usuario->nome);
        break;
    case '4':

        break;

    default:

        break;
    }

    return 1;

    // system("clear");
}

void freeUsuarios(Usuario *usuarios)
{

    for (int i = 0; i < qtdUsuarios; i++)
    {
        free(usuarios[i].nome);
        free(usuarios[i].senha);
    }
    free(usuarios);
}

freeVetorChar(char **vetor, int qtd)
{
    for (int i = 0; i < qtd; i++)
    {
        free(vetor[i]);
    }
    free(vetor);
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

int *carregarInativos()
{
    // Usuario *usuarios;
    // usuarios = (Usuario *)malloc(sizeof(Usuario) * TAM);
    // qtdUsuariosInativos = 0;

    int *usuarios;
    usuarios = (int *)malloc(sizeof(int *) * TAM);

    FILE *file = fopen("data/inativos.csv", "r");

    char linha[10];

    while (fgets(linha, 10, file))
    {
        if (qtdUsuariosInativos + 1 == TAM)
        {
            usuarios = realloc(usuarios, sizeof(int *) * TAM * 2);
        }
        sscanf(linha, "%d", &usuarios[qtdUsuariosInativos]); 
        
        //printf("\n%d",usuarios[qtdUsuariosInativos]); 
        usuarios[qtdUsuariosInativos]; 
        

        qtdUsuariosInativos++;
    };

    fclose(file);

    return usuarios;
}

Usuario *carregarUsuarios()
{
    Usuario *usuarios;
    usuarios = (Usuario *)malloc(sizeof(Usuario) * TAM);
    qtdUsuarios = 0;

    FILE *file = fopen("data/usuarios.csv", "r");

    char linha[1024];

    while (fgets(linha, 1024, file))
    {
        if (qtdUsuarios + 1 == TAM)
        {
            usuarios = realloc(usuarios, sizeof(Usuario) * TAM * 2);
        }
        usuarios[qtdUsuarios].nome = malloc(sizeof(char) * TAM);
        usuarios[qtdUsuarios].senha = malloc(sizeof(char) * TAM);
        
        sscanf(strtok(linha, ","), "%d", &usuarios[qtdUsuarios].id);
        strcpy(usuarios[qtdUsuarios].nome, strtok(NULL, ","));
        strcpy(usuarios[qtdUsuarios].senha, strtok(NULL, ","));

         //printf("1:%d,\n ", usuarios[qtdUsuarios].id);
        // printf("2:%s\n", usuarios[countUsuario].senha);

        qtdUsuarios++;
    };

    fclose(file);

    return usuarios;
}

int realizarLogin(Usuario *usuario)
{
    Usuario *usuarios = carregarUsuarios();
    int *inativos = carregarInativos();

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

    int logado = 0;
    int inativo = 0;
    int cadastrado = 0;

    for (int i = 0; i < qtdUsuarios; i++)
    {
        if (!strcmp(nome, usuarios[i].nome)) // verifica se há um usuario com o que foi digitado
        {
            cadastrado = 1;

            usuarios[i].senha[strcspn(usuarios[i].senha, "\n")] = 0; // Toma como nulo a posição da string que ocorrer um "\n"

            if (!strcmp(senha, usuarios[i].senha)) // verifica se a senha do usuario confere.
            {
                for (int y = 0; y < qtdUsuariosInativos; y++)
                {
               

                    if (usuarios[i].id == inativos[y]) // verifica se o usuario está no vetor de inativos
                    {
                        system("clear");
                        printf("Usuário inativo.\n");

                        inativo = 1;
                        break;
                    }
                }

                if (!inativo)
                {
                    
                    usuario->id = usuarios[i].id; 
                    usuario->nome = malloc(sizeof(char) * TAM);
                    strcpy(usuario->nome, usuarios[i].nome);

                    logado = 1;

                    break;
                }
            }
            else
            {
                system("clear");
                printf("Senha incorreta.\n");

                break;
            }
        }
    }

    if (!cadastrado)
    {
        system("clear");
        printf("Usuário não cadastrado.\n");
    }
    freeUsuarios(usuarios);
    free(nome);
    free(senha);

    return logado;
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
        novoUsuario.id = usuarios[qtdUsuarios-1].id + 1; 
        fprintf(file, "\n%d,%s,%s",novoUsuario.id, novoUsuario.nome, novoUsuario.senha);
        qtdUsuarios++;

        fclose(file);

        system("clear");
        printf("Usuário cadastrado com sucesso!\nInsira as informações para fazer o login:\n");

        freeUsuarios(usuarios);
        free(novoUsuario.nome);
        free(novoUsuario.senha);
        free(confSenha);

        return 1;
    }
    else
    {
        system("clear");
        printf("As senhas não conferem.\n");
    }

    freeUsuarios(usuarios);
    free(novoUsuario.nome);
    free(novoUsuario.senha);
    freeUsuarios(usuarios);
    return 0;
}

void excluirConta(int inativado)
{
    FILE *file = fopen("data/inativos.csv", "a");
    fprintf(file, "%d\n", inativado);
    fclose(file);
}

void verHistorico(Usuario usuario, int ordem)
{

    ordernarPorNota(usuario.nome);

    //  Filme *filmes = carregarFilmes();
    //  FILE *file = fopen("data/historicos.csv", "r");

    //  char linha[1024];

    // fclose(file);

    getchar();
}

void perfilUsuario(int id)
{

    system("clear");

    printf("------------\n");
    printf(" MEU PERFIL \n");
    printf("------------\n\n");

    printf("D ou N - Historico ordenado por data ou por Nota\n");
    printf("2 - Excluir minha conta :(\n");
    printf("3 - Voltar\n\n");
    printf("Opção: ");
    getchar();
    char c = getchar();

    switch (c)
    {
    case 'D':
     //   verHistorico(*usuario, 0);
        break;

    case 'N':
      //  verHistorico(*usuario, 1);
        break;
    case '2':
       
        excluirConta(id);
       // system("clear");
        printf("\nConta excluida com sucesso!\n");

        break;
    case '3':

        break;

    default:
        break;
    }
}