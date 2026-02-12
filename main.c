#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "parser.h"
#include <stdlib.h>


#define CERO 48
#define BASE 10

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
    if(b == 0){
        return fprintf(stderr,"ERROR: La division por cero no esta definida\n");
    }
    return a / b;
}

int pot(int num,int exp){
    if(exp < 0){
        return fprintf(stderr,"ERROR: No se pueden calcular exponentes negativos\n");
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
    return fprintf(stderr,"ERROR: No implementado\n");
    return resul;
}

//conviente una cadena a un valor entero
int to_int(char n[]){
    int num = 0;
    int len = strlen(n);
    for(int i = 0; i < len; i++){
        //CERO es en numero 48 del codigo ascii al restarselo a los caracteres del 0..9 
        //puedo transformarlos en enteros.
       num += pot(BASE,len - 1 - i) * (n[i] - CERO);
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


//Toma un nuimero y devielve su logitud, es decir la cantidad de digitos
//por los que est� formado.
int int_len(int num){
    if(num == 0) return 1;
    if(num < 0) num *= -1;
    int len = 0;
    while(num != 0){
        len++;
        num /= BASE;
    }
    return len;
}

//Convierte un valor entero a una cadena de caracteres
char* int_to_char(int num){
    int len = int_len(num);
    char *c = (char*)malloc(len + 1);
    for(int i = 0; i < len; i ++){
        c[len - 1 - i] = CERO + (num % BASE);
        num /= BASE;
    }
    c[len] = '\0';
    return c;
}

void liberar_nodo(token_t *nodo){
    free(nodo->c);
    free(nodo);
}



int eval(token_t *token){
    token_t *c = token;
    token_t *op = NULL;
    token_t *num1;
    int resul;
    while(token != NULL){
        if(token->t == OPERADOR){
            op = token;
            num1 = NULL;
            token = token->sig;
        } else if(token->t == NUMERO){
            num1 = token;
            token_t *n2 = num1->sig;
            if(n2->t == NUMERO){
                int rParcial = ejecutar_operacion(op->c[0],to_int(num1->c),to_int(n2->c));
                op->sig = n2->sig;
                free(op->c);
                op->c = int_to_char(rParcial);
                op->t = NUMERO;
                liberar_nodo(num1);
                liberar_nodo(n2);
                if(op == c){
                    if(op->sig == NULL){
                        token = NULL;
                        resul = to_int(op->c);
                        liberar_nodo(op);
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
    return resul;
}

int main(){
    char expr[256];
    //No se me ocurrio ning�n otro nombre
    token_t *token = NULL;
    printf("Ingrese expresion matematica: \n");
    fgets(expr,256,stdin);
    generar_tokens(&token,expr);
    token = a_pol(&token);
    printf("%d\n",eval(token));
    return 0;
  }
