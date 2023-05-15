#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// grafo dinamico - lista de adjacencia
typedef struct no {
    int vertice;
    struct no* prox;
} No;

typedef struct {
    int num_vertices;
    int num_arestas;
    No** lista_adj;
} Grafo;

Grafo* cria_grafo(int num_vertices) {
    Grafo* g = (Grafo*) malloc(sizeof(Grafo));
    g->num_vertices = num_vertices;
    g->num_arestas = 0;
    g->lista_adj = (No**) malloc(num_vertices * sizeof(No*));
    int i;
    for (i = 0; i < num_vertices; i++) {
        g->lista_adj[i] = NULL;
    }
    return g;
}

void insere_aresta(Grafo* g, int v1, int v2) {
    No* novo = (No*) malloc(sizeof(No));
    novo->vertice = v2;
    novo->prox = g->lista_adj[v1];
    g->lista_adj[v1] = novo;
    g->num_arestas++;
}

void remove_aresta(Grafo* g, int v1, int v2) {
    No* atual = g->lista_adj[v1];
    No* anterior = NULL;
    while (atual != NULL && atual->vertice != v2) {
        anterior = atual;
        atual = atual->prox;
    }
    if (atual != NULL) {
        if (anterior == NULL) {
            g->lista_adj[v1] = atual->prox;
        } else {
            anterior->prox = atual->prox;
        }
        free(atual);
        g->num_arestas--;
    }
}

void imprime_grafo(Grafo* g) {
    int i;
    for (i = 0; i < g->num_vertices; i++) {
        printf("%d: ", i);
        No* atual = g->lista_adj[i];
        while (atual != NULL) {
            printf("%d ", atual->vertice);
            atual = atual->prox;
        }
        printf("\n");
    }
}

int main() {
    Grafo* g = cria_grafo(5);
    insere_aresta(g, 0, 1);
    insere_aresta(g, 0, 2);
    insere_aresta(g, 1, 2);
    insere_aresta(g, 1, 3);
    insere_aresta(g, 2, 3);
    insere_aresta(g, 3, 4);

    imprime_grafo(g);
    printf("Numero de vertices: %d\n", g->num_vertices);
    printf("Numero de arestas: %d\n", g->num_arestas);
    
    remove_aresta(g, 1, 3);
    remove_aresta(g, 3, 4);
    
    imprime_grafo(g);
    printf("Numero de vertices: %d\n", g->num_vertices);
    printf("Numero de arestas: %d\n", g->num_arestas);
    return 0;
}