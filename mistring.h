#ifndef MISTRING_H
#include <stdbool.h>
#define MISTRING_H
//cambiar A y Z tambien lostengo definido en lexer.h
#define A 65
#define Z 90
#define L_DIF 32

int to_int(char n[]);

char* to_lower(char arg[]);

int int_len(int num);

char* int_to_char(int num);

char* redim_string(char *c,int aum);

void invert_float(bool vf,int *n,float *no);


void pent_pfrac(int *pentera, float *num);

void float_to_int(int *pentera,int *df,float *num);
//Convierte un valor flotante a una cadena de caracteres
char* float_to_char(float num);

float to_float(char *c);

int len(char *src);

bool isequal(char *src1,char *src2);

void strcopy(char *source,char *dst);

char* tokenizar(char input[],char sep,int pos);
#endif // !MISTRING_H
