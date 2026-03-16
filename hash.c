#include <stdlib.h>
#include "mistring.h"
#include "hash.h"
#include <stdio.h>
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

//agega elementos a la lista LIFO
//FIXME: se rompe si algun elemnto de item es NULL
hashNodo_t *insertar_adelante(hashNodo_t *nodo, keyvalue_t item) {
    hashNodo_t *aux = (hashNodo_t *)malloc(sizeof(hashNodo_t));
    if(item.clave != NULL){
        aux->item.clave = (char *)malloc(len(item.clave) + 1);
        strcopy(item.clave,aux->item.clave); 
    }
    if(item.valor != NULL){
        aux->item.valor = (char *)malloc(len(item.valor) + 1);
        strcopy(item.valor,aux->item.valor);

    }
    aux->sig = nodo;
    return aux; 
}

//si la clave existe devuelve el nodo, caso contrario devuelve NULL
hashNodo_t *existe(hashNodo_t *nodo, char *clave){
   hashNodo_t *aux = nodo;
    while(aux != NULL && !isequal(aux->item.clave, clave)) {
        aux = aux->sig;
    }
    return aux;
}

//Devuelve el indice correspondiente
//mas que nada para no escribir hash... saraza todo el tiempo.
int obtener_indice(char *clave, int maxsize){
    return hash((unsigned char *)clave) % maxsize;
}

//inserta un elemento al array, si existe la clave reemplaza el valor
void insertar_item(hashtable_t *hash,keyvalue_t item){
    int i = obtener_indice(item.clave,hash->maxsize);
    if(hash->tabla[i] == NULL) hash->tabla[i] = insertar_adelante(hash->tabla[i], item);
    else {
        hashNodo_t *aux = existe(hash->tabla[i],item.clave);
        if(aux == NULL) hash->tabla[i] = insertar_adelante(hash->tabla[i],item);
        else if(aux->item.valor == NULL){
            aux->item.valor = strdupl(item.valor);
        } else{
            strcopy(item.valor, aux->item.valor);
        }  
    } 
    
}

//retorna el nodo anterior
hashNodo_t *nodo_anterior(hashNodo_t *nodo,hashNodo_t *enlace){
    hashNodo_t *ant = NULL;
    while(nodo != enlace) {
        ant = nodo;
        nodo = nodo->sig;
    }    

    return ant;
}

//Libera clave y valor antes de liberar el nodo
void liberar_nodo_hash(hashNodo_t *nodo){
    free(nodo->item.clave);
    free(nodo->item.valor);
    free(nodo);
}

//Elimina un nodo de la lista
void eliminar_item(hashtable_t *hash,char *clave){
    int i = obtener_indice(clave,hash->maxsize);
    hashNodo_t *aux = existe(hash->tabla[i],clave);
    if(aux != NULL) {
        if(aux == hash->tabla[i]){
            hash->tabla[i] = hash->tabla[i]->sig;
            liberar_nodo_hash(aux);
        } else {
           hashNodo_t *ant = nodo_anterior(hash->tabla[i],aux); 
            ant->sig = aux->sig;
            liberar_nodo_hash(aux);
        }
    }
}


void print_tabla(hashtable_t hash){

    for(int i = 0; i < hash.maxsize; i++){
        if(hash.tabla[i] == NULL) printf("%d: Vacio\n",i+1);
        else {
            hashNodo_t *aux = hash.tabla[i];
            while(aux != NULL){
                printf("Elementos de la posicion %d de la tabla\n",i+1);
                printf("Clave: %s Valor: %s\n",aux->item.clave,aux->item.valor);
                aux = aux->sig;
            }
        }
    }
}


//Recerma memoria segun el valor maxsize y lo inicializa en NULL
void init_tabla(hashtable_t *hash){
    hash->tabla = malloc(sizeof(hashNodo_t*)*hash->maxsize);
    if(hash->tabla == NULL){
        fprintf(stderr,"INIT_TABLA ERROR: No se pudo asignar memoria a la tabla hash\n");
        exit(1);
    }
    for(int i = 0; i < hash->maxsize; i++) hash->tabla[i] = NULL;
}

//Recibe una clave y retorna el nodo en la posicion(si hay colisiones recorre los nodos).
//Si la clave no existe en la tabla retorna NULL
hashNodo_t *obtener_elemento(hashtable_t *hash,char *clave){
    hashNodo_t *encontrado = NULL;
    int indice = obtener_indice(clave,hash->maxsize);
    encontrado = existe(hash->tabla[indice],clave);
    return encontrado;
}


char *obtener_valor(hashtable_t *hash,char *clave){
    int i = obtener_indice(clave,hash->maxsize);
    hashNodo_t *nodo = existe(hash->tabla[i],clave);
    char *valor = NULL;
    if(nodo != NULL){
        valor = strdupl(nodo->item.valor);
    }
    return valor;
}
