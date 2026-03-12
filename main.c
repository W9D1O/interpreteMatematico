#include <stdio.h>
#include "parser.h"
#include <stdlib.h>
#include <time.h>
#include "evaluador.h"
#include <conio.h>
#include "mistring.h"
#include "hash.h"

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

void calc(){

}

void let(){

}

void help(){

}

void print(){

}

void imp(token_t *token){
    printf("Imprimiendo Tokens: \n");
    while(token != NULL){
        printf(" %s ",token->c);
        token = token->sig;
    }
    printf("\n");
}

void dispatcher(char *command,char *argv,bool *status){

    if(isequal(to_lower(command), "exit")){
        *status = new_exit();
    }
    (void)argv;
}


void relp(char *expr){
    bool status = true;
    while(status){
        cargar_buffer(expr);
        char *command = tokenizar(expr,' ',0);
        int nxtpos = len(command) + 1;
        dispatcher(command,&expr[nxtpos],&status);
    }
    printf("%s\n",expr);

}

void print_tabla(hashNodo_t **tabla){
    for(int i = 0; i < MAX_TABLA; i++){
        if(tabla[i] == NULL) printf("%d: Vacio\n",i+1);
        else {
            while(tabla[i] != NULL){
                printf("Elementos de la posicion %d de la tabla\n",i+1);
                printf("Clave: %s Valor: %s\n",tabla[i]->item.clave,tabla[i]->item.valor);
                tabla[i] = tabla[i]->sig;
            }
        }
    }
}

void init_tabla(hashNodo_t **tabla){
    for(int i = 0; i < MAX_TABLA; i++) tabla[i] = NULL;
}
int main(){
    hashNodo_t *tabla[MAX_TABLA];
    srand(time(NULL));
    /*char expr[MAX_BUFFER];
    //No se me ocurrio ning�n otro nombre
    //relp(expr); 
    token_t *token = NULL;
    printf("Ingrese expresion matematica: \n");
    fgets(expr,256,stdin);
    generar_tokens(&token,expr);
    imp(token);
    token = a_pol(&token);
    imp(token);*/
    init_tabla(tabla);
    insertar_item(tabla, (keyvalue_t){.clave = "hola",.valor = "69"});
    insertar_item(tabla, (keyvalue_t){.clave = "HOLA",.valor = "96"});
    insertar_item(tabla, (keyvalue_t){.clave = "hola",.valor = "220"});
    print_tabla(tabla);
    //eval(token);
    return 0;
  }
