#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "funcoes.h"

#define INF 1000000

/* Cria matriz [ l ] [ c ] vazia */
int **MATRIZint(int l, int c){
    int i, j;
    int ** m = (int **) malloc(l * sizeof(int *));
    for (i = 0; i < l; i++)
        m[i] = (int *) malloc(c * sizeof(int));
    for (i = 0; i < l; i++)
        for (j = 0; j < c; j++)
            m[i][j] = 0;
    return m;
}

/* Cria vetor [ n ] vazio */
int *VETORint(int n){
    int i;
    int *v = (int *) malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        v[i] = 0;
    return v;
}

/* Cria um grafo vazio de n vertices */
Grafo GRAFOcria(int n){
    Grafo G = (Grafo) malloc(sizeof(Grafo));
    G->n = n;
    G->m = 0;
    G->adj = MATRIZint(n,n);

    return G;
}

/* Funcao para inserir um arco em um grafo com peso */
void GRAFOinsereA(Grafo G, Arco e, int peso){
    int v = e.v;
    int w = e.w;
    if (G->adj[v][w] == 0) {
        G->m++;
        G->adj[v][w] = peso;
    }
}

/* Funcao para remover um arco de um grafo */
void GRAFOremoveA(Grafo G, Arco e){
    int v = e.v;
    int w = e.w;
    if (G->adj[v][w] > 0) {
        G->m--;
        G->adj[v][w] = 0;
    }
}

/* Funcao para imprimir um grafo */
void GRAFOimprime(Grafo G) {
    int v, w;

    if (G != NULL){
    	printf("%d vertices, %d arestas\n", G->n, G->m);
    	for (v = 0; v < G->n; v++) {
            for (w = 0; w < G->n; w++){
            	printf( " %2d", G->adj[v][w]);
            }
            printf( "\n");
    	}
    }
    else{
	printf("%p\n", G);
    }
}

/* Funcao para destruir um grafo */
void GRAFOdestroi(Grafo G){
    int i;
    for (i = 0; i < G->n; i++) {
        free(G->adj[i]);
    }
    free(G->adj);
    free(G->peso);
    free(G);

}

Grafo GRAFOleitura(const char *nomearq){
    int n,m,t,peso,r,i,flag,x,y;
    Arco a;
    FILE *arquivo;
    arquivo = fopen(nomearq,"r");

    if (!arquivo) {
        printf("O Arquivo %s nao pode ser aberto.\n", nomearq);
        getchar();
        exit(1);
    }

    r = fscanf(arquivo, "%d %d", &n, &m);
    Grafo G = GRAFOcria(n);
		G->peso = (int *) malloc(n * sizeof(int));

		r = fscanf(arquivo, "%d", &flag);

		for(i=0; i < n ; i++){
			r = fscanf(arquivo, "%d %d %d", &x, &y, &G->peso[i]);
		}
		r = fscanf(arquivo, "%d", &flag);
		for(i=0; i < m ; i++){
			r = fscanf(arquivo, "%d %d %d", &a.v, &a.w, &peso);
			GRAFOinsereA(G, a, peso);
		}
    fclose(arquivo);
    return G;
}


int cont;
int *ordem, *pai, *menor;


// Profundidade
void BPrec(Grafo G){
    int i;
    ordem = VETORint(G->n);
    cont = 0;

    printf("Ordem BP: ");

    for (i = 0; i < G->n; i++)
        ordem[i] = -1;

    for (i = 0; i < G->n; i++){
        if (ordem[i] == -1){
            visitaBP(G,i);
        }
    }

    printf("\n");
    free(ordem);
}

void visitaBP(Grafo G, int v){
    int j;
    ordem[v] = cont++;
    printf("%d ", v);

    for (j = 0; j < G->n; j++){
        if (G->adj[v][j] != 0 && ordem[j] == -1){
            visitaBP(G,j);
        }
    }
}


Grafo Kruskal(Grafo G,int *custo){
    int min, k, l, x, y;
    int *comp = malloc(G->n * sizeof(int));
    Grafo AGM = GRAFOcria(G->n);
    int i,j;
    Arco a;

    // TO DO
    *custo=0;
    k = -1;
    l = -1;
    x = -1;
    y = -1;

    for(i=0; i< G->n; i++){
      comp[i] = i;
    }

    while (1){
      min = INF;
      for(i=0;i < G->n ; i++){
        for(j=0; j < G->n; j++){
          if(G->adj[i][j] != 0){
            if((comp[i] != comp[j]) && (min > G->adj[i][j])){
              min = G->adj[i][j];
              k = i;
              l = j;
            }
          }
        }
      }
      if(min == INF){
        break;
      }
      a.v = k;
      a.w = l;
      GRAFOinsereA(AGM,a,G->adj[k][l]);
      *custo+= G->adj[k][l];

      x = comp[k];
      y = comp[l];
      for(i=0; i < G->n; i++){
        if(comp[i] == y){
          comp[i] = x;
        }
      }
    }
    // imprime arvore
    //GRAFOimprime(AGM);
    printf("** Custo AGM: %d\n", *custo);
    return(AGM);
}

Grafo Heuristica(Grafo AGM, Grafo G,int *custo){
  int i,j;

  for(i=0; i < AGM->n; i++){
    for(j=0; j < AGM->n; j++){
      if(AGM->adj[i][j]!=0){
        *custo += AGM->peso[i];
        *custo += AGM->peso[j];
      }
    }
  }
  printf("** Custo Heuristica: %d\n", *custo);
  return(AGM);
}
