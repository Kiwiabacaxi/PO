#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// grafo estatico - matriz de adjacencia
#define MAX_VERTICES 100
#define MAX_ARESTAS 4500

typedef struct {
    int v1, v2;
} Aresta;

typedef struct {
    int num_vertices;
    int num_arestas;
    int matriz_adj[MAX_VERTICES][MAX_VERTICES];
} Grafo;

Grafo* cria_grafo(int num_vertices) {
    Grafo* g = (Grafo*) malloc(sizeof(Grafo));
    g->num_vertices = num_vertices;
    g->num_arestas = 0;
    int i, j;
    for (i = 0; i < num_vertices; i++) {
        for (j = 0; j < num_vertices; j++) {
            g->matriz_adj[i][j] = 0;
        }
    }
    return g;
}

void insere_aresta(Grafo* g, int v1, int v2) {
    if (g->matriz_adj[v1][v2] == 0) {
        g->matriz_adj[v1][v2] = 1;
        g->matriz_adj[v2][v1] = 1;
        g->num_arestas++;
    }
}

void remove_aresta(Grafo* g, int v1, int v2) {
    if (g->matriz_adj[v1][v2] == 1) {
        g->matriz_adj[v1][v2] = 0;
        g->matriz_adj[v2][v1] = 0;
        g->num_arestas--;
    }
}

void imprime_grafo(Grafo* g) {
    int i, j;
    for (i = 0; i < g->num_vertices; i++) {
        printf("%d: ", i);
        for (j = 0; j < g->num_vertices; j++) {
            if (g->matriz_adj[i][j] == 1) {
                printf("%d ", j);
            }
        }
        printf("\n");
    }
}

void libera_grafo(Grafo* g) {
    free(g);
}

int main() {
    int num_vertices, num_arestas;


    // scanf("%d %d", &num_vertices, &num_arestas);
    
    // para teste inserindo valores aleatorios
    num_vertices = rand() % MAX_VERTICES;
    
    Grafo* g = cria_grafo(num_vertices);
    int i;
    /* for (i = 0; i < num_arestas; i++) {
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        insere_aresta(g, v1, v2);
    } */

    // para teste inserindo valores aleatorios
    for (i = 0; i < MAX_ARESTAS; i++) {
        int v1 = rand() % num_vertices;
        int v2 = rand() % num_vertices;
        insere_aresta(g, v1, v2);
    }

    imprime_grafo(g);
    libera_grafo(g);
    return 0;
}
