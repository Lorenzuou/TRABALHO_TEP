#ifndef USER_H
#define USER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h> 
#include "util.h"
#include "filme.h"


#define TAM 100

static int qtdUsuarios = 0;
static int qtdUsuariosInativos = 0;

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



int criarMenuLogin(Usuario *usuario, int verbosidade); 


int criarMenuPrincipal(Usuario *usuario , int verbosidade);





Usuario *carregarUsuarios();

int realizarLogin(Usuario *usuario, int verbosidade);

int realizarCadastro(int verbosidade);


void excluirConta(int inativado, int verbosidade);

void verHistorico(int id, int ordem, int verbosidade); 

int perfilUsuario(int id, int verbosidade); 


#endif