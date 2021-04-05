#include "filme.h"
#include "user.h"
#include "util.h"

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

// void verHistorico(Usuario usuario)
// {
//     Filme *filmes = carregarFilmes();
//     FILE *file = fopen("data/historicos.csv", "r");

//     char linha[1024];

//     fclose(file);
// }

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

        assistirFilme(filmes[posicao - 1], nome);
    }
    free(filmes);
}

void procurarFilme()
{

    Filme *filmes = carregarFilmes();

    for (int i = 0; i < qtdFilmes; i++)
    {
    }
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
    if(c == '1'){ 
        
        float nota; 
        printf("\nDigite a sua nota para o filme: ");
        scanf("%f",&nota);
        
        char data[11];
        char c; 
        printf("\nDigite a data que você viu o filme: ");
        
        scanf("%s",data);
        // data[11] = '\0';
        FILE *file = fopen("data/historicos.csv", "a");
        fprintf(file, "\n%s,%s,%.02f,%s", nome, filmes.nome,nota,data);
        fclose(file);
    }
getchar(); 
    
}