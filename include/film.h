#ifndef FILME_H
#define FILME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "user.h"
#include "util.h"

#define TAM_F 20

static int qtdFilmes = 0; 
static int qtdFilmesHistorico = 0;



typedef struct filme Filme; 
/**
*@brief Struct de filmes que estão armazenados em "filmes.csv". Com todos os dados referentes aos filmes. 
*/


typedef struct filmeHistorico FilmeHistorico; 

/**
*@brief Struct de filmes que estão armazenados em "historico.csv". 
*/





typedef struct data Data; 






/**
* @brief Função para obter a data a partir de uma string
* @param campo string contendo a data
* @return struct de data
*/


Data obterData(char *campo);

/**
* @brief Carrega um array de FilmeHistorico armazenado em "../data/csv/historicos.csv" 
* @return array com todos os FilmeHistorico 
*/
FilmeHistorico *carregarFilmesHistorico(); 

/**
* @brief Carrega um array com todos os filmes armazenados em "../data/csv/historicos.csv" 
* @return array com todos os Filmes
*/
Filme *carregarFilmes();

/**
* @brief Ordena e printa os filmes assistidos pelo usuario em ordem decrescente pelas avaliações dele 
* Pré-Condição: Usuário ter assistido algum filme
* @param int idUsuario 
*/
void ordenarPorNota(int idUsuario); 

/**
* @brief Ordena e printa os filmes assistidos pelo usuario em ordem decrescente pela data na qual ele assistiu
* Pré-Condição: Usuário ter assistido algum filme
* @param idUsuario id do usuário logado 
*/
void ordenarPorData(int idUsuario); 

/**
* @brief Lista 10 filmes por vez e mostrando ao usuario. O usuario pode voltar ou esolher um desses filmes para assistir. 
* @param m quantidade de filmes já mostrados. 
* @param idUsuario id do usuário logado 
* @param verbosidade 1 se os menus aparecerão | 0 se não
* @return 1 se a funcao vai ser reutilizada | 0 se a funcao terminou de ser utilizada
*/
int listarFilmes(int m, int idUsuario, int verbosidade); 

/**
* @brief Pesquisa a ocorrência de uma string digitada pelo usuário e retonra a lista de filmes que contém a string no nome
* @param idUsuario id do usuário logado 
* @param Nome do parâmetro Descrição do parâmetro
* @param verbosidade 1 se os menus aparecerão | 0 se não
* @return 1 se usuario terminou a pesquisa | 0 se o usuario irá pesquisar outra vez 
*/
int procurarFilme(int idUsuario, int verbosidade);

/**
* @brief Mostra ao usuário os metados de um filme, e o usuário pode optar po assistindo, avaliando o filme por nota e anotando a data em que ele assistiu
* @param filme que o usuario optou por assistir
* @param idUsuario id do usuário logado 
* @param verbosidade 1 se os menus aparecerão | 0 se não
*/
void assistirFilme(Filme filme, int idUsuario, int verbosidade);

/**
* @brief Libera a memória alocada pela função "carregarFilmes()"
* @param filmes lista de filmes a serem liberados
*/
void freeFilmes(Filme *filmes); 

/**
* @brief Libera a memória alocada pela função "carregarFilmesHistorico()"
* @param filmes lista de filmes a serem liberados
*/
void freeFilmesHistoricos(FilmeHistorico *filmes); 

/**
* @brief Deleta um filme da lista de filmes
* @param filme filme a ser deletado
* @param idUsuario filme a ser deletado
* @param verbosidade 1 se os menus aparecerão | 0 se não
*/
void deletarFilme(Filme filme, int idUsuario, int verbosidade); 

/**
* @brief Lista 10 filmes por vez e mostrando ao admin. O admin pode voltar ou esolher um desses filmes para deletar. pode digitar A para chamar a função de adicionar filme. 
* @param m quantidade de filmes já mostrados. 
* @param idUsuario id do usuário logado 
* @param verbosidade 1 se os menus aparecerão | 0 se não
* @return 1 se a funcao vai ser reutilizada | 0 se a funcao terminou de ser utilizada
*/
int listarFilmesADM(int m, int idUsuario, int verbosidade); 
/**
* @brief Adiciona um novo filme ao arquivo que armazena os filmes
* @param verbosidade 1 se os menus aparecerão | 0 se não
*/
void adicionarFilme(int verbosidade); 



#endif