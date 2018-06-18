#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** aloca_matriz(int lin, int col){
	//cria uma nova matriz e preenche com 0
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

void imprime_vetor(int* vetor){
	int i;
	printf("vetor: \n");
	for(i=0; i<9; i++){
		printf("%d ", vetor[i]);
	}
	printf("\n");
}

int verifica_vetor(int* vetor, int num){
	//função que verifica se um numero já foi inserido
	/*a função recebe o vetor e o numero para ser procurado, caso esse numero seja encontrado
	significa que o número já foi inserido na matriz, portanto a função retorna 1 indicando a repetição*/
	int i, verifica;
	int c = 0;
	verifica = 0;
	if((c==0)&&(num==0)){
		c++;
		verifica = 1;
	} else if(vetor[num]!=num){
		verifica = 1;
	} else {
		verifica = 0;
	}
	return verifica;
}

int** cria_resposta(int** m_resposta){//matriz da resposta ideal para o jogo
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

int** cria_jogo(int** matriz){//cria uma matriz aleatória sem repetições, seguindo o padrão do jogo
	srand(time(NULL));
	int i, j, num;
	int verif=0;
	int quant_zero = 0;
	int *vet_num = (int*) malloc(9 * sizeof(int));
	for(i=0; i<9; i++){//preenche o vetor com 0
		vet_num[i] = 0; 
	}
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			do{
				num = (rand()%9);
				if(num==0){
					quant_zero++;
				}
				verif = verifica_vetor(vet_num, num);//chama a função para verificar se o número é repetido ou não
				if(quant_zero>1){
					verif--;
				}
				if(verif==1){
					matriz[i][j] = num;
					vet_num[num] = num;
					verif=2;
					//caso o numero não seja repetido, ele é colocado na matriz, e 
					//também no vetor que armazena os números já inseridos
					imprime_vetor(vet_num);
				}
			}while(verif!=2);
		}
	}
	return matriz;
}

int compara(int** a, int** b){
	int x, i, j;
	x=1;
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			if(a[i][j]!=b[i][j]){
				x=0;
			}
		}
	}
	return x;
}

int** troca(int num1, int num2, int** jogo){
	int aux;
	int i, j, x, y;
	int pos_i, pos_j;
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			if(jogo[i][j]==num1){
				aux = num1;
				jogo[i][j] = num2;
				pos_i=i;
				pos_j=j;
				break;
			}
		}
	}
	for(x=0; x<3; x++){
		for(y=0; y<3; y++){
			if(jogo[x][y]==num2){
				if(x!=pos_i || y!=pos_j){
					jogo[x][y] = aux;
				}
			}
		}
	}
	return jogo;
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
	printf("\nTroca 5 e 8\n");
	resposta = troca(8, 5, resposta);
	imprime_matriz(resposta);
	return 0;
}

