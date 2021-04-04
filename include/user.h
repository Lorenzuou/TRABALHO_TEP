#ifndef USER_H
#define USER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h> 

#define TAM 20

static int qtdUsuarios = 0;

typedef struct
{
    int id;
    char *nome;
    char *senha;
    char **historico;
} Usuario;

/*
* Carrega os usuários do arquivo usuarios.csv e armazena em um vetor de usuários  
*/




Usuario *carregarUsuarios();

int realizarLogin();

int realizarCadastro();


void perfilUsuario(); 


#endif