#include <stdio.h>
#include <stdlib.h>

//Temos uma fila em que, há um ponteiro para o fim, mas o nó cabeça é o fim->prox, ou seja, o começo.

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

	printf("inicializaFila...\n");
	fila->fim = malloc(sizeof(No*));
	//fila->fim->prox = malloc(sizeof(No*));

	return 1;
}

int imprime(Fila* fila){
	printf("Imprimindo fila.....................................................\n");
	if(fila->fim != NULL){
		printf("fim não eh nulo\n");
	}

	if(fila->fim->prox != NULL){
		printf("prox do fim nao eh nulo\n");
	}

	No* atual = fila->fim->prox; //recebe o início da fila

	do{
		printf("oi\n");
		printaProcesso(atual->processo);

		atual = atual->prox;
	}while(atual != fila->fim->prox); //até chegar no nó cabeça
	printf(".....................................................................\n");
}

int insereProcesso(Fila* fila, int id, int tempo, int prio){
	//Insere depois do fim atual e altera o fim
	No* novoNo = malloc(sizeof(No*));
	Processo* processo = malloc(sizeof(Processo*));

	processo->id = id;
	processo->exec = tempo;
	processo->prio = prio;

	printaProcesso(processo);

	novoNo->processo = processo;

	if(novoNo != NULL){
		printf("Novo no nao eh nulo\n");
	}

	novoNo->prox = fila->fim->prox;
	fila->fim->prox = novoNo;

	fila->fim = novoNo;

	printf("Inserido!\n");
	return 1;
}

int main(){
	Fila* fila = malloc(sizeof(Fila*));
	inicializaFila(fila);

	if(fila->fim == NULL){
		printf("Nao DEU CERTO\n");
	}else{
		printf(" deu certo\n");
	}

	insereProcesso(fila, 1, 1, 1);

	imprime(fila);
}