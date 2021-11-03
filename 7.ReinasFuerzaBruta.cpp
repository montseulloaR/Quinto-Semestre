//Montserrat Alejandra Ulloa Rivera
//Resuelve el problema de las 5 reinas por el método de Fuerza Bruta
//5°A Optimización Inteligente
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

void imprimir (int V[5], int n, int it);

int main(){
	unsigned t0, t1;
	t0 = clock();
	int espS[5], i, j, k, l, m, a, b, it=0, nSol=0; 
	bool sol = false;
	printf("SOLUCIONES\n");
	for(i=0; i<25; i++){
		espS[0] = i;
		for(j=0; j<25; j++){
			espS[1]= j;
			for(k=0; k<25; k++){
				espS[2] = k;
				for(l=0; l<25; l++){
					espS[3] = l;
					for(m=0; m<25; m++){
						espS[4] = m;
						
						it++;
						
							if( (espS[0]>=0 && espS[0]<=4) && (espS[1]>=5 &&espS[1]<=9) && (espS[2]>=10 && espS[2]<=14) && (espS[3]>=15 && espS[3]<=19) && (espS[4]>=20 && espS[4]<=24) ){ //FILAS
							for(a=0; a<5; a++){
								for(b=a+1; b<5; b++){

									
									//if(espS[a]!=espS[b]){ //ESPACIO
										//if(espS[a]/5!=espS[b]/5){ //FILA
											if(espS[a]%5!=espS[b]%5){ //COLUMNA
												if( (espS[a]%5-espS[a]/5) != (espS[b]%5-espS[b]/5) ){ //DIAGONAL DESCENDIENTE (COL - FIL)
													if( (espS[a]%5+espS[a]/5) != (espS[b]%5+espS[b]/5) ){  //DIAGONAL ASCENDENTE (COL + FIL)
														//printf("%d %d\n", espS[a]%5, espS[b]%5);
														sol = true;
														
													} else {sol = false; a=6; b=6;}
												} else {sol = false; a=6; b=6;}	
											} else {sol = false; a=6; b=6;}
										//} else {sol = false; a=6; b=6;}
									//} else {sol = false; a=6; b=6;}
									
									
								} 
							} 
						}else {sol = false;}
						
						//IMPRESION
						if (sol == true){
							nSol++;
							imprimir(espS, nSol, it);
						}
						
						
						
					}
				}
			}
		}
	}
	t1 = clock();
	double time = (double)(t1 - t0) / CLOCKS_PER_SEC;
	printf("\nTiempo: %f", time);
	printf("\nTotal de soluciones: %d", nSol);
	printf("\nTotal de iteraciones: %d", it); 
}

void imprimir (int V[5], int n, int it){
	int i, j;
	bool pr;
	printf("\nIteracion: %d\n", it);
	printf("Solucion: %d", n);
	for(i=0; i<25; i++){
		if(i%5==0){printf("\n");}
		pr = false;
		for(j=0; j<5; j++){
			if(i==V[j]){
				printf(" |R%d| ", j+1);
				pr = true;
			}
		}
		if (pr == false) {printf(" |  | ");}
	}
	printf("\n V={");
	for(j=0; j<5; j++){
		printf(" %d ", V[j]);
	}
	printf("}\n");
	
}

