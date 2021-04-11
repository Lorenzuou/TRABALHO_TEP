#include "user.h"
#include "string.h"


char *allocString(char *vetor)
{
  int tamanho = strlen(vetor);

  char *aux = (char *)malloc(sizeof(char) * tamanho);

  strcpy(aux, vetor);

  //free(vetor);

  return aux;
}

// converte uma string no formato dd/mm/yyyy no tipo time_t
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
// converte o tipo time_t em uma string no formato dd/mm/yyyy. A string
// `date` é a string que vai conter a data no formato especificado e deve
// ter sua memória alocada anteriormente (estatica ou dinamicamente) e
// deve ter ao menos 11 caracteres de tamanho
void ttos(time_t time, char *date)
{
  struct tm tm = *gmtime(&time);
  sprintf(date, "%02d/%02d/%4d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
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
    while ((caracter = texto[i]) != '\n' && caracter != '\r')
    {
        string[posicaoChunk++] = caracter;
        if (posicaoChunk == tamanhoChunk)
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

