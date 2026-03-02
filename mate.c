#include <stdio.h>
#include <stdlib.h>



int sum(int a, int b){
    return a + b;
}

int resta(int a,int b){
    return a - b;
}

int mul(int a,int b){
    return a*b;
}

int division(int a,int b){

    if(b == 0){
      fprintf(stderr,"ERROR: La division por cero no esta definida\n");
      exit(1);
    }
    return a / b;
}

float fsum(float a, float b){
    return a + b;
}

float fresta(float a,float b){
    return a - b;
}

float fmul(float a,float b){
    return a*b;
}

float fdivision(float a,float b){

    if(b == 0){
      fprintf(stderr,"ERROR: La division por cero no esta definida\n");
      exit(1);
    }
    return a / b;
}

int pot(int num,int exp){
    if(exp < 0){
         fprintf(stderr,"ERROR: No se pueden calcular exponentes negativos\n");
	 exit(1);
    }
    int n = num;
    if(exp == 0){
        return 1;
    }else{
        for(int i = 1; i < exp; i++){
            num = num*n; 
        }
    }
    return num;
}

float fpot(float num,int exp){
    float n = num;
    if(exp < 0){
        exp *= -1;
        for(int i = 1; i < exp; i++){
            num = num*n; 
        }
        return  1 / num;
    }
    if(exp == 0){
        return 1;
    }else{
        for(int i = 1; i < exp; i++){
            num = num*n; 
        }
    }
    return num;
}


int myabs(int n){
  if(n < 0) return n * -1;
  return n;
}


//Metodo babilonico
float raiz_cuadrada(float a){
  int r = a / 2;
  float h,b;
  float epsilon = 0.00001;
	do{
	  h = rand() % r;
	  b = rand() % r;
	}while(b*h != a);
  while(myabs(h - b) > epsilon){
	b = (h + b) * 0.5; //0.5 es lo mismo que dividir por 2
	h = a /b;
  }

  return b;
}

float raiz(float a,int b){
  if(b < 1){
	fprintf(stderr,"ERROR: Raiz invalida.\n");
	exit(1);
  } else if(b > 2){
	fprintf(stderr,"ERROR: Las raices mayores a 2 no se encuentran implmentadas.\n");
	exit(1);
  }
  return raiz_cuadrada(a);
}
