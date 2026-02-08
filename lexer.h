#ifndef LEXER_H
#define LEXER_H
#include <stdbool.h>
#endif // !LEXER_H

typedef enum {
    OPERADOR = 0, 
    NUMERO,
    SEPARADOR, 
    IDENTIFICADOR,
}type_t;

typedef struct token_t{
    char *c;
    type_t t;    
    struct token_t *sig;
} token_t;



token_t* adelante(token_t *lis,char uni[],type_t type);

bool isoperator(char op);

bool isseparator(char op);

void generar_tokens(token_t **t, char expr[]);
