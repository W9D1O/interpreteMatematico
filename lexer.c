#include "lexer.h"
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

token_t* adelante(token_t *lis,char c[], type_t type){
    token_t *aux = (token_t*)malloc(sizeof(token_t));
    //Sugerencia de chatgpt
    if (aux == NULL) {
        fprintf(stderr, "Error: malloc de token_t falló\n");
        exit(EXIT_FAILURE);
}
    aux->c = (char*)malloc(strlen(c) + 1);
    //Sugerencia de chatgpt
    if (aux->c == NULL) {
        fprintf(stderr, "Error: malloc de lexema falló\n");
        free(aux);
        exit(EXIT_FAILURE);
    }
    strcpy(aux->c,c);
    aux->t = type;
    aux->sig = lis;
    return aux;

  }


bool isoperator(char op){
  char *sim = "+-*/^#";
  int len = strlen(sim);
  bool vf = false;
    for(int i =  0; i < len; i++){
        if(sim[i] == op) return true;
    }
  return vf;
}

bool isseparator(char op){
  char *sim = "{}[]()";
  int len = strlen(sim);
  bool vf = false;
    for(int i =  0; i < len; i++){
        if(sim[i] == op) return true;
    }
  return vf;
}
void generar_tokens(token_t **t, char expr[]){
    int len = strlen(expr);
    int pos = 0;
    char dig[21];
    for(int i = 0; i < len ; i++){
        if(isdigit(expr[i])){
            dig[pos] = expr[i];
            pos++;
        } else if(isoperator(expr[i]) || isseparator(expr[i])){
            if(pos > 0){
            dig[pos] = '\0';
            *t = adelante(*t,dig,NUMERO);
            }
            pos = 0;
            char op[2];
            op[0] = expr[i];
            op[1] = '\0';
            if(isseparator(op[0])){
                *t = adelante(*t,op,SEPARADOR);
            } else *t = adelante(*t,op,OPERADOR);
        }
    }

    if(pos > 0){
        dig[pos] = '\0';
        *t = adelante(*t,dig,NUMERO);
    }
}
