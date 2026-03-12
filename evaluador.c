#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mate.h"
#include "lexer.h"
#include "mistring.h"


int eje_op_int(char op,int n1,int n2){
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
            resul = (int)raiz((float)n1,n2);
            break;
        case '^':
            resul = pot(n1,n2);
            break;
    }
    return resul;
}

float eje_op_float(char op,float n1,float n2){
    float resul;
    switch (op) {
        case '+': 
            resul = fsum(n1,n2);
            break;
        case '-':
            resul = fresta(n1,n2);
            break;
        case '/':
            resul = fdivision(n1,n2);
            break;
        case '*':
            resul = fmul(n1,n2);
            break;
        case '#':
            resul = raiz(n1,n2);
            break;
        case '^':
            resul = fpot(n1,n2);
            break;
    }
    return resul;
}





void liberar_nodo(token_t *nodo){
    free(nodo->c);
    free(nodo);
}


//FIXME: esta funcion crecion demasiado
void eval(token_t *token){
    token_t *c = token;
    token_t *op = NULL;
    token_t *num1;
    bool esFloat = false;
    int resulI;
    float resulF;
    while(token != NULL){
        if(token->t == OPERADOR){
            op = token;
            num1 = NULL;
            token = token->sig;
        } else if(token->t == NUMERO_ENTERO || token->t == NUMERO_FRACCIONARIO){
            num1 = token;
            token_t *n2 = num1->sig;
            if(n2->t == NUMERO_ENTERO || n2->t == NUMERO_FRACCIONARIO){
                if(num1->t == NUMERO_ENTERO && n2->t == NUMERO_ENTERO){
                    int rParcial = eje_op_int(op->c[0],to_int(num1->c),to_int(n2->c));
                    op->sig = n2->sig;
                    free(op->c);
                    op->c = int_to_char(rParcial);
                    op->t = NUMERO_ENTERO;
                } else{
                    float rParcial = eje_op_float(op->c[0],to_float(num1->c),to_float(n2->c));
                    op->sig = n2->sig;
                    free(op->c);
                    op->c = float_to_char(rParcial);
                    op->t = NUMERO_FRACCIONARIO;
                }
                liberar_nodo(num1);
                liberar_nodo(n2);
                if(op == c){
                    if(op->sig == NULL){
                        token = NULL;
                        if(op->t == NUMERO_ENTERO) {
                            resulI = to_int(op->c);
                            liberar_nodo(op);
                        } else{
                            esFloat = true;
                            resulF = to_float(op->c);
                            liberar_nodo(op);
                        }
                    }else{
                        token = op->sig;
                    }
                }else{
                    token = c;
                }
            }else if(n2->t == OPERADOR){
                op = n2;
                token = op->sig;
            }
        }
    }
    if(esFloat) printf("%f\n",resulF);
    else printf("%d\n",resulI);
}
