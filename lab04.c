#include <stdio.h>
#include <stdlib.h>

//Temos uma fila em que, há um ponteiro para o fim, mas o nó cabeça é o fim->prox, ou seja, o começo.
//Inserimos no fim
//Retiramos do início

typedef struct Processo{
	int id;
	int exec;
	int prio;
}Processo;

typedef struct NoLista{
	struct NoLista* prox;
	Processo* processo;
} No;

typedef struct Lista{
	No* fim;
} Fila;

int printaProcesso(Processo* processo, int idLista){
	if (processo == NULL){
		printf("ERRO[printaProcesso] processo nulo.\n");
		return 0;
	}

	printf("Processo %d (tempo de execucao %d) da fila %d\n",processo->id, processo->exec, idLista);
	return 1;
}

int inicializaFila(Fila* fila){
	if(fila == NULL){
		printf("Erro [inicializaFila]: Fila nula.\n");
		return 0;
	}

	fila->fim = malloc(sizeof(No*));
	fila->fim->prox = fila->fim;
	fila->fim->processo = NULL;

	return 1;
}

int imprime(Fila* fila){
	printf("Imprimindo fila.....................................................\n");
	printf("cabeça: ");
	printaProcesso(fila->fim->prox->processo, 0);

	No* atual = fila->fim->prox->prox; //recebe o inicio da fila, ou seja, o nó depois do cabeça

	while(atual != fila->fim->prox){		
		printaProcesso(atual->processo, 0);
		atual = atual->prox;
	}; //até chegar no nó cabeça

	printf("fim: ");
	printaProcesso(fila->fim->processo, 0);
	printf(".....................................................................\n");
}

void exibeProcessos(Fila* fila, int idLista){
	No* atual = fila->fim->prox->prox; //recebe o inicio da fila, ou seja, o nó depois do cabeça

	if(atual == fila->fim){
		printf("Nenhum processo existe na fila %d\n",idLista);
		return;
	}

	while(atual != fila->fim->prox){		
		printaProcesso(atual->processo, idLista);
		atual = atual->prox;
	}; //até chegar no nó cabeça

	return;
}



Processo* removeProcesso(Fila* fila){
	//Remove o primeiro processo, e o retorna.
	No* cabeca  = fila->fim->prox;

	if(cabeca == fila->fim->prox->prox){
		//lista vazia
		return NULL;
	}

	Processo* processo = cabeca->prox->processo;

	//estamos excluindo o fim, então fazemos ele apontar para a cabeça
	if(cabeca->prox == fila->fim){
		fila->fim = cabeca;
	}

	cabeca->prox = cabeca->prox->prox;
	
	return processo;
}

void insereProcesso(Fila* fila, Processo* processo){
	//Insere depois do fim atual e altera o fim
	if(processo == NULL){
		printf("ERRO[insereProcesso] processo nulo\n");
	}
	
	No* novoNo = malloc(sizeof(No*));
	novoNo->processo = processo;

	novoNo->prox = fila->fim->prox;
	fila->fim->prox = novoNo;

	fila->fim = novoNo;
}

Processo* moveProcessos(Fila* origem, Fila* destino){
	Processo* processo = removeProcesso(origem);

	if(processo != NULL)
		insereProcesso(destino, processo);

	return processo;
}

Processo* geraProcesso(int id, int tempo){
	Processo* processo = malloc(sizeof(Processo*));

	processo->id = id;
	processo->exec = tempo;
	processo->prio = 0;

	return processo;
}

void contaProcessos(Fila* fila){
	No* atual = fila->fim->prox->prox; //recebe o inicio da fila, ou seja, o nó depois do cabeça

	int contador = 0;

	while(atual != fila->fim->prox){		
		contador++;
		atual = atual->prox;
	}; //até chegar no nó cabeça

	//printf("Quantidade de processos na fila %d: %d\n",idLista, contador);
}

int testeMove(){
	Fila* fila1 = malloc(sizeof(Fila*));
	Fila* fila2 = malloc(sizeof(Fila*));
	inicializaFila(fila1);
	inicializaFila(fila2);

	moveProcessos(fila1, fila2);

	insereProcesso(fila1, geraProcesso(1, 15));
	insereProcesso(fila1, geraProcesso(2, 15));
	insereProcesso(fila2, geraProcesso(3, 15));
	insereProcesso(fila2, geraProcesso(4, 15));

	printf("\nANTES\n");
	imprime(fila1);
	imprime(fila2);

	printf("\nDEPOIS\n");
	moveProcessos(fila1, fila2);
	imprime(fila1);
	imprime(fila2);
}

int testaRemove(){
	Fila* fila = malloc(sizeof(Fila*));
	inicializaFila(fila);

	if(fila->fim == NULL){
		printf("Nao DEU CERTO\n");
	}

	Processo* processo = removeProcesso(fila);
	printaProcesso(processo, 0);	

	insereProcesso(fila,  geraProcesso(1, 15));
	insereProcesso(fila,  geraProcesso(2, 15));
	//insereProcesso(fila,  geraProcesso(3, 15));

	printf("\nANTES\n");
	imprime(fila);

	processo = removeProcesso(fila);

	printf("processo removido... ");
	printaProcesso(processo, 0);

	printf("\nDEPOIS\n");
	imprime(fila);

	removeProcesso(fila);
	//removeProcesso(fila);

	exibeProcessos(fila, 0);
}

void testaContador(){
	Fila* fila = malloc(sizeof(Fila*));
	inicializaFila(fila);

	contaProcessos(fila); // 0

	insereProcesso(fila,  geraProcesso(1, 15));
	insereProcesso(fila,  geraProcesso(2, 15));

	contaProcessos(fila); //2

	insereProcesso(fila,  geraProcesso(3, 15));

	contaProcessos(fila); // 3

	insereProcesso(fila,  geraProcesso(1, 15));
	insereProcesso(fila,  geraProcesso(2, 15));

	contaProcessos(fila); //5

}

void verificaInicializacao(Fila** filas){
	int i; 
	for(i=0; i<3; i++){
		if(filas[i] == NULL){
			printf("FILA %d NULAAAAAAAAAAAAAAAAAAAAAAAA\n", i);
		}
	}
}

Processo* criaProcesso(int id, int exec, int prio){
	Processo* processo = malloc(sizeof(Processo*));

	processo->id = id;
	processo->exec = exec;
	processo->prio = prio;

	return processo;
}
void preparaParaMoverProcesso(Fila* origem, Fila* destino, int idFilaOrigem, int idFilaDestino){
	Processo* processo = moveProcessos(origem, destino);

	if(processo == NULL)
		printf("Nenhum processo existe na fila %d\n", idFilaOrigem);
	else
		printf("Processo %d movido da fila %d para a fila %d\n",processo->id, idFilaOrigem, idFilaDestino);
}

void preparaParaRemoverProcesso(Fila* fila, int idFila){
	Processo* processo = removeProcesso(fila);

	if(processo == NULL)
		printf("Nenhum processo existe na fila %d\n", idFila);
	else
		printf("Processo %d removido da fila %d\n", processo->id, idFila);
}

void preparaParaInserirProcesso(Fila* fila, int idFila, int maxProcessos, int maxOperacoes, int* numProcessos){
	if(fila == NULL){
		printf("ERRO [preparaParaInserirProcesso] - Fila nula\n");
	}

	int id, tempoExec, prioridade;

	//Número de processos iria exceder
	if(*numProcessos >= maxProcessos){
		printf("Limite de processos excedido\n");
		return;
	}

	scanf("%d", &id);
	scanf("%d", &tempoExec);
	scanf("%d", &prioridade);

	Processo* processo = criaProcesso(id, tempoExec, prioridade);

	//printf("\n processo sendo adicionado. ");
	//printaProcesso(processo, idFila);

	insereProcesso(fila, processo);

	printf("Processo %d (tempo de execucao %d) adicionado na fila %d\n", processo->id, processo->exec, idFila);
}

int main(){
	Fila** filas = malloc(3*sizeof(Fila*));

	int i;
	for(i = 0; i < 3; i++){
		filas[i] = malloc(sizeof(Fila*));
		inicializaFila(filas[i]);
	}

	verificaInicializacao(filas);
	

	int op, numFila, maxProcessos, maxOperacoes;
	int numProcessos, numTransicoes, numFilaDestino;

	scanf("%d", &maxProcessos);
	scanf("%d", &maxOperacoes);

	while(scanf("%d", &op) != EOF){
		switch(op){
			case 1: scanf("%d", &numFila);
					preparaParaInserirProcesso(filas[numFila], numFila, maxProcessos, maxOperacoes, &numProcessos);
					numProcessos++;
					break;
			case 2: scanf("%d", &numFila);
					preparaParaRemoverProcesso(filas[numFila], numFila);
					numProcessos--;
					break;
			case 3: scanf("%d", &numFila);
					scanf("%d", &numFilaDestino);
					preparaParaMoverProcesso(filas[numFila], filas[numFilaDestino], numFila, numFilaDestino);
					break;
		}
	}

	//testaContador();
	//testeMove();
	//testaRemove();
}