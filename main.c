#include <stdio.h>
#include "lexer.h"
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

void calc(char *argv,hashtable_t **hash){

    token_t *token;
    generar_tokens(&token,argv);
    token = a_pol(&token);
    eval(token, *hash);
}

/*Por el momento para poder diferenciar la                 *
 *declaracion de la asignacion vamos a crear               *
 *la variable que queremos declarar y despues le asignamos *
 *el vamor, es choto pero va a servir para generar un error*
 *si no tenemos la variable declarada cuando queremos hacer*
 *alguna asignacion*/
void let(hashtable_t **hash,char *argv){
    char *var = tokenizar(argv,' ',0);
    keyvalue_t item = {
        .clave = strdupl(var),
        .valor = "",
    };
    argv[len(var)] = ' ';
    insertar_item(*hash,item);
    strfree(item.clave);
    token_t *token;
    generar_tokens(&token,argv);
    token = a_pol(&token);
    eval(token, *hash);
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

void dispatcher(char *command,char *argv,bool *status,hashtable_t *hash){

    if(isequal(to_lower(command), "exit")){
        *status = new_exit();
    } else if(isequal(to_lower(command),"let")){
        let(&hash,argv);
    } else if(isequal(to_lower(command),"calc")){
        printf("entre\n");
        calc(argv, &hash);
    }
    else {
        /*command[len(command)] = ' ';
        token_t *tok;
        generar_tokens(&tok,command);
        imp(tok);
        tok = a_pol(&tok);
        printf("%s\n",command);
        eval(tok,hash);
        */
    }
}


void relp(char *expr,hashtable_t *hash){
    bool status = true;
    while(status){
        cargar_buffer(expr);
        char *command = tokenizar(expr,' ',0);
        int nxtpos = len(command) + 1;
        dispatcher(command,&expr[nxtpos],&status,hash);
    }
    printf("%s\n",expr);

}

int main(){
    hashtable_t hash;
    hash.maxsize = 73;
    srand(time(NULL));
    char expr[MAX_BUFFER];
    //No se me ocurrio ning�n otro nombre
    init_tabla(&hash);
    relp(expr,&hash); 
    /*token_t *token = NULL;
    printf("Ingrese expresion matematica: \n");
    fgets(expr,256,stdin);
    generar_tokens(&token,expr);
    imp(token);
    token = a_pol(&token);
    imp(token);
    init_tabla(&hash);
    insertar_item(&hash, (keyvalue_t){.clave = "a", .valor = "12"});
    insertar_item(&hash, (keyvalue_t){.clave = "b", .valor = NULL});
    insertar_item(&hash, (keyvalue_t){.clave = "c", .valor = "83"});
    eval(token,&hash);
    print_tabla(hash);*/

    return 0;
  }
