//Montserrat Alejandra Ulloa Rivera
//Práctica 6. “Captura de los datos de un archivo TSPLIB”
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	FILE *manejador_archivo = NULL;
	char buffer[19] = "";
	int matriz[29][29], i, j;
	manejador_archivo= fopen("bays29.txt",  "r");
	
	if(manejador_archivo == NULL) {
     printf("No fue posible abrir el archivo\n");
     return -1;
   }
   
	//Leer lo anterior a la matriz
   while(strcmp(buffer, "EDGE_WEIGHT_SECTION") != 0){
   		fgets(buffer, 20, manejador_archivo);
   		printf("%s\n", buffer); 
   }
    
    puts("\tCONTENIDO DEL ARREGLO");
	//Leer la matriz del archivo y almacenarla   
   for(i=0;i<29;i++){                                
   		for(j=0;j<29;j++){        
        	fscanf(manejador_archivo, "%d", &matriz[i][j]);           
    	}
	}
	
	for(i=0;i<29;i++){                                
   		for(j=0;j<29;j++){        
        	printf("[%d]",matriz[i][j]);            
    	}
    	puts("");
	}

	fclose(manejador_archivo);
  	return 0;
}
