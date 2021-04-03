#include <stdio.h>
#include <stdlib.h>
#include "../include/user.h"










// void criarMenu()
// {
//     char entrada;
//     scanf("%c", &entrada);
    
//     switch (entrada)
//     {
//     case '1':
//         realizarLogin();
//         break;
//     case '2':
//         realizarCadastro();
//         break;
//     case '3':
//         // procurarFilme();
//         break;
//     case '4':

//         break;

//     default:
//         break;
//     }
// }

int main()
{
    int verificar = 0; 

    while(!verificar){ // Enquanto não houver um usuário logado, o menu será chamado    
    verificar = criarMenuLogin(); 
    }
    if(verificar == 1){ // Verifica se o usuario está de fato logado

    }

     

    return 0;
}