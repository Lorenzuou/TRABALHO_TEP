#include "user.h"
#include "util.h"

struct usuario
{
    int id;
    char *nome;
    char *senha;
};

int criarMenuLogin(Usuario *usuario, int verbosidade)
{
    int resultado = 0;

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

    int m = 0;
    int listar = 1;
    int parar = 2;

    switch (entrada)
    {

    case 1:
        while (listar)
        {
            if (usuario->id != 0) //verificar se o usuário é o ADM
                listar = listarFilmes(m, usuario->id, verbosidade);
            else
                listar = listarFilmesADM(m, usuario->id, verbosidade);
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
        return 0;

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

        sscanf(strtok(linha, ","), "%d", &usuarios[qtdUsuarios].id);
    
        usuarios[qtdUsuarios].nome = lerLinhaArquivo(strtok(NULL, ","));
        usuarios[qtdUsuarios].senha = lerLinhaArquivo(strtok(NULL, ","));

        qtdUsuarios++;
    };

    fclose(file);

    return usuarios;
}

int *carregarInativos()
{
    int *usuarios;
    usuarios = (int *)malloc(sizeof(int *) * TAM);

    FILE *file = fopen("data/inativos.csv", "r");

    char linha[10];
    int fator = 2;

    //carrega a lista de inativos a partir do arquivo contendo o id dos usuarios inativos
    while (fgets(linha, 10, file))
    {
        if (qtdUsuariosInativos % TAM)
        {
            usuarios = realloc(usuarios, sizeof(int) * (TAM + 1) * fator++);
        }

        sscanf(linha, "%d", &usuarios[qtdUsuariosInativos]);

        qtdUsuariosInativos++;
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

    if (verbosidade)
    {
        printf("-------------\n");
        printf("    LOGIN    \n");
        printf("-------------\n\n");

        printf("Usuario: ");
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
                if (verbosidade)
                    system("clear");

                printf("Senha incorreta.\n");
            }
        }
        else
        {
            if (verbosidade)
                system("clear");

            printf("Usuário inativo.\n");
        }
    }
    else
    {
        if (verbosidade)
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
    novoUsuario.nome = lerLinha();

    if (verbosidade)
        printf("\nDigite sua senha: ");
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
                    if (verbosidade)
                        system("clear");

                    printf("Usuário inativo.\n");

                    inativo = 1;
                    break;
                }
            }

            if (!inativo)
            {
                if (verbosidade)
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
                if (verbosidade)
                    system("clear");
                printf("Senha fora do padrão.\n");

                return 0;
            }
        }

        FILE *file = fopen("data/usuarios.csv", "a");
        novoUsuario.id = usuarios[qtdUsuarios - 1].id + 1;
        fprintf(file, "%d,%s,%s\n", novoUsuario.id, novoUsuario.nome, novoUsuario.senha);
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
        if (verbosidade)
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

    if (verbosidade)
    {
        printf("\n\nPressione 1 para continuar. \n");
        int entrada;

        scanf("%d", &entrada);
        getchar();
    }
}

int perfilUsuario(int id, int verbosidade)
{
    if (verbosidade)
    {
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
    return 2;
}

void freeUsuarios(Usuario *usuarios)
{
    //percorre o vetor de usuarios, liberando o nome e a senha
    for (int i = 0; i < qtdUsuarios; i++)
    {
        free(usuarios[i].nome);
        free(usuarios[i].senha);
    }

    //libera o vetor de usuarios
    free(usuarios);
}
