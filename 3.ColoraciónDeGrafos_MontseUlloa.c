//COLORACIÓN DE GRAFOS
//Montserrat Alejandra Ulloa Rivera
//ICI 5° Optimización Inteligente

#include <stdio.h>
#include <stdlib.h>
void swap(int *xp, int *yp);

struct  vertices{
	int nombre;
	int  grado;
	int  color;
};
typedef struct vertices ver;


int main(){
	int grafo[15][15], i, j, numV, k, aux, max;
	printf("\tCOLORACION DE GRAFOS\n");
	printf("Inserte cantidad de vertices del grafo: "  );
	scanf("%d", &numV);
	
	ver V[numV];
	for (i = 0; i < numV; i++) { 
		V[i].grado = 0; 
		V[i].color = 0;
		V[i].nombre = i;
	}
	
	for(i=0; i<numV; i++){V[i].nombre=i;} //Nombre de los vertices
	
	printf("\nAdyacencia entre grafos");
	printf("\n\t1 = SI\t0 = NO\n\n");
	for(i=0; i<numV; i++){
		for(j=i+1; j<numV; j++){
			printf("Entre el vertice %d y %d: ", i+1, j+1);
			scanf("%d", &grafo[i][j]);
			grafo[j][i] = grafo[i][j];
			
			//Grado de los vertices
			if(grafo[i][j]==1){
				V[i].grado= V[i].grado + 1;
				V[j].grado= V[j].grado + 1;
				//printf("\nV[%d]=%d\nV[%d]=%d\n", i, V[i].grado, j, V[j].grado);
			}
		}
	}
	
	//Bubble sort
	for (i = 0; i < numV-1; i++){
		for (j = 0; j < numV-i-1; j++){
           if (V[j].grado < V[j+1].grado){
              swap(&V[j].grado, &V[j+1].grado); 
              swap(&V[j].nombre, &V[j+1].nombre);
			}     
        }
	}         
	
	//Coloreo de grafos
	for (i = 0; i < numV; i++) {
		V[i].color = 1;
		k = 0;
		aux = 1;
		while(aux == 1) {
			for (j = 0; j < numV; j++) {
				if (grafo[V[j].nombre][V[i].nombre] == 1) {
					if (V[i].color == V[j].color) {
						k = 1;
					}
			    }
			}
			if (k == 1) {
				V[i].color++;
				k = 0;
				aux = 1;
			} else {
				aux = 0;
			}
			if (V[i].color > max) {
				max = V[i].color;
			}
		}
	}


	//IMPRIMIR
	//Matriz de Adyacencia
	printf("\n\nMATRIZ DE ADYACENCIA\n   ");
	for(i=0; i<numV; i++){printf("{%d}", i);}
	puts("");
	for(i=0; i<numV; i++){
		printf("{%d}", i);
		for(j=0; j<numV; j++){
			if(j==i){printf(" 0 ");}
			else {printf(" %d ", grafo[i][j]);}
		}
		puts(" ");
	}
	
	//Vector
	printf("\n\nVECTOR DE VERTICES ORDENADO");
	printf("\nV = { ");
	for(i=0; i<numV; i++){
		printf("%d ", V[i].nombre+1);
	}
	printf("}");
	
	//Coloración
	printf("\n\nCOLORACION");
	printf("\nvertice\t color");
	for(i=0; i<numV; i++){
		printf("\nv%d\t %d", V[i].nombre+1, V[i].color);
	}
	printf("\nX(G) = %d\n", max);

	
	system("pause");
	return 0;
}

void swap(int *xp, int *yp) { 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
