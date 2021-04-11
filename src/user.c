#include "user.h"
#include "filme.h"
#include "util.h"

int criarMenuLogin(Usuario *usuario, int verbosidade)
{
    int resultado = 0; // 0 = não logado | 1 = logado | 2 = sair

    if (verbosidade)
    {

        printf("\n**LOCADORA VIRTUAL**\n\n");
        printf("1.Login\n");
        printf("2.Cadastro\n");
        printf("3.Sair\n\n");

        printf("Opção: ");
    }

    int entrada = 0;
    scanf("%d", &entrada);
    getchar();

    switch (entrada)
    {
    case 1:
        resultado = realizarLogin(usuario, verbosidade);
        break;
    case 2:
        if (realizarCadastro(verbosidade))
        {
            resultado = realizarLogin(usuario, verbosidade);
        }
        break;
    case 3:
        resultado = 2;
        break;
    default:
        printf("Opção invalida.");
        break;
    }

    return resultado;
}

int criarMenuPrincipal(Usuario *usuario, int verbosidade)
{
    if (verbosidade)
    {
        printf("\n**LOCADORA VIRTUAL**\n\n");
        printf("1.Listar filmes\n");
        printf("2.Meu perfil\n");
        printf("3.Pesquisar filme\n");
        printf("4.Sair\n\n");

        printf("Opção: ");
    }

    int entrada = 0;
    scanf("%d", &entrada);
    getchar();

    int listar = 1;
    int m = 0;
    int parar = 2;
    switch (entrada)
    {
    case 1:
        while (listar)
        {
            listar = listarFilmes(m, usuario->id, verbosidade);
            m += 10;
        }

        return 0;
        break;
    case 2:

        while (parar == 2)
        {
            parar = perfilUsuario(usuario->id, verbosidade);
        }
        if (parar == 1)
        {
            return 0;
        }
        else
        {
            return 1;
        }
        break;
    case 3:
        procurarFilme(usuario->id, verbosidade);
        //return 0;

    case 4:
        return 1;
        break;

    default:
        printf("Opção inválida");
        return 0;
        break;
    }

    return 1;
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

int *carregarInativos()
{

    int *usuarios;
    usuarios = (int *)malloc(sizeof(int *) * TAM);

    FILE *file = fopen("data/inativos.csv", "r");

    char linha[10];
    int fator = 2;
    while (fgets(linha, 10, file))
    {
        if (qtdUsuariosInativos % TAM)
        {
            usuarios = realloc(usuarios, sizeof(int)*(TAM + 1) * fator++);
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
    int fator = 2;

    while (fgets(linha, 1024, file))
    {
        if (qtdUsuarios % TAM)
        {
            usuarios = realloc(usuarios, sizeof(Usuario) * (TAM + 1) * fator++);
        }
        // usuarios[qtdUsuarios].nome = malloc(sizeof(char) * TAM);
        // usuarios[qtdUsuarios].senha = malloc(sizeof(char) * TAM);

        sscanf(strtok(linha, ","), "%d", &usuarios[qtdUsuarios].id);
        // strcpy(usuarios[qtdUsuarios].nome, strtok(NULL, ","));
        // strcpy(usuarios[qtdUsuarios].senha, strtok(NULL, ","));

        // usuarios[qtdUsuarios].nome = lerLinhaArquivo(usuarios[qtdUsuarios].nome);
        // usuarios[qtdUsuarios].senha = lerLinhaArquivo(usuarios[qtdUsuarios].senha);

        usuarios[qtdUsuarios].nome = lerLinhaArquivo(strtok(NULL, ","));
        usuarios[qtdUsuarios].senha = lerLinhaArquivo(strtok(NULL, ","));

        //printf("1:%d,\n ", usuarios[qtdUsuarios].id);
        // printf("2:%s\n", usuarios[countUsuario].senha);

        qtdUsuarios++;
    };

    fclose(file);

    return usuarios;
}

int realizarLogin(Usuario *usuario, int verbosidade)
{
    Usuario *usuarios = carregarUsuarios();
    int *inativos = carregarInativos();

    char *nome;
    char *senha;

    //system("clear");

    if (verbosidade)
    {
        printf("-------------\n");
        printf("    LOGIN    \n");
        printf("-------------\n\n");

        printf("Usuario: ");

        //getchar(); // pegar o enter do input de usuario
    }

    nome = lerLinha();

    if (verbosidade)
        printf("\nSenha: ");

    senha = lerLinha();

    int logado = 0;
    int senhaCorreta = 0;
    int ativo = 0;
    int cadastrado = 0;

    for (int i = 0; i < qtdUsuarios; i++)
    {
        if (!strcmp(nome, usuarios[i].nome)) // verifica se há um usuario com o que foi digitado
        {
            cadastrado = 1;

            for (int y = 0; y < qtdUsuariosInativos; y++)
            {
                if (usuarios[i].id == inativos[y]) // verifica se o usuario está no vetor de inativos
                {
                    ativo = 0;
                    break;
                }
                else
                {
                    ativo = 1;
                }
            }
        }

        if (ativo)
        {
            usuarios[i].senha[strcspn(usuarios[i].senha, "\n")] = 0; // Toma como nulo a posição da string que ocorrer um "\n"
            if (!strcmp(senha, usuarios[i].senha))                   // verifica se a senha do usuario confere.
            {
                senhaCorreta = 1;
            }
            else
            {
                senhaCorreta = 0;
            }
        }

        if (cadastrado)
        {
            if (ativo)
            {
                if (senhaCorreta)
                {
                    usuario->id = usuarios[i].id;
                    usuario->nome = lerLinhaArquivo(usuarios[i].nome);
                    

                    logado = 1;
                    break;
                }
            }
        }
    }

    if (cadastrado)
    {
        if (ativo)
        {
            if (!senhaCorreta)
            {
                system("clear");
                printf("Senha incorreta.\n");
            }
        }
        else
        {
            system("clear");
            printf("Usuário inativo.\n");
        }
    }
    else
    {
        system("clear");
        printf("Usuário não cadastrado.\n");
    }

    freeUsuarios(usuarios);
    free(inativos);
    free(nome);
    free(senha);

    return logado;
}

int realizarCadastro(int verbosidade)
{

    Usuario *usuarios = carregarUsuarios();

    int *inativos = carregarInativos();

    Usuario novoUsuario;
    char *confSenha;

    if (verbosidade)
    {
        system("clear");

        printf("------------\n");
        printf("  CADASTRO  \n");
        printf("------------\n\n");

        printf("Digite seu nome de usuario: ");
    }

    // pegar o enter do input de usuario
    novoUsuario.nome = lerLinha();
    if (verbosidade)
        printf("\nDigite sua senha: ");
    // pegar o enter do input de usuario
    novoUsuario.senha = lerLinha();
    if (verbosidade)
        printf("\nConfirme sua senha: ");
    confSenha = lerLinha();

    for (int i = 0; i < qtdUsuarios; i++)
    {
        if (!strcmp(novoUsuario.nome, usuarios[i].nome)) // verifica se há um usuario com o que foi digitado
        {
            int inativo = 0;
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
                system("clear");
                printf("Usuário já cadastrado.\n");
                return 0;
            }
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
        novoUsuario.id = usuarios[qtdUsuarios - 1].id + 1;
        fprintf(file, "\n%d,%s,%s", novoUsuario.id, novoUsuario.nome, novoUsuario.senha);
        qtdUsuarios++;

        fclose(file);
        if (verbosidade)
        {
            system("clear");
            printf("Usuário cadastrado com sucesso!\nInsira as informações para fazer o login:\n");
        }
        free(inativos);
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
    free(inativos);
    freeUsuarios(usuarios);
    free(novoUsuario.nome);
    free(novoUsuario.senha);
    return 0;
}

void excluirConta(int idUsuario, int verbosidade)
{
    FILE *file = fopen("data/inativos.csv", "a");
    fprintf(file, "%d\n", idUsuario);
    fclose(file);

    if (verbosidade)
        printf("\nConta excluida com sucesso!\n");
}

void verHistorico(int id, int ordem, int verbosidade)
{
    if (ordem)
        ordenarPorNota(id);
    else
        ordenarPorData(id);

    getchar();
}

int perfilUsuario(int id, int verbosidade)
{
    // printf("ID:");

    if (verbosidade)
    {
        //system("clear");

        printf("------------\n");
        printf(" MEU PERFIL \n");
        printf("------------\n\n");

        printf("D ou N - Historico ordenado por data ou por Nota\n");
        printf("2 - Excluir minha conta :(\n");
        printf("3 - Voltar\n\n");
        printf("Opção: ");
    }
    char entrada;
    scanf("%c", &entrada);
    getchar();

    switch (entrada)
    {
    case 'D':
        verHistorico(id, 0, verbosidade);
        break;

    case 'N':
        verHistorico(id, 1, verbosidade);
        break;

    case '2':
        excluirConta(id, verbosidade);
        return 0;

    case '3':
        return 1;

    default:
        printf("Opcao invalida.\n");
        return 2;
    }

    return 1;
}