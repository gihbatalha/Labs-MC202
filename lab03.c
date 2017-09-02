#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct NoDuplamenteLigado{
	struct Contato* chave;
	struct NoDuplamenteLigado* esq;
	struct NoDuplamenteLigado* dir;
} No;

typedef struct ListaDuplamenteLigada{
	struct NoDuplamenteLigado* selecionado;
	struct NoDuplamenteLigado* inicio;
	struct NoDuplamenteLigado* fim;
} Lista;

typedef struct Contato{
	char* nome;
	int cod;
	int tel;
	int preferido;
} Contato;



//Coloca 0 e "" nos atrivutos
int inicializaNo(No* no){
	if(no == NULL)
		return 0;

	no->chave = NULL;
	no->esq = NULL;
	no->dir = NULL;

	return 1;
}

int inicializaLista(Lista* lista){
	printf("Inicializando lista...\n");

	if(lista == NULL)
		return 0;

	lista->inicio = malloc(sizeof(No*));
	lista->fim = malloc(sizeof(No*));
	lista->selecionado = NULL;

	inicializaNo(lista->inicio);
	inicializaNo(lista->fim);

	if(lista->inicio == NULL || lista->fim == NULL)
		return 0;

	return 1;
}

int adicionaNoFimListaVazia(Lista* lista, No* no){
	printf("Adicionando no fim da lista vazia \n");
	
	if(no == NULL){
		printf("ERRO [adicionaNoFimListaVazia] Nó nulo \n");
		return 0;
	}

	no->dir = no;
	no->esq = no;

	lista->inicio->esq = no;
	lista->fim->dir = no;
	lista->selecionado = no;

	return 1;
}


//Adiciona um nó já com a chave preenchida, no fim da lista
int adicionaNoFim(Lista* lista, No* no){
	printf("Código do novo contato %d\n", no->chave->cod);
	
	if(no == NULL){
		printf("ERRO [Adiciona no fim] Nó nulo \n");
		return 0;
	}

	if(lista->inicio->esq == NULL && lista->fim->dir == NULL){
		printf("LISTA VAZIA!!!!!\n");
		return adicionaNoFimListaVazia(lista, no);
	}

	printf("Lista não vaziaaaaaaaaaaaaa\n");

	if(no->dir == NULL){
		printf("No->dir nulooooo\n");
	}
	
	no->dir = lista->inicio->esq;
	lista->inicio->esq->esq = no;
	lista->fim->dir->dir = no;
	no->esq = lista->fim->dir;

	return 1;
}

int adicionaContato(Lista* lista, int cod, char* nome, int tel, int preferido){
	Contato* novoContato;
	novoContato = malloc(sizeof(Contato*));

	if(novoContato == NULL)
		return 0;

	novoContato->nome = nome;

	printf("Nome: %s\n", novoContato->nome);
	novoContato->cod = cod;
	printf("Cód: %d\n", novoContato->cod);
	novoContato->tel = tel;
	printf("Telefone: %d\n", novoContato->tel);
	novoContato->preferido = preferido;
	printf("Preferido: %d\n", novoContato->preferido);

	No* novoNo;
	novoNo = malloc(sizeof(No*));

	novoNo->chave = novoContato;
	// novoNo->dir = malloc(sizeof(No*));
	// novoNo->esq = malloc(sizeof(No*));

	return adicionaNoFim(lista, novoNo);
}

int main()
{
	Lista* lista = malloc(sizeof(Lista*));

	int resposta = inicializaLista(lista);
	printf("Resposta do inicializaLista: %d \n",resposta);

	printf("Validando lista... \n");

	if(lista == NULL){
		printf("Lista nulaaaaa\n\n");
	}else{
		printf("Lista nao nulaaa\n\n");
		if(lista->fim != NULL){
			printf("Fim nao nulooo\n");
		}

		if(lista->inicio != NULL){
			printf("Inicio nao nulooo\n");
		}
	}

	printf("Acabou validação....\n");

	int contato = adicionaContato(lista, 12345678, "Giovanna", 981344418, 0);

	printf("Resposta do novo contato: %d \n",contato);
		
	printf("selecionado.nome: %s\n\n", lista->selecionado->chave->nome);

	int outroContato = adicionaContato(lista, 12, "Lucas", 988314300, 0);

	printf("Resposta do novo contato: %d \n", outroContato);

	printf("lista->selecionado->dir->chave->nome: %s\n\n", lista->selecionado->dir->chave->nome);
	return 0;
}