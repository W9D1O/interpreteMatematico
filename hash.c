#include <stdlib.h>
#include "mistring.h"
#include "hash.h"
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

//Devuelve el indice correspondiente
//mas que nada para no escribir hash... saraza todo el tiempo.
int obtener_indice(char *clave){
    //FIXME: Me acabo de dar cuenta que no es una muy buena idea tener definido el limite
    //es mejor poder definilo cuando se lo quiera usar.
    //por el momento voy a dejar definido MAX_TABLA en hash.h
    return hash((unsigned char *)clave) % MAX_TABLA;
}

//inserta un elemento al array, si existe la clave reemplaza el valor
void insertar_item(hashNodo_t **tabla,keyvalue_t item){
    int i = obtener_indice(item.clave);

    if(tabla[i] == NULL) tabla[i] = insertar_adelante(tabla[i], item);
    else {
        hashNodo_t *aux = existe(tabla[i],item.clave);
        if(aux == NULL) tabla[i] = insertar_adelante(tabla[i],item);
        else strcopy(item.valor, aux->item.valor);
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
void eliminar_item(hashNodo_t **tabla,char *clave){
    int i = obtener_indice(clave);
    hashNodo_t *aux = existe(tabla[i],clave);
    if(aux != NULL) {
        if(aux == tabla[i]){
            tabla[i] = tabla[i]->sig;
            liberar_nodo_hash(aux);
        } else {
           hashNodo_t *ant = nodo_anterior(tabla[i],aux); 
            ant->sig = aux->sig;
            liberar_nodo_hash(aux);
        }
    }
}



//Recibe una clave y retorna el nodo en la posicion(si hay colisiones recorre los nodos).
//Si la clave no existe en la tabla retorna NULL
hashNodo_t *obtener_elemento(hashNodo_t **tabla,char *clave){
    hashNodo_t *encontrado = NULL;
    int indice = obtener_indice(clave);
    if(tabla[indice] != NULL && tabla[indice]->item.clave == clave) encontrado  = tabla[indice];
    else {
        hashNodo_t *aux = tabla[indice];
        while(aux != NULL && aux->item.clave != clave) aux = aux->sig;
        encontrado = aux;
    }
    return encontrado;
}
