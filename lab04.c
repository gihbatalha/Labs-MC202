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

int printaProcesso(Processo* processo){
	if (processo == NULL){
		printf("ERRO[printaProcesso] processo nulo.\n");
		return 0;
	}

	printf("Processo %d => tempo de exec: %d, prio: %d\n", processo->id, processo->exec, processo->prio);
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
	printaProcesso(fila->fim->prox->processo);

	No* atual = fila->fim->prox->prox; //recebe o inicio da fila, ou seja, o nó depois do cabeça

	while(atual != fila->fim->prox){		
		printaProcesso(atual->processo);
		atual = atual->prox;
	}; //até chegar no nó cabeça

	printf("fim: ");
	printaProcesso(fila->fim->processo);
	printf(".....................................................................\n");
}



Processo* removeProcesso(Fila* fila){
	//Remove o primeiro processo, e o retorna.
	No* cabeca  = fila->fim->prox;

	if(cabeca == fila->fim->prox->prox){
		//lista vazia
		printf("Nenhum processo existe na fila\n");
		return NULL;
	}

	//TODO-------------------------------------------------------
	//se tem somente um processo, devemos atualizar o fim

	Processo* processo = cabeca->prox->processo;
	cabeca->prox = cabeca->prox->prox;

	printf("processo removido!\n");
	return processo;
}

Processo* insereProcesso(Fila* fila, Processo* processo){
	//Insere depois do fim atual e altera o fim
	if(processo == NULL){
		printf("ERRO[insereProcesso] processo nulo\n");
	}
	
	No* novoNo = malloc(sizeof(No*));
	novoNo->processo = processo;

	novoNo->prox = fila->fim->prox;
	fila->fim->prox = novoNo;

	fila->fim = novoNo;

	//printf("Processo %d (tempo de execucao %d) adicionado na fila %d\n", id, tempo, idLista);
	return processo;
}

Processo* moveProcessos(Fila* origem, Fila* destino){
	Processo* processo = removeProcesso(origem);

	if(processo == NULL){
		printf("Nenhum processo para mover\n");
	}else{
		insereProcesso(destino, processo);
	}

	return processo;
}

// Processo* insereProcesso(Fila* fila, int id, int tempo, int prio, int idLista){
// 	//Insere depois do fim atual e altera o fim
// 	No* novoNo = malloc(sizeof(No*));
// 	Processo* processo = malloc(sizeof(Processo*));

// 	processo->id = id;
// 	processo->exec = tempo;
// 	processo->prio = prio;

// 	novoNo->processo = processo;

// 	novoNo->prox = fila->fim->prox;
// 	fila->fim->prox = novoNo;

// 	fila->fim = novoNo;

// 	printf("Processo %d (tempo de execucao %d) adicionado na fila %d\n", id, tempo, idLista);
// 	return processo;
// }

// int testandoMetodos(Fila* fila){
// 	if(fila->fim == NULL){
// 		printf("Nao DEU CERTO\n");
// 	}

// 	Processo* processo = removeProcesso(fila, 0);

// 	printaProcesso(processo);
	

// 	insereProcesso(fila, 1, 15, 0, 0);
// 	insereProcesso(fila, 2, 25, 0, 0);
// 	insereProcesso(fila, 3, 10, 1, 0);

// 	imprime(fila);

// 	printf("\n");

// 	processo = removeProcesso(fila, 0);

// 	imprime(fila);
// }

Processo* geraProcesso(int id, int tempo){
	Processo* processo = malloc(sizeof(Processo*));

	processo->id = id;
	processo->exec = tempo;
	processo->prio = 0;

	return processo;
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

int main(){
	Fila* fila = malloc(sizeof(Fila*));
	inicializaFila(fila);

	testeMove();
	//testandoMetodos(fila);
}