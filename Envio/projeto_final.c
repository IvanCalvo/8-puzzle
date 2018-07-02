#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
typedef struct arv_binaria_busca{
    int soma;
    int** matriz;
    struct arv_binaria_busca* esquerda;
    struct arv_binaria_busca* direita;
}Arv_BBusca;

typedef struct lista{

    int info;
    struct lista* prox;

}ListaSimp;
Arv_BBusca* cria_arv(){
    return NULL;
}
ListaSimp* cria_lista(){
    return NULL;
}
int lista_vazia(ListaSimp* L){
    return (L==NULL);
}
ListaSimp* insere_elem(ListaSimp* L,int valor){

    ListaSimp* novo = (ListaSimp*)malloc(sizeof(ListaSimp));

    novo->info = valor;
    novo->prox = L;

    return novo;
}
typedef struct lista2{
    int info;
    int** matriz;
    struct lista2* prox;
    struct lista2* ant;

}Lista_D;
Lista_D* insere_elem2(Lista_D* L,int valor,int** jogo){
    Lista_D* novo =(Lista_D*)malloc(sizeof(Lista_D));
    Lista_D* aux=L;
    novo->matriz = jogo;
    novo->info=valor;

    if(L==NULL){
        novo->prox=NULL;
        novo->ant=NULL;
        return novo;
    }
    else{
            if(aux->info < valor){
            novo->prox = aux->prox;
            novo->ant=aux;
            aux->ant=NULL;
            aux->prox=novo;
            return aux;
            }else{
            novo->prox=aux;
            novo->ant=NULL;
            return novo;
            }


    }

}


ListaSimp* acha_distancias( int** jogo_certo,int** jogo){
    int i ,j ;
    ListaSimp* L;
    L = cria_lista();
    int x = 0, z = 0 , d , valor ;

    for(i = 0 ; i < 3;i++){
        for(j = 0; j < 3; j++){
            z = 0;
            x = 0;
            d = 0;
            valor = jogo_certo[i][j];

                while( jogo[x][z]!= valor){
                    ++z;
                    if(z>=3){
                        ++x;
                        z = 0;
                    }
                }
            d = (abs(i - x)) + (abs( j - z ));
            L = insere_elem( L , abs(d));
        }
    }
    return L;

}

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

void imprimir_lista(ListaSimp* L){
    ListaSimp* p;

        if(lista_vazia(L))
            printf("\nLista vazia");
        else{
            for(p = L ;p!=NULL;p=p->prox)
                printf("%d\n",p->info);

        }

}

void imprime_matriz(int** matriz){
	int i, j;
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			printf(" %d ", matriz[i][j]);
		}
		printf("\n");
	}
	printf("\n=============\n");
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
	verifica = 0;
	if(vetor[num]!=num){
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
	int *vet_num = (int*) malloc(9 * sizeof(int));
	for(i=0; i<9; i++){//preenche o vetor com 9
		vet_num[i] = 9;
	}
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			do{
				while(verif!=1){
					num = (rand()%9);
					verif = verifica_vetor(vet_num, num);//chama a função para verificar se o número é repetido ou não
				}
				if(verif==1){
					matriz[i][j] = num;
					vet_num[num] = num;
					verif=2;
					//caso o numero não seja repetido, ele é colocado na matriz, e
					//também no vetor que armazena os números já inseridos
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
Arv_BBusca* arv_insere(Arv_BBusca* ABB,int s1,int** matriz){

    

            ABB=(Arv_BBusca*)malloc(sizeof(Arv_BBusca));

            ABB->soma = s1;
            ABB->matriz = matriz;
            ABB->direita = NULL;
            ABB->esquerda = NULL;
            
   return ABB;
}
int soma_lista(ListaSimp* L){

    ListaSimp* aux;
    int aux2 = 0;

    for(aux = L;aux!=NULL;aux = aux->prox){
        aux2 += aux->info;
    }
    return aux2;
}
int** jogada1(int** jogo1){
    int z = 0,y = 0,i =0,j=0,aux;

     while( jogo1[i][j]!= 0){
            ++j;
            if(j>=3){
                ++i;
                j = 0;
            }
        }
    y = i + 1 ;
    z = j ;

    if(y!=3){
    aux = jogo1[y][z];
    jogo1[i][j] = aux;
    jogo1[y][z] = 0;
    }

    return jogo1;
}

int** jogada2(int** jogo1){
    int z = 0,y = 0,i =0,j=0,aux;

       while( jogo1[i][j]!= 0){
            ++j;
            if(j>=3){
                ++i;
                j = 0;
            }
        }
    y = i - 1;
    z = j ;
    if(y >=0){
    aux = jogo1[y][z];
    jogo1[i][j] = aux;
    jogo1[y][z] = 0;
}

    return jogo1;
}
int** jogada3(int** jogo1){
    int z = 0,y = 0,aux,i =0,j=0;

     while( jogo1[i][j]!= 0){
            ++j;
            if(j>=3){
                ++i;
                j = 0;
            }
        }
    y = i;
    z = j + 1;
    if(z!=3){
    aux = jogo1[y][z];
    jogo1[i][j] = aux;
    jogo1[y][z] = 0;

}


    return jogo1;
}
int** jogada4(int** jogo1){
    int z = 0,y = 0,aux,i =0,j=0;

    while( jogo1[i][j]!= 0){
            ++j;
            if(j>=3){
                ++i;
                j = 0;
            }
        }
    y = i;
    z = j - 1;
    if(z >= 0){
    aux = jogo1[y][z];
    jogo1[i][j] = aux;
    jogo1[y][z] = 0;

}

    return jogo1;
}

int compara2(int** aux, int** jogo){
	int cont = 0;
	int i, j;
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
				if (aux[i][j]!= jogo[i][j]){
					++cont;
				}
			}
		}
	return cont;
				
}
Arv_BBusca* jogada_arvore(int** jogo1,Arv_BBusca* ABB, int** resposta){

    int** aux1= aloca_matriz(3,3) ;
    int** aux2= aloca_matriz(3,3);
    int** aux3= aloca_matriz(3,3) ;
    int** aux4= aloca_matriz(3,3) ;
    int** aux = jogo1;
    ListaSimp* L;
    L = cria_lista();
    Lista_D* L2;
    L2 = NULL;
    int s1,s2,s3,s4,i,j;
	int cont1 = 0,cont2 = 0,cont3 = 0,cont4 = 0;


    for(i=0; i<3; i++){
		for(j=0; j<3; j++){
            aux1[i][j]= aux[i][j];
            aux2[i][j]= aux[i][j];
            aux3[i][j]= aux[i][j];
            aux4[i][j]= aux[i][j];
		}
		}
    aux1 = jogada1(aux1);
    cont1 =  compara2(aux1,jogo1);
    if(cont1!=0){
    L = acha_distancias(resposta,aux1);
    s1 = soma_lista(L);
    L2 = insere_elem2(L2,s1,aux1);
}
    aux2 = jogada2(aux2);
    cont2 =  compara2(aux2,jogo1);
    if(cont2!=0){
    L = acha_distancias(resposta,aux2);
    s2 = soma_lista(L);
    L2 = insere_elem2(L2,s2,aux2);
}
    aux3 = jogada3(aux3);
    cont3 =  compara2(aux3,jogo1);
    if(cont3!=0){
    L = acha_distancias(resposta,aux3);
    s3 = soma_lista(L);
    L2 = insere_elem2(L2,s3,aux3);
}
    aux4 = jogada4(aux4);
    cont4 =  compara2(aux4,jogo1);
    if(cont4!=0){
    L = acha_distancias(resposta,aux4);
    s4 = soma_lista(L);
    L2 = insere_elem2(L2,s4,aux4);
}
    Lista_D* L0 = L2 ;
    int**matriz1 = L0->matriz;
    int**matriz2 = L0->prox->matriz;
    int w = L0->info;
    int f = L0->prox->info;
	
    ABB->esquerda= arv_insere(ABB,w,matriz1);
    ABB->direita = arv_insere(ABB,f,matriz2);

    return ABB;
}

Arv_BBusca* adiciona_jogadas(int** jogo1,Arv_BBusca* ABB1, int** resposta){
    int s , x, i, j;
    Arv_BBusca* aux;
    Arv_BBusca* aux2;
    Arv_BBusca* aux3;
    Arv_BBusca* aux4;
    int** matriz ;
    int** matriz1 = aloca_matriz(3,3);
    int** matriz2 = aloca_matriz(3,3) ;
    int** matriz3;
    ABB1 = jogada_arvore(jogo1,ABB1,resposta);
    aux = ABB1;
    aux3 = ABB1;
    aux3 = aux3->direita;
    s= ABB1->soma;
    x= ABB1->soma;

    
    do{
    	aux2 = aux;
        aux = aux->esquerda;
        matriz = aux->matriz;
        for(i=0; i<3; i++){
            for(j=0; j<3; j++){
            matriz1[i][j]= matriz[i][j];
            }
        }
        if(s==aux->soma){
        	aux2=aux2->direita; 	
        	aux = aux2;
		}
        aux = jogada_arvore(matriz1,aux,resposta);
		imprime_matriz(matriz1);
        s = aux->soma;

       aux4 = aux3;
        
        matriz3 = aux3->matriz;
        for(i=0; i<3; i++){
            for(j=0; j<3; j++){
            matriz2[i][j]= matriz3[i][j];
            }
        }
        aux3 = jogada_arvore(matriz2,aux3,resposta);
		imprime_matriz(matriz2);
		aux3 = aux3->esquerda;
        x = aux3->soma;
		
    }while(x!=0&&s!=0);

    return ABB1;
}

int main(){

    int s;

	ListaSimp* L;
	L = cria_lista();
	
    Arv_BBusca* ABB;
    ABB = cria_arv();
    
    int** resposta = aloca_matriz(3,3);
	resposta = cria_resposta(resposta);
	
	printf("Tabela resposta\n");
	imprime_matriz(resposta);

	srand(time(NULL));
	int** jogo = aloca_matriz(3, 3);
	jogo = cria_jogo(jogo);
	printf("Tabela Inicial\n");
	imprime_matriz(jogo);

	
	L = acha_distancias(resposta,jogo);
    s = soma_lista(L);
    
    printf("\njogadas\n");
	ABB = arv_insere(ABB,s,jogo);
    ABB = adiciona_jogadas(jogo,ABB,resposta);

	return 0;
}

