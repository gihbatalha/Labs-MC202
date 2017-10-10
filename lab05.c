#include <stdio.h>
#include <stdlib.h>

typedef struct Livro{
	int id;
	char* nome;
}Livro;

typedef struct No{
	struct No* prox;
	Livro* livro;
}No;

typedef struct PilhaDeLivros{
	No* topo;
	int maximo;
	int tamanho;
} Pilha;

typedef struct Prateleira{
	Pilha** pilhaDeLivros; 	
	int qtddDeLivros;
	int maxLivros;
}Prateleira;

typedef struct Estante{
	Prateleira** prateleiras;
	Pilha* pilhaAux;
}Estante;

void inicializaPilha(Pilha* pilha){
	if(pilha == NULL){
		printf("Pilha nula\n");
		return;
	}

	pilha->topo = NULL;
	pilha->maximo = 0;
	pilha->tamanho = 0;
}

void printaLivro(Livro* livro){
	printf("Livro %d %s", livro->id, livro->nome);
}

void imprimePilha(Pilha* pilha){
	No* atual = pilha->topo;

	printf("Printando pilha -----------------------------------------\n");

	while(atual != NULL){
		//printaNo(atual);
		printaLivro(atual->livro);
		if(atual == pilha->topo){
			printf("--topo");
		}
		printf("\n");
		atual = atual->prox;
	}

	printf("----------------------------------------------------------\n");
}

void empilha(Pilha* pilha, Livro* livro){
	printf("Empilhando ");
	printaLivro(livro);
	printf("\n");

	if(pilha == NULL || livro == NULL){
		printf("ERRO[empilha] - Parâmetros nulos...\n");
	}

	//Cria novo nó
	No* novoNo = malloc(sizeof(No*));
	novoNo->livro = livro;

	novoNo->prox = pilha->topo;
	pilha->topo = novoNo;
}

Livro* desempilha(Pilha* pilha){

	No* noTopo = pilha->topo;

	pilha->topo = pilha->topo->prox;

	return noTopo->livro;
}

int testaInicializaPilha(Pilha* pilha){
	inicializaPilha(pilha);
}

int testaEmpilha(Pilha* pilha){
	

	imprimePilha(pilha);
	Livro* livro = malloc(sizeof(Livro*));
	livro->id = 0;
	livro->nome = "Livro\0";

	empilha(pilha, livro);

	imprimePilha(pilha);

	Livro* livro1 = malloc(sizeof(Livro*));
	livro1->id = 1;
	livro1->nome = "Livro1\0";

	empilha(pilha, livro1);
	imprimePilha(pilha);

	Livro* livro2 = malloc(sizeof(Livro*));
	livro2->id = 2;
	livro2->nome = "Livro2\0";

	empilha(pilha, livro2);
	imprimePilha(pilha);

	Livro* desemp = desempilha(pilha);
	printf("Livro desempilhado: %s\n", desemp->nome);

	imprimePilha(pilha);

	desempilha(pilha);
	desempilha(pilha);

	imprimePilha(pilha);
}

Prateleira* inicializaPrateleira(int numPilhas, int numLivros){
	Prateleira* retorno = malloc(sizeof(Prateleira*));

	retorno->pilhaDeLivros = malloc(numPilhas*sizeof(Pilha*));

	return retorno;
}

int inicializaEstante(Estante* estante, int numPrateleiras, int numPilhasPorPrateleira, int numMaxLivros){
	printf("Inicializando estante....\n");
	if(estante == NULL){
		printf("Estante nulaaaaaa\n");
	}

	estante->prateleiras = malloc(numPrateleiras*sizeof(Prateleira*));

	int i;
	for (i = 0; i < numPrateleiras; i++)
	{
		estante->prateleiras[i] = inicializaPrateleira(numPilhasPorPrateleira, numMaxLivros);
	}

	estante->pilhaAux = malloc(2*numMaxLivros*sizeof(Pilha*));
}

void testeInicializaEstante(Estante* estante){
	inicializaEstante(estante, 5, 3, 1);
}

int testes(){
	printf("Oiii\n");

	Pilha* pilha = malloc(sizeof(Pilha*));
	inicializaPilha(pilha);

	testaInicializaPilha(pilha);
	testaEmpilha(pilha);

	Estante* estante = malloc(sizeof(Estante*));
	
	testeInicializaEstante(estante);


	//programa();
}

void adicionaLivros(Estante* estante,int prat, int qtdLivros, char* nomes){

}

void preparaParaAdicionarLivros(Estante* estante){
	printf("Preparando para adicionar livrosssss....\n");
}

int main(){
	testes();

	int op = 0;
	int p, c, l;

	scanf("%d", &p);
	scanf("%d", &c);
	scanf("%d", &l);

	Estante* estante = malloc(sizeof(Estante*));
	inicializaEstante(estante, p, c, l);

	

	

	while(scanf("%d", &op) != EOF){
		switch(op){
			case 1: preparaParaAdicionarLivros(estante);
					op = 0;
					break;
		}
	}

}