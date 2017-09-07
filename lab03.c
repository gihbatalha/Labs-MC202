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
	//printf("Contato %s (telefone​ %d) codigo: %d ", contatinho->nome, contatinho->tel, contatinho->cod);

	if(contatinho->preferido == 0){
		printf("Contato %s (telefone %d) codigo: %d [N_PREFERIDO]\n", contatinho->nome, contatinho->tel, contatinho->cod);
		//printf("[N_PREFERIDO]\n");
	}else{
		printf("Contato %s (telefone %d) codigo: %d [PREFERIDO]\n", contatinho->nome, contatinho->tel, contatinho->cod);
		//printf("[PREFERIDO]\n");
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

	return 1;

}

//Imprime TODOS os contatos da lista
int imprimeTodosContatos(Lista* lista){
	printf("\n--------------- Imprimindo todos os contatos ----------------\n");
	if(lista->inicio->esq == NULL && lista->fim->dir == NULL){
		printf("ImprimeContato: Lista vazia\n");
		printf("-------------------------------------------------------------\n");
		return 1;
	}
	
	No* aux = lista->inicio->esq; //Recebe o início da lista

	//percorrendo pela direita
	do{	
		printaContato(aux->chave);
		aux = aux->dir;
	}while(aux != lista->inicio->esq);

	printf("selecionado: %s\n", lista->selecionado->chave->nome);
	printf("-------------------------------------------------------------\n");

	return 1;
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

	printf("Contato %s (telefone %d) adicionado na agenda\n", no->chave->nome, no->chave->tel);
	//printf("Contato %s (telefone​ %d) adicionado na agenda\n", no->chave->nome, no->chave->tel);
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
	//printf("Contato %s (telefone​ %d) adicionado na agenda\n", no->chave->nome, no->chave->tel);
	printf("Contato %s (telefone %d) adicionado na agenda\n", no->chave->nome, no->chave->tel);
	return 1;
}

//Métodos oficiais a serem chamados......

int adicionaContato(Lista* lista, int cod, char* nome, int tel, int preferido){
	//printf("Adicionando contato....\n");
	//printf("cod: %d| nome %s| tel %d|\n", cod, nome, tel);
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

	if(lista->inicio->esq == NULL && lista->fim->dir == NULL){
		//lista vazia
		printf("Contato nao existe\n");
		return 0;
	}

	No* noAchado = ant->dir;

	//Se há um nó na lista
	if(noAchado == noAchado->dir){
		lista->inicio->esq = NULL;
		lista->fim->dir = NULL;

		free(noAchado);
		return 1;
	}


	//Se á mais de um nó...
	//settando o nó SEL
	if(lista->selecionado == noAchado){
		if(noAchado->dir == noAchado){
			lista->selecionado = NULL;
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

	//printf("Contato %s (telefone​ %d) removido da agenda\n",noAchado->chave->nome, noAchado->chave->tel);
	printf("Contato %s (telefone %d) removido da agenda\n",noAchado->chave->nome, noAchado->chave->tel);
	free(noAchado);

	return 1;
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
		//printf("Lista vazia\n");
		printf("Contato nao existe\n");
		return 0;
	}

	//noAchado começa do selecionado
	noAchado = noAchado->dir; 

	do{
		if(noAchado->chave->tel == tel){
			//printf("Ligando para %s (telefone​ %d)\n", noAchado->chave->nome, noAchado->chave->tel);
			printf("Ligando para %s (telefone %d)\n",noAchado->chave->nome, noAchado->chave->tel);
			lista->selecionado = noAchado;
			return 1;
		}

		noAchado = noAchado->dir;

	}while(noAchado != lista->selecionado);

	//Não achou nenhum nó com o tel buscado
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
		sel = sel->esq;
	}

	lista->selecionado = sel;
	//printf("Contato %s (telefone​ %d) selecionado\n", sel->chave->nome, sel->chave->tel);
	printf("Contato %s (telefone %d) selecionado\n",sel->chave->nome, sel->chave->tel);
	return 1;
	
}

int retroceder(Lista* lista, int n){
	if(n<0){
		printf("ERRO [retroceder]: parâmetro n negativo.\n");
		return 0;
	}

	if(lista == NULL){
		printf("ERRO[retroceder]: Lista nula\n");
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

	//printf("Contato %s (telefone​ %d) selecionado\n", sel->chave->nome, sel->chave->tel);
	printf("Contato %s (telefone %d) selecionado\n",sel->chave->nome, sel->chave->tel);

	return 1;
}

int preferido(Lista* lista, char* nome){
	if(lista == NULL){
		printf("ERRO[preferido]: Lista nula\n");
		return 0;
	}

	if(nome == NULL){
		printf("ERRO[preferido]: nome nulo\n");
		return 0;
	}

	if(lista->inicio->esq == NULL && lista->fim->dir == NULL){
		printf("Contato nao existe\n");
		return 1;
	}

	//retorna o ant do selecionado
	No* no = busca(lista, lista->selecionado->chave->cod);
	no = no->dir; // setamos o no para o selecionado

	//printf("nome: %s\n",nome);

	do{
		char* nomeDoNo = no->chave->nome;
		//printf("Nome do no: %s\n",nomeDoNo);

		if(strcmp(nomeDoNo, nome) == 0){
			//printaNo(no);
			//printf("Contato %s (telefone​ %d) assinalado como preferido\n",no->chave->nome, no->chave->tel);
			printf("Contato %s (telefone %d) assinalado como preferido\n",no->chave->nome, no->chave->tel);
			no->chave->preferido = 1;
			return 1;
		}

		no = no->dir;

	}while(no != lista->selecionado);

	printf("Contato nao existe\n");
	return 0;	
}

int imprimirPreferidos(Lista* lista){
	if(lista == NULL){
		printf("ERRO[imprimirPreferidos]: Lista nula\n");
		return 0;
	}

	printf("[CONTATOS PREFERIDOS]\n");

	int preferidos = 0;

	if(lista->inicio->esq == NULL && lista->fim->dir == NULL){
		printf("Nenhum preferido encontrado\n");
		return 1;
	}

	//Retorna o ant do selecionado
	No* no = busca(lista, lista->selecionado->chave->cod);
	no = no->dir;
	//no = no->esq;

	//verifica se o selecionado é preferido
	if(no->chave->preferido == 1){
		preferidos++;
		//printf("Contato %s (telefone %d) codigo: %d\n",no->chave->nome, no->chave->tel, no->chave->cod);
		printf("Contato %s (telefone %d) codigo: %d\n",no->chave->nome, no->chave->tel, no->chave->cod);
	}

	//no = no->dir;
	no = no->esq;

	//Percorrendo pela direita
	while(no != lista->selecionado){
		if(no->chave->preferido == 1){
			preferidos++;
			//printf("Contato %s (telefone %d) codigo: %d\n",no->chave->nome, no->chave->tel, no->chave->cod);
			printf("Contato %s (telefone %d) codigo: %d\n",no->chave->nome, no->chave->tel, no->chave->cod);
		}

		//no = no->dir;
		no = no->esq;
	}

	if(preferidos <= 0){
		printf("Nenhum preferido encontrado\n");
	}
	return 1;
}

int imprimirContatos(Lista* lista, char letra){
	if(lista == NULL){
		printf("ERRO[imprimirContatos]: Lista nula\n");
		return 0;
	}
	//printf("Letra recebida: %c\n",letra);
	printf("[CONTATOS COM INICIAL %c]\n",letra);

	//lista vazia
	if(lista->inicio->esq == NULL && lista->fim->dir == NULL){
		printf("Nenhum contato encontrado\n");
		return 1;
	}

	//Retorna o ant do selecionado
	No* no = busca(lista, lista->selecionado->chave->cod);
	no = no->dir;
	//no = no->esq;
	
	int contatos = 0;

	do{
		char* nome = no->chave->nome;
		char primeiraLetra = nome[0];
		//printf("primeiraLetra: %c\n", primeiraLetra);

		if(primeiraLetra == letra){

			if(no->chave->preferido == 0){
				printf("Contato %s (telefone %d) codigo: %d [N_PREFERIDO]\n", no->chave->nome, no->chave->tel, no->chave->cod);
			}else{
				printf("Contato %s (telefone %d) codigo: %d [PREFERIDO]\n", no->chave->nome, no->chave->tel, no->chave->cod);
			}
			
			//printaContato(no->chave);
			contatos++;
		}

		//no = no->dir;
		no = no->esq;
	}while(no != lista->selecionado);

	if(contatos <= 0){
		printf("Nenhum contato encontrado\n");
	}

	return 1;
}

int preparaParaAdicao(Lista* lista){
	int cod, tel, preferido;
	char* nome = malloc(sizeof(char*));

	scanf("%d", &cod);
	scanf("%s", nome);
	scanf("%d", &tel);

	preferido = 0; //default

	adicionaContato(lista, cod, nome, tel, preferido);

	return 1;	
}

int preparaParaRemocao(Lista* lista){
	int cod;

	scanf("%d", &cod);
	removeContato(lista, cod);

	return 1;
}

int preparaParaLigar(Lista* lista){
	int tel;

	scanf("%d", &tel);
	liga(lista, tel);

	return 1;
}

int preparaParaAvancar(Lista* lista){
	int n;

	scanf("%d", &n);

	avancar(lista, n);
	return 1;
}

int preparaParaRetroceder(Lista* lista){
	int n;

	scanf("%d", &n);
	retroceder(lista, n);

	return 1;
}

int preparaParaMarcarComoPreferido(Lista* lista){
	char* nome = malloc(sizeof(No*));

	scanf("%s", nome);
	preferido(lista, nome);
	return 1;
}

int preparaParaImprimirContatos(Lista* lista){
	char letra;

	scanf(" %c", &letra);

	imprimirContatos(lista, letra);
	return 1;
}

int preparaParaImprimirPreferidos(Lista* lista){
	imprimirPreferidos(lista);
	return 1;
}

int main(){
	int op;

	Lista* agenda = malloc(sizeof(Lista*));
	inicializaLista(agenda);

	while(scanf("%d", &op) != EOF){

		switch(op){
			case 1: preparaParaAdicao(agenda);
					op = 0;
					break;

			case 2: preparaParaRemocao(agenda);
					op = 0;
					break;

			case 3: preparaParaLigar(agenda);
					op = 0;
					break;

			case 4: preparaParaAvancar(agenda);
					op = 0;
					break;

			case 5: preparaParaRetroceder(agenda);
					op = 0;
					break;

			case 6: preparaParaMarcarComoPreferido(agenda);
					op = 0;
					break;

			case 7: preparaParaImprimirContatos(agenda);
					op = 0;
					break;

			case 8: preparaParaImprimirPreferidos(agenda);
					op = 0;
					break;
		}
	}

	return 1;
}