#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "parser.h"
#include <stdlib.h>
#include <time.h>
#include "mate.h"


//convierte una cadena a un valor entero
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
    int resul;
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

//Redimensiona un string recibiendo un string y el valor
//de caracteres a acumentar.
char* redim_string(char *c,int aum){
    char *nc = (char*)realloc(c, aum*sizeof(char));
    if(nc == NULL){
        fprintf(stderr,"ERROR: no se pudo redimencionar el string\n");
        exit(1);
    }
    return nc;
}

//en caso de que el redondeo den intero sea hacia arriba resta 1 para 
//no perder la parte fraccionaria
void pent_pfrac(int *pentera, float *num){

    if(*pentera > *num){
        *pentera -= 1;
        *num -= *pentera;
     }else if(*pentera < *num){
        *num -= *pentera;
    }
}


//Multiplica por la BASE para desplazar la coma
//hasta que sea un entero o se hayan cubierto los 4 decimales.
void float_to_int(int *pentera,int *df,float *num){
    while(*num != 0 && *df < 4){
        *num *= BASE;
        int dig = (int)*num;
        pent_pfrac(&dig, num);
        *pentera = *pentera*BASE + dig;
        *df += 1;
    }
}



//Convierte un valor flotante a una cadena de caracteres
char* float_to_char(float num){
    int pentera = (int)num;
    int len = int_len(pentera);
    pent_pfrac(&pentera,&num);
    if(pentera == num){
        char *c = redim_string(int_to_char(pentera),2);
        c[len] = '.';
        c[len + 1] = CERO;
        c[len + 2] = '\0';
        return c;
    }
    char *c = int_to_char(pentera);
    int df = 0;
    pentera = 0;
    float_to_int(&pentera,&df,&num);
    char *nc = redim_string(c,df);
    strcat(nc,".");
    strcat(nc,int_to_char(pentera));
    return nc;
}


//Devuelve la longitud de la parte entera
//o la parte fraccionaria de un numero decimal
int len_pent_pfrac(char *c){
    int pos = 0;
    while(c[pos] != '.' && c[pos] != '\0') pos++;
    return pos;
}

void sep_pent_pfrac(char *c,int len,char *n){
    for(int i = 0; i < len; i++){
        n[i] = c[i];
    }
    n[len] = '\0';
}

//Convierte una cadena de caracteres
//a un numero fraccionario
float to_float(char *c){
    float epsilon = 0.00001;
    int lenPEnt = len_pent_pfrac(c);
    char pEnt[lenPEnt];
    sep_pent_pfrac(c,lenPEnt,pEnt);
    float result = (float)to_int(pEnt);
    if(lenPEnt < (int)strlen(c)){
        int lenPFrac = len_pent_pfrac(&c[lenPEnt + 1]);
        char pFrac[lenPFrac];
        sep_pent_pfrac(&c[lenPEnt + 1],lenPFrac,pFrac);

        for(int i = 1; i <= lenPFrac; i++){
            result += fpot(BASE, i*-1) * (pFrac[i-1] - CERO);
        }
    } else{
        result += fpot(BASE,-1) * ('0' - CERO);
    }
    return result + epsilon;
}

void liberar_nodo(token_t *nodo){
    free(nodo->c);
    free(nodo);
}

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
			  //TODO: solucionar el problema con numeros fraccionarios			  
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


void imp(token_t *token){
    while(token != NULL){
        printf("%s ",token->c);
        token = token->sig;
    }
    printf("\n");
}

int main(){
  srand(time(NULL));
    char expr[256];
    //No se me ocurrio ning�n otro nombre
    token_t *token = NULL;
    printf("Ingrese expresion matematica: \n");
    fgets(expr,256,stdin);
    generar_tokens(&token,expr);
    imp(token);
    token = a_pol(&token);
    eval(token);
    return 0;
  }
