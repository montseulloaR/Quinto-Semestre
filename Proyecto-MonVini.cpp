/*Ingenieria en Computacion Inteligente
  Automatas I: 5to A
  Proyecto Final.*/
/*Integrantes del Equipo:
	Montserrat Alejandra Ulloa Rivera
	Paulo Vinicio Martinez Roque*/
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>

/*DFA*/
bool DFA(char cadena[50], int n);
int delta(int estado, char c);

/*NPDA*/
/*Estados*/
void q0(char leer, char p);
void q1(char leer, char p);
void q2(char leer, char p);
void q3(char leer, char p);
void q4(char leer);
void q5(char leer);
void q6(char leer);
void q7(char leer);
void q8(char leer);
void q9(char leer);
void q11(char leer);
void q12(char leer);
void q13(char leer);
void q14(char leer);
void q15(char leer);
void q16(char leer);
void q17(char leer);
void q18(char leer);
void q19(char leer);
void q20(char leer);

int contEle(char ele, int cont, int n);

/*PILA*/
void eliminarPila(int n);
void copiarPila(int n);
void pop(void);
void push(char ele);
void imprimir(int n);

char pila[100][251];
int numPila = 0, info[100][3];
bool aceptada = false;

int main(){
	setlocale(LC_ALL, "");
	
	char correo[250];
	bool aceptadaFinal = false;
	int tamano = 0, i, j;
	
	char contrasena[50];
	int n;
	bool test;
		
	printf("\t-Proyecto Final: Montse y Vini-");
	printf("\n\n ->Formulario de registro de usuario");
	printf("\n\nInstrucciones:\n\tIngrese un correo válido, con terminacion .com, .net, o un correo institucional de la UAA.");
	printf("\n\tIngrese una contraseña válida, con almenos 5 caractéres, un número y una letra mayúscula.");
	
	
	while(aceptadaFinal!=true){
		printf("\n\nIngrese su correo: ");
		scanf("%s", correo);
		tamano = strlen(correo);		
		//Reinicia la información
		aceptada = false;
		numPila=0;
		for(i=0; i<100; i++){
			for(j=0; j<251; j++){
				pila[i][j] = ' ';
				info[i][0] = 0; //ESTADO
				info[i][1] = 0; //CONTADOR CARACTERES LEIDOS
				info[i][3] = 0; //ELEMENTO SUPERIOR DE LA PILA
			}
		}
		//Se inicializa la pila	
		pila[0][0] = 'Z';
			
		while(numPila > -1){	
			/*Estados finales*/
			if(info[numPila][0] ==7 || info[numPila][0] == 20){
				aceptada = true;
			}
			
			/*Ya se temrino de leer la cadena*/
			if(info[numPila][1] == tamano){
				if(aceptada == true){
					aceptadaFinal = true;
				}
				eliminarPila(info[numPila][2]);
			}
			else{
				/*Estados*/
				//Automata
				//Basandose en cual estado se encuentra el automata
				switch(info[numPila][0]){
					case 0:
						q0(correo[info[numPila][1]], pila[numPila][info[numPila][2]]);
					break;
					case 1:
						q1(correo[info[numPila][1]], pila[numPila][info[numPila][2]]);
					break;
					case 2:
						q2(correo[info[numPila][1]], pila[numPila][info[numPila][2]]);
					break;
					case 3:
						q3(correo[info[numPila][1]], pila[numPila][info[numPila][2]]);
					break;
					case 4:
						q4(correo[info[numPila][1]]);
					break;
					case 5:
						q5(correo[info[numPila][1]]);
					break;
					case 6:
						q6(correo[info[numPila][1]]);
					break;
					case 7:
						q7(correo[info[numPila][1]]);
					break;
					case 8:
						q8(correo[info[numPila][1]]);
					break;
					case 9:
						q9(correo[info[numPila][1]]);
					break;
					case 11:
						q11(correo[info[numPila][1]]);
					break;
					case 12:
						q12(correo[info[numPila][1]]);
					break;
					case 13:
						q13(correo[info[numPila][1]]);
					break;
					case 14:
						q14(correo[info[numPila][1]]);
					break;
					case 15:
						q15(correo[info[numPila][1]]);
					break;
					case 16:
						q16(correo[info[numPila][1]]);
					break;
					case 17:
						q17(correo[info[numPila][1]]);
					break;
					case 18:
						q18(correo[info[numPila][1]]);
					break;
					case 19:
						q19(correo[info[numPila][1]]);
					break;
					case 20:
						q20(correo[info[numPila][1]]);
					break;
					default:
						eliminarPila(info[numPila][2]);
					break;
				} 
			}
		}
		
		if(aceptadaFinal==true){
			printf("\n\t-El correo ingresado es válido-");
		}
		else{
			printf("\n\tEl correo no es válido, favor de ingresar otro.");
		}
	}
	do{
		printf("\n\nIngrese su contraseña: ");
		scanf("%s", contrasena);
		n = strlen(contrasena);
		test = DFA(contrasena,n);
		if(test){
			printf("\n\t-Su contraseña es válida!");
		}
		else{
			printf("\n\t-Su contraseña es inválida!, porfavor, introduzca otra.");
		}	
	
	}while(test==false);
	printf("\n\n -USUARIO CREADO EXITOSAMENTE-\n\n");
	system("pause");
	return 0;
}

//DFA

bool DFA(char cadena[50], int n){
	bool aceptada = false;
	int estado = 0; //Iniciamos en el estado inicial (q0)

	for(int i=0; i<n; i++){
		estado = delta(estado, cadena[i]);
	}
	if(estado<0){ //Se salio de los estados
		return false;
	}
	else{
		if(estado==8){
			//Quedo en q8, es aceptado
			aceptada = true;
		}
		else{
			//No quedo en q8, es rechazada
			aceptada= false;
		}
	}
	
	return aceptada;
}

int delta(int estado, char c){
	switch(estado){
		case 0: 
			if (c>96 && c<123){
				return 1;
			}
			else if (c>64 && c<91){
				return 9;
			}
			else if (c>47 && c<58){
				return 13;
			}
			else {
				return -1;}
			break;
			
		case 1:
			if (c>96 && c<123){
				return 2;
			}
			else if (c>64 && c<91){
				return 10;
			}
			else if (c>47 && c<58){
				return 14;
			}
			else {
				return -1;}
			break;
			
		case 2:
			if (c>96 && c<123){
				return 3;
			}
			else if (c>64 && c<91){
				return 11;
			}
			else if (c>47 && c<58){
				return 15;
			}
			else {
				return -1;}
			break;	
		
		case 3:	
			if (c>96 && c<123){
				return 4;
			}
			else if (c>64 && c<91){
				return 12;
			}
			else if (c>47 && c<58){
				return 16;
			}
			else {
				return -1;}
			break;
			
		case 4:
			if (c>96 && c<123){
				return 5;
			}
			else if (c>64 && c<91){
				return 6;
			}
			else if (c>47 && c<58){
				return 7;
			}
			else {
				return -1;}
			break;
			
		case 5:
			if (c>96 && c<123){
				return 5;
			}
			else if (c>64 && c<91){
				return 6;
			}
			else if (c>47 && c<58){
				return 7;
			}
			else {
				return -1;}
			break;
		
		case 6:
			if ((c>96 && c<123) || (c>64 && c<91)){
				return 6;
			}
			else if (c>47 && c<58){
				return 8;
			}
			else {
				return -1;}
			break;
		
		case 7:
			if (c>96 && c<123){
				return 7;
			}
			else if (c>64 && c<91){
				return 8;
			}
			else if (c>47 && c<58){
				return 7;
			}
			else {
				return -1;}
			break;	
		case 8:
			if (c>96 && c<123){
				return 8;
			}
			else if (c>64 && c<91){
				return 8;
			}
			else if (c>47 && c<58){
				return 8;
			}
			else {
				return -1;}
			break;	
		case 9:
			if (c>96 && c<123){
				return 10;
			}
			else if (c>64 && c<91){
				return 10;
			}
			else if (c>47 && c<58){
				return 17;
			}
			else {
				return -1;}
			break;
		case 10:
			if (c>96 && c<123){
				return 11;
			}
			else if (c>64 && c<91){
				return 11;
			}
			else if (c>47 && c<58){
				return 18;
			}
			else {
				return -1;}
			break;
		case 11:
			if (c>96 && c<123){
				return 12;
			}
			else if (c>64 && c<91){
				return 12;
			}
			else if (c>47 && c<58){
				return 19;
			}
			else {
				return -1;}
			break;	
		case 12:
			if (c>96 && c<123){
				return 6;
			}
			else if (c>64 && c<91){
				return 6;
			}
			else if (c>47 && c<58){
				return 8;
			}
			else {
				return -1;}
			break;
		case 13:
			if (c>96 && c<123){
				return 14;
			}
			else if (c>64 && c<91){
				return 17;
			}
			else if (c>47 && c<58){
				return 14;
			}
			else {
				return -1;}
			break;	
		case 14:
			if (c>96 && c<123){
				return 15;
			}
			else if (c>64 && c<91){
				return 18;
			}
			else if (c>47 && c<58){
				return 15;
			}
			else {
				return -1;}
			break;
			
		case 15:
			if (c>96 && c<123){
				return 16;
			}
			else if (c>64 && c<91){
				return 19;
			}
			else if (c>47 && c<58){
				return 16;
			}
			else {
				return -1;}
			break;
			
		case 16:
			if (c>96 && c<123){
				return 7;
			}
			else if (c>64 && c<91){
				return 8;
			}
			else if (c>47 && c<58){
				return 7;
			}
			else {
				return -1;}
			break;
			
		case 17:
			if (c>96 && c<123){
				return 18;
			}
			else if (c>64 && c<91){
				return 18;
			}
			else if (c>47 && c<58){
				return 18;
			}
			else {
				return -1;}
			break;
			
		case 18:
			if (c>96 && c<123){
				return 19;
			}
			else if (c>64 && c<91){
				return 19;
			}
			else if (c>47 && c<58){
				return 19;
			}
			else {
				return -1;}
			break;
			
		case 19:
			if (c>96 && c<123){
				return 8;
			}
			else if (c>64 && c<91){
				return 8;
			}
			else if (c>47 && c<58){
				return 8;
			}
			else {
				return -1;}
			break;					
		default:
			return -1;	
	}
}

//NPDA
void q0(char leer, char p){
	int cont2 = 0, caminos = 0, i;
	
	cont2 = contEle('0', 4, info[numPila][2]);
	
	//CUANTOS CAMINOS SE PUEDEN SEGUIR
	if(leer>96 && leer<123 && cont2 == 4) {caminos++;}
	if(leer>64 && leer<91 && cont2 == 4) {caminos++;}
	if(leer>47 && leer<58 && cont2 == 4) {caminos++;}
	if(leer>96 && leer<123 &&  p == 'Z') {caminos++;}
	if(leer>96 && leer<123 &&  p == '0') {caminos++;}
	if(leer>64 && leer<91 && p == 'Z') {caminos++;}
	if(leer>64 && leer<91 &&  p == '0') {caminos++;}
	if(leer>47 && leer<58 &&  p == '0') {caminos++;}
	
	if(caminos > 0){ //Hay transiciones que se pueden hacer
		if(caminos>1){ //Existen más de una transicion que se puede hacer. Se hacen copias de la pila actual
			for(i=1; i<caminos; i++){
				copiarPila(info[numPila][2]);
			}
		}
		
		if(leer>96 && leer<123 && cont2 == 4) { // a-z, 00000, 1
			pop();
			pop();
			pop();
			pop();
			push('1');
			info[numPila][1]++;
			info[numPila][0] = 1; //Lo mandamos al estado correspondiente
			if(caminos>1){
				numPila--; //Nos regresamos a la copia de la pila para poder seguir el otro camino
			}
		}
		
		if(leer>64 && leer<91 && cont2 == 4) { // A-Z, 00000, 1
			pop();
			pop();
			pop();
			pop();
			push('1');
			info[numPila][1]++;
			info[numPila][0] = 1; //Lo mandamos al estado correspondiente
			if(caminos>1){
				numPila--; //Nos regresamos a la copia de la pila para poder seguir el otro camino
			}
		}
		
		if(leer>47 && leer<58 && cont2 == 4) { // 0-9, 00000, 1
			pop();
			pop();
			pop();
			pop();
			push('1');
			info[numPila][1]++;
			info[numPila][0] = 1; //Lo mandamos al estado correspondiente
			if(caminos>1){
				numPila--; //Nos regresamos a la copia de la pila para poder seguir el otro camino
			}
		}
		
		
		if(leer>96 && leer<123 &&  p == 'Z') { // a-z, Z, 0
			pop();
			push('0');
			info[numPila][1]++;
			info[numPila][0] = 0; //Lo mandamos al estado correspondiente
			if(caminos>1){
				numPila--; //Nos regresamos a la copia de la pila para poder seguir el otro camino
			}
		}
		
		if(leer>96 && leer<123 &&  p == '0') { // a-z, 0, 00
			pop();
			push('0');
			push('0');
			info[numPila][1]++;
			info[numPila][0] = 0; //Lo mandamos al estado correspondiente
			if(caminos>1){
				numPila--; //Nos regresamos a la copia de la pila para poder seguir el otro camino	
			}
		}
		
		if(leer>64 && leer<91 && p == 'Z') { // A-Z, Z, 0
			pop();
			push('0');
			info[numPila][1]++;
			info[numPila][0] = 0; //Lo mandamos al estado correspondiente
			if(caminos>1){
				numPila--; //Nos regresamos a la copia de la pila para poder seguir el otro camino
			}
		}
		
		if(leer>64 && leer<91 &&  p == '0'){ // A-Z, 0, 00
			pop();
			push('0');
			push('0');
			info[numPila][1]++;
			info[numPila][0] = 0; //Lo mandamos al estado correspondiente
			if(caminos>1){
				numPila--; //Nos regresamos a la copia de la pila para poder seguir el otro camino	
			}
		}
		
		if(leer>47 && leer<58 &&  p == '0'){ // 0-9, 0, 00
			pop();
			push('0');
			push('0');
			info[numPila][1]++;
			info[numPila][0] = 0; //Lo mandamos al estado correspondiente
			if(caminos>1){
				numPila--; //Nos regresamos a la copia de la pila para poder seguir el otro camino	
			}
		}
		
		if(caminos>1){
			numPila += caminos; //Regresamos a la pila "de hasta arriba"
		}
	}
	else{
		info[numPila][0] = 100; //Informamos que no hubo transición
	}
}
void q1(char leer, char p){
	int caminos = 0, i;
	
	//CUANTOS CAMINOS SE PUEDEN SEGUIR
	if(leer>64 && leer<91 && p == '1')  {caminos++;}
	if(leer>96 && leer<123 && p == '1') {caminos++;}
	if(leer>47 && leer<58 &&  p == '1') {caminos++;}
	if(leer == '@' &&  p == '1') {caminos++;}
	
	if(caminos>0){
		if(caminos>1){ //Existen más de una transicion que se puede hacer. Se hacen copias de la pila actual
			for(i=1; i<caminos; i++){
				copiarPila(info[numPila][2]);
			}
		}
		
		if(leer>64 && leer<91 && p == '1') { // A-Z, 1, 1
			pop();
			push('1');
			info[numPila][1]++;
			info[numPila][0] = 1; //Lo mandamos al estado correspondiente
			if(caminos>1){
				numPila--; //Nos regresamos a la copia de la pila para poder seguir el otro camino
			}
		}
		
		if(leer>96 && leer<123 && p == '1'){ // a-z,  1, 1
			pop();
			push('1');
			info[numPila][1]++;
			info[numPila][0] = 1; //Lo mandamos al estado correspondiente
			if(caminos>1){
				numPila--; //Nos regresamos a la copia de la pila para poder seguir el otro camino	
			}
		}
		
		if(leer>47 && leer<58 &&  p == '1'){ // 0-9, 1, 1
			pop();
			push('1');
			info[numPila][1]++;
			info[numPila][0] = 1; //Lo mandamos al estado correspondiente
			if(caminos>1){
				numPila--; //Nos regresamos a la copia de la pila para poder seguir el otro camino	
			}
		}
		
		if(leer == '@' &&  p == '1'){ // 0-9, 1, 1
			pop();
			push('x');
			info[numPila][1]++;
			info[numPila][0] = 2; //Lo mandamos al estado correspondiente
			if(caminos>1){
				numPila--; //Nos regresamos a la copia de la pila para poder seguir el otro camino	
			}
		}
		if(caminos>1){
			numPila += caminos; //Regresamos a la pila "de hasta arriba"
		}
	}
	else{
		info[numPila][0] = 100; //Informamos que no hubo transición
	}
}
void q2(char leer, char p){
	int cont2 = 0, caminos = 0, i;
	
	cont2 = contEle('2', 2, info[numPila][2]);
	
	//CUANTOS CAMINOS SE PUEDEN SEGUIR
	if(leer>96 && leer<123 && cont2 == 2) {caminos++;}
	if(leer>64 && leer<91 && cont2 == 2) {caminos++;}
	if(leer>47 && leer<58 && cont2 == 2) {caminos++;}
	if(leer>96 && leer<123 &&  p == 'x') {caminos++;}
	if(leer>96 && leer<123 &&  p == '2') {caminos++;}
	if(leer>64 && leer<91 && p == 'x') {caminos++;}
	if(leer>64 && leer<91 &&  p == '2') {caminos++;}
	if(leer>47 && leer<58 &&  p == '2') {caminos++;}
	if(leer == 'e' &&  p == 'x') {caminos++;}
	
	if(caminos > 0){ //Hay transiciones que se pueden hacer
		if(caminos>1){ //Existen más de una transicion que se puede hacer. Se hacen copias de la pila actual
			for(i=1; i<caminos; i++){
				copiarPila(info[numPila][2]);
			}
		}
		
		if(leer>96 && leer<123 && cont2 == 2) { // a-z, 22, 3
			pop();
			pop();
			push('3');
			info[numPila][1]++;
			info[numPila][0] = 3; //Lo mandamos al estado correspondiente
			if(caminos>1){
				numPila--; //Nos regresamos a la copia de la pila para poder seguir el otro camino
			}
		}
		
		if(leer>64 && leer<91 && cont2 == 2) { // A-Z,  22, 3
			pop();
			pop();
			push('3');
			info[numPila][1]++;
			info[numPila][0] = 3; //Lo mandamos al estado correspondiente
			if(caminos>1){
				numPila--; //Nos regresamos a la copia de la pila para poder seguir el otro camino
			}
		}
		
		if(leer>47 && leer<58 && cont2 == 4) { // 0-9, 22, 3
			pop();
			pop();
			push('3');
			info[numPila][1]++;
			info[numPila][0] = 3; //Lo mandamos al estado correspondiente
			if(caminos>1){
				numPila--; //Nos regresamos a la copia de la pila para poder seguir el otro camino
			}
		}
		
		
		if(leer>96 && leer<123 &&  p == 'x') { // a-z, x, 2
			pop();
			push('2');
			info[numPila][1]++;
			info[numPila][0] = 2; //Lo mandamos al estado correspondiente
			if(caminos>1){
				numPila--; //Nos regresamos a la copia de la pila para poder seguir el otro camino
			}
		}
		
		if(leer>96 && leer<123 &&  p == '2') { // a-z, 2, 22
			pop();
			push('2');
			push('2');
			info[numPila][1]++;
			info[numPila][0] = 2; //Lo mandamos al estado correspondiente
			if(caminos>1){
				numPila--; //Nos regresamos a la copia de la pila para poder seguir el otro camino	
			}
		}
		
		if(leer>64 && leer<91 && p == 'x') { // A-Z, x, 2
			pop();
			push('2');
			info[numPila][1]++;
			info[numPila][0] = 2; //Lo mandamos al estado correspondiente
			if(caminos>1){
				numPila--; //Nos regresamos a la copia de la pila para poder seguir el otro camino
			}
		}
		
		if(leer>64 && leer<91 &&  p == '2'){ // A-Z, 2, 22
			pop();
			push('2');
			push('2');
			info[numPila][1]++;
			info[numPila][0] = 2; //Lo mandamos al estado correspondiente
			if(caminos>1){
				numPila--; //Nos regresamos a la copia de la pila para poder seguir el otro camino	
			}
		}
		
		if(leer>47 && leer<58 &&  p == '2'){ // 0-9, 2, 22
			pop();
			push('2');
			push('2');
			info[numPila][1]++;
			info[numPila][0] = 2; //Lo mandamos al estado correspondiente
			if(caminos>1){
				numPila--; //Nos regresamos a la copia de la pila para poder seguir el otro camino	
			}
		}
		
		if(leer == 'e' &&  p == 'x'){ // e, x, lambda
			pop();
			info[numPila][1]++;
			info[numPila][0] = 11; //Lo mandamos al estado correspondiente
			if(caminos>1){
				numPila--; //Nos regresamos a la copia de la pila para poder seguir el otro camino	
			}
		}
		
		if(caminos>1){
			numPila += caminos; //Regresamos a la pila "de hasta arriba"
		}
	}
	else{
		info[numPila][0] = 100; //Informamos que no hubo transición
	}
	
}
void q3(char leer, char p){
	if(leer == '.' && p == '3'){ // ., 3, lambda
		pop();
		info[numPila][1]++;
		info[numPila][0] = 4; //Lo mandamos al estado correspondiente
	}
	else{
		info[numPila][0] = 100; //Informamos que no hubo transición
	}
}
void q4(char leer){
	if(leer == 'c'){ // c, lambda, lambda
		info[numPila][1]++;
		info[numPila][0] = 5; //Lo mandamos al estado correspondiente
	}
	else{
		if(leer == 'm'){ // c, lambda, lambda
			info[numPila][1]++;
			info[numPila][0] = 8; //Lo mandamos al estado correspondiente
		}
		else{
			info[numPila][0] = 100; //Informamos que no hubo transición
		}
	}
}
void q5(char leer){
	if(leer == 'o'){ // o, lambda, lambda
		info[numPila][1]++;
		info[numPila][0] = 6; //Lo mandamos al estado correspondiente
	}
	else{
		info[numPila][0] = 100; //Informamos que no hubo transición
	}
}
void q6(char leer){
	if(leer == 'm'){ // o, lambda, lambda
		aceptada = true;
		info[numPila][1]++;
		info[numPila][0] = 7; //Lo mandamos al estado correspondiente
	}
	else{
		info[numPila][0] = 100; //Informamos que no hubo transición
	}
}
void q7(char leer){
	if(leer == '.'){ // ., lambda, lambda
		info[numPila][1]++;
		info[numPila][0] = 18; //Lo mandamos al estado correspondiente
	}
	else{
		aceptada = false;
		info[numPila][0] = 100; //Informamos que no hubo transición
	}
}
void q8(char leer){	
	if(leer == 'e'){ // e, lambda, lambda
		info[numPila][1]++;
		info[numPila][0] = 9; //Lo mandamos al estado correspondiente
	}
	else{
		info[numPila][0] = 100; //Informamos que no hubo transición
	}
	
}
void q9(char leer){
	if(leer == 't'){ // e, lambda, lambda
		info[numPila][1]++;
		info[numPila][0] = 7; //Lo mandamos al estado correspondiente
	}
	else{
		info[numPila][0] = 100; //Informamos que no hubo transición
	}
}
void q11(char leer){
	if(leer == 'd'){ // d, lambda, lambda
		info[numPila][1]++;
		info[numPila][0] = 12; //Lo mandamos al estado correspondiente
	}
	else{
		info[numPila][0] = 100; //Informamos que no hubo transición
	}
}
void q12(char leer){
	if(leer == 'u'){ // u, lambda, lambda
		info[numPila][1]++;
		info[numPila][0] = 13; //Lo mandamos al estado correspondiente
	}
	else{
		info[numPila][0] = 100; //Informamos que no hubo transición
	}
}
void q13(char leer){
	if(leer == '.'){ // ., lambda, lambda
		info[numPila][1]++;
		info[numPila][0] = 14; //Lo mandamos al estado correspondiente
	}
	else{
		info[numPila][0] = 100; //Informamos que no hubo transición
	}
}
void q14(char leer){
	if(leer == 'u'){ // u, lambda, lambda
		info[numPila][1]++;
		info[numPila][0] = 15; //Lo mandamos al estado correspondiente
	}
	else{
		info[numPila][0] = 100; //Informamos que no hubo transición
	}
}
void q15(char leer){
	if(leer == 'a'){ // a, lambda, lambda
		info[numPila][1]++;
		info[numPila][0] = 16; //Lo mandamos al estado correspondiente
	}
	else{
		info[numPila][0] = 100; //Informamos que no hubo transición
	}
}
void q16(char leer){
	if(leer == 'a'){ // e, lambda, lambda
		info[numPila][1]++;
		info[numPila][0] = 17; //Lo mandamos al estado correspondiente
	}
	else{
		info[numPila][0] = 100; //Informamos que no hubo transición
	}
}
void q17(char leer){
	if(leer == '.'){ // ., lambda, lambda
		info[numPila][1]++;
		info[numPila][0] = 18; //Lo mandamos al estado correspondiente
	}
	else{
		info[numPila][0] = 100; //Informamos que no hubo transición
	}
}
void q18(char leer){
	aceptada = false;
	if(leer == 'm'){ // ., lambda, lambda
		info[numPila][1]++;
		info[numPila][0] = 19; //Lo mandamos al estado correspondiente
	}
	else{
		info[numPila][0] = 100; //Informamos que no hubo transición
	}
}
void q19(char leer){
	if(leer == 'x'){ // x, lambda, lambda
		info[numPila][1]++;
		info[numPila][0] = 20; //Lo mandamos al estado correspondiente
	}
	else{
		info[numPila][0] = 100; //Informamos que no hubo transición
	}
}
void q20(char leer){
	aceptada = false;
	info[numPila][0] = 100; //Informamos que no hubo transición
}

//
int contEle(char ele, int cont, int n){
	int contT = 0;
	bool stop = false;
	while (stop != true) {
  		if(pila[numPila][n] != ele){stop = true;}
  		else{
	  		if(contT == cont) {
			  stop = true;}
	  		else{
		  		if(pila[numPila][n] == ele) {
					contT++;
					n--;
				}
		  		else{stop = true;}
	    	}
    	}
	}
  return contT;
}

//PILA
void push(char ele){
	info[numPila][2]++;
	pila[numPila][info[numPila][2]] = ele;
}

void pop(void){
	pila[numPila][info[numPila][2]] = '\0';
	info[numPila][2]--;
}

void imprimir(int n){
	int i;
	printf("\tPILA: ");
	for(i=n; i>-1; i--){
		printf("[%c]", pila[numPila][i]);
	}
	printf("\n");
}

void copiarPila(int n){
	int i;
	for(i=0; i<n+1; i++){
		pila[numPila + 1][i] = pila[numPila][i];
	}
	info[numPila + 1][0] = info[numPila][0];
	info[numPila + 1][1] = info[numPila][1];
	info[numPila + 1][2] = info[numPila][2];
	numPila++;
}

void eliminarPila(int n){
	int i;
	for(i=0; i<n; i++){
		pop();
	}
	info[numPila][0] = 0; //ESTADO
	info[numPila][1] = 0; //CONTADOR CARACTERES LEIDOS
	numPila--;
}
