#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"
#endif // !PARSER_H
int jerarquia_op(char op[]);
token_t* liberar_mem(token_t *l);
bool es_mayor(int topeOp,int topeToken);
void separadores(token_t *ops,token_t *pol,token_t **token);
token_t* a_pol(token_t **token);
