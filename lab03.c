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
int imprimeContatos(Lista* lista){
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
	printf("Inicializando lista...\n");

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
	printf("Adicionando no fim da lista vazia - Contato %d\n", no->chave->cod);
	
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
	if(no == NULL){
		printf("ERRO [Adiciona no fim] Nó nulo \n");
		return 0;
	}

	//Lista vazia
	if(lista->inicio->esq == NULL && lista->fim->dir == NULL){
		return adicionaNoFimListaVazia(lista, no);
	}

	printf("Adicionando no fim da lista - Contato %d\n", no->chave->cod);
	
	no->dir = lista->inicio->esq;
	lista->inicio->esq->esq = no;
	lista->fim->dir->dir = no;
	no->esq = lista->fim->dir;

	//atualiza o fim
	lista->fim->dir = no;

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

//Caso só exista um no na lista e ele for o buscado, o ant será retornado NULL
//Caso a lista estiver vazia, o noAchado será retornado NULL
int buscaContato(Lista* lista, int cod, No* noRetorno, No* anterior){
	if(anterior == NULL || noRetorno == NULL || lista == NULL){
		printf("ERRO [buscaContato] parâmetros nulos\n");
		return 0;
	}

	if(lista->inicio->esq == NULL && lista->fim->dir == NULL){
		printf("Buscando contato - Lista vazia\n");
		noRetorno = NULL;
		anterior = NULL;
		return 0;
	}

	noRetorno = lista->inicio->esq; 
}



int removeContato(Lista* lista, int cod){
	// No* noAchado = malloc(sizeof(No*));
	// No* ant =  malloc(sizeof(No*));

	// //int busca = buscaContato(lista, cod, noAchado, ant);

	// int busca = 0;

	// if(lista->inicio->esq == NULL && lista->fim->dir == NULL){
	// 	//Lista vazia;
	// 	printf("Busca Nó - Lista vazia\n");
	// 	noAchado = NULL;
	// 	ant = NULL;
	// 	return -1;
	// }

	// //printf("Busca Nó - Lista não vazia\n");
	// noAchado = lista->inicio->esq; //Recebe o início da lista
	// ant = lista->inicio->esq; //Recebe o início da lista

	// if(noAchado->chave->cod == cod){
	// 	printf("achado no primeiro nó:  %s\n", noAchado->chave->nome);
	// 	//printf("noAchado cod: %d\n",noAchado->chave->cod);
	// 	busca = 1;
	// }

	// noAchado = noAchado->dir;

	// //Percorrendo pela direita
	// while(noAchado != lista->inicio->esq){
	// 	if(noAchado->chave->cod == cod){
	// 		printf("achado %s\n", noAchado->chave->nome);
	// 		busca = 1;
	// 		break;
	// 	}

	// 	ant = noAchado;
	// 	noAchado = noAchado->dir;
	// }

	// //Não achou nenhum nó com o cod buscado
	// if(busca != 1){
	// 	printf("Não achou o nó\n");
	// 	noAchado = NULL;
	// 	ant = NULL;
	// 	busca = -1;
	// }
	
	// //Remoção de verdade a partir da busca:
	// if(busca != 1)
	// 	return 0;


	// printf("Busca deu certo\n");

	// printaContato(noAchado->chave);

	// printf("\n");
	// printf("ant:\n");
	// printaContato(ant->chave);

	// if(lista->selecionado == noAchado){
	// 	if(noAchado->dir == noAchado){
	// 		lista->selecionado == NULL;
	// 	}else{
	// 		lista->selecionado = ant;
	// 	}
	// }

	// if(noAchado == lista->inicio->esq){
	// 	lista->inicio->esq = noAchado->dir;
	// }

	// if(noAchado == lista->fim->dir){
	// 	lista->fim->dir = ant;
	// }

	// ant->dir = noAchado->dir;
	// noAchado->dir->esq = ant;	

	// free(noAchado);
}

// int liga(Lista* lista, int tel){
// 	No* noAchado = malloc(sizeof(No*));

// 	if(noAchado == NULL){
// 		printf("ERRO [liga]: no nulo\n");
// 	}
// 	if(lista == NULL){
// 		printf("ERRO [liga]: lista nula\n");
// 	}

// 	//Lista vazia
// 	if(lista->inicio->esq == NULL && lista->fim->dir == NULL){
// 		printf("Contato nao existe\n");
// 		return 0;
// 	}

// 	noAchado = lista->inicio->esq; //Recebe o início da lista

// 	if(noAchado->chave->tel == tel){
// 		printf("Ligando para %s (telefone​ %d)\n", noAchado->chave->nome, noAchado->chave->tel);
// 		return 1;
// 	}

// 	noAchado = noAchado->dir;

// 	//Percorrendo pela direita
// 	while(noAchado != lista->inicio->esq){
// 		if(noAchado->chave->cod == tel){
// 			printf("Ligando para %s (telefone​ %d)\n", noAchado->chave->nome, noAchado->chave->tel);
// 			return 1;
// 		}

// 		noAchado = noAchado->dir;
// 	}

// 	//Não achou nenhum nó com o cod buscado
// 	printf("Contato nao existe\n");
// 	return 0;
// }

int main()
{
	Lista* lista = malloc(sizeof(Lista*));

	inicializaLista(lista);

	No* noAchado = malloc(sizeof(No*));
	No* ant =  malloc(sizeof(No*));
	buscaContato(lista, 999, noAchado, ant);

	printaContato(noAchado->chave);

	imprimeContatos(lista);
	removeContato(lista, 001);
	printf("\n");

	adicionaContato(lista, 12345678, "Giovanna", 981344418, 0);	
	adicionaContato(lista, 001, "Gabriel", 9111, 0);
	adicionaContato(lista, 002, "Luma", 9222, 0);
	adicionaContato(lista, 003, "João", 9888, 0);
	adicionaContato(lista, 004, "Lucas", 9000, 0);
	adicionaContato(lista, 007, "Fernanda", 9272, 0);
	printf("selecionado.nome: %s\n\n", lista->selecionado->chave->nome);

	imprimeContatos(lista);
	printf("\n");

	removeContato(lista, 12345678);
	removeContato(lista, 2);
	removeContato(lista, 999);

	imprimeContatos(lista);
	printf("selecionado.nome: %s\n\n", lista->selecionado->chave->nome);

	printf("\n");	
	return 0;
}