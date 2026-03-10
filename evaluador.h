#ifndef EVALUADOR_H
#define EVALUADOR_H 
#include "mate.h"


int eje_op_int(char op,int n1,int n2);

float eje_op_float(char op,float n1,float n2);


void pent_pfrac(int *pentera, float *num);

void liberar_nodo(token_t *nodo);

void eval(token_t *token);
#endif // !EVALUADOR_H
