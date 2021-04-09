#ifndef FILME_H
#define FILME_H
#include "user.h"
#include "util.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>

#define TAM_F 20


static int  qtdFilmes = 0; 
static int qtdFilmesHistorico = 0;
typedef struct
{
    int id;
    char *nome;
    int duracao;
    int ano;
    float nota; 
    char* sinopse;
    
} Filme;


typedef struct
{
    int idUsuario; 
    char *nomeFilme;
    char data[20];
    float nota; 
 
    
} FilmeHistorico;



FilmeHistorico *carregarFilmesHistorico(); 

void ordernarPorNota(int idUsuario); 

void ordernarPorData(int idUsuario); 

Filme *carregarFilmes();

void procurarFilme(int verbosidade);






int listarFilmes(int m, int idUsuario, int verbosidade); 



void assistirFilme(Filme filme, int idUsuario, int verbosidade);






#endif