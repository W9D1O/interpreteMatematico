#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "parser.h"



#define CERO 48

int sum(int a, int b){
    return a + b;
}

int resta(int a,int b){
    return a - b;
}

int mul(int a,int b){
    return a*b;
}

int division(int a,int b){
    if(b < 1){
        fprintf(stderr,"ERROR: La division por cero no esta definida\n");
    }
    return a / b;
}

int pot(int num,int exp){
    if(exp < 0){
        fprintf(stderr,"ERROR: No se pueden calcular exponentes negativos\n");
    }
    int n = num;
    if(exp == 0){
        return 1;
    }else{
        for(int i = 1; i < exp; i++){
            num = num*n; 
        }
    }
    return num;
}


int raiz(int a,int b){
    int resul = -1;
    fprintf(stderr,"ERROR: No implementado\n");
    return resul;
}

int to_int(char n[]){
    int num = 0;
    int base = 10;
    int len = strlen(n);
    for(int i = 0; i < len; i++){
        //CERO es en numero 48 del codigo ascii al restarselo a los caracteres del 0..9 
        //puedo transformarlos en enteros.
       num += pot(base,len - 1 - i) * (n[i] - CERO);
    }
    return num;
}


int ejecutar_operacion(char op,int n1,int n2){
    int resul;
    switch (op) {
        case '+': 
            resul = sum(n1,n2);
            break;
        case '-':
            resul = resta(n1,n2);
            break;
        case '/':
            resul = division(n1,n2);
            break;
        case '*':
            resul = mul(n1,n2);
            break;
        case '#':
            resul = raiz(n1,n2);
    }
    return resul;
}

void eval(token_t *token){
    token_t *c = token;
    token_t *op = NULL;
    token_t *num1 = NULL;
    while(token != NULL){
        if(token->t == OPERADOR){
            op = token;
            num1 = NULL;
        }else if(token->t == NUMERO && num1 == NULL){
            num1 = token; 
        }else if (token->t == NUMERO){
            
        }
    }
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

    while(token != NULL){
        token = liberar_mem(token);
    }
    return 0;
  }
