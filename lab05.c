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
	int numColunas;
	int preco;
}Prateleira;

typedef struct Estante{
	Prateleira** prateleiras;
	Pilha* pilhaAux;
	int numPrateleiras;
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
	printf("Livro: %s",  livro->nome);
}

void imprimePilha(Pilha* pilha){
	No* atual = pilha->topo;

	printf("Printando pilha -----------------------------------------\n");

	printf("tamanho: %d\n",pilha->tamanho);
	printf("maximo: %d\n", pilha->maximo);

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


void printaPrateleira (Prateleira* prateleira, int index){
	int i; 

	printf("PRINTANDO PRATELEIRA %d (R$ %d) \n", index, prateleira->preco);

	for(i=0; i < prateleira->numColunas; i++){
		printf("Pilha %d\n",i);
		imprimePilha(prateleira->pilhaDeLivros[i]);
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

	//atualiza o tamanho da pilha
	pilha->tamanho = pilha->tamanho + 1;
}

Livro* desempilha(Pilha* pilha){
	printf("desempilha.....\n");
	No* noTopo = pilha->topo;

	pilha->topo = pilha->topo->prox;

	pilha->tamanho = pilha->tamanho - 1;

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

Pilha* criaPilha(int numMaxLivros){
	Pilha* retorno = malloc(sizeof(Pilha*));

	retorno->tamanho = 0;
	retorno->maximo = numMaxLivros;
	retorno->topo = NULL;

	return retorno;
}

void associaPreco(Prateleira* prateleira, int preco){
	prateleira->preco = preco;
}

Prateleira* inicializaPrateleira(int numPilhas, int numMaxLivros){
	Prateleira* retorno = malloc(sizeof(Prateleira*));

	retorno->maxLivros = numMaxLivros * numPilhas;
	retorno->qtddDeLivros = 0;
	retorno->numColunas = numPilhas;
	retorno->preco = 0;

	retorno->pilhaDeLivros = malloc(numPilhas*sizeof(Pilha*));

	int i;
	for(i=0; i < numPilhas; i++){
		retorno->pilhaDeLivros[i] = criaPilha(numMaxLivros);
		
	}

	return retorno;
}

int inicializaEstante(Estante* estante, int numPrateleiras, int numPilhasPorPrateleira, int numMaxLivros){
	printf("Inicializando estante.... %d, %d, %d.\n", numPrateleiras, numPilhasPorPrateleira, numMaxLivros);
	if(estante == NULL){
		printf("Estante nulaaaaaa\n");
	}

	estante->numPrateleiras = numPrateleiras;
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

Livro* criaLivro(char* nome){
	Livro* meuLivro = malloc(sizeof(Livro*));
	meuLivro->nome = nome;

	return meuLivro;
}

int cabeMaisUmLivroNaPilha(Pilha* pilhaDeLivros){
	printf("pilhaDeLivros tamanho: %d\n", pilhaDeLivros->tamanho);
	printf("pilhaDeLivros maximo: %d\n", pilhaDeLivros->maximo);

	return pilhaDeLivros->maximo > pilhaDeLivros->tamanho;
}

void empilhaNaPrateleira(Prateleira* prateleira, Livro* livro){
	int i;
	printf("empilhando na prateleira....\n");
	printf("inicio: qtdd de livros da prateleira: %d\n", prateleira->qtddDeLivros);
	printf("numColunas da prateleira: %d\n", prateleira->numColunas);
	
	for(i=0; i < prateleira->numColunas; i++){
		if(cabeMaisUmLivroNaPilha(prateleira->pilhaDeLivros[i])){
			printf("ta cabendo na prateleira %d\n", i);
			empilha(prateleira->pilhaDeLivros[i], livro);
			prateleira->qtddDeLivros++;
			return;
		}
	}

	printf("no fim dos empilhamentos: qtdd de livros da prateleira: %d\n", prateleira->qtddDeLivros);
}

int cabeNaPrateleira(Prateleira* prateleira, int numLivrosNovos){
	printf("max livros prateleira: %d\n", prateleira->maxLivros);
	printf("qtdd livros prateleira: %d \n", prateleira->qtddDeLivros);
	return prateleira->maxLivros >= prateleira->qtddDeLivros + numLivrosNovos;
}

void adicionaLivros(Estante* estante, int prat, int qtdLivros, char** nomes){
	int i;

	//empilha na pilha auxiliar
	for (i = 0; i < qtdLivros; ++i){
		Livro* novoLivro = criaLivro(nomes[i]);
		empilha(estante->pilhaAux, novoLivro);
	}

	printf("pilha aux....\n");
	imprimePilha(estante->pilhaAux);

	if(!cabeNaPrateleira(estante->prateleiras[prat], qtdLivros)){
		printf("Adicionando livros. Não cabe na prateleiraaaaaaa\n");
		return;
	}

	//vai empilhando na prateleira, preenchendo as colunas da esq pra direita
	for (i = 0; i < qtdLivros; ++i){
		printf("Entrando no for %d\n",i);
		Livro* livroDesemp = desempilha(estante->pilhaAux);
		printf("livro desempilhado: %s\n", livroDesemp->nome);
		empilhaNaPrateleira(estante->prateleiras[prat], livroDesemp);
	}

}

int transformaNumeroDaPrateleira(int prat, int numTotalDePrateleirasNaEstante){
	printf("numTotalDePrateleirasNaEstante: %d\n", numTotalDePrateleirasNaEstante);
	printf("prat: %d\n", prat);

	return numTotalDePrateleirasNaEstante - prat - 1;
}

void moveLivrosDasPilhas(Pilha* origem, Pilha* destino, int qtosLivros){
	printf("move livros das pilhas....");

	int i;
	for (i = 0; i < qtosLivros; ++i){
		Livro* desemp = desempilha(origem);
		empilha(destino, desemp);
	}
}

//Remove da pilha o elemento da linha l
//sendo 0 o livro mais baixo
void removeLivroDaPilha(Pilha* pilha, int l, Pilha* pilhaAux){
	int i;
	int numLivrosColocadosNaAux = 0;

	for (i = pilha->tamanho - 1; i >= 0 ; i--)
	{
		if(i == l){

			Livro* livroPraRetirar = desempilha(pilha);
			free(livroPraRetirar);

			moveLivrosDasPilhas(pilhaAux, pilha, numLivrosColocadosNaAux);

			printf("depois de remover:::::::\n");
			printf("pilha:\n");
			imprimePilha(pilha);
			printf("\n");
			printf("pilha aux:\n");
			imprimePilha(pilhaAux);

			return;
		}else{
			//se não for o indice q buscamos
			Livro* desempilhado = desempilha(pilha);
			empilha(pilhaAux, desempilhado);
			numLivrosColocadosNaAux++;
		}
	}
}

void preparaParaMudarPrecos(Estante* estante){
	int pratOrigem, colOrigem, pratDest, colDest;

	scanf("%d", &pratOrigem);
	scanf("%d", &colOrigem);
	scanf("%d", &pratDest);
	scanf("%d", &colDest);

	pratDest = transformaNumeroDaPrateleira(pratDest, estante->numPrateleiras);
	pratOrigem = transformaNumeroDaPrateleira(pratOrigem, estante->numPrateleiras);

	//IMPORTANTEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
	//verificar se é possivel realizar essa operacao
	//ou seja, se na pilha de destino cabem os livros da pilha de origem
	Pilha* origem = estante->prateleiras[pratOrigem]->pilhaDeLivros[colOrigem];
	Pilha* destino = estante->prateleiras[pratDest]->pilhaDeLivros[colDest];

	moveLivrosDasPilhas(origem, destino, origem->tamanho);
}

void preparaParaRemoverLivros(Estante* estante){
	int p, c, l;

	printf("params: prat, coluna, linha da pilha\n");
	scanf("%d", &p);
	scanf("%d", &c);
	scanf("%d", &l);

	p = transformaNumeroDaPrateleira(p, estante->numPrateleiras);

	//validar se o numero da prateleira, coluna e linha são validos
	//IMPORTANTEEEEEEEEEEEEEEEEEEEEEEEEEEEEE

	removeLivroDaPilha(estante->prateleiras[p]->pilhaDeLivros[c], l, estante->pilhaAux);
}

void preparaParaAdicionarLivros(Estante* estante){
	printf("Preparando para adicionar livrosssss....\n");
	printf("params: prat, qtdLivros, os nomes dos livros \n");

	int prat, qtdLivros;
	char** nomes;

	scanf("%d", &prat);
	scanf("%d", &qtdLivros);

	printf("prat antes: %d\n", prat);
	prat = transformaNumeroDaPrateleira(prat, estante->numPrateleiras);
	printf("novo prat: %d\n", prat);

	nomes = malloc(qtdLivros*sizeof(char*));

	int i;
	for (i = 0; i < qtdLivros; i++){
		//printf("preparado para ler %dº nome\n", i);

		char* nome = malloc(sizeof(char*));
		scanf("%s", nome);
		//printf("nome lido: %s\n", nome);

		nomes[i] = nome;
		//printf("nome[%d]: %s\n", i, nomes[i]);
	}

	adicionaLivros(estante, prat, qtdLivros, nomes);
}

void preparaParaImprimirPrateleira(Estante* estante){
	printf("imprimindo prateleira......\n");

	int numPrat, numPratDigitado;

	scanf("%d", &numPratDigitado);

	numPrat = transformaNumeroDaPrateleira(numPratDigitado, estante->numPrateleiras);	

	printaPrateleira(estante->prateleiras[numPrat], numPratDigitado);
}



int main(){
	//testes();
	int opcao = 0;
	printf("Usar estante default: 1. Criar a sua 2.\n");

	scanf("%d", &opcao);

	int op = 0;
	Estante* estante;

	if(opcao == 2){
	
	int p, c, l;

	printf("começando... params: numPrateleiras, numColunas, maximo de Livros por pilha na pos [linha][coluna]\n");
	scanf("%d", &p);
	scanf("%d", &c);
	scanf("%d", &l);

	estante = malloc(sizeof(Estante*));
	inicializaEstante(estante, p, c, l);

	printf("digite os precos associados a cada prateleira - numPrateleiras: %d\n", p);
	int i, precoLido;
	for (i = p-1; i >= 0; i--)
	{
		scanf("%d", &precoLido);
		associaPreco(estante->prateleiras[i], precoLido);
	}

	} // fim da opcao 2

	else{
		estante = malloc(sizeof(Estante*));
		inicializaEstante(estante, 2, 3, 3);

		associaPreco(estante->prateleiras[0], 15);
		associaPreco(estante->prateleiras[1], 35);

		printf("sua estante tem: \n");
		printf("2 prateleiras de 3 colunas\n");
		printf("cada pilha tem max de 3 livros\n");

		printf("preco das prateleiras: 15, 35\n");
	}
		
	printf("escolha a operacao...\n");
	printf("1 para adicionar\n");
	printf("2 para remover\n");
	printf("3 para mudar de prateleiras/colunas\n");
	printf("7 + numPrateleira para printar prateleira\n");
	printf("\n");

	while(scanf("%d", &op) != EOF){
		switch(op){
			case 1: preparaParaAdicionarLivros(estante);
					op = 0;
					break;
			case 2: preparaParaRemoverLivros(estante);
					op=0;
					break;
			case 3: preparaParaMudarPrecos(estante);
					op = 0;
					break;
			case 7: preparaParaImprimirPrateleira(estante);
					op = 0;
					break;
		}
	}

}