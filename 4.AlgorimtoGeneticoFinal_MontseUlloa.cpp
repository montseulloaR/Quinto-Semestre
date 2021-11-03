//Montserrat Alejandra Ulloa Rivera
//5°A Optimización Inteligente
/* Algoritmo Genetico */

#include<stdlib.h>
#include<windows.h>
#include<locale.h>
#include <time.h>

int P[30][11], Pm[30][11]; //Matriz de población

int insertarValores(int *x, int *y, int *z);

void iniP();
void seleccion(int t, int *p1, int *p2);
void cruzamiento(int Pr, int p1, int p2, int *h1, int *h2);
void mutacion(int Pr);
void elitismo();
int evaluacion();
void pasar();

void print(int M[50][11], bool eva);


int main(){
	srand(time(0));
	
	int geneS=0, mutP=101, cruzP=101, sumaT=0;
	int padre1=0, padre2=0, hijo1=0, hijo2=1;

	printf("\t\tALGORITMO GENETICO\n");
	
	insertarValores(&geneS, &mutP, &cruzP); 

	iniP(); //Inicializar la población
	sumaT = evaluacion();
	
	printf("\nPROMEDIOS/ MEJOR GEN");
	printf("\nGeneracion 1\n-Promedio: %d", sumaT/30);
	
	for(int j=1; j<geneS; j++){
		hijo1=0; hijo2=1; padre1=0; padre2=0;
		for(int i=0; i<14; i++){
			seleccion(sumaT, &padre1, &padre2);
			cruzamiento(cruzP, padre1, padre2, &hijo1, &hijo2);
		}
		printf("\n-Gen: ");
		mutacion(mutP);
		elitismo();
		
		printf("\n\nGeneracion %d", j+1);
		pasar();
		sumaT = evaluacion();
		printf("\n-Promedio: %d", sumaT/30);
	}
	printf("\n-Gen: ");
	elitismo();
	printf("\n\nULTIMA GENERACION");
	print(P, true);
	
	return 0;
}

int insertarValores(int *x, int *y, int *z){
	printf("Inserte numero de generaciones para trabajar: ");
	scanf("%d", x);
	while(*y>100||*z<0){
		printf("Inserte la probabilidad de mutacion [entero entre 0 y 100]: ");
		scanf("%d", y);
	}
	while(*z>100||*z<0){
		printf("Inserte la probabilidad de cruzamiento [entero entre 0 y 100]: ");
		scanf("%d", z);
	}
}

void iniP(){
	int al;
	for(int i=0;i<30;i++)	{
		for(int j=0;j<10;j++){
			al=rand()%2;
			P[i][j]=al; 
		}
	}
	
	//////////////////////////////////////////
	/*printf("\nINICIALIZAR LA POBLACION\n");
	print(P, false);*/
	//////////////////////////////////////////
	
}

int evaluacion(){
	int total=0;
	for(int i=0;i<30;i++)	{
		P[i][10]=0;
		for(int j=0;j<10;j++){
			P[i][10]+=P[i][j]; 
		}
		total+=P[i][10];
	}
	
	//////////////////////////////////////////
	/*printf("\nEVALUACION\n");
	print(P, true);
	printf("\t\t\t\t\t\t\t Total: %d\n", total);*/
	/////////////////////////////////////////
	
	return total;
}

void seleccion(int t, int *p1, int *p2){
	//SELECCION DE PADRES
	int r1=0, r2=0, s=0;
	r1=rand()%t; //Valor entre 0 y suma total de la población
	r2=rand()%t; //Valor entre 0 y suma total de la población
	for (int i=0; i<30; i++){
		for(int j=0;j<10;j++){
			s+=P[i][j]; 
		}
		if (s-r1>=0&&s-r1<=10) *p1 = i;
		if (s-r2>=0&&s-r2<=10) *p2 = i;		
	}
}

void cruzamiento(int Pr, int p1, int p2, int *h1, int *h2){
	int SPX, p;
	SPX = rand()%10; //Punto de cruzamiento
	p = rand()%101;
	if(Pr>=p){ //Si la probabilidad de cruzamiento es menor a la ingresada por el usuario
		for(int i=0; i<SPX; i++){
			Pm[*h1][i] = P[p1][i]; 
			Pm[*h2][i] = P[p2][i]; 
		}
		
		for(int i=SPX; i<10; i++){
			Pm[*h1][i] = P[p2][i]; 
			Pm[*h2][i] = P[p1][i]; 
		}
	}
	
	else{
		for(int i=0; i<10; i++){
			Pm[*h1][i] = P[p1][i]; 
			Pm[*h2][i] = P[p2][i]; 
		}
	}
	
	*h1+=2;
	*h2+=2;
	
}

void mutacion(int Pr){
	int p;
	for(int i=0; i<28; i++){
		p=rand()%101;
		if(Pr>=p){
			if(Pm[i][5]==0) Pm[i][5]=1;
			else Pm[i][5]=0;
		}
	}
}

void elitismo(){
	int best1=0, best2=0, s, temp1=0, temp2=0;
	
	for(int i=0;i<30;i++)	{
		s=0;
		for(int j=0;j<10;j++){
			s+=P[i][j]; 
		}
		if(s>temp1) {
			best1 = i;
			temp1 = s;
		}
		
		if(best1!=i && s>=temp2) {
			best2 = i;
			temp2 = s;
		}
	}

	for(int i=0;i<10;i++){
		printf(" [%d] ", P[best1][i]);
		Pm[28][i] = P[best1][i];
		Pm[29][i] = P[best2][i];
	}
}

void print (int M[50][11], bool eva){
	int h;
	if (eva == true) h=11;
	else h=10;
	puts("");
	for(int i=0;i<30;i++)	{
		printf("%d.\t", i+1);
		for(int j=0;j<h;j++){
			if(j==10&&eva==true) printf("     ");
			printf(" [%d] ", M[i][j]);
		}
		puts("");
	}
}

void pasar(){
	for(int i=0;i<30;i++)	{
		for(int j=0;j<10;j++){
			P[i][j] = Pm[i][j];
			Pm[i][j] = 0;
		}
	}
}




