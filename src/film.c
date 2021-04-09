#include "filme.h"
#include "user.h"
#include "util.h"


#define _GNU_SOURCE


Data obterData(char *campo)
{

    Data data;
    char *identificador;
    char *delimitador = "/";
    char *valor;
    int dataInvalida = 0;

    //separando os campos pelo delimitador e armazenando nas propriedades da struct
    valor = strtok(campo, delimitador);
    sscanf(valor, "%d", &data.ano);
    if (valor > 1970 && valor < 2100)
    {
        dataInvalida = 1;
    }

    valor = strtok(NULL, delimitador);
    sscanf(valor, "%d", &data.mes);
    if (valor > 0 && valor < 13)
    {
        dataInvalida = 1;
    }

    valor = strtok(NULL, delimitador);
    sscanf(valor, "%d", &data.dia);
    if (valor > 0&& valor < 32)
    {
        dataInvalida = 1;
    }
    return data;
}

void freeFilmes(Filme *filmes)
{

    for (int i = 0; i < qtdFilmes; i++)
    {
        free(filmes[i].nome);
        free(filmes[i].sinopse);
    }
    free(filmes);
}

void freeFilmesHistoricos(FilmeHistorico *filmes)
{

    for (int i = 0; i < qtdFilmesHistorico; i++)
    {
        free(filmes[i].nomeUsuario);
        free(filmes[i].nomeFilme);
    }
    free(filmes);
}

FilmeHistorico *carregarFilmesHistorico()
{
    FilmeHistorico *filmes;
    filmes = (FilmeHistorico *)malloc(sizeof(Filme) * TAM_F);
    qtdFilmesHistorico = 0;
    FILE *file = fopen("data/historicos.csv", "r");
    int fator = 2;

    char linha[1024];

    while (fgets(linha, 1024, file))
    {
        if (qtdFilmes % TAM_F)
        {
            filmes = realloc(filmes, sizeof(FilmeHistorico) * (TAM_F + 1) * fator++);
        }

        // filmes[qtdFilmesHistorico].nomeUsuario = malloc(sizeof(char) * 1000);
        // filmes[qtdFilmesHistorico].nomeFilme = malloc(sizeof(char) * 1000);

        strcpy(filmes[qtdFilmesHistorico].nomeUsuario, strtok(linha, ","));
        strcpy(filmes[qtdFilmesHistorico].nomeFilme, strtok(NULL, ","));
        sscanf(strtok(NULL, ","), "%f", &filmes[qtdFilmesHistorico].nota);
        sscanf(strtok(NULL, ","), "%s", &filmes[qtdFilmesHistorico].data);

        qtdFilmesHistorico++;
    };

    fclose(file);

    return filmes;
}

void ordernarPorNota(char *nome)
{
    int max = 0;

    char auxiliarNomeUsuario[100];
    char auxiliarNomeFilme[100];
    float auxiliarNota = 0;
    char auxiliarData[11];

    FilmeHistorico *filmesHistorico = carregarFilmesHistorico();

    //selection sort para ordernar as cidades por quantidade de casos confirmados
    for (int i = 0; i < qtdFilmesHistorico - 1; i++)
    {
        max = i;
        for (int j = i + 1; j < qtdFilmesHistorico; j++)
        {
            if (filmesHistorico[j].nota > filmesHistorico[max].nota)
            {
                max = j;
            }
        }

        //verificando se existe uma cidade com número de casos maior que a atual
        if (max != i)
        {
            //se sim, troca as cidades de lugar com auxilio de variáveis temporárias
            strcpy(auxiliarNomeUsuario, filmesHistorico[max].nomeUsuario);
            strcpy(auxiliarNomeFilme, filmesHistorico[max].nomeFilme);
            auxiliarNota = filmesHistorico[max].nota;
            strcpy(auxiliarData, filmesHistorico[max].data);

            strcpy(filmesHistorico[max].nomeUsuario, filmesHistorico[i].nomeUsuario);
            strcpy(filmesHistorico[max].nomeFilme, filmesHistorico[i].nomeFilme);
            filmesHistorico[max].nota = filmesHistorico[i].nota;
            strcpy(filmesHistorico[max].data, filmesHistorico[i].data);

            strcpy(filmesHistorico[i].nomeUsuario, auxiliarNomeUsuario);
            strcpy(filmesHistorico[i].nomeFilme, auxiliarNomeFilme);
            filmesHistorico[i].nota = auxiliarNota;
            strcpy(filmesHistorico[i].data, auxiliarData);
        }
    }

    //exibindo o top n casos confirmados
    for (int i = 0; i < qtdFilmesHistorico; i++)
    {
        if (!strcmp(filmesHistorico[i].nomeUsuario, nome))
            printf("%s: %s, %.2f \n", filmesHistorico[i].nomeFilme, filmesHistorico[i].data, filmesHistorico[i].nota);
    }
}

void ordernarPorData(char *nome)
{
    int max = 0;

    char auxiliarNomeUsuario[100];
    char auxiliarNomeFilme[100];
    float auxiliarNota = 0;
    char auxiliarData[11];

    FilmeHistorico *filmesHistorico = carregarFilmesHistorico();

    //selection sort para ordernar as cidades por quantidade de casos confirmados
    for (int i = 0; i < qtdFilmesHistorico - 1; i++)
    {
        max = i;
        for (int j = i + 1; j < qtdFilmesHistorico; j++)
        {
            if (filmesHistorico[j].nota > filmesHistorico[max].nota)
            {
                max = j;
            }
        }
    }
}

Filme *carregarFilmes()
{
    qtdFilmes = 0;

    Filme *filmes;
    filmes = (Filme *)malloc(sizeof(Filme) * TAM_F);

    FILE *file = fopen("data/filmes-grande.csv", "r");

    int fator = 2;
    char linha[1024];

    while (fgets(linha, 1024, file))
    {
        if (qtdFilmes % TAM_F)
        {
            filmes = realloc(filmes, sizeof(Filme) * (TAM_F + 1) * fator++);
        }

        filmes[qtdFilmes].nome = malloc(sizeof(char) * 1000);
        filmes[qtdFilmes].sinopse = malloc(sizeof(char) * 1000);

        strcpy(filmes[qtdFilmes].nome, strtok(linha, ","));

        sscanf(strtok(NULL, ","), "%d", &filmes[qtdFilmes].ano);
        sscanf(strtok(NULL, ","), "%d", &filmes[qtdFilmes].duracao);
        sscanf(strtok(NULL, ","), "%f", &filmes[qtdFilmes].nota);

        strcpy(filmes[qtdFilmes].sinopse, strtok(NULL, ""));

        qtdFilmes++;
    };

    fclose(file);

    return filmes;
}

int listarFilmes(int m, char *nome)
{
    Filme *filmes = carregarFilmes();
    char entrada[3];

    //system("clear");

    if (m >= qtdFilmes)
    {
        printf("Fim de filmes disponiveis\n");
    }

    printf("---------------------------\n");
    printf("LISTA DE FILMES | QTD.: %d\n", qtdFilmes);
    printf("---------------------------\n\n");

    printf("Digite o id do filme que deseja assistir:\n\n");

    int i = 0;
    for (i = m; i < 10 + m; i++)
    {
        if (i >= qtdFilmes)
        {
            break;
        }
        printf("%d- <%s>\n", i + 1, filmes[i].nome);
    }

    printf("\nM - Mais filmes\n");
    printf("0 - Voltar\n\n");
    printf("Opcao: ");

    getchar();
    scanf("%s", &entrada);
    printf("\nEntrada: %s\n\n", entrada);

    if (entrada[0] == 'M' || entrada[0] == 'm')
    {
        return 1;
    }
    else if (entrada[0] == '0')
    {
        return 0;
    }
    else
    {
        // for (int i = m; i < 5 + m; i++)
        // {
        //     if (c == i + '0')
        //     {

        //         assistirFilme(filmes[i - 1], nome);
        //         break;
        //     }
        // }
        //
        //assistirFilme(filmes[i - 1], nome);

        int posicao = 0;
        sscanf(entrada, "%d", &posicao);
        
        if( posicao < m + 10 && posicao > m)
            assistirFilme(filmes[posicao - 1], nome);
        else
            printf("\mFilme não está na lista. "); 
    }
    freeFilmes(filmes);
}

void procurarFilme(char *nomeUsuario)
{

    char pesquisa[100];
    printf("Pesquisa de filme: ");
    scanf("%s", pesquisa);

    Filme *filmes = carregarFilmes();
    printf("|ID do filme | Nome do filme\n");
    for (int i = 0; i < qtdFilmes; i++)
    {
        if (strcasestr(filmes[i].nome, pesquisa))
        {
            printf("|%d|  - %s \n", i, filmes[i].nome);
        }
    }
    int posicao;
    getchar();
    printf("\nDigite o numero do filme ou digite 0 para voltar: ");
    scanf("%d", &posicao);

    if (posicao != 0)
    {
        assistirFilme(filmes[posicao - 1], nomeUsuario);
    }

    freeFilmes(filmes);
}

void assistirFilme(Filme filmes, char *nome)
{

    system("clear");

    printf("Filme: %s \n", filmes.nome);
    printf("Ano de lancamento: %d \n", filmes.ano);
    printf("Duracao: %d min\n", filmes.duracao);

    printf("Avaliacao: %.02f \n", filmes.nota);

    printf("Sinopse: %s \n", filmes.sinopse);

    printf("1 - Assistir \n");
    printf("2 - Voltar \n");
    char c;
    getchar();
    c = getchar();
    if (c == '1')
    {

        float nota;
        printf("\nDigite a sua nota para o filme: ");
        scanf("%f", &nota);

        char data[11];
        char c;
        printf("\nDigite a data que você viu o filme: ");

        scanf("%s", data);
        // data[11] = '\0';
        FILE *file = fopen("data/historicos.csv", "a");
        fprintf(file, "%s,%s,%.02f,%s\n", nome, filmes.nome, nota, data);
        fclose(file);
    }

    getchar();
}