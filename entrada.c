#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "entrada.h"
#include "funcoes.h"



int leArquivo(char *arquivoEntrada){
	FILE *entrada;
	int num,i;

	entrada = fopen (arquivoEntrada, "r");
  if (entrada == NULL){ //verificando a existencia do arquivo
		printf ("Arquivo de entrada nao existe. \n");
		return -1;
  }
	
	while ((fscanf(entrada,"%d",&num))!= EOF){
		totalCartas=num*2;
		valores = (long int*)(malloc(totalCartas * sizeof( long int)));
		for (i=0;i<totalCartas;i++){
			fscanf(entrada,"%li",&valores[i]);
		}
		resposta=Soluciona(valores,totalCartas);
		fprintf(saida,"%ld\n",resposta);
		Tempo();
	}
	fclose(entrada);
	fclose(saida);
  return 1;
}
