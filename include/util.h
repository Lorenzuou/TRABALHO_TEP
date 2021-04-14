#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>
#include <time.h>

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "user.h"
#include "film.h"
#define TAM_UTIL 1 

typedef struct
{
    int dia;
    int mes;
    int ano;
} Data;

/**
*@brief Converte um array em um numero uma struct de time_t
* @param date data em formato de dd/mm/yyyy
* @return truct de time_t
*/
time_t stot(char *date);

/**
*@brief Lê uma uma string allocada e retorna uma string alocada com o tamanho exato dos carecteres dela
* @param texto string a ser alocada
* @return String alocada
*/
char *lerLinhaArquivo(char * texto);

/**
*@brief Lê uma uma string do usuario e retorna uma string alocada com o tamanho exato dos carecteres dela
* @return String alocada
*/
char *lerLinha();




#endif