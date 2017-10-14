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

Livro* criaLivro(char* nome){
	Livro* meuLivro = malloc(sizeof(Livro*));
	meuLivro->nome = nome;

	return meuLivro;
}

Pilha* criaPilha(int numMaxLivros){
	Pilha* retorno = malloc(sizeof(Pilha*));

	retorno->tamanho = 0;
	retorno->maximo = numMaxLivros;
	retorno->topo = NULL;

	return retorno;
}

void inicializaPilha(Pilha* pilha){
	if(pilha == NULL){
		printf("Pilha nula\n");
		return;
	}

	pilha->topo = NULL;
	pilha->maximo = 0;
	pilha->tamanho = 0;
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

int transformaNumeroDaPrateleira(int prat, int numTotalDePrateleirasNaEstante){
	return numTotalDePrateleirasNaEstante - prat - 1;
}

void printaLivro(Livro* livro, int topo){

	if(topo){
		printf("[%s -- topo]",  livro->nome);
	}else{
		printf("[%s]",  livro->nome);
	}
	
}

void imprimePilha(Pilha* pilha){
	No* atual = pilha->topo;

	while(atual != NULL){
		printf(" ");
		//if(atual == pilha->topo){
			//printaLivro(atual->livro, 1);
		//}else{
			printaLivro(atual->livro, 0);
		//}

		atual = atual->prox;

	}

	//printf("|tamanho: %d",pilha->tamanho);
	//printf("|maximo: %d", pilha->maximo);
}

void imprimePrateleira(Prateleira* prateleira, int index){
	int i;

	printf("[LIVROS DA PRATELEIRA %d]\n", index);
	//printf("[LIVROS DA PRATELEIRA %d](R$%d)\n", index, prateleira->preco);
	//printf("numColunas: %d\n", prateleira->numColunas);
	//printf("qtddDeLivros: %d\n", prateleira->qtddDeLivros);
	//printf("maximo: %d\n", prateleira->maxLivros);

	for(i=0; i < prateleira->numColunas; i++){
		printf("Coluna %d:", i);
		imprimePilha(prateleira->pilhaDeLivros[i]);
		printf("\n");
	}
}

void imprimeEstante(Estante* estante){
	printf("[ESTANTE]\n");
	printf("Número de prateleiras: %d \n", estante->numPrateleiras);

	int i, prat;
	for (i = estante->numPrateleiras - 1; i >= 0; i--){
		prat = transformaNumeroDaPrateleira(i, estante->numPrateleiras);
		
		imprimePrateleira(estante->prateleiras[prat], i);
	}

	printf("[PILHA AUX]\n");
	imprimePilha(estante->pilhaAux);
}

//Métodos básico empilha e desempilha
void empilha(Pilha* pilha, Livro* livro){
	// printf("Empilhando ");
	// printaLivro(livro);
	// printf("\n");

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
	//printf("desempilha.....\n");
	No* noTopo = pilha->topo;

	pilha->topo = pilha->topo->prox;

	pilha->tamanho = pilha->tamanho - 1;

	return noTopo->livro;
}

void associaPreco(Prateleira* prateleira, int preco){
	prateleira->preco = preco;
}

int cabeMaisUmLivroNaPilha(Pilha* pilhaDeLivros){
	//printf("pilhaDeLivros tamanho: %d\n", pilhaDeLivros->tamanho);
	//printf("pilhaDeLivros maximo: %d\n", pilhaDeLivros->maximo);

	return pilhaDeLivros->maximo > pilhaDeLivros->tamanho;
}

int cabeNaPilhaLivros(Pilha* pilhaDeLivros, int qtosLivros){
	return pilhaDeLivros->maximo >= pilhaDeLivros->tamanho + qtosLivros;
}

int cabeNaPrateleira(Prateleira* prateleira, int numLivrosNovos){
	//printf("max livros prateleira: %d\n", prateleira->maxLivros);
	//printf("qtdd livros prateleira: %d \n", prateleira->qtddDeLivros);
	return prateleira->maxLivros >= prateleira->qtddDeLivros + numLivrosNovos;
}

int prateleiraValida(Estante* estante, int prat){
	return prat >= 0 && prat < estante->numPrateleiras; 
}

int colunaDaPrateleiraValida(Prateleira* prateleira, int coluna){
	return coluna >= 0 && coluna < prateleira->numColunas;
}

int linhaDaPilhaValida(Pilha* pilha, int linha){
	return linha >= 0 && linha < pilha->tamanho;
}

void empilhaNaPrateleira(Prateleira* prateleira, Livro* livro){
	int i;
	
	for(i=0; i < prateleira->numColunas; i++){
		if(cabeMaisUmLivroNaPilha(prateleira->pilhaDeLivros[i])){
			empilha(prateleira->pilhaDeLivros[i], livro);
			prateleira->qtddDeLivros++;
			return;
		}
	}

	//printf("no fim dos empilhamentos: qtdd de livros da prateleira: %d\n", prateleira->qtddDeLivros);
}

void adicionaLivros(Estante* estante, int prat, int qtdLivros, char** nomes){
	int i;

	//empilha na pilha auxiliar
	for (i = 0; i < qtdLivros; ++i){
		Livro* novoLivro = criaLivro(nomes[i]);
		empilha(estante->pilhaAux, novoLivro);
	}

	if(!cabeNaPrateleira(estante->prateleiras[prat], qtdLivros)){
		printf("Espaco​ insuficiente​ na prateleira de custo​ $%d. Favor remover os livros do compartimento​ auxiliar\n", estante->prateleiras[prat]->preco);
		return;
	}

	//vai empilhando na prateleira, preenchendo as colunas da esq pra direita
	for (i = 0; i < qtdLivros; ++i){
		Livro* livroDesemp = desempilha(estante->pilhaAux);
		empilhaNaPrateleira(estante->prateleiras[prat], livroDesemp);
	}

	printf("Foram inseridos com sucesso %d livros na prateleira de custo $%d\n",qtdLivros, estante->prateleiras[prat]->preco);

}

void moveLivrosDasPilhas(Pilha* origem, Pilha* destino, int qtosLivros){
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
			return;
		}else{
			//se não for o indice q buscamos
			Livro* desempilhado = desempilha(pilha);
			empilha(pilhaAux, desempilhado);
			numLivrosColocadosNaAux++;
		}
	}
}

int calculaMontantePrateleira(Prateleira* prateleira){
	return prateleira->preco * prateleira->qtddDeLivros;
}

//retorna um vetor de valores
//no indice i coloca o montante da prateleira i
//o montante final fica no indice numPrateleiras
int* calculaMontanteEstante(Estante* estante){
	int i, montante, prat;
	int* retorno = malloc((estante->numPrateleiras+1)*sizeof(int));

	montante = 0;

	for (i = estante->numPrateleiras -1; i >= 0 ; i--){
		int montPrat = calculaMontantePrateleira(estante->prateleiras[i]);
		prat = transformaNumeroDaPrateleira(i, estante->numPrateleiras);

		// Colocamos no vetor[prat] o montante da prat
		retorno[prat] = montPrat;
		montante += montPrat;
	}

	retorno[estante->numPrateleiras] = montante;
	return retorno;
}

void preparaParaPrintarPrateleira(Estante* estante){
	int prat, pratTransf;

	scanf("%d", &prat);

	pratTransf = transformaNumeroDaPrateleira(prat, estante->numPrateleiras);

	imprimePrateleira(estante->prateleiras[pratTransf], prat);
}

void preparaParaMudarPrecos(Estante* estante){
	int pratOrigem, colOrigem, pratDest, colDest, pratDestDigitado;

	scanf("%d", &pratOrigem);
	scanf("%d", &colOrigem);
	scanf("%d", &pratDest);
	scanf("%d", &colDest);

	pratDestDigitado = pratDest;

	pratDest = transformaNumeroDaPrateleira(pratDest, estante->numPrateleiras);
	pratOrigem = transformaNumeroDaPrateleira(pratOrigem, estante->numPrateleiras);

	int precoOrigem = estante->prateleiras[pratOrigem]->preco;
	int precoDestino = estante->prateleiras[pratDest]->preco;

	Pilha* origem = estante->prateleiras[pratOrigem]->pilhaDeLivros[colOrigem];
	Pilha* destino = estante->prateleiras[pratDest]->pilhaDeLivros[colDest];

	//Verificando se na pilha de destino cabem os livros da pilha de origem
	if(!cabeNaPilhaLivros(destino, origem->tamanho)){
		printf("Espaco insuficiente na prateleira %d e coluna %d\n", pratDestDigitado, colDest);
		return;
	}

	moveLivrosDasPilhas(origem, destino, origem->tamanho);

	printf("A mudança de livros : [%d, $%d] ==> [%d, $%d] foi feita com sucesso\n", colOrigem, precoOrigem, colDest, precoDestino);
}

void preparaParaRemoverLivros(Estante* estante){
	int p, c, l;

	scanf("%d", &p);
	scanf("%d", &c);
	scanf("%d", &l);

	p = transformaNumeroDaPrateleira(p, estante->numPrateleiras);

	//Validando se a posição é válida
	if(!prateleiraValida(estante, p)){
		printf("Nao existe nenhum livro na posicao desejada\n");
		return;
	}

	if(!colunaDaPrateleiraValida(estante->prateleiras[p], c)){
		printf("Nao existe nenhum livro na posicao desejada\n");
		return;
	}

	if(!linhaDaPilhaValida(estante->prateleiras[p]->pilhaDeLivros[c],l)){
		printf("Nao existe nenhum livro na posicao desejada\n");
		return;
	}

	removeLivroDaPilha(estante->prateleiras[p]->pilhaDeLivros[c], l, estante->pilhaAux);
}

void preparaParaAdicionarLivros(Estante* estante){
	int prat, qtdLivros;
	char** nomes;

	scanf("%d", &prat);
	scanf("%d", &qtdLivros);

	prat = transformaNumeroDaPrateleira(prat, estante->numPrateleiras);

	nomes = malloc(qtdLivros*sizeof(char*));

	int i;
	for (i = 0; i < qtdLivros; i++){
		char* nome = malloc(sizeof(char*));
		scanf("%s", nome);
		nomes[i] = nome;
	}

	adicionaLivros(estante, prat, qtdLivros, nomes);
}

void preparaParaExibirMontante(Estante* estante){
	int* montante = calculaMontanteEstante(estante);

	printf("[VALOR TOTAL DA ESTANTE $%d] dos quais:\n", montante[estante->numPrateleiras]);

	int i;
	for (i = 0; i < estante->numPrateleiras ; i++){
		printf("Prateleira %d: $%d\n", i, montante[i]);
	}
}

/*

Reorganiza​ ​ a ​ ​ disposição​ ​ das​ ​ pilhas​ ​ de
livros​ ​ de​ ​ uma​ ​ prateleira​ ​ prat
especificada.​ ​ configuracao​ ​ é ​ ​ um​ ​ vetor
de​ ​ inteiro​ ​ que​ ​ possui​ ​ valores​ ​ distintos
de​ ​ 0 ​ ​ a ​ ​ c-1​ .

Se​ ​ configuracao[i]​ ​ = ​ ​ x ​ , ​ ​ isso​ ​ indica​ ​ que
na​ ​ nova​ ​ configuração​ ​ a ​ ​ pilha​ ​ que​ ​ antes
estava​ ​ na​ ​ coluna​ ​ x ​ ​ agora​ ​ deve​ ​ ser
colocada​ ​ na​ ​ coluna​ ​ i ​ .

Obs1.:​ ​ Note​ ​ que​ ​ implementar​ ​ uma
função​ ​ que​ ​ efetue​ ​ a ​ ​ troca​ ​ entre​ ​ duas
pilhas,​ ​ utilizando​ ​ uma​ ​ pilha​ ​ auxiliar,
pode​ ​ facilitar​ ​ essa​ ​ operação.
Obs2.:​ ​ Lembre-se​ ​ que​ ​ ao​ ​ começar​ ​ a
efetuar​ ​ as​ ​ trocas,​ ​ você​ ​ está​ ​ alterando​ ​ a
configuração​ ​ original!


config

vetor   0 1 2 3 4 5 6 7    pilha/coluna destino
valores 7                  pilha/coluna origem

*/
void preparaParaReorganizarPrateleira(Estante* estante){
	int p, pTransf, conf;
	int* configuracao;

	scanf("%d", p);

	pTransf = transformaNumeroDaPrateleira(p, estante->numPrateleiras);
	Prateleira* prat = estante->prateleiras[pTransf];

	configuracao = malloc(prat->numColunas * sizeof(int));

	int i;
	for(i = 0; i < prat->numColunas; i++){
		scanf("%d", conf);
		configuracao[i] = conf;
	}

	//Temos o vetor ok e o numero da prat... Desenvolver a lógicaaaa

	
	printf("A reorganização​ da prateleira​ %d foi feita com sucesso\n", p);
}

int main(){
	int opcao = 0;
	printf("Usar estante default: 1. Criar a sua 2.\n");

	scanf("%d", &opcao);

	int op = 0;
	Estante* estante;

	if(opcao == 2){
	
		int p, c, l;

		scanf("%d", &p);
		scanf("%d", &c);
		scanf("%d", &l);

		estante = malloc(sizeof(Estante*));
		inicializaEstante(estante, p, c, l);

		//Lendo os preços associados a cada prateleira
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
		
	// printf("escolha a operacao...\n");
	// printf("1 para adicionar\n");
	// printf("2 para remover\n");
	// printf("3 para mudar de prateleiras/colunas\n");

	// printf("5 para calcular o montante\n");
	// printf("6 para exibir os livros da prateleira\n");

	// printf("7 para imprimir a estante\n");
	// printf("\n");

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
			case 4: preparaParaReorganizarPrateleira(estante);
					op = 0;
					break;
			case 5: preparaParaExibirMontante(estante);
					op = 0;
					break;
			case 6: preparaParaPrintarPrateleira(estante);
					op = 0;
					break;
			case 7: imprimeEstante(estante);
					op = 0;
					break;
		}
	}

}


//Testes
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