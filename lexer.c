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
        fprintf(stderr, "Error: malloc de token_t fallÃ³\n");
        exit(EXIT_FAILURE);
}
    aux->c = (char*)malloc(strlen(c) + 1);
    //Sugerencia de chatgpt
    if (aux->c == NULL) {
        fprintf(stderr, "Error: malloc de lexema fallÃ³\n");
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


bool isidentificador(char c){
  if((c >= A_MINUS && c <= Z_MINUS) ||
     (c >= A_MAYUS && c <= Z_MAYUS)) return true;
  return false;
}

// Se toma como un valor negativo 
// a una expresion de la siguiente forma
// -n es decir - n no es un numero negativo
bool isnegativo(char *exp){
    if(exp[0] != '-') return false;
    bool vf = false;
    int len = strlen(exp);
    if(len > 1 && isdigit(exp[1])){
        vf = true;
    }
    return vf;
    
}

void generar_tokens(token_t **t, char expr[]){
    int len = strlen(expr);
    int pos = 0;
    char dig[21];
	bool frac = false;
    for(int i = 0; i < len ; i++){
        if(isdigit(expr[i]) || expr[i] == '.' || isnegativo(&expr[i])){
            dig[pos] = expr[i];
            pos++;
			if(expr[i] == '.') frac = true;
        } else if(isoperator(expr[i]) || isseparator(expr[i])){
            if(pos > 0){
            dig[pos] = '\0';
			if(!frac)
            *t = adelante(*t,dig,NUMERO_ENTERO);
			else{
			  *t = adelante(*t,dig,NUMERO_FRACCIONARIO);
			  frac = false;
			}
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
		if(!frac)
        *t = adelante(*t,dig,NUMERO_ENTERO);
		else *t = adelante(*t,dig,NUMERO_FRACCIONARIO);
    }
}
