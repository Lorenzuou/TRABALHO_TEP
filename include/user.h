#ifndef USER_H
#define USER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 20

typedef struct
{
    int id;
    char nome[30];
    char senha[30];
    char data[10];
} Filme;



static int qtdUsuarios = 0;

typedef struct
{
    int id;
    char nome[30];
    char senha[30];
    char **historico;
} Usuario;

/*
* Carrega os usuários do arquivo usuarios.csv e armazena em um vetor de usuários  
*/


int criarMenu();


Usuario *carregarUsuarios( );

int realizarLogin();

void realizarCadastro();

void procurarFilme();

#endif