#include <stdio.h>
#include <stdlib.h>

typedef struct Livro{
	int id;
	char* nome;
}Livro;

typedef struct No{
	Livro* livro;
	struct No* prox;
}No;

typedef struct PilhaDeLivros{
	No* topo;
	int maximo;
	int tamanho;
} Pilha;

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
	printf("Livro %d %s\n", livro->id, livro->nome);
}

void imprimePilha(Pilha* pilha){
	No* atual = pilha->topo;

	printf("Printando pilha -----------------------------------------\n");

	while(atual != NULL){
		printaLivro(atual->livro);
		atual = atual->prox;
	}

	printf("----------------------------------------------------------\n");
}

void empilha(Pilha* pilha, Livro* livro){
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

}

int testaInicializaPilha(Pilha* pilha){
	inicializaPilha(pilha);
}

int testaEmpilha(Pilha* pilha){
	

	imprimePilha(pilha);
	Livro* livro = malloc(sizeof(Livro*));
	livro->id = 0;
	livro->nome = "Livro";

	printf("Novo livro::::::::");
	printaLivro(livro);

	empilha(pilha, livro);

	imprimePilha(pilha);

	Livro* livro1 = malloc(sizeof(Livro*));
	livro->id = 1;
	livro->nome = "Livro1\0";

	empilha(pilha, livro1);
	imprimePilha(pilha);
}


int main(){
	printf("Oiii\n");

	Pilha* pilha = malloc(sizeof(Pilha*));
	inicializaPilha(pilha);

	testaInicializaPilha(pilha);
	testaEmpilha(pilha);

}