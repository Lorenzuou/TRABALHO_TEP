#ifndef FILME_H
#define FILME_H
#include "user.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>

#define TAM 20


static int  qtdFilmes = 0; 

typedef struct
{
    int id;
    char *nome;
    int duracao;
    int ano;
    float nota; 
    char* sinopse;
    
} Filme;



Filme *carregarFilmes();

void procurarFilme();


void verHistorico(Usuario usuario); 




void listarFilmes(); 



void assistirFilme(Filme filme);






#endif