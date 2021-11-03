#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#ifndef MPI
#define M_Pi 3.14159265358979323846
#endif

/*	Variables de decisión: longitud (l) y diámetro (d)
	F1: Minimización del peso
	F2: Minimización de la deflexión al final
	
	Parámetros
		-Densidad (p)
		-Fuerza (P) N
		-Presión (E)
		-Límite de deflexión (Smax) m
		-Fuerza permitida (Sy)
		-Esfuezo máximo (Emax)
*/

int removerSolucionP(int lim, int remover, float(*P)[5]);

int main(){
	float soluciones[100][4], FP[100][5];
	float p, P, E, Smax, Sy=0, Emax=1000;
	int i, j, contP, h;
	bool ignorarSolucion = false;
	
	//VALORES PREDETERMINADOS
	p = 7800;
	P = 1;
	E = 208;
	Sy = 300;
	Smax = 5;
	
	/*
	//PARÁMETROS
	printf("\nIngrese el valor de la densidad: ");
	scanf("%f", &p);
	printf("\nIngrese el valor de la fuerza: ");
	scanf("%f", &P);
	printf("\nIngrese el valor de la presion: ");
	scanf("%f", &E);
	printf("\nIngrese el valor del limite de deflexion: ");
	scanf("%f", &Smax);
	printf("\nIngrese el valor de la fuerza permitida: ");
	scanf("%f", &Sy);
	*/
	
	srand (time(NULL)); 
	//GENERACION DE SOLUCIONES
	printf("\nPOBLACION INICIAL\n");
	printf("i.\tl\td\tF1\t\tF2\t\tEmax\n");																						
	for(i=0; i<100; i++){																				     		// Sujeto a: 
		soluciones[i][3] = Smax + 1;
		Emax=Sy + 1;																								//Esfuerzo maximo <= Fuerza permitida
		while(Emax > Sy && soluciones[i][3] > Smax){ 																//Deflexión <= Límite de deflexión										
		/*l*/ 	soluciones[i][0] = rand()%10000+1;
		/*d*/ 	soluciones[i][1] = rand()%10000+1;
				soluciones[i][0] /= 100;
				soluciones[i][1] /= 100;
		/*F1*/ 	soluciones[i][2] = p * ((M_PI* pow(soluciones[i][1], 2))/4) * soluciones[i][0];  					// p*(pi*d^2/4)*l
		/*F2*/ 	soluciones[i][3] = (64 * P * pow(soluciones[i][0], 3))/ (3 * E * M_Pi * pow(soluciones[i][1], 4));  // 64*P*(l^3)/3*E*pi(d^4)
				Emax = (32 * P * soluciones[i][0]) / (M_PI * pow(soluciones[i][0], 3)); 							// 32PL/pi(d^3) 
				
				printf("%d.\t%.2f\t%.2f\t%.2f\t%.6f\t", i, soluciones[i][0], soluciones[i][1], soluciones[i][2], soluciones[i][3]);
				printf("%f\n", Emax);
		}
	}
	
	//Se pasa la primera solución al frente de pareto
	FP[0][0] = soluciones[0][0];
	FP[0][1] = soluciones[0][1];
	FP[0][2] = soluciones[0][2];
	FP[0][3] = soluciones[0][3];
	FP[0][4] = 0;
	contP = 1;
	
	//ACTUALIZACIÓN CONTINUA
	//Se compara cada iesima solución contra cada solución del frente {P}
	for(i=0; i<100; i++){
		//printf("\n\n i: %d\n\n", i);
		ignorarSolucion = true;
		for(j=0; j<contP; j++){
			if(FP[j][4]!=i){										//Evitar comparar la misma solución
				if(soluciones[i][2]<FP[j][2]){						//F1: Solución dominada por la iésima solución
					if(soluciones[i][3]<FP[j][3]){					//F2: Solución domiada  por la iésima solución
						//La iesima solución dominó al miembo P[j]
						//Es removido del frente y pasamos al siguiente
						contP = removerSolucionP(contP, j, FP);	
						ignorarSolucion = false;
						j++;										
					}else{ 
						//NO SE DOMINAN 
						ignorarSolucion = false;
					}
				}else{ 												//F1: Solución dominada por P[j]
					if(FP[j][3]<soluciones[i][3]){					//F2: Solución dominada por P[j]
						//Se ignora soluciones[i] y pasamos al siguiente
						j=contP;
						ignorarSolucion = true;
						//printf("SOLUCION IGNORADA %d\n", i);
					}else{
						//NO SE DOMINAN
						ignorarSolucion = false;
						
					}
				}
			}	
		}
		
		if(ignorarSolucion == false){							//La iésima solución jamás fue dominada
			//Se agrega la solución al frente de pareto	
			FP[contP][0] = soluciones[i][0];
			FP[contP][1] = soluciones[i][1];
			FP[contP][2] = soluciones[i][2];
			FP[contP][3] = soluciones[i][3];
			FP[contP][4] = i;		
			contP++;	
			/*printf("SE AGREGO SOLUCION\n");	
			printf("CONTP: %d\n", contP);					
			printf("i.\tl\td\tF1\t\tF2\t\ti\n");
			for(h=0; h<contP; h++){
				printf("%d.\t%.2f\t%.2f\t%.2f\t%.9f\t\t%.0f\n", h, FP[h][0], FP[h][1], FP[h][2], FP[h][3], FP[h][4]);
			}*/				
		}
	
	}
	
	//SE ACTUALIZA PK
	
	
	//IMPRIMIR EL FRENTE
	printf("\nFrente de pareto\n");
	printf("i.\tl\td\tF1\t\tF2\t\n");
	for(i=0; i<contP; i++){
		printf("%d.\t%.2f\t%.2f\t%.2f\t%.9f\t\t%.0f\n", i, FP[i][0], FP[i][1], FP[i][2], FP[i][3], FP[i][4]);
	}
	
	return 0;
}

int removerSolucionP(int lim, int remover, float (*P)[5]){
	int i;
	for(i=remover; i<lim; i++){
		P[i][0] = P[i + 1][0];
		P[i][1] = P[i + 1][1];
		P[i][2] = P[i + 1][2];
		P[i][3] = P[i + 1][3];
	}	
	
	P[lim][0] = 0;
	P[lim][1] = 0;
	P[lim][2] = 0;
	P[lim][3] = 0;
	
	/*printf("SE ELIMINO EXITOSAMENTE %d\n", remover);
	printf("i.\tl\td\tF1\t\tF2\t\n");
	for(i=0; i<lim-1; i++){
		printf("%d.\t%.2f\t%.2f\t%.2f\t%.9f\t\n", i, P[i][0], P[i][1], P[i][2], P[i][3]);
	}*/
		
	return lim-1;
}
