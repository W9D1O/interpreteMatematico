#ifndef HASH_H

#define HASH_H

//#define MAX_TABLA 73

typedef struct {
    char *clave;
    char *valor;
}keyvalue_t;

typedef struct hashNodo_t{
    keyvalue_t item;
    struct hashNodo_t *sig;
}hashNodo_t;

typedef struct{
    int maxsize;
    hashNodo_t **tabla;
}hashtable_t;
//No me termina de convencer el nombre de hashtable_t

void init_tabla(hashtable_t *hash);

void print_tabla(hashtable_t hash);

unsigned long hash(unsigned char *str);


hashNodo_t *existe(hashNodo_t *nodo, char *clave);

int obtener_indice(char *clave,int maxsize);

void insertar_item(hashtable_t *hash,keyvalue_t item);

void eliminar_item(hashtable_t *hash,char *clave);

hashNodo_t *obtener_elemento(hashtable_t *table,char *clave);
#endif // !HASH_H
