#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <getopt.h>
#include "entrada.h"
#include "funcoes.h"

int main (int argc, char **argv){
	char *arquivoEntrada;
	int opcao,flagEntrada=0,custo;
	Grafo G = NULL;
	Grafo AGM = NULL;
	Grafo Gmod = NULL;

	/* ------------------Primitiva GetOpt------------------  */
	while ((opcao = getopt( argc, argv, "i:" )) != -1) {
		switch (opcao){
			case 'i':
				arquivoEntrada = optarg;
				flagEntrada = 1;
				break;
			default:
				printf("\nErro - Uso de parâmetro incorreto. \n");
				printf("\n");
				printf("Utilize -i para indicar o arquivo de entrada. \n");
				printf("Por exemplo:   ./tp -i entrada.txt\n\n");
		}
	}
	/* Obriga o usuário a passar os arquivos na execução do programa */
	if (flagEntrada !=1){
		printf("\nErro. Arquivo não setado.\n");
		printf("\n");
		printf("Utilize -i para indicar o arquivo de entrada. \n");
		printf("Por exemplo:   ./tp1 -i entrada.txt\n\n");
		return 0;
	}else{
		G = GRAFOleitura(arquivoEntrada);
		AGM = Kruskal(G,&custo);
		Gmod = Heuristica(AGM,G,&custo);
	}
}
