//Montserrat Alejandra Ulloa Rivera
//Optimización Inteligente 5°A
//Optimización por medio de colonia de hormigas
#include <stdio.h>
#include<stdlib.h>
#include <time.h> 
#include <string.h>
#include<stdbool.h>

struct auxiliar {
	int nodo;
	bool caminox = false;
	float probabilidad;
};

struct auxiliar2 {
	int orden;
	int sig;
};



float fermT[7][7];
auxiliar2 camino[7];
float matriz[24][24];

int construirSolucion(float b, float **dist, int n);
void actualizarFermona(int Lk, float r, float Q, float a,int n);
void imprimirCamino(int n);
void lectura(int n);

int main(){
	srand(time(0));
	int i, j, longitud, n;
	float **dist;
	float T, Q, ro, a, b;
	
	puts("\tANT COLONY OPTIMIZATION");
	puts("\tEste programa optimiza el recorrido de un grafo predeterminado desde el nodo 1 hasta el nodo 4.");
	puts("\tNOTA: Solo se hace uso de una hormiga y una iteracion.");
	printf("\nInserte el valor inicial de la fermona [T]: ");
	scanf("%f", &T);
	
	printf("Inserte el valor del factor de apredizaje [Q]: ");
	scanf("%f", &Q);
	
	printf("Inserte el valor de factor de evaporacion [p]: ");
	scanf("%f", &ro);
	
	printf("Inserte el valor de factor alpha: ");
	scanf("%f", &a);
	
	printf("Inserte el valor de factor de beta: ");
	scanf("%f", &b);
	
	
	dist = (float **) malloc (n * sizeof(float *));
	for (i=0 ; i<n ; i=i+1) {
    	dist[i] = (float *) malloc (n * sizeof(float));
  	}
  	
	
	puts("Distancia entre los vertices [0 = no existe camino]");
	for(i=0; i<n; i++){
		for(j=i+1; j<n; j++){
			printf("%d y %d: ", i+1, j+1);
			scanf("%f", &dist[j][i]);
			dist[i][j] = dist[j][i];
			
			//Matriz fermonas
			if(dist[j][i] != 0){
				fermT[i][j] = T;
				fermT[j][i] = T;
			}
			else { 
				fermT[i][j]=0;
				fermT[j][1]=0;
			}
			
		}
		dist[i][i] = 0;
		fermT[i][i] = 0;
	}
	
	for(i=0; i<n; i++){
		for(j=i+1; j<n; j++){
			//Matriz fermonas
			if(dist[j][i] != 0){
				fermT[i][j] = T;
				fermT[j][i] = T;
			}
			else { 
				fermT[i][j]=0;
				fermT[j][1]=0;
			}
		}
		fermT[i][i] = 0;
	}
	
	puts("\nMATRIZ DE DISTANCIAS\t\t\tMATRIZ DE FERMONAS");
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			printf("[%.0f] ", dist[i][j]);
		}
		printf("\t\t");
		for(j=0; j<n; j++){
			printf("[%.1f] ", fermT[i][j]);
		}
		puts("");
	}


	longitud = construirSolucion(b, dist, n);
	actualizarFermona(longitud, ro, Q, a, n);
	imprimirCamino(n);
	printf("\nPeso del camino: %d", longitud);
	
	puts("\nMATRIZ DE FERMONAS ACTUALIZADA");
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			printf("[%.3f] ", fermT[i][j]);
		}
		puts("");
	}
	
	system("pause");
	return 0;
	
}

int construirSolucion(float b, float **dist, int n){
	int i, j, cont=2;
	
	auxiliar caminosPosibles[n];
	float TN[n], TNS = 0, p = 0, pesoCamino;
	int h = 0, sum = 0; //nodo inicial
	camino[0].orden = 1; 
	
	while (h!=3){
		//REINICIAR AUXILIARES
		sum = 0;
		TNS = 0;
		j = 0;
		for(i=0; i<n; i++){
			caminosPosibles[i].caminox = false;
			caminosPosibles[i].nodo = 0;
			caminosPosibles[i].probabilidad = 0;
		}
		
		//PROBABILIDADES PIJ
		for(i=0; i<n; i++){
			if(dist[h][i]>0 && camino[i].orden == 0){
				caminosPosibles[j].caminox = true;
				caminosPosibles[j].nodo = i;
				caminosPosibles[j].probabilidad =  fermT[h][i] * (1/dist[h][i] * b);
				TNS += caminosPosibles[j].probabilidad;
				j++;
			}
		}
		
		//printf("\nPROBABILIDADES DEL NODO %d", h);
		for(i=0; i<n; i++){
			if(caminosPosibles[i].caminox==true){
				caminosPosibles[i].probabilidad/=TNS;
				if(i!=0) caminosPosibles[i].probabilidad+=caminosPosibles[i-1].probabilidad; 
			}
			//printf("\n%d - %d: %f", h, caminosPosibles[i].nodo, caminosPosibles[i].probabilidad);
		}
		//PROBABILIDADES PIJ
		
		p = (rand() % 100);
		p /= 100;
		//printf("\nProbabilidad = %f", p);
		
		for(i=0; i<n; i++){
			if(caminosPosibles[i].probabilidad>p){
				pesoCamino += dist[h][caminosPosibles[i].nodo]; 
				camino[h].sig = caminosPosibles[i].nodo;
				h=caminosPosibles[i].nodo; i=8;
			}
		}
		
		//printf("\nNodo siguiente = %d", h);
		camino[h].orden = cont;
		cont++;
	}

	return (int)(pesoCamino);
	
}

void actualizarFermona(int Lk, float r, float Q, float a, int n){
	int i, j;
	float Tij, DeltaTij;
	for(i=0; i<n; i++){
		for(j=i+1; j<n; j++){
			if(fermT != 0){
				Tij = fermT[i][j];
				DeltaTij = Q/Lk;
				if(camino[i].sig == j){
					fermT[i][j] = ((1 - r) * Tij + DeltaTij) * a;
					fermT[j][i] = fermT[i][j];
				}
				else {
					fermT[i][j] = ((1 - r) * Tij) * a;
					fermT[j][i] = fermT[i][j];
				}
			}
		}
	}
	
}

void imprimirCamino(int n){
	int i, cont=1, aux;
	printf("\nCamino: ");
	while(aux!=3){
		for(i=0; i<n; i++){
			if(camino[i].orden == cont){
				printf("[%d]", i+1);
				cont++;
				aux = i;
			}
		}
	}
}

void lectura(int n){
	FILE * archivo = NULL; 
	char buffer[19] = "";
	int i, j;
	archivo = fopen("gr24.txt",  "r");
	if(archivo == NULL)
		printf("\n Error al abrir el archivo");
	while(strcmp(buffer, "EDGE_WEIGHT_SECTION") != 0){ //EDGE_WEIGHT_SECTION es la última línea de texto
		fgets(buffer, 20, archivo);
	}
	printf("\n Contenido de la matriz:\n\n     ");
	for(i = 0; i <n; i ++){
		if(i > 9)
			printf("__%d", i + 1);
		else
			printf("___%d", i + 1);
	}
	for(i = 0; i < n; i ++){
		for(j = 0; j <= i; j ++){
			fscanf(archivo, "%d", &matriz[i][j]);
		}
	}
	for(i = 0; i < n - 2; i ++){
		for(j = n - 1; j > 0; j --){
			matriz[i][j] = matriz[j][i];
		}
	}
	matriz[n - 2][n - 1] = matriz[n - 1][n - 2];
	for(i = 0; i < n; i ++){
		if(i < 10)
			printf("\n  %d | ", i + 1);
		else if(i > 9)
			printf("\n %d | ", i + 1);
		for(j = 0; j < n; j ++){
			if(matriz[i][j] > 99)
				printf(" %d", matriz[i][j]);
			else if(matriz[i][j] < 100 && matriz[i][j] > 9)
				printf("  %d", matriz[i][j]);
			else
				printf("   %d", matriz[i][j]);
		}
	}
	printf("\n %d", matriz[5][1]);
	fclose(archivo);
}
