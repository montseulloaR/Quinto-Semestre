//Montserat Alejandra Ulloa Rivera 
//Recocido Simulado
//Optimización Computacional 5°A
#include <stdlib.h>
#include <time.h>
#include<iostream>
#include <math.h>
#include <stdio.h>

int recorrido[8] = {1,2,3,4,5,6,7,1};
int aux[8];
int grafo[7][7] = {{0,12,10,0,0,0,12}, //1 = 0
				   {12,0,8,12,0,0,0},
				   {10,8,0,11,3,0,9},
				   {0,12,11,0,11,10,0},
				   {0,0,3,11,0,6,7},
				   {0,0,0,10,6,0,9},
				   {12,0,9,0,7,9,0,}};
int main()
{
	int sum=0,num,num1,aux1=0,sum1,aux2=0,iter,aux3=0; 
	float t,to,tf,p,a;
	double prob,num2,elev;
	printf("Ingrese la temperatura inicial: ");
	scanf("%f",&to);
	printf("Ingrese la temperatura final: ");
	scanf("%f",&tf);
	printf("Ingrese el numero de iteraciones: ");
	scanf("%d",&iter);
	printf("Factor de enfriamiento: ");
	scanf("%f",&a);
	printf("Factor de reduccion de iteraciones: ");
	scanf("%f",&p);
	t = to;
	srand(time(NULL));
	do{
	for(int k=0;k<=iter;k++) //for de las k's iteraciones
	{	
	//Comprobando el camino
	do{
	for(int y=0;y<=7;y++)
	{
		aux[y] = recorrido[y];
	}
	sum=0;
	sum1=0;
	aux2=0;
	num = 2 + rand()%(5); //primer numero aleatorio	
	aux1 = num;
	num1 = aux1 + rand()%(8 - aux1);//segundo numero aleatorio
	aux3 = num1;
	for(int y=num;y<=num1;y++)
	{
		aux[y-1] = recorrido[aux3-1];
		aux3--;
	}
	aux3=0;
	//tenemos que verificar que el camino sea valido y se realiza su suma
	for(int z=0;z<=6;z++)
	{
		//12345671
		if(grafo[aux[z]-1][aux[z+1]-1] != 0)
		{
			//Si hay camino
			sum = grafo[aux[z]-1][aux[z+1]-1] + sum; //coste del recorrido actual
			aux2++;
		}
		//coste del recorrido anterior
		sum1 = grafo[recorrido[z]-1][recorrido[z+1]-1] + sum1;
	}
	}while(aux2!=7);//Si sale del while es camino aceptado
	//Verificar los costes del camino
	//printf("sum: %d   sum1: %d\n",sum,sum1);
	elev = (sum1 - sum);
	elev = elev/t;
	prob = exp(elev);
	num2 = rand()%(101);
	num2 = num2/100;
	//printf("prob: %lf   num2: %lf\n",prob,num2);
	if((sum - sum1) <= 0)
	{
		for(int y=0;y<=7;y++)
		{
			recorrido[y] = aux[y];//el nuevo camino es mas optimo
		}
	}
	else if(num2 < prob)
	{
		for(int y=0;y<=7;y++)
		{
			recorrido[y] = aux[y];//se selecciona dado 
		}
	}
	aux2=0;
	}//Fin de las k
	//Agregar acerca de los cambios de temperaturas
	t = a*t;
	iter = p*iter;
	}while(t > tf);
	printf("Mejor ruta para recorrer el mapa: ");
	sum1=0;
	for(int y=0;y<=7;y++)
		{
			printf("%d ",recorrido[y]); 
			sum1 = grafo[recorrido[y]-1][recorrido[y+1]-1] + sum1;
		}
	printf("\nSuma del recorrido: %d",sum1);
}
