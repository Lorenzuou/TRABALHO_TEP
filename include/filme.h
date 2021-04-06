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
    char *nomeUsuario; 
    char *nomeFilme;
    char data[11];
    float nota; 
 
    
} FilmeHistorico;


FilmeHistorico *carregarFilmesHistorico(char* nome); 

void ordernarPorNota(char* nome); 


Filme *carregarFilmes();

void procurarFilme(char* nome);






int listarFilmes(int m, char* nome); 



void assistirFilme(Filme filme, char* nome);






#endif