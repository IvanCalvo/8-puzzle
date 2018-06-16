#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** aloca_matriz(int lin, int col){ 
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
	int c = 0;
	verifica = 0;
	if((c==0)&&(num==0)){
		c=1;
		return 1;
	}
	if(vetor[num]!=num){
		return 1;
	}
	return verifica;
}

int** cria_resposta(int** m_resposta){
	int i, j;
	int x=0;
	m_resposta[0][0] = 1;
	m_resposta[0][1] = 2;
	m_resposta[0][2] = 3;
	m_resposta[1][0] = 4;
	m_resposta[1][1] = 5;
	m_resposta[1][2] = 6;
	m_resposta[2][0] = 7;
	m_resposta[2][1] = 8;
	m_resposta[2][2] = 0;
	return m_resposta;
}

int** cria_jogo(int** matriz){
	srand(time(NULL));
	int i, j, num;
	int verif=0;
	int *vet_num = (int*) malloc(9 * sizeof(int));
	for(i=0; i<9; i++){
		vet_num[i] = 0; 
	}
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			do{
				num = (rand()%9);
				verif = verifica_vetor(vet_num, num);
				if(verif==1){
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
	int** jogo = aloca_matriz(3, 3);
	jogo = cria_jogo(jogo);
	printf("Tabela Inicial\n");
	imprime_matriz(jogo);
	int** resposta = aloca_matriz(3,3);
	resposta = cria_resposta(resposta);
	printf("\nResposta\n");
	imprime_matriz(resposta);
	return 0;
}

