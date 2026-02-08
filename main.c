#include <stdio.h>
#include <stdbool.h>
#include "parser.h"

int sum(int a, int b){
    return a + b;
}

int resta(int a,int b){
    return a - b;
}

int mul(int a,int b){
    return a*b;
}


int pot(int a,int exp){
    int n = a;
    if(exp == 0){
        return 1;
    }else{
        for(int i = 1; i < exp; i++){
            a = a*n; 
        }
    }
    return a;
}

void eval(token_t *token){

}

int main(){
    char expr[256];
    //No se me ocurrio ningún otro nombre
    token_t *token = NULL;
    printf("Ingrese expresion matematica: \n");
    fgets(expr,256,stdin);
    generar_tokens(&token,expr);
    token = a_pol(&token);
    token_t *aux = token;
    while(aux !=NULL){
        printf("%s ",aux->c);
        aux = aux->sig;

	}
    return 0;
  }
