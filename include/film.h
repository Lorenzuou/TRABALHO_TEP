#ifndef FILME_H
#define FILME_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "user.h"
#include "util.h"
#define TAM_F 20

static int  qtdFilmes = 0; 
static int qtdFilmesHistorico = 0;


/**
*@brief Struct de filmes que estão armazenados em "filmes.csv". Com todos os dados referentes aos filmes. 

*/

typedef struct
{
    int id;
    char *nome;
    int duracao;
    int ano;
    float nota; 
    char* sinopse;
    
} Filme;

/**
*@brief Struct de filmes que estão armazenados em "historico.csv". 

*/
typedef struct
{
    int idUsuario; 
    char *nomeFilme;
    char data[20];
    float nota; 
 
    
} FilmeHistorico;

/**
 *@brief Crrega um array de FilmeHistorico armazenado em "../data/csv/historicos.csv" 
* @return array com todos os FilmeHistorico 
*/
FilmeHistorico *carregarFilmesHistorico(); 

/**
*@brief Ordena e printa os filmes assistidos pelo usuario em ordem decrescente pelas avaliações dele 
*Pré-Condição: Usuário ter assistido algum filme
* @param int idUsuario 
*/
void ordenarPorNota(int idUsuario); 

/**
*@brief Ordena e printa os filmes assistidos pelo usuario em ordem decrescente pela data na qual ele assistiu
*Pré-Condição: Usuário ter assistido algum filme
* @param idUsuario id do usuário logado 
*/
void ordenarPorData(int idUsuario); 

/**
*@brief Carrega um array com todos os filmes armazenados em "../data/csv/historicos.csv" 
*@return array com todos os Filmes
*/
Filme *carregarFilmes();

/**
*@brief Pesquisa a ocorrência de uma string digitada pelo usuário e retonra a lista de filmes que contém a string no nome
* @param idUsuario id do usuário logado 
* @param Nome do parâmetro Descrição do parâmetro
* @param verbosiade 1 se os menus aparecerão | 0 se não
* @return 1 se usuario terminou a pesquisa | 0 se o usuario irá pesquisar outra vez 
*/
int procurarFilme(int idUsuario, int verbosidade);


/**
*@brief Lista 10 filmes por vez e mostrando ao usuario. O usuario pode voltar ou esolher um desses filmes para assistir. 
* @param m quantidade de filmes já mostrados. 
* @param idUsuario id do usuário logado 
* @param verbosiade 1 se os menus aparecerão | 0 se não
* @return 1 se a funcao vai ser reutilizada | 0 se a funcao terminou de ser utilizada
*/
int listarFilmes(int m, int idUsuario, int verbosidade); 

/**
*@brief Mostra ao usuário os metados de um filme, e o usuário pode optar po assistindo, avaliando o filme por nota e anotando a data em que ele assistiu
* @param filme que o usuario optou por assistir
* @param idUsuario id do usuário logado 
* @param verbosiade 1 se os menus aparecerão | 0 se não
*/
void assistirFilme(Filme filme, int idUsuario, int verbosidade);

/**
*@brief Libera a memória alocada pela função "carregarFilmes()"
* @param filmes lista de filmes a serem liberados
*/
void freeFilmes(Filme *filmes); 

/**
*@brief Libera a memória alocada pela função "carregarFilmesHistorico()"
* @param filmes lista de filmes a serem liberados
*/
void freeFilmesHistoricos(FilmeHistorico *filmes); 


#endif