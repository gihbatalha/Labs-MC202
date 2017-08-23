//Giovanna Batalha 197960
//Objetivos: O programa a seguir realiza o gerenciamento de produtos(de ID único) separados por setores de um galpão.

//Entrada: Possuirá diversas linhas, da seguinte maneira:
//linha 1 : Número de setores do galpão, quantidade máxima de produtos diferentes em um setor
//próximas linhas: Representam o produto que será incluso, passando-se as seguintes informações:
//ID setor, ID produto, quantidade de itens desse produto no estoque

//Saída: N linhas, sendo N o número de setores do galpão, com as seguintes informações:
//Número do setor, número de produtos distintos no setor, Quantidade média de itens em estoque com duas casas decimais
//Última linha: Informa se existem ou não produtos iguais cadastrados em setores distintos (SIM/NAO)

//Devo saber:
// - numero de produtos distintos em cada setor
// - numero de itens no estoque
// - Adição: verificar se o produto ja existe em outros estoques


//funções
// - adiciona
// - busca produto nos estoques

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int id;
    int qtddProdutos;
    int estoque;
    int *produtosIds;
}Setor;

int inicializaSetores(Setor** setores, int qtddSetores){
	printf("%d\n", qtddSetores);
	setores = malloc(qtddSetores*sizeof(Setor*));

	if(setores == NULL)
		return 0;

	int i;
	for(i=0; i < qtddSetores; i++){
		Setor *novoSetor = malloc(1*sizeof(Setor));
		novoSetor->id = i;
		novoSetor->qtddProdutos = 0;
		novoSetor->estoque = 0;

		printf("Novo setor...\n");
		printf("%d\n",novoSetor->id);
		printf("%d\n",novoSetor->qtddProdutos);
		printf("%d\n",novoSetor->estoque);
		// novoSetor->produtosIds = malloc(1*sizeof(int));

		if(novoSetor == NULL)
			return 0;

		setores[i] = novoSetor;
	}

	return 1;
}

int main(){
	int qtddSetores = 0; //Quantidade de setores no galpão
    int maxProdsPorSetor = 0; //Quantidade máxima de produtos diferentes por setor
    Setor **setores;

    scanf("%d", &qtddSetores);
    scanf("%d", &maxProdsPorSetor);

    if(qtddSetores > 1000 || maxProdsPorSetor > 1000){
        return 0;
    }

   inicializaSetores(setores, qtddSetores);

   int i;
   printf("%d\n",qtddSetores);
   for (i = 0; i < qtddSetores; ++i)
   {
   		if(setores[i] != NULL)
  		printf("NAO EH NULO %d, id: %d\n", i, setores[i]->id);
  		else
  			printf("eh nulo %d\n",i);
   }
}