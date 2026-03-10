#ifndef LEXER_H
#define LEXER_H
#include <stdbool.h>
typedef enum {
    OPERADOR = 0, 
    NUMERO_ENTERO,
    NUMERO_FRACCIONARIO,
    SEPARADOR, 
    IDENTIFICADOR,
    IGUAL,
}type_t;

typedef struct token_t{
    char *c;
    type_t t;    
    struct token_t *sig;
} token_t;

#define A_MINUS 97
#define Z_MINUS 122
#define A_MAYUS 65
#define Z_MAYUS 90

token_t* adelante(token_t *lis,char uni[],type_t type);

bool isoperator(char op);

bool isseparator(char op);

bool isidentificador(char ide);

bool isnegativo(char *exp);

void generar_tokens(token_t **t, char expr[]);

#endif // !LEXER_H

