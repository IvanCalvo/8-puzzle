#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** aloca_matriz(int lin,int col){ 
	int i, j;
	int **matriz = (int**)malloc(lin * sizeof(int*));
 
	for (i = 0; i < lin; i++){
    	matriz[i] = (int*) malloc(col * sizeof(int));
    	for (j = 0; j < col; j++){
    		matriz[i][j] = 0;				
       	}
  	}
	
	return matriz;
}

void imprime_matriz(int** matriz){
	int i, j;
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			printf(" %d ", matriz[i][j]);
		}
		printf("\n");
	}
}

int verifica_vetor(int* vetor, int num){
	int i, verifica;
	verifica = 1;
	if((vetor[num] = num)&&num!=0){
		verifica = 0;
	}
	return verifica;
}

int** cria_jogo(int** matriz){
	srand(time(NULL));
	int i, j, num;
	int verif;
	int *vet_num = (int*) malloc(9 * sizeof(int));
	for(i=0; i<9; i++){
		vet_num[i] = 0; 
	}
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			do{
				num = (rand()%8)+1;
				verif = verifica_vetor(vet_num, num);
				if(verif = 1){
					matriz[i][j] = num;
					vet_num[num] = num;
					verif=2;
				}
			}while(verif!=2);
		}
	}
	return matriz;
}

int main(){
	srand(time(NULL));
	int** jogo = aloca_matriz(3,3);
	jogo = cria_jogo(jogo);
	printf("Tabela Inicial\n");
	imprime_matriz(jogo);
}

