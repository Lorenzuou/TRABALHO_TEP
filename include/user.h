#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

#include "util.h"

#define TAM 100

static int qtdUsuarios = 0;
static int qtdUsuariosInativos = 0;

/**
*@brief Struct de usuários que estão armazenados em "usuarios.csv"
*/
typedef struct usuario Usuario; 


/**
* @brief Cria o menu de login, onde o usuario digita nome e senha para acessar o menu principal
* @param usuario endereço do usuário que será atribuido o usuário logado
* @param verbosidade 1 se os menus aparecerão | 0 se não
* @return 2 para sair da aplicacao | 1 se o usuário logou | 0 se não logou
*/
int criarMenuLogin(Usuario *usuario, int verbosidade); 

/**
* @brief Cria o menu principal, onde o usuário pode escolher o que quer fazer no progrma
* @param usuario Usuario que está logado no sistema
* @param verbosiade 1 se os menus aparecerão | 0 se não
* @return 1 se terminou se ser utilizado | 0 se não
*/
int criarMenuPrincipal(Usuario *usuario , int verbosidade);

/**
* @brief Carrega a lista de todos os usuários em "../data/usuarios.csv"
* @return Lista de todos os usuarios (Usuario)
*/
Usuario *carregarUsuarios();

/**
* @brief Carrega a lista de usuários inativos em "../data/inativos.csv"
* @return Vetor com o id dos usuários inativos
*/
int *carregarInativos();

/**
* @brief Recebe nome e senha digitados pelo usuário e verifica se o usuário pode logar
* @param usuario endereço de memória do usuário que será atribuido ao usuário logado
* @param verbosidade 1 se os menus aparecerão | 0 se não
* @return 1 se o usuário logou | 0 se não
*/
int realizarLogin(Usuario *usuario, int verbosidade);

/**
* @brief Realiza o cadastro de um usuário, recebendo nome e senha
* @param verbosidade 1 se os menus aparecerão | 0 se não
* @return 1 se o usuário cadastrou | 0 se não
*/
int realizarCadastro(int verbosidade);

/**
* @brief Exclui a conta do usuário 
* Pré-Condição: Usuário deve ter uma conta cadastrada
* @param inativado id do usuário a ser inativado
* @param verbosidade 1 se os menus aparecerão | 0 se não
*/
void excluirConta(int inativado, int verbosidade);

/**
* @brief Exibe o histórico do usuário de acordo com a opção informada(ordem1)
* Pré-Condição: Usuário deve ter assistido filmes
* @param id id do usuário
* @param ordem 1 para ordenar por nota | 0 para ordenar por data
* @param verbosidade 1 se os menus aparecerão | 0 se não
*/
void verHistorico(int id, int ordem, int verbosidade); 

/**
* @brief Exibe as opcoes do perfil do usuário
* @param id Usuário logado 
* @param verbosidade 1 se os menus aparecerão | 0 se não
 *@return 2 para reexibir as opcoes do perfil do usuário | 1 para voltar para o menu principal | 0 para retornar ao menu de login
*/
int perfilUsuario(int id, int verbosidade); 


/**
* @brief Libera a memória alocada pela função "carregarUsuarios()"
* @param usuarios lista de usuairos a serem liberados
*/
void freeUsuarios(Usuario *usuario); 


#endif