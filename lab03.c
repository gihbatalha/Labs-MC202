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

int printaContato(Contato* contatinho){
	if(contatinho == NULL){
		printf("ERRO [printaContato]: contatinho nulo\n");
		return 0;
	}

	//Ex. Contato​ ​ Dexter​ ​ (telefone​ ​ 9555)​ ​ codigo:​ ​ 5555​ ​ [N_PREFERIDO]
	printf("Contato %s (telefone​ %d) codigo: %d ", contatinho->nome, contatinho->tel, contatinho->cod);

	if(contatinho->preferido == 0){
		printf("[N_PREFERIDO]\n");
	}else{
		printf("PREFERIDO\n");
	}

	return 1;
}

int printaNo(No* no){
	if(no->esq == NULL){
		printf("esq: NULL\n");
	}else{
		printf("esq: %s\n", no->esq->chave->nome);	
	}
	
	printf("no: %s\n", no->chave->nome);

	if(no->dir == NULL){
		printf("dir: NULL\n");
	}else{
		printf("dir: %s\n", no->dir->chave->nome);
	}

}

//Imprime TODOS os contatos da lista
int imprimeTodosContatos(Lista* lista){
	if(lista->inicio->esq == NULL && lista->fim->dir == NULL){
		printf("ImprimeContato: Lista vazia\n");
		return 1;
	}

	No* aux = lista->inicio->esq; //Recebe o início da lista

	//percorrendo pela direita
	do{	
		printaContato(aux->chave);
		aux = aux->dir;
	}while(aux != lista->inicio->esq);
}

//Coloca 0 e "" nos atrivutos
int inicializaNo(No* no){
	if(no == NULL){
		printf("ERRO [inicializaNo]: nó nulo\n");
		return 0;
	}

	no->chave = NULL;
	no->esq = NULL;
	no->dir = NULL;

	return 1;
}

int inicializaLista(Lista* lista){
	//printf("Inicializando lista...\n");

	if(lista == NULL){
		printf("ERRO [inicializaLista]: Lista nula \n");
		return 0;
	}

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
	//printf("Adicionando no fim da lista vazia - Contato %d\n", no->chave->cod);
	
	if(no == NULL){
		printf("ERRO [adicionaNoFimListaVazia] Nó nulo \n");
		return 0;
	}

	no->dir = no;
	no->esq = no;

	lista->inicio->esq = no;
	lista->fim->dir = no;
	lista->selecionado = no;

	printf("Contato %s (telefone​ %d) adicionado na agenda\n", no->chave->nome, no->chave->tel);
	return 1;
}


//Adiciona um nó já com a chave preenchida, no fim da lista
int adicionaNoFim(Lista* lista, No* no){	
	if(no == NULL){
		printf("ERRO [Adiciona no fim] Nó nulo \n");
		return 0;
	}

	//Lista vazia
	if(lista->inicio->esq == NULL && lista->fim->dir == NULL){
		return adicionaNoFimListaVazia(lista, no);
	}
	
	no->dir = lista->inicio->esq;
	lista->inicio->esq->esq = no;
	lista->fim->dir->dir = no;
	no->esq = lista->fim->dir;

	//atualiza o fim
	lista->fim->dir = no;
	printf("Contato %s (telefone​ %d) adicionado na agenda\n", no->chave->nome, no->chave->tel);
	return 1;
}

//Métodos oficiais a serem chamados......

int adicionaContato(Lista* lista, int cod, char* nome, int tel, int preferido){
	Contato* novoContato;
	novoContato = malloc(sizeof(Contato*));

	if(novoContato == NULL)
		return 0;

	novoContato->nome = nome;
	novoContato->cod = cod;
	novoContato->tel = tel;
	novoContato->preferido = preferido;

	No* novoNo;
	novoNo = malloc(sizeof(No*));

	novoNo->chave = novoContato;
	return adicionaNoFim(lista, novoNo);
}

No* busca(Lista* lista, int cod){
	if(lista == NULL){
		printf("ERRO [buscaContato] lista nula\n");
		return NULL;
	}

	if(lista->inicio->esq == NULL && lista->fim->dir == NULL){
		//printf("Buscando contato - Lista vazia\n");
		return NULL;
	}

	No* noAchado = malloc(sizeof(No*));
	No* ant = malloc(sizeof(No*));
	//printf("Busca Nó - Lista não vazia\n");
	noAchado = lista->inicio->esq; //Recebe o início da lista
	ant = lista->inicio->esq->esq; //Recebe o início da lista

	if(noAchado->chave->cod == cod){
		//printf("achado no primeiro nó:  %s\n", noAchado->chave->nome);
		return ant;
	}			

	ant = noAchado;
	noAchado = noAchado->dir;

	//Percorrendo pela direita
	while(noAchado != lista->inicio->esq){
		if(noAchado->chave->cod == cod){
			return ant;
		}

		ant = noAchado;
		noAchado = noAchado->dir;
	}

	return NULL;
	
}



int removeContato(Lista* lista, int cod){
	No* ant = busca(lista, cod);
	
	//Remoção de verdade a partir da busca:
	if(ant == NULL){
		printf("Contato nao existe\n");
		return 0;
	}

	No* noAchado = ant->dir;

	//settando o nó SEL
	if(lista->selecionado == noAchado){
		if(noAchado->dir == noAchado){
			lista->selecionado == NULL;
		}else{
			lista->selecionado = ant;
		}
	}

	//setamos o inicio se o no que será removido for o primeiro
	if(noAchado == lista->inicio->esq){
		lista->inicio->esq = noAchado->dir;
	}

	//setamos o fim se o no que será removido for o ultimo
	if(noAchado == lista->fim->dir){
		lista->fim->dir = ant;
	}

	ant->dir = noAchado->dir;
	noAchado->dir->esq = ant;	

	printf("Contato %s (telefone​ %d) removido da agenda\n",noAchado->chave->nome, noAchado->chave->tel);

	free(noAchado);
}

int liga(Lista* lista, int tel){
	//recebe o anterior do nó selecionado da lista
	No* noAchado = busca(lista, lista->selecionado->chave->cod);

	if(noAchado == NULL){
		printf("ERRO [liga]: no nulo\n");
	}
	if(lista == NULL){
		printf("ERRO [liga]: lista nula\n");
	}

	//Lista vazia
	if(lista->inicio->esq == NULL && lista->fim->dir == NULL){
		printf("Contato nao existe\n");
		return 0;
	}

	//noAchado começa do selecionado
	noAchado = noAchado->dir; 

	//Percorrendo pela direita
	while(noAchado != lista->inicio->esq){
		if(noAchado->chave->tel == tel){
			printf("Ligando para %s (telefone​ %d)\n", noAchado->chave->nome, noAchado->chave->tel);
			lista->selecionado = noAchado;
			return 1;
		}

		noAchado = noAchado->dir;
	}

	//Não achou nenhum nó com o cod buscado
	printf("Contato nao existe\n");
	return 0;
}

int avancar(Lista* lista, int n){
	if(n<0){
		printf("ERRO [avancar]: parâmetro n negativo. Usar função retroceder.\n");
		return 0;
	}

	if(lista == NULL){
		printf("ERRO[avancar]: Lista nula\n");
		return 0;
	}

	//Lista vazia
	if(lista->inicio->esq == NULL && lista->fim->dir == NULL){
		printf("Agenda vazia\n");
		return 0;
	}

	//busca retorna o anterior do nó selecionado
	No* sel = busca(lista, lista->selecionado->chave->cod);
	sel = sel->dir;

	int i;
	for(i=0; i < n; i++){
		sel = sel->dir;
	}

	lista->selecionado = sel;

	printf("Contato %s (telefone​ %d) selecionado\n", sel->chave->nome, sel->chave->tel);
}

int retroceder(Lista* lista, int n){
	if(n<0){
		printf("ERRO [avancar]: parâmetro n negativo.\n");
		return 0;
	}

	if(lista == NULL){
		printf("ERRO[avancar]: Lista nula\n");
		return 0;
	}

	//Lista vazia
	if(lista->inicio->esq == NULL && lista->fim->dir == NULL){
		printf("Agenda vazia\n");
		return 0;
	}

	//busca retorna o anterior do nó selecionado
	No* sel = busca(lista, lista->selecionado->chave->cod);
	sel = sel->dir;

	int i;
	for(i=0; i < n; i++){
		sel = sel->esq;
	}

	lista->selecionado = sel;
	printf("Contato %s (telefone​ %d) selecionado\n", sel->chave->nome, sel->chave->tel);
}

int preferido(Lista* lista, char* nome){
	if(lista == NULL){
		printf("ERRO[avancar]: Lista nula\n");
		return 0;
	}

	if(nome == NULL){
		printf("ERRO[avancar]: nome nulo\n");
		return 0;
	}

	No* no = busca(lista, lista->selecionado->chave->cod);
	no = no->dir;

	//verifica se é o selecionado
	if(no->chave->nome == nome){		
		printf("Contato %s (telefone​ %d) assinalado como preferido\n",no->chave->nome, no->chave->tel);
		no->chave->preferido = 1;
		return 1;
	}

	no = no->dir;

	//Percorrendo pela direita
	while(no != lista->selecionado){
		if(no->chave->nome == nome){
			printf("Contato %s (telefone​ %d) assinalado como preferido\n",no->chave->nome, no->chave->tel);
			no->chave->preferido = 1;
			return 1;
		}

		no = no->dir;
	}

	printf("Contato nao existe\n");
	return 0;	
}

int imprimirPreferidos(Lista* lista){
	printf("[CONTATOS PREFERIDOS]\n");

	int preferidos = 0;

	//Retorna o ant do selecionado
	No* no = busca(lista, lista->selecionado->chave->cod);
	no = no->dir;

	//verifica se o selecionado é preferido
	if(no->chave->preferido == 1){
		preferidos++;
		printf("Contato %s (telefone %d) codigo: %d\n",no->chave->nome, no->chave->tel, no->chave->cod);
	}

	no = no->dir;

	//Percorrendo pela direita
	while(no != lista->selecionado){
		if(no->chave->preferido == 1){
			preferidos++;
			printf("Contato %s (telefone %d) codigo: %d\n",no->chave->nome, no->chave->tel, no->chave->cod);
		}

		no = no->dir;
	}

	if(preferidos <= 0){
		printf("Nenhum preferido encontrado\n");
	}
	return 1;
}

int imprimirContatos(Lista* lista, char letra){
	//Retorna o ant do selecionado
	No* no = busca(lista, lista->selecionado->chave->cod);
	no = no->dir;

	printf("[CONTATOS COM INICIAL %c]\n",letra);

	int contatos = 0;

	do{
		char* nome = no->chave->nome;
		char primeiraLetra = nome[0];
		//printf("primeiraLetra: %c\n", primeiraLetra);

		if(primeiraLetra == letra){
			printaContato(no->chave);
			contatos++;
		}

		no = no->dir;
	}while(no != lista->selecionado);

	if(contatos <= 0){
		printf("Nenhum contato encontrado\n");
	}

	return 1;
}

int main()
{
	Lista* lista = malloc(sizeof(Lista*));

	inicializaLista(lista);

	No* noAchado = malloc(sizeof(No*));
	No* ant =  malloc(sizeof(No*));

	printaContato(noAchado->chave);

	printf("\n");

	adicionaContato(lista, 87, "Daniel", 981344418, 0);	
	adicionaContato(lista, 12345678, "Giovanna", 981344418, 0);	
	adicionaContato(lista, 001, "Gabriel", 9111, 0);
	adicionaContato(lista, 002, "Luma", 9222, 0);
	adicionaContato(lista, 003, "João", 9888, 0);
	adicionaContato(lista, 004, "Lucas", 9000, 0);
	adicionaContato(lista, 11, "José", 9111, 0);
	adicionaContato(lista, 10, "Jon Snow", 12121, 0);
	adicionaContato(lista, 007, "Fernanda", 9272, 0);
	printf("selecionado.nome: %s\n\n", lista->selecionado->chave->nome);

	imprimirContatos(lista, 'G');

	imprimirContatos(lista, 'M');

	printf("\n");

	removeContato(lista, 12345678);
	removeContato(lista, 2);
	removeContato(lista, 87);
	removeContato(lista, 999);
	removeContato(lista, 7);
	//adicionaContato(lista, 007, "Telefoneee", 9111, 0);
	liga(lista, 9111);

	printf("\n Contatos: \n");
	imprimeTodosContatos(lista);

	printf("selecionado.nome: %s\n\n", lista->selecionado->chave->nome);

	avancar(lista, 3);
	printf("selecionado.nome: %s\n\n", lista->selecionado->chave->nome);

	retroceder(lista, 2);
	printf("selecionado.nome: %s\n\n", lista->selecionado->chave->nome);

	printf("\n");	

	preferido(lista, "Giovanna");
	imprimirPreferidos(lista);

	preferido(lista, "Jon Snow");
	imprimirPreferidos(lista);

	return 0;
}