#include <stdio.h>
#include "parser.h"
#include <stdlib.h>
#include <time.h>
#include "evaluador.h"




void imp(token_t *token){
    printf("Imprimiendo Tokens: \n");
    while(token != NULL){
        printf(" %s ",token->c);
        token = token->sig;
    }
    printf("\n");
}



int main(){
    srand(time(NULL));
    char expr[256];
    //No se me ocurrio ning�n otro nombre
    token_t *token = NULL;
    printf("Ingrese expresion matematica: \n");
    fgets(expr,256,stdin);
    generar_tokens(&token,expr);
    imp(token);
    token = a_pol(&token);
    imp(token);
    eval(token);
    return 0;
  }
