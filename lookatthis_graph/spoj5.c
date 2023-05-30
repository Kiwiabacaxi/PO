/* 
@Kiwiabacaxi
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

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
    // peso das arestas
    int** pesos;
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
    // adiciona 1 ao vertice para printar de 1 a n
    for (i = 0; i < g->num_vertices; i++) {
        printf("%d: ", i+1);
        No* atual = g->lista_adj[i];
        while (atual != NULL) {
            printf("%d ", atual->vertice+1);
            atual = atual->prox;
        }
        printf("\n");
    }
}


// funcao recursiva que realiza a busca em profundidade limitada
void busca_profundidade_limitada_rec(Grafo* g, int inicio, int limite, int* visitados) {
    // marca o vertice como visitado
    visitados[inicio] = 1;

    // printa o vertice
    // printf("%d ", inicio+1);
    
    No* atual = g->lista_adj[inicio];
    
    // percorre os vertices adjacentes
    while (atual != NULL) {
        // se o vertice nao foi visitado e o limite ainda nao foi atingido
        if (!visitados[atual->vertice] && limite > 0) {
            busca_profundidade_limitada_rec(g, atual->vertice, limite-1, visitados);
        }
        // vai para o proximo vertice adjacente
        atual = atual->prox;
    }
}

// funcao que realiza a busca em profundidade limitada 
void busca_profundidade_limitada(Grafo* g, int inicio, int limite) {
    int* visitados = (int*) malloc(g->num_vertices * sizeof(int));
    int i;
    for (i = 0; i < g->num_vertices; i++) {
        visitados[i] = 0;
    }
    busca_profundidade_limitada_rec(g, inicio, limite, visitados);
    // printf("\n");
    free(visitados);
}

// funcao que realiza a busca em profundidade limitada e retorna um array com os vertices visitados
int* busca_profundidade_limitada_retorno(Grafo* g, int inicio, int limite) {
    int* visitados = (int*) malloc(g->num_vertices * sizeof(int));
    int i;
    for (i = 0; i < g->num_vertices; i++) {
        visitados[i] = 0;
    }
    busca_profundidade_limitada_rec(g, inicio, limite, visitados);
    // printf("\n");
    return visitados;
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
        printf("%d ", vertice+1);
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
    printf("%d ", inicio+1); // printa o vertice + 1
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

// -------------------- // DIJKSTRA // -------------------- //
// funcao que retorna o vertice com a menor distancia
int menor_distancia(int* distancias, int* visitados, int num_vertices) {
    int i;
    int min = -1;
    for (i = 0; i < num_vertices; i++) {
        if (!visitados[i] && (min == -1 || distancias[i] < distancias[min])) {
            min = i;
        }
    }
    return min;
}

// funcao que realiza o algoritmo de Dijkstra com pesos iguais
void dijkstra(Grafo* g, int inicio) {
    int* distancias = (int*) malloc(g->num_vertices * sizeof(int));
    int* visitados = (int*) malloc(g->num_vertices * sizeof(int));
    int* anteriores = (int*) malloc(g->num_vertices * sizeof(int));
    int i;
    for (i = 0; i < g->num_vertices; i++) {
        distancias[i] = INT_MAX;
        visitados[i] = 0;
        anteriores[i] = -1;
    }
    distancias[inicio] = 0;
    while (1) {
        int vertice = menor_distancia(distancias, visitados, g->num_vertices);
        if (vertice == -1) {
            break;
        }
        visitados[vertice] = 1;
        No* atual = g->lista_adj[vertice];
        while (atual != NULL) {
            int distancia = distancias[vertice] + 1; // peso igual a 1
            if (distancia < distancias[atual->vertice]) {
                distancias[atual->vertice] = distancia;
                anteriores[atual->vertice] = vertice;
            }
            atual = atual->prox;
        }
    }
    for (i = 0; i < g->num_vertices; i++) {
        // lembrando de somar 1 ao vertice para printar
        printf("Distancia de %d para %d: %d\n", inicio+1, i+1, distancias[i]);
    }
    free(distancias);
    free(visitados);
    free(anteriores);
}

// funcao que realiza o algoritmo de Dijkstra com pesos diferentes
/* void dijkstra(Grafo* g, int inicio) {
    int* distancias = (int*) malloc(g->num_vertices * sizeof(int));
    int* visitados = (int*) malloc(g->num_vertices * sizeof(int));
    int* anteriores = (int*) malloc(g->num_vertices * sizeof(int));
    int i;
    for (i = 0; i < g->num_vertices; i++) {
        distancias[i] = INT_MAX;
        visitados[i] = 0;
        anteriores[i] = -1;
    }
    distancias[inicio] = 0;
    while (1) {
        int vertice = menor_distancia(distancias, visitados, g->num_vertices);
        if (vertice == -1) {
            break;
        }
        visitados[vertice] = 1;
        No* atual = g->lista_adj[vertice];
        while (atual != NULL) {
            int distancia = distancias[vertice] + atual->peso;
            if (distancia < distancias[atual->vertice]) {
                distancias[atual->vertice] = distancia;
                anteriores[atual->vertice] = vertice;
            }
            atual = atual->prox;
        }
    }
    for (i = 0; i < g->num_vertices; i++) {
        printf("Distancia de %d para %d: %d\n", inicio, i, distancias[i]);
    }
    free(distancias);
    free(visitados);
    free(anteriores);
}
*/

// -------------------- // FLOYD WARSHALL // -------------------- //
// funcao que realiza o algorithmo de Floyd Warshall com pesos iguais
void floyd_warshall(Grafo* g) {
    int** distancias = (int**) malloc(g->num_vertices * sizeof(int*));
    int** anteriores = (int**) malloc(g->num_vertices * sizeof(int*));
    int i, j, k;
    for (i = 0; i < g->num_vertices; i++) {
        distancias[i] = (int*) malloc(g->num_vertices * sizeof(int));
        anteriores[i] = (int*) malloc(g->num_vertices * sizeof(int));
        for (j = 0; j < g->num_vertices; j++) {
            distancias[i][j] = INT_MAX;
            anteriores[i][j] = -1;
        }
    }
    for (i = 0; i < g->num_vertices; i++) {
        distancias[i][i] = 0;
        No* atual = g->lista_adj[i];
        while (atual != NULL) {
            distancias[i][atual->vertice] = 1;
            anteriores[i][atual->vertice] = i;
            atual = atual->prox;
        }
    }
    for (k = 0; k < g->num_vertices; k++) {
        for (i = 0; i < g->num_vertices; i++) {
            for (j = 0; j < g->num_vertices; j++) {
                if (distancias[i][k] != INT_MAX && distancias[k][j] != INT_MAX && distancias[i][k] + distancias[k][j] < distancias[i][j]) {
                    distancias[i][j] = distancias[i][k] + distancias[k][j];
                    anteriores[i][j] = anteriores[k][j];
                }
            }
        }
    }
    for (i = 0; i < g->num_vertices; i++) {
        for (j = 0; j < g->num_vertices; j++) {
            printf("Distancia de %d para %d: %d\n", i, j, distancias[i][j]);
        }
    }
    for (i = 0; i < g->num_vertices; i++) {
        free(distancias[i]);
        free(anteriores[i]);
    }
    free(distancias);
    free(anteriores);
}

// funcao que realiza o algoritmo de Floyd Warshall com pesos diferentes
/* void floyd_warshall(Grafo* g) {
    int** distancias = (int**) malloc(g->num_vertices * sizeof(int*));
    int** anteriores = (int**) malloc(g->num_vertices * sizeof(int*));
    int i, j, k;
    for (i = 0; i < g->num_vertices; i++) {
        distancias[i] = (int*) malloc(g->num_vertices * sizeof(int));
        anteriores[i] = (int*) malloc(g->num_vertices * sizeof(int));
        for (j = 0; j < g->num_vertices; j++) {
            distancias[i][j] = INT_MAX;
            anteriores[i][j] = -1;
        }
    }
    for (i = 0; i < g->num_vertices; i++) {
        distancias[i][i] = 0;
        No* atual = g->lista_adj[i];
        while (atual != NULL) {
            distancias[i][atual->vertice] = atual->peso;
            anteriores[i][atual->vertice] = i;
            atual = atual->prox;
        }
    }
    for (k = 0; k < g->num_vertices; k++) {
        for (i = 0; i < g->num_vertices; i++) {
            for (j = 0; j < g->num_vertices; j++) {
                if (distancias[i][k] != INT_MAX && distancias[k][j] != INT_MAX && distancias[i][k] + distancias[k][j] < distancias[i][j]) {
                    distancias[i][j] = distancias[i][k] + distancias[k][j];
                    anteriores[i][j] = anteriores[k][j];
                }
            }
        }
    }
    for (i = 0; i < g->num_vertices; i++) {
        for (j = 0; j < g->num_vertices; j++) {
            printf("Distancia de %d para %d: %d\n", i, j, distancias[i][j]);
        }
    }
    for (i = 0; i < g->num_vertices; i++) {
        free(distancias[i]);
        free(anteriores[i]);
    }
    free(distancias);
    free(anteriores);
} */

// -------------------- // BELLMAN FORD // -------------------- //
// funcao que realiza o algoritmo de Bellman Ford com pesos iguais
void bellman_ford(Grafo* g, int inicio) {
    int* distancias = (int*) malloc(g->num_vertices * sizeof(int));
    int* anteriores = (int*) malloc(g->num_vertices * sizeof(int));
    int i, j;
    for (i = 0; i < g->num_vertices; i++) {
        distancias[i] = INT_MAX;
        anteriores[i] = -1;
    }
    distancias[inicio] = 0;
    for (i = 0; i < g->num_vertices - 1; i++) {
        for (j = 0; j < g->num_vertices; j++) {
            No* atual = g->lista_adj[j];
            while (atual != NULL) {
                int distancia = distancias[j] + 1; // peso = 1
                if (distancia < distancias[atual->vertice]) {
                    distancias[atual->vertice] = distancia;
                    anteriores[atual->vertice] = j;
                }
                atual = atual->prox;
            }
        }
    }
    for (i = 0; i < g->num_vertices; i++) {
        printf("Distancia de %d para %d: %d\n", inicio, i, distancias[i]);
    }
    free(distancias);
    free(anteriores);
}

// funcao que realiza o algoritmo de Bellman Ford com pesos diferentes
/* void bellman_ford(Grafo* g, int inicio) {
    int* distancias = (int*) malloc(g->num_vertices * sizeof(int));
    int* anteriores = (int*) malloc(g->num_vertices * sizeof(int));
    int i, j;
    for (i = 0; i < g->num_vertices; i++) {
        distancias[i] = INT_MAX;
        anteriores[i] = -1;
    }
    distancias[inicio] = 0;
    for (i = 0; i < g->num_vertices - 1; i++) {
        for (j = 0; j < g->num_vertices; j++) {
            No* atual = g->lista_adj[j];
            while (atual != NULL) {
                int distancia = distancias[j] + atual->peso;
                if (distancia < distancias[atual->vertice]) {
                    distancias[atual->vertice] = distancia;
                    anteriores[atual->vertice] = j;
                }
                atual = atual->prox;
            }
        }
    }
    for (i = 0; i < g->num_vertices; i++) {
        printf("Distancia de %d para %d: %d\n", inicio, i, distancias[i]);
    }
    free(distancias);
    free(anteriores);
} */

// -------------------- // MAIN // -------------------- //
/* 0 <= C <= 50 (C = 0 apenas para indicar o fim da entrada)
0 <= E <= 2500 (E = 0 apenas para indicar o fim da entrada)
0 <= L <= C (L = 0 apenas para indicar o fim da entrada)
0 <= P <= C (P = 0 apenas para indicar o fim da entrada)
1 <= X <= C
1 <= Y <= C */

// compara
int compara(const void* a, const void* b) {
    int* x = (int*) a;
    int* y = (int*) b;
    return *x - *y;
}





int main() {
    // leitura da entrada
    int C, E, L, P, i, x, y, teste = 1;
    Grafo* g;
    // numero de vertices, numero de estradas, numero de linhas, numero de postes, vertice inicial, vertice final

    scanf("%d %d %d %d", &C, &E, &L, &P);
    while(C != 0 && E != 0 && L != 0 && P != 0) {
        // cria grafo
        g = cria_grafo(C);
        
        // le as arestas
        for (i = 0; i < E; i++) {
            scanf("%d %d", &x, &y);
            insere_aresta(g, x - 1, y - 1);
            insere_aresta(g, y - 1, x - 1);
        }

        // L = cidade inicial
        // P = numero maximo de pedagios

        // Teste n
        printf("Teste %d\n", teste);

        // busca em largura a partir de L, com P como limite
        // busca_profundidade_limitada_retorno(g, L - 1, P);

        // array de vertices visitados
        int* visitados = (int*) malloc(g->num_vertices * sizeof(int));
        memset(visitados, 0, g->num_vertices * sizeof(int));

        visitados = busca_profundidade_limitada_retorno(g, L - 1, P);

        // ordena o array de vertices visitados
        // qsort(visitados, g->num_vertices, sizeof(int), compara);

        // printa os vertices visitados
        for (i = 0; i < g->num_vertices; i++) {
            
            if(visitados[i] && i != L-1)
                printf("%d ", i + 1);
            
        }


        // printa o grafo
        // printa_grafo(g);


        printf("\n\n");
        
        // libera o grafo
        libera_grafo(g);
        // incrementa o n do teste
        teste++;
        
        // reescanear os valores
        scanf("%d %d %d %d", &C, &E, &L, &P);
    }



    return 0;
}
