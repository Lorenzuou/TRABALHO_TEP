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


/**
*@brief Cria o menu de login, onde o usuario digita nome e senha para acessar o menu principal
* @param usuario endereço do usuário que será atribuido o usuário logado
* @param verbosiade 1 se os menus aparecerão | 0 se não
* @return 1 se o usuário logou | 0 se não
*/
int criarMenuLogin(Usuario *usuario, int verbosidade); 


/**
*@brief Cria o menu principal, onde o usuário pode escolher o que quer fazer no progrma
* @param usuario Usuario que está logado no sistema
* @param verbosiade 1 se os menus aparecerão | 0 se não
* @return 1 se terminou se ser utilizado | 0 se não
*/
int criarMenuPrincipal(Usuario *usuario , int verbosidade);




/**
*@brief Carrega a lista de todos os usuários em "../data/usuarios.csv"
* @return Lista de todos os usuarios (Usuario)
*/
Usuario *carregarUsuarios();

/**
*@brief Recebe nome e senha digitados pelo usuário e verifica se o usuário pode logar
* @param usuario endereço do usuário que será atribuido o usuário logado
* @param verbosiade 1 se os menus aparecerão | 0 se não
* @return 1 se o usuário logou | 0 se não
*/

int realizarLogin(Usuario *usuario, int verbosidade);

/**
*@brief Realiza o cadastro de um usuário, recebendo nome e senha
* @param verbosiade 1 se os menus aparecerão | 0 se não
* @return 1 se o usuário cadastrou | 0 se não
*/
int realizarCadastro(int verbosidade);

/**
*@brief Exclui a conta do usuário 
* @param inativado id do usuário a ser inativado
* @param verbosiade 1 se os menus aparecerão | 0 se não
* @return Variavel de retorno Descrição do retorno
*/
void excluirConta(int inativado, int verbosidade);

/**
*@brief Recebe o id do usuário, a ordem 
*Pré-Condição: Pré-condição
* Pós-Condição: Pós-condição
* @param Nome do parâmetro Descrição do parâmetro
* @param Nome do parâmetro Descrição do parâmetro
* @return Variavel de retorno Descrição do retorno
*/
void verHistorico(int id, int ordem, int verbosidade); 



/**
*@brief Exibe as opcoes do perfil do usuário
* @param id Usuário logado 
* @param verbosidade do parâmetro Descrição do parâmetro
* @param verbosiade 1 se os menus aparecerão | 0 se não
 *@return 1 se o menu de perfil será reutilizado | 0 se não 
*/
int perfilUsuario(int id, int verbosidade); 


#endif