
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
    if (valor > 0 && valor < 32)
    {
        dataInvalida = 1;
    }
    return data;
}

FilmeHistorico *carregarFilmesHistorico()
{
    FilmeHistorico *filmes;
    filmes = (FilmeHistorico *)malloc(sizeof(FilmeHistorico) * TAM_F);
    qtdFilmesHistorico = 0;
    FILE *file = fopen("data/historicos.csv", "r");
    int fator = 2;

    char linha[1024];

    while (fgets(linha, 1024, file))
    {
        if (strlen(linha) != 0)
        {
            if (qtdFilmesHistorico % TAM_F)
            {
                filmes = realloc(filmes, sizeof(FilmeHistorico) * (TAM_F + 1) * fator++);
            }
            // lê filme por filme na lista do historico de filmes separando os elementos por ","
            filmes[qtdFilmesHistorico].nomeFilme = malloc(sizeof(char) * 100);
            sscanf(strtok(linha, ","), "%d", &filmes[qtdFilmesHistorico].idUsuario);
            strcpy(filmes[qtdFilmesHistorico].nomeFilme, strtok(NULL, ","));
            sscanf(strtok(NULL, ","), "%f", &filmes[qtdFilmesHistorico].nota);
            strcpy(filmes[qtdFilmesHistorico].data, strtok(NULL, ""));
            filmes[qtdFilmesHistorico].data[strcspn(filmes[qtdFilmesHistorico].data, "\n")] = 0;

            qtdFilmesHistorico++;
        }
    };

    fclose(file);

    return filmes;
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

        // lê filme por filme na lista de filmes separando os elementos por ","
        filmes[qtdFilmes].nome = lerLinhaArquivo(strtok(linha, ","));

        sscanf(strtok(NULL, ","), "%d", &filmes[qtdFilmes].ano);
        sscanf(strtok(NULL, ","), "%d", &filmes[qtdFilmes].duracao);
        sscanf(strtok(NULL, ","), "%f", &filmes[qtdFilmes].nota);
        filmes[qtdFilmes].sinopse = lerLinhaArquivo(strtok(NULL, ""));

        qtdFilmes++;
    };

    fclose(file);

    return filmes;
}

void ordenarPorNota(int idUsuario)
{
    int max = 0;

    int auxiliarIdUsuario = 0;
    char auxiliarNomeFilme[100];
    float auxiliarNota = 0;
    char auxiliarData[20];

    FilmeHistorico *filmesHistorico = carregarFilmesHistorico();
    if (qtdFilmesHistorico > 0)
    {
        //selection sort para ordernar os filmes pela data que foram assistidos em ordem decrescente
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

            //verificando se existe uma um filme com a data maior que o atual
            if (max != i)
            {
                //se sim, troca os filmes de lugar com auxilio de variáveis temporárias
                auxiliarIdUsuario = filmesHistorico[max].idUsuario;
                strcpy(auxiliarNomeFilme, filmesHistorico[max].nomeFilme);
                auxiliarNota = filmesHistorico[max].nota;
                strcpy(auxiliarData, filmesHistorico[max].data);

                filmesHistorico[max].idUsuario = filmesHistorico[i].idUsuario;
                strcpy(filmesHistorico[max].nomeFilme, filmesHistorico[i].nomeFilme);
                filmesHistorico[max].nota = filmesHistorico[i].nota;
                strcpy(filmesHistorico[max].data, filmesHistorico[i].data);

                filmesHistorico[i].idUsuario = auxiliarIdUsuario;
                strcpy(filmesHistorico[i].nomeFilme, auxiliarNomeFilme);
                filmesHistorico[i].nota = auxiliarNota;
                strcpy(filmesHistorico[i].data, auxiliarData);
            }
        }
    }

    //exibindo a ordenação por data dos filmes
    int historicoUsuario = 0;
    for (int i = 0; i < qtdFilmesHistorico; i++)
    {
        if (filmesHistorico[i].idUsuario == idUsuario)
        {
            if (filmesHistorico[i].nota < 0)
            {
                printf("%s: %s, %s \n", filmesHistorico[i].nomeFilme, filmesHistorico[i].data, "Sem avaliacao");
                historicoUsuario = 1;
            }
            else
            {

                printf("%s: %s, %.2f \n", filmesHistorico[i].nomeFilme, filmesHistorico[i].data, filmesHistorico[i].nota);
                historicoUsuario = 1;
            }
        }
    }
    if (!historicoUsuario)
    {
        printf("\nNao ha filmes assistidos pelo usuario.");
    }
    freeFilmesHistoricos(filmesHistorico);
}

void ordenarPorData(int idUsuario)
{
    int max = 0;

    int auxiliarIdUsuario;
    char auxiliarNomeFilme[100];
    float auxiliarNota = 0;
    char auxiliarData[20];

    FilmeHistorico *filmesHistorico = carregarFilmesHistorico();
    if (qtdFilmesHistorico > 0)
    {
        //selection sort para ordernar os filmes pela data que foram assistidos em ordem decrescente
        for (int i = 0; i < qtdFilmesHistorico - 1; i++)
        {
            max = i;
            for (int j = i + 1; j < qtdFilmesHistorico; j++)
            {
                if (stot(filmesHistorico[j].data) > stot(filmesHistorico[max].data))
                {
                    max = j;
                }
            }

            //verificando se existe uma um filme com a data maior que o atual
            if (max != i)
            {
                //se sim, troca os filmes de lugar com auxilio de variáveis temporárias
                auxiliarIdUsuario = filmesHistorico[max].idUsuario;
                strcpy(auxiliarNomeFilme, filmesHistorico[max].nomeFilme);
                auxiliarNota = filmesHistorico[max].nota;
                strcpy(auxiliarData, filmesHistorico[max].data);

                filmesHistorico[max].idUsuario = filmesHistorico[i].idUsuario;
                strcpy(filmesHistorico[max].nomeFilme, filmesHistorico[i].nomeFilme);
                filmesHistorico[max].nota = filmesHistorico[i].nota;
                strcpy(filmesHistorico[max].data, filmesHistorico[i].data);

                filmesHistorico[i].idUsuario = auxiliarIdUsuario;
                strcpy(filmesHistorico[i].nomeFilme, auxiliarNomeFilme);
                filmesHistorico[i].nota = auxiliarNota;
                strcpy(filmesHistorico[i].data, auxiliarData);
            }
        }
    }

    //exibindo a ordenação por data dos filmes
    int historicoUsuario = 0;
    for (int i = 0; i < qtdFilmesHistorico; i++)
    {
        if (filmesHistorico[i].idUsuario == idUsuario)
        {
            if (filmesHistorico[i].nota < 0)
            {
                printf("%s: %s, %s \n", filmesHistorico[i].nomeFilme, filmesHistorico[i].data, "Sem avaliacao");
                historicoUsuario = 1;
            }
            else
            {

                printf("%s: %s, %.2f \n", filmesHistorico[i].nomeFilme, filmesHistorico[i].data, filmesHistorico[i].nota);
                historicoUsuario = 1;
            }
        }
    }

    if (!historicoUsuario)
    {
        printf("\nNao ha filmes assistidos pelo usuario.");
    }

    freeFilmesHistoricos(filmesHistorico);
}

int listarFilmes(int m, int idUsuario, int verbosidade)
{
    Filme *filmes = carregarFilmes();

    if (verbosidade)
    {
        if (m >= qtdFilmes)
        {
            printf("Fim de filmes disponiveis\n");
        }

        printf("---------------------------\n");
        printf("LISTA DE FILMES | QTD.: %d\n", qtdFilmes);
        printf("---------------------------\n\n");

        printf("Digite o id do filme que deseja assistir:\n\n");
    }

    //exbindo 10 filmes
    int i = 0;
    for (i = m; i < 10 + m; i++)
    {
        if (i >= qtdFilmes)
        {
            break;
        }
        printf("%d- %s\n", i + 1, filmes[i].nome);
    }

    if (verbosidade)
    {
        printf("\nM - Mais filmes\n");
        printf("0 - Voltar\n\n");
        printf("Opcao: ");
    }

    char entrada[3];
    scanf("%s", &entrada);
    getchar();

    if (entrada[0] == 'M' || entrada[0] == 'm') // se o usuário quer avançar na lista de filmes
    {
        freeFilmes(filmes);
        return 1;
    }
    else if (entrada[0] == '0') // se o usuário quer voltar
    {
        freeFilmes(filmes);
        return 0;
    }
    else // se o usuario quer assistir um filme
    {

        int posicao = 0;
        sscanf(entrada, "%d", &posicao);

        if (posicao <= m + 10 && posicao > m)
        {

            assistirFilme(filmes[posicao - 1], idUsuario, verbosidade);
        }
        else
            printf("\nFilme não está na lista. ");
    }
    freeFilmes(filmes);
    return 0;
}

int procurarFilme(int idUsuario, int verbosidade)
{
    if (verbosidade)
    {
        printf("Pesquisa de filme: ");
    }

    char *pesquisa;
    pesquisa = lerLinha();

    Filme *filmes = carregarFilmes();
    int *ids;
    int qtdFilmesPesquisa = 0;

    if (verbosidade)
    {
        printf("Digite o id do filme que deseja assistir:\n\n");
        printf("|ID do filme | Nome do filme\n");
    }

    ids = (int *)malloc(sizeof(int) * 10);
    int fator = 2;

    //exibe os filmes de acordo com a pesquisa
    for (int i = 0; i < qtdFilmes; i++)
    {
        if (strcasestr(filmes[i].nome, pesquisa))
        {
            printf("|%d| - %s \n", i + 1, filmes[i].nome);

            ids[qtdFilmesPesquisa] = i + 1; // atribui-se o id do filme;
            qtdFilmesPesquisa++;

            if (qtdFilmesPesquisa % 10)
            {
                ids = (int *)realloc(ids, sizeof(int) * (10 * fator++));
            }
        }
    }

    if (qtdFilmesPesquisa == 0)
    {
        printf("Não foram encontrados filmes para a chave de pesquisa informada.");
    }
    else
    {
        if (verbosidade)
        {
            printf("\n0 - Voltar\n\n");
            printf("Opcao: ");
        }

        int entrada;
        scanf("%d", &entrada);
        getchar();

        if (entrada == 0)
        {
            free(ids);
            freeFilmes(filmes);
            free(pesquisa);

            return 0;
        }
        else
        {
            int estaNaLista = 0;

            for (int i = 0; i < qtdFilmesPesquisa; i++)
            {
                if (entrada == ids[i])
                {
                    assistirFilme(filmes[entrada - 1], idUsuario, verbosidade);
                    estaNaLista = 1;
                }
            }

            if (!estaNaLista)
                printf("\nFilme não está na lista. ");
        }
    }
    free(ids);
    freeFilmes(filmes);
    free(pesquisa);
}

void assistirFilme(Filme filmes, int idUsuario, int verbosidade)
{
    if (verbosidade)
        system("clear");

    printf("Titulo: %s \n", filmes.nome);
    printf("Ano: %d \n", filmes.ano);
    printf("Duracao: %d min\n", filmes.duracao);
    printf("Avaliacao: %.02f \n", filmes.nota);
    printf("Descricao: %s \n", filmes.sinopse);

    if (verbosidade)
    {
        printf("1 - Assistir \n");
        printf("2 - Voltar \n\n");
        printf("Opção: ");
    }

    char entrada;
    scanf("%s", &entrada);
    getchar();

    if (entrada == '1')
    {
        float nota;
        if (verbosidade)
            printf("\nDigite a sua nota para o filme: ");
        scanf("%f", &nota);

        char data[10];
        char c;
        if (verbosidade)
            printf("\nDigite a data que você viu o filme: ");

        scanf("%s", data);

        //verificando se a data é válida
        int EhData = 1;
        char diaData[3];
        diaData[2] = '\0';
        char mesData[3];
        mesData[2] = '\0';

        int i = 0;
        for (i; i < 2; i++)
        {

            if (!isdigit(data[i]))
                EhData = 0;

            diaData[i] = data[i];
        }

        if (atoi(diaData) > 31 || atoi(diaData) < 1)
        {
            EhData = 0;
        }

        if (data[i++] != '/')
            EhData = 0;

        for (i; i < 5; i++)
        {
            if (!isdigit(data[i]))
                EhData = 0;

            mesData[(i - 3)] = data[i];
        }

        if (atoi(mesData) > 12 || atoi(mesData) < 1)
        {
            EhData = 0;
        }

        if (data[i++] != '/')
            EhData = 0;

        char ano[5];
        ano[4] = '\0';

        for (i; i < 10; i++)
        {
            ano[i - 6] = data[i];

            if (!isdigit(data[i]))
                EhData = 0;
        }

        if (atoi(ano) > 2021 || atoi(ano) < 1900)
        {
            EhData = 0;
        }

        //se a data inserida é valida, salva os dados inseridos no arquivo do historico
        if (!EhData)
        {
            printf("\nData inválida");
        }
        else
        {

            FILE *file = fopen("data/historicos.csv", "a");
            fprintf(file, "%d,%s,%.02f,%s\n", idUsuario, filmes.nome, nota, data);
            fclose(file);
        }
    }
}

void freeFilmes(Filme *filmes)
{
    //percorre o array de filmes, liberando a string do nome do filme e a sinopse
    for (int i = 0; i < qtdFilmes; i++)
    {
        free(filmes[i].nome);
        free(filmes[i].sinopse);
    }

    //libera o array de filmes
    free(filmes);
}

void freeFilmesHistoricos(FilmeHistorico *filmes)
{
    //percorre o array de historico de filmes, liberando a string do nome do filme
    for (int i = 0; i < qtdFilmesHistorico; i++)
    {
        free(filmes[i].nomeFilme);
    }

    //libera o array de historico de filmes
    free(filmes);
}