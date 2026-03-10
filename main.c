#include <stdio.h>
#include "parser.h"
#include <stdlib.h>
#include <time.h>
#include "evaluador.h"
#include <conio.h>
#include <string.h>

#define MAX_BUFFER 256
#define ENTER 13
#define BACKSPACE 8

//recibe input del usuario
void cargar_buffer(char *input){
    int i = 0;
    bool status = true;
    char c;
    //Leo caracteras hasta recibir la tecla enter o hasta
    //llegar al maximo -1 para poder agregar el correspondiente fin de linea
    char *promt = ">>> ";
    printf("%s",promt);
    while(status && (c = _getch()) && i < MAX_BUFFER - 1){
        if(c == ENTER) status = false;
        
        if(status && c != BACKSPACE){
            printf("%c",c);
            input[i++] = c;
        } else if(c == BACKSPACE && i > 0) {
            printf("%c",c);
            i--;
        }
    }
    printf("\r\n");
    input[i++] = '\0';
}

bool new_exit(){
    return false;
}

void imp(token_t *token){
    printf("Imprimiendo Tokens: \n");
    while(token != NULL){
        printf(" %s ",token->c);
        token = token->sig;
    }
    printf("\n");
}

void ditpatcher(){

}

void relp(char *expr){
    bool status = true;
    while(status){
        cargar_buffer(expr);
    }
    printf("%s\n",expr);

}

int main(){
    srand(time(NULL));
    char expr[MAX_BUFFER];
    //No se me ocurrio ning�n otro nombre
    relp(expr); 
    return 0;
    /*token_t *token = NULL;
    printf("Ingrese expresion matematica: \n");
    fgets(expr,256,stdin);
    generar_tokens(&token,expr);
    imp(token);
    token = a_pol(&token);
    imp(token);
    eval(token);
    return 0;*/
  }
