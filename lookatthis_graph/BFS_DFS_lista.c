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

// funcao que preenche ARESTAS de um grafo
void preenche_arestas(Grafo* g) {
    int i, j;
    for (i = 0; i < g->num_vertices; i++) {
        for (j = i + 1; j < g->num_vertices; j++) {
            if (rand() % 2) {
                insere_aresta(g, i, j);
            }
        }
    }
}

// printa o grafo - printa as listas de adjacencia
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

// funcao que retorna 1 se existe caminho de origem para destino, usando busca em largura
int existe_caminho_largura(Grafo* g, int origem, int destino) {
    int* visitados = (int*) malloc(g->num_vertices * sizeof(int));
    int i;
    for (i = 0; i < g->num_vertices; i++) {
        visitados[i] = 0;
    }
    Fila* f = cria_fila();
    insere_fila(f, origem);
    visitados[origem] = 1;
    
    // enquanto a fila nao estiver vazia
    while (!fila_vazia(f)) {
        // remove o primeiro elemento da fila
        int vertice = remove_fila(f);
        // se o vertice removido for o destino, entao existe caminho
        No* atual = g->lista_adj[vertice];

        // percorre a lista de adjacencia do vertice removido
        while (atual != NULL) {
            // se o vertice atual for o destino, entao existe caminho
            if (atual->vertice == destino) {
                free(visitados);
                libera_fila(f);
                return 1;
            }
            // se o vertice atual nao foi visitado, entao o insere na fila
            if (!visitados[atual->vertice]) {
                insere_fila(f, atual->vertice);
                visitados[atual->vertice] = 1;
            }
            
            // vai para o proximo vertice da lista de adjacencia
            atual = atual->prox;
        }
    }
    free(visitados);
    libera_fila(f);
    return 0;
}

// --------------------// BUSCA EM PROFUNDIDADE // -------------------- //
// funcao recursiva que realiza a busca em profundidade
void busca_profundidade_rec(Grafo* g, int inicio, int* visitados) {
    visitados[inicio] = 1;
    printf("%d ", inicio);
    No* atual = g->lista_adj[inicio];
    while (atual != NULL) {
        if (!visitados[atual->vertice]) {
            busca_profundidade_rec(g, atual->vertice, visitados);
        }
        atual = atual->prox;
    }
}

// funcao que realiza a busca em profundidade
void busca_profundidade(Grafo* g, int inicio) {
    int* visitados = (int*) malloc(g->num_vertices * sizeof(int));
    int i;
    for (i = 0; i < g->num_vertices; i++) {
        visitados[i] = 0;
    }
    busca_profundidade_rec(g, inicio, visitados);
    free(visitados);
}

// funcao que retorna 1 se existe caminho de origem para destino, usando busca em profundidade
int existe_caminho_profundidade(Grafo* g, int origem, int destino) {
    int* visitados = (int*) malloc(g->num_vertices * sizeof(int));
    int i;
    for (i = 0; i < g->num_vertices; i++) {
        visitados[i] = 0;
    }
    busca_profundidade_rec(g, origem, visitados);
    int resultado = visitados[destino];
    free(visitados);
    return resultado;
}

// -------------------- // MAIN // -------------------- //
int main() {

/*     // criar um grafo com 8 vertices (0 a 7) nao direcionado
    Grafo* g = cria_grafo(8);

    // preencher o grafo com arestas
    preenche_arestas(g); */
    
    // criar um grafo com 8 vertices (0 a 7) nao direcionado na mao
    Grafo* g = cria_grafo(11);

    // inserir arestas na mao
    insere_aresta(g, 0, 1);
    insere_aresta(g, 0, 2);
    insere_aresta(g, 0, 3);
    insere_aresta(g, 1, 4);
    insere_aresta(g, 1, 5);
    insere_aresta(g, 2, 6);
    insere_aresta(g, 3, 7);

    insere_aresta(g, 4, 5);
    insere_aresta(g, 4, 3);
    
    
    insere_aresta(g, 2, 9);

    insere_aresta(g, 9, 8);
    insere_aresta(g, 9, 10);
    insere_aresta(g, 10, 8);
    

    // printar o grafo
    printf("Grafo:\n");
    printa_grafo(g);

    // Largura
    printf("Caminho por largura: ");

    // realizar a busca em largura
    busca_largura(g, 0);

    // verificar se existe caminho de 0 para 7
    printf("\nExiste caminho por largura %d\n", existe_caminho_largura(g, 0, 9));

    // Profundidade
    printf("Caminho por profundidade: ");

    // realizar a busca em profundidade
    // busca_profundidade(g, 0);

    // verificar se existe caminho de 0 para 7
    printf("\nExiste caminho por profundidade %d\n", existe_caminho_profundidade(g, 0, 7));




    libera_grafo(g);
    return 0;
}
