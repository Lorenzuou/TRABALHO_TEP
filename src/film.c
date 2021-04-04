#include "filme.h"
#include "user.h"

Filme *carregarFilmes()
{
    Filme *filme;
    filme = (Filme *)malloc(sizeof(Filme) * TAM);
    qtdFilmes = 0;

    FILE *file = fopen("data/filmes-pequeno.csv", "r");

    char linha[1024];

    while (fgets(linha, 1024, file))
    {
        if (qtdFilmes + 1 == TAM)
        {
            filme = realloc(filme, sizeof(Filme) * TAM * 2);
        }
        filme[qtdFilmes].nome = malloc(sizeof(char) * TAM);
        filme[qtdFilmes].sinopse = malloc(sizeof(char) * TAM);

        strcpy(filme[qtdFilmes].nome, strtok(linha, ","));
        sscanf(strtok(NULL, ","), "%d", &filme[qtdFilmes].duracao);
        sscanf(strtok(NULL, ","), "%d", &filme[qtdFilmes].ano);
        sscanf(strtok(NULL, ","), "%d", &filme[qtdFilmes].nota);
        strcpy(filme[qtdFilmes].sinopse, strtok(NULL, "\""));

        // printf("1:%s, ", user[countUsuario].nome);
        // printf("2:%s\n", user[countUsuario].senha);

        qtdFilmes++;
    };

    fclose(file);

    return filme;
}

void verHistorico(Usuario usuario)
{
    Filme *filmes = carregarFilmes();
    FILE *file = fopen("data/historicos.csv", "r");

    

    char linha[1024];

    fclose(file);
}

void listarFilmes(int m)
{

    Filme *filmes = carregarFilmes();
    printf("LISTA DE FILMES\n");
    for (int i = m; i < 5 + m; i++)
    {

        printf("%d- <%s>\n", i, filmes[i].nome);
        if (i == qtdFilmes)
        {
            break;
        }
    }
    printf("M - Mais filmes\n");
    printf("0 - Voltar");
    char c;
    scanf("%c", &c);
    if (c == "M" || c == "m")
    {
        listarFilmes(m + 5);
    }
    else if (!isdigit(c))
    {
    }
    else
    {

        for (int i = m; i < 5 + m; i++)
        {
            if ((int)c == i)
            {
                assistirFilme(filmes[i]);
            }
        }
    }
}

void procurarFilme()
{

    Filme *filmes = carregarFilmes();

    for (int i = 0; i < qtdFilmes; i++)
    {
    }
}

void assistirFilme(Filme filme)
{

    printf("Filme: %s \n", filme.nome);
    printf("Nota: %s \n", filme.nota);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("Data que assistiu: %02d/%02d/%d\n",tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900) ; 
}