#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mate.h"
#include "lexer.h"
#include "mistring.h"
#include "hash.h"

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

//Enlaza los nodos y libera la memoria del string
void enlazar_y_liberar(token_t *op,token_t *n){
    op->sig = n->sig;
    free(op->c);
}

//Agrega un nuevo string y le asigna el tipo
void guardar_y_asignar(token_t *op,char *num,type_t type){
    op->c = strdupl(num);
    op->t = type;
}

//ejecuta la operacion con numeros flotantes, transforma el 
//resultado en un string y lo vuelve a guardar
void resultado_parcial_f(token_t *op,token_t *num1,token_t *n2){

    float rParcial = eje_op_float(op->c[0],to_float(num1->c),to_float(n2->c));
    enlazar_y_liberar(op,n2);
    guardar_y_asignar(op,float_to_char(rParcial),NUMERO_FRACCIONARIO);
}

//ejecuta la operacion con numeros enteros, transforma el 
//resultado en un string y lo vuelve a guardar
void resultado_parcial(token_t *op,token_t *num1, token_t *n2){

    int rParcial = eje_op_int(op->c[0],to_int(num1->c),to_int(n2->c));
    enlazar_y_liberar(op,n2);
    guardar_y_asignar(op,int_to_char(rParcial),NUMERO_ENTERO);
}

//Inserta un elemento en la tabla, si el elemento existe
//reemplaza el valor
void asignacion(hashtable_t *hash,token_t *valor,token_t *var){
    keyvalue_t item = {
        .valor = strdupl(valor->c),
        .clave = strdupl(var->c)
    };
    insertar_item(hash,item);
    strfree(item.clave);
    strfree(item.valor);
}

//Libera string anterior y reemplaza valor
void reemplazo(token_t *n,char *valor,type_t tipo){

    if(n->c != NULL){
        strfree(n->c);
    }
    n->c = valor;
    n->t = tipo;
}

//Toma un identificador, toma su valor y
//lo reemplaza
void idenficador_valor(hashtable_t *hash,token_t *n){
    char *valor = obtener_valor(hash,n->c);
    if(isfloat(valor)){
        reemplazo(n,valor,NUMERO_FRACCIONARIO);
    }else reemplazo(n,valor,NUMERO_ENTERO);
}

//FIXME: esta funcion crecio demasiado
//Hasta acá no ayudo dion
void eval(token_t *token ,hashtable_t *hash){
    token_t *c = token;
    token_t *op = NULL;
    token_t *num1;
    bool esFloat = false;
    int resulI;
    float resulF;
    while(token != NULL){
        printf("%s\n",token->c);
        if(token->t == OPERADOR){
            op = token;
            num1 = NULL;
            token = token->sig;
        } else if(token->t == NUMERO_ENTERO || token->t == NUMERO_FRACCIONARIO || token->t == IDENTIFICADOR){
            num1 = token;
            token_t *n2 = num1->sig;
            if(n2->t == NUMERO_ENTERO || n2->t == NUMERO_FRACCIONARIO || n2->t == IDENTIFICADOR){
                if(num1->t == NUMERO_ENTERO && n2->t == NUMERO_ENTERO){
                    resultado_parcial(op,num1,n2);
                } else if(num1->t != IDENTIFICADOR && n2->t != IDENTIFICADOR){
                    resultado_parcial_f(op,num1,n2);
                }else {
                    if(num1->t == IDENTIFICADOR && n2->t == IDENTIFICADOR && op->c[0] != '='){
                        idenficador_valor(hash,num1);
                        idenficador_valor(hash,n2);
                        if(num1->t == NUMERO_FRACCIONARIO || n2->t == NUMERO_FRACCIONARIO){
                            resultado_parcial_f(op,num1,n2);
                        } else resultado_parcial(op,num1,n2);
                    } else if(num1->t == IDENTIFICADOR && n2->t == IDENTIFICADOR && op->c[0] == '='){
                        insertar_item(hash, (keyvalue_t){.clave = num1->c,.valor = n2->c});
                        if(isfloat(n2->c)){
                            guardar_y_asignar(op,n2->c,NUMERO_FRACCIONARIO);
                        } else {
                            guardar_y_asignar(op,n2->c,NUMERO_ENTERO);
                        }
                    } else if(num1->t == IDENTIFICADOR && n2->t != IDENTIFICADOR && op->c[0] != '='){
                        idenficador_valor(hash, num1);
                        if(num1->t == NUMERO_FRACCIONARIO || n2->t == NUMERO_FRACCIONARIO){
                            resultado_parcial_f(op,num1,n2);
                        } else resultado_parcial(op,num1,n2);
                    } else if(num1->t == IDENTIFICADOR && n2->t != IDENTIFICADOR && op->c[0] == '='){
                        insertar_item(hash, (keyvalue_t){.clave = num1->c,.valor = n2->c});
                        if(isfloat(n2->c)){
                            enlazar_y_liberar(op,n2);
                            guardar_y_asignar(op,n2->c,NUMERO_FRACCIONARIO);
                        } else {
                            enlazar_y_liberar(op,n2);
                            guardar_y_asignar(op,n2->c,NUMERO_ENTERO);
                        }
                    }else if(num1->t != IDENTIFICADOR && n2->t == IDENTIFICADOR && op->c[0] != '='){
                        idenficador_valor(hash, n2);
                        if(num1->t == NUMERO_FRACCIONARIO || n2->t == NUMERO_FRACCIONARIO){
                            resultado_parcial_f(op,num1,n2);
                        } else resultado_parcial(op,num1,n2);
                    } else if(num1->t != IDENTIFICADOR && n2->t == IDENTIFICADOR && op->c[0] == '='){
                        insertar_item(hash, (keyvalue_t){.clave = n2->c,.valor = num1->c});
                        if(isfloat(n2->c)){
                            enlazar_y_liberar(op,n2);
                            guardar_y_asignar(op,n2->c,NUMERO_FRACCIONARIO);
                        } else {
                            enlazar_y_liberar(op,n2);
                            guardar_y_asignar(op,n2->c,NUMERO_ENTERO);
                        }
                    }
                            
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
