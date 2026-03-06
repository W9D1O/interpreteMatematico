#ifndef EVALUADOR_H
#define EVALUADOR_H 
#include "mate.h"

int to_int(char n[]);

int eje_op_int(char op,int n1,int n2);

float eje_op_float(char op,float n1,float n2);

int int_len(int num);

char* int_to_char(int num);

char* redim_string(char *c,int aum);

void invert_float(bool vf,int *n,float *no);

void pent_pfrac(int *pentera, float *num);

void float_to_int(int *pentera,int *df,float *num);

char* float_to_char(float num);

int len_pent_pfrac(char *c);

void sep_pent_pfrac(char *c,int len,char *n);

float to_float(char *c);

void liberar_nodo(token_t *nodo);

void eval(token_t *token);
#endif // !EVALUADOR_H
