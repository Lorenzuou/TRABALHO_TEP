#include "user.h"
#include "string.h"

time_t stot(char *date)
{
  struct tm tm = {0};
  int d, m, y;
  sscanf(date, "%2d/%2d/%4d", &d, &m, &y);
  tm.tm_mday = d;
  tm.tm_mon = m - 1;
  tm.tm_year = y - 1900;
  time_t time = mktime(&tm);
  return time;
}

char *lerLinha()
{
    int caracter;
    size_t tamanhoChunk = TAM;
    size_t posicaoChunk = 0;

    char *string = malloc(sizeof(char)*TAM);

    if (string == NULL)
    {
        printf("Não ha espaço para ser alocado em memoria\n");
        exit(EXIT_FAILURE);
    }

    while ((caracter = getchar()) != '\n' && caracter != '\r')
    {
        string[posicaoChunk++] = caracter;
        if (posicaoChunk == tamanhoChunk)
        {
            tamanhoChunk += TAM;

            string = realloc(string,sizeof(char)* tamanhoChunk);

            if (string == NULL)
            {
                printf("Não há mais espaço para ser alocado em memória\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    string[posicaoChunk] = '\0';

    return string;
}

char *lerLinhaArquivo(char * texto)
{
    int caracter;
    size_t tamanhoChunk = TAM_UTIL;
    size_t posicaoChunk = 0;

    char *string = malloc(sizeof(char)*TAM_UTIL);

    if (string == NULL)
    {
        printf("Não ha espaço para ser alocado em memoria\n");
        exit(EXIT_FAILURE);
    }

    int i = 0; 
    while ((caracter = texto[i]) != '\n' && caracter != '\r') //enquanto não encontrar uma quebra de linha, continua a ler os caracteres
    {
        string[posicaoChunk++] = caracter;
        if (posicaoChunk == tamanhoChunk) // Se o tamanho da string é maior que o chunk, aumenta-se o tamanho alocado da string com realloc
        {
            tamanhoChunk += TAM_UTIL;

            string = realloc(string,sizeof(char)* tamanhoChunk); 

            if (string == NULL)
            {
                printf("Não há mais espaço para ser alocado em memória\n");
                exit(EXIT_FAILURE);
            }
        }
        i++; 
    }
    string[posicaoChunk] = '\0';

    return string;
}