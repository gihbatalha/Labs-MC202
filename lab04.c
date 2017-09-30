//Giovanna Batalha 197960 TURMA F - MC202

//OBJETIVO------
//Desenvolver uma série de operações utilizando a estrutura de dados FILA, ou seja, inserimos no fim, retiramos do início.

//Fila:
//Inserimos no fim
//Retiramos do início

//Essas operações com filas tem o intuito de simular um Sistema operacional, que possui filas de processamento de processos.
//O SO utilizará três filas
//0 - Aptos, 1 - Bloqueados, 2- Executando

//ENTRADA E SAÍDA----
//Recebemos como entrada inicialmente um valor máximo de processos sendo manuzeados no SO e um valor máximo de operaçoes de transições entre filas.
//Após isso, recebemos um número que representa uma das operações que serão executadas, e em seguida seus respectivos parâmetros
//1 - Inserir na fila (núm fila, id do processo, tempo de execução do processo, número da prioridade) - Adiciona no fim da fila
//2 - Remover da fila (núm fila) - remove o processo que está no início
//3 - Mover entre filas (núm fila origem, núm fila destino) - remove o processo da origem e adiciona no destino
//4 - Exibe os processos (núm fila) - Exibe os processos do início para o fim
//5 - Número de processos (núm fila) - Retorna o número de processos da fila
//6 - Finaliza processos (tempo) - Desenfilera da fila de executando, se o tempo de exec do processo está dentro do tempo passado,
//								   Percorremos a fila desenfileirando os processos e atualizando o tempo que resta. No fim, 
//								   retornamos a quantidade de processos desenfileirados naquele tempo de execução.
//Nesses métodos existe os seguintes tratamentos:
//Se a fila não está vazia
//Se os limites de processos e operações de transições não foi excedido
//Se é possível mover de uma fila para outra.
// - Não podemos mover de Bloqueado para Executando
// - Não podemos mover de Aptos para Bloqueado
// - Não podemos mover um processo com prioridade 1 para fora de Executando

//RACIOCÍNIO USADO------
//Temos uma fila em que, há um ponteiro para o fim, mas o nó cabeça é o fim->prox.
//Portanto, para pegarmos o primeiro nó efetivo, devemos usar fim->prox->prox

//ex.
// cabeça  inicio              fim
// Nó      Nó       Nó    Nó   Nó 

//Apesar do exemplo, na fila só temos um ponteiro "fim", mas utilizamos o conceito de cabeça, ou seja, um nó com informações nulas
// e o Início representa o primeiro nó com valor não nulo, ou seja, que representa um processo efetivamente.

#include <stdio.h>
#include <stdlib.h>

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

//Usado ao adicionar um novo processo.
Processo* criaProcesso(int id, int exec, int prio){
	Processo* processo = malloc(sizeof(Processo*));

	processo->id = id;
	processo->exec = exec;
	processo->prio = prio;

	return processo;
}

int printaProcesso(Processo* processo, int idLista){
	if (processo == NULL){
		printf("ERRO[printaProcesso] processo nulo.\n");
		return 0;
	}

	printf("Processo %d (tempo de execucao %d) da fila %d\n",processo->id, processo->exec, idLista);
	return 1;
}

//Operação 4
void exibeProcessos(Fila* fila, int idLista){
	No* atual = fila->fim->prox->prox; //recebe o inicio da fila, ou seja, o nó depois do cabeça

	if(atual == fila->fim->prox){
		printf("Nenhum processo existe na fila %d\n",idLista);
		return;
	}

	while(atual != fila->fim->prox){		
		printaProcesso(atual->processo, idLista);
		atual = atual->prox;
	}; //até chegar no nó cabeça

	return;
}

//Operação 2
Processo* removeProcesso(Fila* fila){
	//Remove o primeiro processo, e o retorna.
	No* cabeca  = fila->fim->prox;

	if(cabeca == fila->fim->prox->prox){
		return NULL;
	}

	Processo* processo = cabeca->prox->processo;

	//estamos excluindo o fim, então fazemos ele apontar para a cabeça
	if(cabeca->prox == fila->fim){
		fila->fim = cabeca;
	}

	//Removemos do inicio da fila e atualizamos os ponteiros da fila
	cabeca->prox = cabeca->prox->prox;
	
	return processo;
}

//Operação 1
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

//Operação 3
Processo* moveProcessos(Fila* origem, Fila* destino){
	//Removemos da origem e adicionamos no destino

	Processo* processo = removeProcesso(origem);

	if(processo != NULL)
		insereProcesso(destino, processo);

	return processo;
}

//Operação 5
int contaProcessos(Fila* fila){
	No* atual = fila->fim->prox->prox; //recebe o inicio da fila, ou seja, o nó depois do cabeça

	int contador = 0;

	while(atual != fila->fim->prox){		
		contador++;
		atual = atual->prox;
	}; //até chegar no nó cabeça

	return contador;
}

//Operação 6
int finalizaProcessos(Fila* fila, int tempo){
	No* atual = fila->fim->prox->prox;
	int processos = 0;

	while(atual != fila->fim->prox && tempo > 0){

		//Vai desenfileirando enquanto a execução do processo está no tempo passado.
		if(atual->processo->exec <= tempo){
			tempo = tempo - atual->processo->exec;
			removeProcesso(fila);
			processos++;
		}else{
			tempo = 0;
		}

		atual = atual->prox;
	}

	return processos;
}

//Métodos auxiliares
void preparaParaFinalizarProcessos(Fila* fila, int tempo){
	int numeroProcessosFinalizados = finalizaProcessos(fila, tempo);

	printf("Quantidade de processos finalizados (em tempo, %d): %d\n",tempo, numeroProcessosFinalizados);
}

void preparaParaContarProcessos(Fila* fila, int idFila){
	int numProcessos = contaProcessos(fila);

	printf("Quantidade de processos na fila %d: %d\n",idFila, numProcessos);

}

Processo* retornaPrimeiro(Fila* fila){
	return fila->fim->prox->prox->processo;
}

int preparaParaMoverProcesso(Fila* origem, Fila* destino, int idFilaOrigem, int idFilaDestino, int maxTransicoes, int numTransicoes){
	int moverExecParaBloq = (idFilaOrigem == 1 && idFilaDestino == 2);
	int moverBloqParaAptos = idFilaOrigem == 0 && idFilaDestino == 1;

	Processo* primeiroProcesso = retornaPrimeiro(origem);

	int prioridade = 0;

	if(primeiroProcesso != NULL){
		prioridade = origem->fim->prox->prox->processo->prio==1 && idFilaDestino == 1;
	}

	int maxTransicoesExcedido = numTransicoes >= maxTransicoes;

	if( moverExecParaBloq || moverBloqParaAptos || prioridade){
		printf("Transacao nao permitida\n");
		return numTransicoes;
	}

	if(maxTransicoesExcedido){
		printf("Limite de transacoes excedidas\n");
		return numTransicoes;
	}

	Processo* processo = moveProcessos(origem, destino);

	if(processo == NULL)
		printf("Nenhum processo existe na fila %d\n", idFilaOrigem);
	else{
		printf("Processo %d movido da fila %d para a %d\n",processo->id, idFilaOrigem, idFilaDestino);
		return (numTransicoes + 1);
	}

	return numTransicoes;
}

void preparaParaRemoverProcesso(Fila* fila, int idFila, int* numProcessos){
	Processo* processo = removeProcesso(fila);

	if(processo == NULL)
		printf("Nenhum processo existe na fila %d\n", idFila);
	else{
		(*numProcessos)--;
		printf("Processo %d removido da fila %d\n", processo->id, idFila);
	}
}

void preparaParaInserirProcesso(Fila* fila, int idFila, int maxProcessos, int* numProcessos){
	if(fila == NULL){
		printf("ERRO [preparaParaInserirProcesso] - Fila nula\n");
	}

	int id, tempoExec, prioridade;

	scanf("%d", &id);
	scanf("%d", &tempoExec);
	scanf("%d", &prioridade);

	//Número de processos iria exceder
	if(*numProcessos >= maxProcessos){
		printf("Limite de processos excedido\n");
		return;
	}

	Processo* processo = criaProcesso(id, tempoExec, prioridade);

	insereProcesso(fila, processo);

	(*numProcessos)++;
	printf("Processo %d (tempo de execucao %d) adicionado na fila %d\n", processo->id, processo->exec, idFila);
}

int main(){
	//Vetor de filas, para representar as filas do SO
	Fila** filas = malloc(3*sizeof(Fila*));

	//Inicialização das filas
	int i;
	for(i = 0; i < 3; i++){
		filas[i] = malloc(sizeof(Fila*));
		inicializaFila(filas[i]);
	}

	int op, numFila, maxProcessos, maxOperacoes;
	int numProcessos, numTransicoes, numFilaDestino, tempoExec;

	numProcessos = 0;
	numTransicoes = 0;
	scanf("%d", &maxProcessos);
	scanf("%d", &maxOperacoes);

	while(scanf("%d", &op) != EOF){
		switch(op){
			case 1: scanf("%d", &numFila);
					preparaParaInserirProcesso(filas[numFila], numFila, maxProcessos, &numProcessos);
					break;
			case 2: scanf("%d", &numFila);
					preparaParaRemoverProcesso(filas[numFila], numFila, &numProcessos);
					break;
			case 3: scanf("%d", &numFila);
					scanf("%d", &numFilaDestino);
					numTransicoes = preparaParaMoverProcesso(filas[numFila], filas[numFilaDestino], numFila, numFilaDestino, maxOperacoes, numTransicoes);
					break;
			case 4: scanf("%d", &numFila);
					exibeProcessos(filas[numFila], numFila);
					break;
			case 5: scanf("%d", &numFila);
					preparaParaContarProcessos(filas[numFila], numFila);
					break;
			case 6: scanf("%d", &tempoExec);
					preparaParaFinalizarProcessos(filas[2], tempoExec); //Para finalizar, verificamos a lista 2
					break;
		}
	}
}