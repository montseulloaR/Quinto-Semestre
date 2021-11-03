#include<bits/stdc++.h>
#include<math.h>

float function(float x);
float equisTres(float x0, float x1, float x2);
void IntCuadr(float x0, float x1, float x2, int maxit, float es);

int main()
{
	int maxit;
	float es, x0, x1, x2;
	
	setlocale(LC_ALL, "");
	puts("\tImplementación del algoritmo de la INTERPOLACIÓN CUADRÁTICA\n");
	
	puts("Ingrese X0: ");
	scanf("%f",&x0);
	puts("Ingrese X1: ");
	scanf("%f",&x1);
	puts("Ingrese X2: ");
	scanf("%f",&x2);
	
	puts("\nIngrese el numero maximo de iteraciones: ");
	scanf("%d",&maxit);
	puts("Ingrese el valor de tolerancia de error permitido: ");
	scanf("%f",&es);
	IntCuadr(x0, x1, x2, maxit, es);
	system ("pause");
	return(0);
	
}

float function(float x){
	return 	(5*exp(x) - x*x*x + 2*(x - 5));
}

float equisTres(float x0, float x1, float x2){	
	return ((function(x0)*(x1*x1 - x2*x2) + function(x1)*(x2*x2 - x0*x0) + function(x2)*(x0*x0 - x1*x1))/(2*function(x0)*(x1 - x2) + 2*function(x1)*(x2 - x0) + 2*function(x2)*(x0 - x1)));
}

void IntCuadr(float x0, float x1, float x2, int maxit, float es){
	int iter;
	float f0,f1,f2,f3,ea,x3;
	iter = 0;

	x3 = equisTres(x0, x1, x2);
	f0 = function(x0);
	f1 = function(x1);
	f2 = function(x2);
	f3 = function(x3);


	
	printf("\ni\tx0\tf(x0)\tx1  \tf(x1)  \t  x2  \t  f(x2) \tx3  \tf(x3)  \tea");
	printf("\n0. %f %f %f %f %f %f %f %f %f",x0,function(x0),x1,function(x1),x2,function(x2),x3,function(x3),ea);
	do{
		if(x3>x1){
			x0 = x1;
			x1 = x3;
			ea = ((equisTres(x0, x1, x2)-x3)/x3)*100;
			x3 = equisTres(x0, x1, x2);
		}
		else{
			x2 = x1;
			x1 = x3;
			ea = ((equisTres(x0, x1, x2)-x3)/x3)*100;
			x3 = equisTres(x0, x1, x2);
		}
		
		if(x3 != 0){
			if(ea < 0){
				ea = ea*-1;
			}
		}	
		iter ++;
		printf("\n%d. %f %f %f %f %f %f %f %f %f",iter,x0,function(x0),x1,function(x1),x2,function(x2),x3,function(x3),ea);
	}while(ea>=es && iter < maxit);
	
	printf("\n\nEl valor optimo de x es: %f", x3);
	printf("\nEl valor de la función evaluada en el óptimo: %f", function(x3));
	printf("\nNumero de Iteraciones ejecutadas: %d", iter);
	printf("\nValor del Error Aproximado: %f", ea);
}

