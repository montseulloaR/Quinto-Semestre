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

struct Poblaciones{
	int k, lim;
	float **poblacion;
	
	Poblaciones *anterior;
	Poblaciones *siguiente;
}; 

int removerSolucionP(int lim, int remover, float(*P)[5]);
void removerPdeSol(int *num, int contP, float (*P)[5], float (*soluciones)[4]);
void imprimirPoblaciones(Poblaciones *inicio, int num);
void bubbleSort (float (*A)[5], int n);

int main(){
	float soluciones[100][4], FP[100][5];
	float p, P, E, Smax, Sy=0, Emax=1000;
	int i, j, contP, k = 0, tamSol = 100;
	bool ignorarSolucion = false;
	Poblaciones *Pk, *inicio, *anterior;
	
	//VALORES PREDETERMINADOS
	p = 7800;
	P = 1000;
	E = 208;
	Sy = 300;
	Smax = 0.05;
	
	
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
	
	
	srand (time(NULL)); 
	//GENERACION DE SOLUCIONES
	printf("\nPOBLACION INICIAL\n");
	printf("i.\tLongitud\tDiametro\tPeso\t\t\tDeflexion\t\n");																						
	for(i=0; i<100; i++){																							// Sujeto a: 
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
				
				printf("%d.\t%.2f\t\t%.2f\t\t%.2f\t\t%.6f\t\t\n", i, soluciones[i][0], soluciones[i][1], soluciones[i][2], soluciones[i][3]);
				//printf("%f\n", Emax);
		}
	}
	
	while(tamSol != 0){
		contP = 0;
		printf("TAMANO DE POBLACION INICIAL: %d\n", tamSol);
		//Se pasa la primera solución al frente de pareto
		FP[0][0] = soluciones[0][0];
		FP[0][1] = soluciones[0][1];
		FP[0][2] = soluciones[0][2];
		FP[0][3] = soluciones[0][3];
		FP[0][4] = 0;
		contP = 1;
		
		/*** ACTUALIZACIÓN CONTINUA ***/
		/*** Se compara cada iesima solución contra cada solución del frente {P} ***/
		for(i=0; i<tamSol; i++){
			ignorarSolucion = true;
			for(j=0; j<contP; j++){
				if(FP[j][4]!=i){										//Evitar comparar la misma solución
					if(soluciones[i][2]<FP[j][2]){						//F1: Solución dominada o parcialmente dominada por la iésima solución
						if(soluciones[i][3]<FP[j][3]){					//F2: Solución domiada o parcialmente dominada por la iésima solución
							/*La iesima solución dominó al miembo P[j]*/
							/*Es removido del frente y pasamos al siguiente*/
							contP = removerSolucionP(contP, j, FP);	
							ignorarSolucion = false;
							j++;										
						}else{ 
							/*NO SE DOMINAN*/ 
							ignorarSolucion = false;
						}
					}else{ 												//F1: Solución dominada por P[j]
						if(FP[j][3]<soluciones[i][3]){					//F2: Solución dominada por P[j]
							/*Se ignora soluciones[i] y pasamos al siguiente*/
							j=contP;
							ignorarSolucion = true;
							i++;
						}else{
							/*NO SE DOMINAN*/
							ignorarSolucion = false;
							
						}
					}	
				}
			}
			
			if(ignorarSolucion == false){
				
				/*Se agrega la solución al frente de pareto*/	
				FP[contP][0] = soluciones[i][0];
				FP[contP][1] = soluciones[i][1];
				FP[contP][2] = soluciones[i][2];
				FP[contP][3] = soluciones[i][3];
				FP[contP][4] = i;		
				contP++;			
				//printf("SOLUCION AGREGADA AL FRENTE\n");								
			}
		
		}
		//printf("TAMANO DE P: %d\n", contP);
		//printf("NIVEL DE DOMINACION TERMINADO\n");
		
		/*** SE ELIMINA {P} DE {SOLUCIONES} ***/
		bubbleSort (FP, contP);
		removerPdeSol(&tamSol, contP, FP, soluciones);
		
		
		/*** SE ACTUALIZA PK ***/
		k++;
		if(k == 1){
			//printf("PRIMER NIVEL DE DOMINANCIA\n");
			/*Reservamos memoria para el nuevo nivel de dominación*/
			Pk = (struct Poblaciones*)malloc(1*sizeof(struct Poblaciones)); 
			//printf("SE RESERVO LA MEMORIA DE LA POBLACION\n");
			
			/*Asignamos valores*/
			Pk->k = k;
			Pk->lim = contP;
			/*Reservamos memoria para la población*/
			Pk->poblacion = (float **) malloc (Pk->lim * sizeof(float *));
			if (Pk->poblacion == NULL) {
			  	printf("No se pudo reservar memoria\n");
			}
			for (i=0 ; i<Pk->lim ; i++) {
			    Pk->poblacion[i] = (float *) malloc (4 * sizeof(float));
			    if (Pk->poblacion[i] == NULL) {
			  		printf("No se pudo reservar memoria\n");
			  	}
			}
			
			/*Pasamos P' a Pk*/  	
			for(i=0; i<Pk->lim; i++){
				Pk->poblacion[i][0] = FP[i][0];
				Pk->poblacion[i][1] = FP[i][1];
				Pk->poblacion[i][2] = FP[i][2];
				Pk->poblacion[i][3] = FP[i][3];
			}
				
			/*Punteros*/
			Pk->anterior = NULL;
			inicio = Pk;
			anterior = Pk;
		}else{
			/*Reservamos memoria para el nuevo nivel de dominación*/
			Pk = (struct Poblaciones*)malloc(1*sizeof(struct Poblaciones)); 
			
			/*Asignamos valores*/
			Pk->k = k;
			Pk->lim = contP;
			
			/*Reservamos memoria para la población*/
			Pk->poblacion = (float **) malloc (Pk->lim * sizeof(float *));
			if (Pk->poblacion == NULL) {
			  	printf("No se pudo reservar memoria\n");
			}
			for (i=0 ; i<Pk->lim ; i++) {
			    Pk->poblacion[i] = (float *) malloc (4 * sizeof(float));
			    if (Pk->poblacion[i] == NULL) {
			  		printf("No se pudo reservar memoria\n");
			  	}
			}
			
			/*Pasamos P' a Pk*/ 
			for(i=0; i<Pk->lim; i++){
				Pk->poblacion[i][0] = FP[i][0];
				Pk->poblacion[i][1] = FP[i][1];
				Pk->poblacion[i][2] = FP[i][2];
				Pk->poblacion[i][3] = FP[i][3];
			}
			
			/*Punteros*/ 
			anterior->siguiente = Pk;
			Pk->anterior = anterior;
			anterior = Pk;
		}
		//printf("P FUE AGREGADO A PK\n\n");
		//imprimirPoblaciones(inicio, k);
		
		/*** SE REINICIA P' ***/
		for(i=0; i<contP; i++){
			FP[i][0] = 0;
			FP[i][1] = 0;
			FP[i][2] = 0;
			FP[i][3] = 0;
		}
	}
	
	
	
	
	
	/*** IMPRIMIR EL POBLACIONES ***/
	//printf("NIVELES DE DOMINACION\n");
	imprimirPoblaciones(inicio, k);
	
	//LIBERAMOS MEMORIA DE POBLACION
	while(inicio->siguiente != NULL){
		for (i = 0; i < inicio->lim; i++) {
    		free(inicio->poblacion[i]);
    	}
		free(inicio->poblacion);
		inicio = inicio->siguiente;
		free(inicio->anterior);
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
		P[i][4] = P[i + 1][4];
	}	
	
	P[lim][0] = 0;
	P[lim][1] = 0;
	P[lim][2] = 0;
	P[lim][3] = 0;
	P[lim][4] = 0;
		
	//printf("SOLUCION REMOVIDA DE P\n");
	return lim-1;
}

void removerPdeSol(int *num, int contP, float (*P)[5], float (*soluciones)[4]){
	int i, j;
	if(contP!=0){
		for(j=0; j<contP; j++){
			for(i=P[j][4]-j; i<P[j+1][4]; i++){
				soluciones[i][0] = soluciones[i + j + 1][0];
				soluciones[i][1] = soluciones[i + j + 1][1];
				soluciones[i][2] = soluciones[i + j + 1][2];
				soluciones[i][3] = soluciones[i + j + 1][3];
			}
		}
	}
	
	if(P[contP-1][4]!=*num-1){
		for(i=P[contP-1][4]-contP; i<*num; i++){
			soluciones[i][0] = soluciones[i + contP-1][0];
			soluciones[i][1] = soluciones[i + contP-1][1];
			soluciones[i][2] = soluciones[i + contP-1][2];
			soluciones[i][3] = soluciones[i + contP-1][3];
		}	
	}
	
	
	*num = *num-contP;
	/*printf("P FUE REMOVIDO DE SOLUCIONES\n");
	printf("i.\tl\td\tF1\t\tF2\t\n");
	for(i=0; i<*num; i++){
		printf("%d.\t%.2f\t%.2f\t%.2f\t%.9f\t\n", i, soluciones[i][0], soluciones[i][1], soluciones[i][2], soluciones[i][3]);
	}*/
	
}

void imprimirPoblaciones(Poblaciones *inicio, int num){
	int i, j;
	Poblaciones *aux;
	aux = inicio;
	
	for(i=0; i<num; i++){
		printf("\nNIVEL %d DE DOMINACION\n", aux->k);
		printf("i.\tLongitud\tDiametro\tPeso\t\t\tDeflexion\t\n");
		for(j=0; j<aux->lim; j++){
			printf("%d.\t%.2f\t\t%.2f\t\t%.2f\t\t%.9f\t\t\n", j+1, aux->poblacion[j][0], aux->poblacion[j][1], aux->poblacion[j][2], aux->poblacion[j][3]);
		}
		aux=aux->siguiente;
	}
}

void bubbleSort (float (*A)[5], int n){
	float swap[5];
	int i, j;
	for (i = 0 ; i < n - 1; i++){
    	for (j = 0 ; j < n - j - 1; j++){
      		if (A[j][4] > A[j+1][4]) {
        		swap[0] = A[j][0];
        		swap[1] = A[j][1];
        		swap[2] = A[j][2];
        		swap[3] = A[j][3];
        		swap[4] = A[j][4];
        		
        		A[j][0] = A[j+1][0];
        		A[j][1] = A[j+1][1];
        		A[j][2] = A[j+1][2];
        		A[j][3] = A[j+1][3];
        		A[j][4] = A[j+1][4];
        		
        		A[j+1][0] = swap[0];
        		A[j+1][1] = swap[1];
        		A[j+1][2] = swap[2];
        		A[j+1][3] = swap[3];
        		A[j+1][4] = swap[4];
      		}
    	}
  	}	 
}

