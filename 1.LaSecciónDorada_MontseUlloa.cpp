#include<bits/stdc++.h>
#include<math.h>

float function(float x);
void Golden(int xL, int xU, int maxit, float es, float function(float x));

int main()
{
	int maxit;
	float es, xL, xU;
	
	setlocale(LC_ALL, "");
	puts("\tImplementación del algoritmo de la SECCION DORADA\n");
	
	puts("Ingrese el limite inferior: ");
	scanf("%f",&xL);
	puts("Ingrese el limite superior: ");
	scanf("%f",&xU);
	
	puts("\nIngrese el numero maximo de iteraciones: ");
	scanf("%d",&maxit);
	puts("Ingrese el Valor de Tolerancia de Error: ");
	scanf("%f",&es);
	Golden(xL,xU,maxit,es,function);
}

float function(float x)
{
	return -(x*x) + 10*exp(0.1*x);
}

void Golden(int xL, int xU, int maxit, float es, float function(float x))
{
	int iter;
	float f1,f2,r,x1,x2,xl,xu,ea,xopt,d,gold;
	iter = 0;
	r = (sqrt(5) - 1)/2;
	xl = xL;
	xu = xU;
	d = r * (xu -xl);
	x1 = xl + d;
	x2 = xu - d;
	f1 = function(x1);
	f2 = function(x2);

	if(f1 > f2){xopt = x1;}
	else{xopt = x2;}
	
	printf("\n i\tx\tf(x1)\tf(x2)\tea");
	do{
		if(f1>f2){
			xu = xu;
			xl = x2;
			x2 = x1;
			d = r * (xu - xl);
			x1 = (xl+d);
			f2 = f1;
			f1 = function(x1);
		}
		else{
			xl = xl;
			xu = x1;
			x1 = x2;
			d = r * (xu - xl);
			x2 = (xu-d);
			f1 = f2;
			f2 = function(x2);}
			iter = iter + 1;
			
		if(f1 > f2){xopt = x1;}
		else{xopt = x2;}
		
		if(xopt != 0){
			ea = (1 - r)* ((xu-xl)/xopt)*100;
			if(ea < 0){
				ea = ea*-1;
			}
		}	
		printf("\n%d. %f %f %f %f",iter,function(x1),function(x2),xopt,ea);
	}while(ea>=es && iter < maxit);
	gold = xopt;	

	
	printf("\n\nEl valor optimo de x es: %f", gold);
	printf("\nLa altura en este punto es: %f", function(xopt));
	printf("\nNumero de Iteraciones ejecutadas: %d", iter);
	printf("\nValor del Error Aproximado: %f", ea);
}

