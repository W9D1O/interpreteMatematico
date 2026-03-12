#ifndef HASH_H

#define HASH_H

#define MAX_TABLA 73

typedef struct {
    char *clave;
    char *valor;
}keyvalue_t;

typedef struct hashNodo_t{
    keyvalue_t item;
    struct hashNodo_t *sig;
}hashNodo_t;

unsigned long hash(unsigned char *str);


hashNodo_t *existe(hashNodo_t *nodo, char *clave);

int obtener_indice(char *clave);

void insertar_item(hashNodo_t **tabla,keyvalue_t item);

void eliminar_item(hashNodo_t **tabla,char *clave);

hashNodo_t *obtener_elemento(hashNodo_t **tabla,char *clave);
#endif // !HASH_H
