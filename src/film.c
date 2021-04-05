#include "filme.h"
#include "user.h"
#include "util.h"

Filme *carregarFilmes()
{
    Filme *filme;
    filme = (Filme *)malloc(sizeof(Filme) * TAM_F);
    qtdFilmes = 0;

    FILE *file = fopen("data/filmes-pequeno.csv", "r");

    char linha[1024];

    while (fgets(linha, 1024, file))
    {
        if (qtdFilmes + 1 == TAM_F)
        {
            filme = realloc(filme, sizeof(Filme) * TAM_F * 2);
        }
        filme[qtdFilmes].nome = malloc(sizeof(char) * 1000);
        filme[qtdFilmes].sinopse = malloc(sizeof(char) * 1000);

        strcpy(filme[qtdFilmes].nome, strtok(linha, ","));
        // filme[qtdFilmes].nome = strtok(linha, ",");
        sscanf(strtok(NULL, ","), "%d", &filme[qtdFilmes].duracao);
        sscanf(strtok(NULL, ","), "%d", &filme[qtdFilmes].ano);
        sscanf(strtok(NULL, ","), "%f", &filme[qtdFilmes].nota);
        // filme[qtdFilmes].sinopse = strtok(NULL, "");

        strcpy(filme[qtdFilmes].sinopse, strtok(NULL, ""));

        qtdFilmes++;
    };

    // fclose(file);

    return filme;
}



// void verHistorico(Usuario usuario)
// {
//     Filme *filmes = carregarFilmes();
//     FILE *file = fopen("data/historicos.csv", "r");

//     char linha[1024];

//     fclose(file);
// }

void listarFilmes(int m)
{

    Filme *filmes = carregarFilmes();
    system("clear");
    if (m >= qtdFilmes)
    {
        system("clear");
        
      

    }

    printf("LISTA DE FILMES qtd %d\n", qtdFilmes);
    int i = 0;
    for (i = m; i < 5 + m; i++)
    {
        printf("%d- <%s>\n", i + 1, filmes[i].nome);
        if (i >= qtdFilmes)
        {
            break;
        }
    }
    printf("M - Mais filmes\n");
    printf("0 - Voltar\n");
    printf("Opcao: ");

    getchar();
    char c;
    c = getchar(); 
    getchar();
    if (c == 'M' || c == 'm')
    {

        printf("\n\n Opcao: %c\n", c);
        listarFilmes(m + 5);
     
    }
    else if (!isdigit(c) || c == '0')
    {
        
         
     
       
    }
    else
    {
        for (int i = m; i < 5 + m; i++)
        {
            if (c  == i + '0')
            {
                system("clear");
                assistirFilme(filmes[i-1]);
                break; 
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
    char c; 
  
    printf("Filme: %s \n", filme.nome);
    printf("Nota: %.02f \n", filme.nota);

     time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("Data que assistiu: %02d/%02d/%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
   
}