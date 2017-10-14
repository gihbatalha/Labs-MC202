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

void trocaConteudoDasPilhas(Pilha* primeira, Pilha* segunda, Pilha* pilhaAux){
	//prilhas iguais
	if(primeira == segunda){
		return;
	}

	int i;
	int tamanhoPilhaUm, tamanhoPilhaDois;

	tamanhoPilhaUm = primeira->tamanho;
	tamanhoPilhaDois = segunda->tamanho;

	// printf("TROCA CONTEUDO DAS PILHAS. PILHAS RECEBIDAS:::::\n");
	// printf("Origem: ");
	// imprimePilha(primeira);

	// printf("Destino: ");
	// imprimePilha(segunda);

	// printf("Auxiliar:");
	// imprimePilha(pilhaAux);
	// printf("\n");

	moveLivrosDasPilhas(primeira, pilhaAux, primeira->tamanho); //move os livros da primeira para aux
	moveLivrosDasPilhas(segunda, pilhaAux, segunda->tamanho); //move os livros da segunda para aux

	// printf("MOVEU OS LIVROS DA ORIGEM PARA AUX E DEPOIS OS DO DESTINO PARA AUX::::::\n");
	// printf("Origem: ");
	// imprimePilha(primeira);

	// printf("Destino: ");
	// imprimePilha(segunda);

	// printf("Auxiliar:");
	// imprimePilha(pilhaAux);
	// printf("\n");

	moveLivrosDasPilhas(pilhaAux, primeira, tamanhoPilhaDois); //move os primeiros livros da aux, que são os que estavam na segunda pilha, para a primeira pilha.
	moveLivrosDasPilhas(pilhaAux, segunda, tamanhoPilhaUm); // move os livros da aux que restaram, que são os que estavam na primeira pilha, para a segunda pilha.

	// printf("MOVEU OS LIVROS DA AUX PARA A ORIGEM E DEPOIS PARA A DESTINO. RESULTADO FINAL:::::\n");
	// printf("Origem: ");
	// imprimePilha(primeira);

	// printf("Destino: ");
	// imprimePilha(segunda);

	// printf("Auxiliar:");
	// imprimePilha(pilhaAux);
	// printf("\n");
}

//Inicialmente, em cada coluna temos uma pilha. Iremos guardar essas posições, ou seja, chamaremos a pilha que começou na coluna 0
//de pilha 0 e assim por diante. 
//Por exemplo, ao lermos uma configuração para colocar a pilha 1 na coluna 0 e pilha 0 na coluna 5:
//Ao colocarmos a pilha 1 na coluna 0, teremos consciencia que ao querer trocar a pilha 0 para a coluna 5 não devemos mais pegar
// a pilha da coluna 0 pois ela já foi alterada e possui agora a pilha 1.

//Para resolver esse problema utilizaremos um vetor auxiliar chamado posicoesDasPilhas, onde os indices serão as colunas da 
//prateleira e os valores serão as pilhas correspondentes.
//Desse modo, ele começará com o índice igual ao valor, já que "chamaremos" de pilha 0 aquela que começou na coluna 0.
//Isso será utilizado ao trocar a configuração:
//No exemplo anterior, ao colocar a pilha 0 na coluna 5, iremos percorrer o vetor auxiliar e perceber que a pilha 0 não está mais
//na coluna 0 e sim na coluna 1. Dessa maneira, mantemos a configuração já feita da pilha 1 para a coluna 0, e conseguimos saber
//a pilha que devemos colocar na coluna 5.

void preparaParaReorganizarPrateleira(Estante* estante){
	int p, pTransf, conf;
	int* posicoesDasPilhas;

	scanf("%d", &p);

	pTransf = transformaNumeroDaPrateleira(p, estante->numPrateleiras);
	Prateleira* prat = estante->prateleiras[pTransf];

	posicoesDasPilhas = malloc(prat->numColunas * sizeof(int));

	//O vetor posicoesDasPilhas começa com os valores iguais os dos índices
	int i;
	for(i = 0; i < prat->numColunas; i++){
		posicoesDasPilhas[i] = i;
	}

	//Vamos ler os valores das novas configurações e realizar as trocas
	for(i = 0; i < prat->numColunas; i++){
		//printf("oi %d\n",i );
		//scanf("%d", &conf);
		//printf("lida %dª conf: %d\n", i, conf);

		//Queremos colocar a pilha <conf> na coluna i
		//Para isso procuraremos em que coluna (pos) atual a pilha <conf> se encontra e trocaremos as pilhas das coluna pos e i.
		int k;
		int pos = -1;

		for(k = 0; k < prat->numColunas && pos == -1; k++){
			//printf("olaa: k: %d\n", k);

			//guardo no pos a coluna que está a pilha <conf>
			if(posicoesDasPilhas[k] == conf){
				//printf("entrou no if\n");
				pos = k;
			}
		}

		//printf("saiu do for...... do k\n");
		//printf("pos: %d\n",pos);
		//printf("i: %d\n", i);

		//atualizo o vetor posicoesDasPilhas:
		if(pos != i){
			int aux = posicoesDasPilhas[pos];
			posicoesDasPilhas[pos] = posicoesDasPilhas[i];
			posicoesDasPilhas[i] = aux;
		}		

		trocaConteudoDasPilhas(prat->pilhaDeLivros[pos], prat->pilhaDeLivros[i], estante->pilhaAux);		
	}

	printf("A reorganização​ da prateleira​ %d foi feita com sucesso\n", p);
}

int main(){

	//int opcao = 0;
	//printf("Usar estante default: 1. Criar a sua 2.\n");

	//scanf("%d", &opcao);

	int op = 0;
	Estante* estante;

	//if(opcao == 2){
	
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

	//} // fim da opcao 2

	// else{
	// 	estante = malloc(sizeof(Estante*));
	// 	inicializaEstante(estante, 1, 5, 3);

	// 	associaPreco(estante->prateleiras[0], 15);
	// }
		
	// printf("escolha a operacao...\n");
	// printf("1 para adicionar\n");
	// printf("2 para remover\n");
	// printf("3 para mudar de prateleiras/colunas\n");
	// printf("4 para alterar a confirguracao das colunas da prateleira\n");
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
}

void testeTrocaConteudoDasPilhas(){
	Estante* estante = malloc(sizeof(Estante*));
	inicializaEstante(estante, 5, 4, 3);

	empilha(estante->prateleiras[0]->pilhaDeLivros[0], criaLivro("Livro1-pilha 0"));
	empilha(estante->prateleiras[0]->pilhaDeLivros[0], criaLivro("Livro2-pilha 0"));

	empilha(estante->prateleiras[0]->pilhaDeLivros[1], criaLivro("Livro3-pilha 1"));
	empilha(estante->prateleiras[0]->pilhaDeLivros[1], criaLivro("Livro4-pilha 1"));

	trocaConteudoDasPilhas(estante->prateleiras[0]->pilhaDeLivros[0],estante->prateleiras[0]->pilhaDeLivros[1], estante->pilhaAux);
}