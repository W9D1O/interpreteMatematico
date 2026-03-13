#include "mate.h"
#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "mistring.h"
#include <string.h>
//Implementar strcat para no usar string.h
//
//devuelve la longitudad de un array
int len(char *src){
    int l = 0;
    while(src[l++] != '\0');

    return l - 1;
}
//convierte una cadena a un valor entero
int to_int(char n[]){
    int j = 0;
    bool vf = isnegativo(n);
    if(vf) j++;
    int num = 0;
    int l = len(n);
    for(int i = j; i < l; i++){
        //CERO es en numero 48 del codigo ascii al restarselo a los caracteres del 0..9 
        //puedo transformarlos en enteros.
       num += pot(BASE,l - 1 - i) * (n[i] - CERO);
    }
    if(vf) num *= -1;
    return num;
}

//Devuelvo una cadena en minuscula
char* to_lower(char arg[])
{
    int lenght = len(arg);
    char *l = (char*)malloc(lenght + 1);
    if(l == NULL) return NULL;
    for(int i = 0; i < lenght; i++){
        if(arg[i] >= A && arg[i] <= Z){
            //32 es la diferencia en el codigo ascii para cada letra del abecedario
            l[i] = arg[i] + L_DIF;
        } else l[i] = arg[i];
    }
    l[lenght] = '\0';
    return l;
}


//Toma un nuimero y devielve su logitud, es decir la cantidad de digitos
//por los que est� formado.
int int_len(int num){
    if(num == 0) return 1;
    if(num < 0) num *= -1;
    int len = 0;
    while(num != 0){
        len++;
        num /= BASE;
    }
    return len;
}

//Convierte un valor entero a una cadena de caracteres
char* int_to_char(int num){
    int len = int_len(num);
    bool vf = false;
    if(num < 0){
        len += 1;
        vf = true;
        num *= -1;
    }
    char *c = (char*)malloc(len + 1);
    for(int i = 0; i < len; i ++){
        c[len - 1 - i] = CERO + (num % BASE);
        num /= BASE;
    }
    if(vf) c[0] = '-';
    c[len] = '\0';
    return c;
}

//Redimensiona un string recibiendo un string y el valor
//de caracteres a acumentar.
char* redim_string(char *c,int aum){
    char *nc = (char*)realloc(c, aum*sizeof(char));
    if(nc == NULL){
        fprintf(stderr,"ERROR: no se pudo redimencionar el string\n");
        exit(1);
    }
    return nc;
}


//Invierte el numero(positivo a negativo) segun un bool
void invert_float(bool vf,int *n,float *no){
    if(vf){
        *no *= -1;
        *n *= -1;
    }

}



//en caso de que el redondeo den intero sea hacia arriba resta 1 para 
//no perder la parte fraccionaria
void pent_pfrac(int *pentera, float *num){
    bool vf = *num < 0;
    invert_float(vf,pentera,num);
    if(*pentera > *num){
        *pentera -= 1;
        *num -= *pentera;
     }else if(*pentera < *num){
        *num -= *pentera;
    }
    invert_float(vf,pentera,num);
}


//Multiplica por la BASE para desplazar la coma
//hasta que sea un entero o se hayan cubierto los 4 decimales.
void float_to_int(int *pentera,int *df,float *num){
    float aux = *num;
    while(aux != 0 && *df < 4){
        aux *= BASE;
        *df += 1;
    }
    *pentera = aux;
}


//Convierte un valor flotante a una cadena de caracteres
char* float_to_char(float num){
    int pentera = num;
    int len = int_len(pentera);
    pent_pfrac(&pentera,&num);
    bool vf = num < 0;
    if(pentera == num){
        char *c = redim_string(int_to_char(pentera),2);
        c[len] = '.';
        c[len + 1] = CERO;
        c[len + 2] = '\0';
        return c;
    }
    char *c = int_to_char(pentera);
    int df = 0;
    pentera = 0;
    float_to_int(&pentera,&df,&num);
    if(vf) pentera *= -1;
    char *nc = redim_string(c,df);
    strcat(nc,".");
    strcat(nc,int_to_char(pentera));
    return nc;
}


//Devuelve la longitud de la parte entera
//o la parte fraccionaria de un numero decimal
int len_pent_pfrac(char *c){
    int pos = 0;
    while(c[pos] != '.' && c[pos] != '\0') pos++;
    return pos;
}

void sep_pent_pfrac(char *c,int len,char *n){
    for(int i = 0; i < len; i++){
        n[i] = c[i];
    }
    n[len] = '\0';
}

//Convierte una cadena de caracteres
//a un numero fraccionario
float to_float(char *c){
    //float epsilon = 0.00001;
    bool vf = isnegativo(c);
    int lenPEnt = len_pent_pfrac(c);
    char pEnt[lenPEnt];
    sep_pent_pfrac(c,lenPEnt,pEnt);
    float result = to_int(pEnt);
    //Probamos con una boludes
    if(vf) result *= -1;
    if(lenPEnt < (int)len(c)){
        int lenPFrac = len_pent_pfrac(&c[lenPEnt + 1]);
        char pFrac[lenPFrac];
        sep_pent_pfrac(&c[lenPEnt + 1],lenPFrac,pFrac);

        for(int i = 1; i <= lenPFrac; i++){
            result += fpot(BASE, i*-1) * (pFrac[i-1] - CERO);
        }
    } else{
        result += fpot(BASE,-1) * ('0' - CERO);
    }
    //Si atado con alambre, lo importante es que funciona
    if(vf) result *= -1;
    return result;
}



bool isequal(char *src1,char *src2){
    bool vf = false;
    int lenght = len(src1);
    if(lenght != len(src2)) return vf;
    
    int i = 0;
    while(i < lenght && src1[i] == src2[i]){
        i++;
    }

    if(i == lenght) vf = true;

    return vf;
}


//reemplaca el caracter seleccionado por sep
//y devuelve la direccion de memoria de donde 
//empezo a leer
char* tokenizar(char input[],char sep,int pos){
    //Sacamos static int pos por el momento
    int aux = pos;
    if(input == NULL) return NULL;
    while(pos < len(input) && input[pos] != sep && input[pos] != '\0') {
        pos++;
      }
    if(aux == pos) return NULL;
    else{
      input[pos] = '\0';
      pos++;
    };
    return  &input[aux];
}

//copia el string de origen al destino
//se tiene que reservar la memoria antes.
void strcopy(char *source,char *dst){
    while((*dst++ = *source++));
}

//Reserva memoria ey copia el string
char *strdupl(char *source){
    char *dup = (char *)malloc(len(source) + 1);
    if(dup == NULL){ 
        fprintf(stderr,"STRDUPL ERROR: no se pudo reservar memoria\n");
        exit(1);
    }
    strcopy(source,dup);
    return dup;
}
//Libera memoria, existe mas que nada por
//strdupl
void strfree(char *src){
    free(src);
}

bool isdig(char d){
    return d >= CERO && d <= NUEVE;
}

bool isfloat(char *num){
    int l = len(num);
    int i = 0;
    bool vf = false;
    while(i < l && isdig(num[i])) i++;
    if(i < l - 1 && num[i] == '.') vf = true;
    return vf;
}
