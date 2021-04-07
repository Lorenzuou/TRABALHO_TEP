#include "user.h"
#include "string.h"

char *allocString (char *vetor)
{
  int tamanho = strlen(vetor);
    
  char *aux = (char *)malloc(sizeof(char) * tamanho);

  strcpy(aux, vetor);

  //free(vetor);
  
  return aux;
}



// char *allocString (char *vetor)
// {
//   char aux[1000];


//   strcpy(aux, vetor);

//   char * retorno = malloc(strlen(aux)); 
//   strcpy(retorno, aux); 
  
//   return retorno;
// }