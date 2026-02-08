#include "lexer.h"
#include <stdlib.h>

//#include "parser.h"

int jerarquia_op(char op[]){
    int valor = 0;
    if(op[0] == '+' || op[0] == '-'){
        valor = 1;
    } else if(op[0] == '*' || op[0] == '/') {valor = 2;
    }
    else if(op[0] == '^' || op[0] == '#'){
        valor = 3;
    }    return valor;
}

//se desplaza al siguiente nodo y libera en nodo que era la cabecera.
token_t* liberar_mem(token_t *l){
    token_t *aux = l;
    if(aux != NULL){
        free(aux->c);
        l = l->sig;
        free(aux);
    }
    return l;
}

//Devuelte true si el tope de la pila de operadores es mayor al tope de tokens
bool es_mayor(int topeOp,int topeToken){
    return topeOp > topeToken;
}

void separadores(token_t **ops,token_t **pol,token_t **token){
    if((*token)->c[0] == ')'){
        //printf("Intre y este es el operador %s\n",(*token)->c);
        *ops = adelante(*ops,(*token)->c,(*token)->t);
    } else if((*token)->c[0] == '('){
        while(*ops != NULL && (*ops)->c[0] != ')'){
            *pol = adelante(*pol,(*ops)->c,(*ops)->t);
            *ops = liberar_mem(*ops);
        }
        *ops = liberar_mem(*ops);
    }
}


//Es un mounstro grande un pisa fuerte..(???)
token_t* a_pol(token_t **token){
    token_t *ops = NULL;
    token_t *pol = NULL;
    while(*token != NULL){
        if((*token)->t == SEPARADOR){
            separadores(&ops,&pol, token);
        } else if((*token)->t == NUMERO){
            pol = adelante(pol,(*token)->c,(*token)->t);
        } else{
            if(ops == NULL){
                ops = adelante(ops, (*token)->c,(*token)->t);
            } else{
                bool mayorPre = es_mayor(jerarquia_op(ops->c), jerarquia_op((*token)->c));
                if(mayorPre && ops->t != SEPARADOR){
                    //agrego el operador que esta en la cabecera de ops a pol
                    pol = adelante(pol,ops->c,ops->t);
                    //Libero la cabecera de ops(ops se desplaza a su siguiente nodo)
                    ops = liberar_mem(ops);
                    //Agrego el operador que esta en token
                    ops = adelante(ops, (*token)->c,(*token)->t);
                } 
                else {
                    ops = adelante(ops,(*token)->c,(*token)->t);
                }
            }
        }

        *token = liberar_mem((*token));
    }
    while(ops != NULL){
        //agrego el operador que esta en la cabecera de ops a pol
        pol = adelante(pol,ops->c,ops->t);
        //Libero la cabecera de ops(ops se desplaza a su siguiente nodo)
        ops = liberar_mem(ops);

    }

    return pol;
}
