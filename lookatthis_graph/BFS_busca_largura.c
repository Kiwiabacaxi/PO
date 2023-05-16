#include <stdlib.h>
#include <stdio.h>

// grafos
// BFS - breadth-first search ou busca em largura

// -------------------- // FILA // -------------------- //
// struct de uma fila
typedef struct no {
    int vertice;
    struct no* prox;
} No;

typedef struct {
    No* inicio;
    No* fim;
} Fila;

// funcoes da fila
// cria uma fila vazia
Fila* cria_fila() {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

// insere um elemento no fim da fila
void insere_fila(Fila* f, int vertice) {
    No* novo = (No*) malloc(sizeof(No));
    novo->vertice = vertice;
    novo->prox = NULL;
    if (f->fim != NULL) {
        f->fim->prox = novo;
    } else {
        f->inicio = novo;
    }
    f->fim = novo;
}

// remove um elemento do inicio da fila
int remove_fila(Fila* f) {
    if (f->inicio != NULL) {
        No* removido = f->inicio;
        int vertice = removido->vertice;
        f->inicio = removido->prox;
        if (f->inicio == NULL) {
            f->fim = NULL;
        }
        free(removido);
        return vertice;
    }
    return -1;
}

// verifica se a fila esta vazia
int fila_vazia(Fila* f) {
    return f->inicio == NULL;
}

// libera a memoria alocada pela fila
void libera_fila(Fila* f) {
    No* atual = f->inicio;
    while (atual != NULL) {
        No* prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(f);
}

// -------------------- // GRAFO DINAMICO // -------------------- //
// grafo dinamico - lista de adjacencia
typedef struct {
    int num_vertices;
    int num_arestas;
    No** lista_adj;
} Grafo;

// funcao que cria um grafo vazio
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

// funcao que insere uma aresta no grafo
void insere_aresta(Grafo* g, int v1, int v2) {
    No* novo = (No*) malloc(sizeof(No));
    novo->vertice = v2;
    novo->prox = g->lista_adj[v1];
    g->lista_adj[v1] = novo;
    g->num_arestas++;
}

// funcao que remove uma aresta do grafo
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

// funcao que verifica se existe uma aresta entre dois vertices
int existe_aresta(Grafo* g, int v1, int v2) {
    No* atual = g->lista_adj[v1];
    while (atual != NULL && atual->vertice != v2) {
        atual = atual->prox;
    }
    return atual != NULL;
}

// funcao que libera a memoria alocada pelo grafo
void libera_grafo(Grafo* g) {
    int i;
    for (i = 0; i < g->num_vertices; i++) {
        No* atual = g->lista_adj[i];
        while (atual != NULL) {
            No* prox = atual->prox;
            free(atual);
            atual = prox;
        }
    }
    free(g->lista_adj);
    free(g);
}

// funcao que preenche grafico - TODO

// -------------------- // BUSCA EM LARGURA // -------------------- //
// funcao que realiza a busca em largura
void busca_largura(Grafo* g, int inicio) {
    int* visitados = (int*) malloc(g->num_vertices * sizeof(int));
    int i;
    for (i = 0; i < g->num_vertices; i++) {
        visitados[i] = 0;
    }
    Fila* f = cria_fila();
    insere_fila(f, inicio);
    visitados[inicio] = 1;
    while (!fila_vazia(f)) {
        int vertice = remove_fila(f);
        printf("%d ", vertice);
        No* atual = g->lista_adj[vertice];
        while (atual != NULL) {
            if (!visitados[atual->vertice]) {
                insere_fila(f, atual->vertice);
                visitados[atual->vertice] = 1;
            }
            atual = atual->prox;
        }
    }
    free(visitados);
    libera_fila(f);
}

// printa o grafo
void printa_grafo(Grafo* g) {
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


// -------------------- // MAIN // -------------------- //
int main() {

    // criar um grafo com 20 vertices
    Grafo* g = cria_grafo(20);

    // loop para inserir as arestas
/*     int i;
    for (i = 0; i < 19; i++) {
        insere_aresta(g, i, i + 1);
    } */

    // inserir as arestas
    insere_aresta(g, 0, 1);
    insere_aresta(g, 0, 2);
    insere_aresta(g, 0, 3);
    insere_aresta(g, 1, 4);
    insere_aresta(g, 1, 5);
    insere_aresta(g, 2, 6);
    insere_aresta(g, 2, 7);

    // realizar a busca em largura
    busca_largura(g, 0);



    libera_grafo(g);
    return 0;
}
