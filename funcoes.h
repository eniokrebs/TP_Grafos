#ifndef FUNCOES_H
#define FUNCOES_H

#include <sys/time.h>
#include <sys/resource.h>


/* Struct Arco */
typedef struct{
    int v;
    int w;
} Arco;

/* Struct Aresta */
typedef struct{
    int v;
    int w;
} Aresta;

typedef struct{
  int peso;
} Vertice;

/* Struct Grafo representado por matriz */
struct grafo{
    int n;
    int m;
    int *peso;
    int **adj;
};

/* Um Grafo é um ponteiro para um grafo, ou seja, Grafo contém o endereço de um grafo. */
typedef struct grafo *Grafo;

/* TAD GRAFO */
Grafo GRAFOcria(int);
void GRAFOinsereA(Grafo, Arco, int);
void GRAFOremoveA(Grafo, Arco);
void GRAFOinsereE(Grafo, Aresta, int);
void GRAFOremoveE(Grafo, Aresta);
void GRAFOimprime(Grafo);
void GRAFOdestroi(Grafo);

/* Algoritmos */
void BPrec(Grafo G);
void visitaBP(Grafo G, int v);
Grafo Kruskal(Grafo G,int *custo);
Grafo Heuristica(Grafo AGM, Grafo G, int *custo);


// Leitura do arquivo
Grafo GRAFOleitura(const char *nomearq);



#endif
