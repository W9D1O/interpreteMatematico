#include <stdio.h>
#include "parser.h"
#include <stdlib.h>
#include <time.h>
#include "evaluador.h"
#include <conio.h>
#include "mistring.h"

#define MAX_BUFFER 256
#define ENTER 13
#define BACKSPACE 8

#define MAX_TABLA 73

typedef struct {
    char *clave;
    char *valor;
}keyvalue_t;

typedef struct hashNodo_t{
    keyvalue_t item;
    struct hashNodo_t *sig;
}hashNodo_t;


/*djb2
this algorithm (k=33) was first reported by dan bernstein many years ago in comp.lang.c. 
another version of this algorithm (now favored by bernstein) uses xor: hash(i) = hash(i - 1) * 33 ^ str[i];
the magic of number 33 (why it works better than many other constants, prime or not) has never been adequately explained.*/
//source: http://www.cse.yorku.ca/~oz/hash.html

 unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

hashNodo_t *insertar_adelante(hashNodo_t *nodo, keyvalue_t item) {
    hashNodo_t *aux = (hashNodo_t *)malloc(sizeof(hashNodo_t));
    aux->item.clave = (char *)malloc(len(item.clave) + 1);
    aux->item.valor = (char *)malloc(len(item.valor) + 1);
    strcopy(item.clave,aux->item.clave); 
    strcopy(item.valor,aux->item.valor);
    aux->sig = nodo;
    return aux; 
}

//si la clave existe devuelve el nodo, caso contrario devuel NULL
hashNodo_t *existe(hashNodo_t *nodo, char *clave){
   hashNodo_t *aux = nodo;
    while(aux != NULL && !isequal(aux->item.clave, clave)) {
        aux = aux->sig;
    }
    return aux;
}

//inserta un elemento al array, si existe la clave reemplaza el valor
void insertar_item(hashNodo_t **tabla,keyvalue_t item){
    int i = hash(item.clave) % MAX_TABLA;

    if(tabla[i] == NULL) tabla[i] = insertar_adelante(tabla[i], item);
    else {
        hashNodo_t *aux = existe(tabla[i],item.clave);
        if(aux == NULL) tabla[i] = insertar_adelante(tabla[i],item);
        else aux->item.valor = item.valor;
    } 
    
}

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

void ditpatcher(char *command,char *argv,bool *status){

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
        ditpatcher(command,&expr[nxtpos],&status);
    }
    printf("%s\n",expr);

}

int main(){
    hashNodo_t *tabla[MAX_TABLA];
    (void)tabla;
    srand(time(NULL));
    char expr[MAX_BUFFER];
    //No se me ocurrio ning�n otro nombre
    //relp(expr); 
    token_t *token = NULL;
    printf("Ingrese expresion matematica: \n");
    fgets(expr,256,stdin);
    generar_tokens(&token,expr);
    imp(token);
    token = a_pol(&token);
    imp(token);

    //eval(token);
    return 0;
  }
