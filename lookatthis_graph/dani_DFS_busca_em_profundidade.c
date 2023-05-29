#include <stdlib.h>
#include <stdio.h>

//-------- // LISTADUPLA // --------//
typedef struct nod{
    void* info;
    struct nod *ant;
    struct nod *prox;
}Nod;

typedef struct listad{
        Nod *ini;
        Nod *fim;
}Listad;

Listad* cria_listad(){
    Listad *L = (Listad*)malloc(sizeof(Listad));
    L->ini = NULL;
    L->fim = NULL;
    return L;
}

Nod* cria_nod(void* valor){
    Nod *n = (Nod*)malloc(sizeof(Nod));
    n->info = valor;
    n->ant = NULL;
    n->prox = NULL;
    return n;
}

Listad* insere_inicio_listad(Listad *L, void* valor){
    Nod *n = cria_nod(valor);
    if(L->ini == NULL){
        L->ini = n;
        L->fim = n;
    }else{
        n->prox = L->ini;
        L->ini->ant = n;
        L->ini = n;
    }
    return L;
}

Listad* insere_fim_listad(Listad *L, void* valor){
    Nod *n = cria_nod(valor);
    if(L->ini == NULL){
        L->ini = n;
        L->fim = n;
    }else{
        n->ant = L->fim;
        L->fim->prox = n;
        L->fim = n;
    }
    return L;
}

void* remove_fim_listad(Listad *L){
    if(L->ini == NULL){
        return NULL;
    }else{
        Nod *n = L->fim;
        void *valor = n->info;
        if(L->ini == L->fim){
            L->ini = NULL;
            L->fim = NULL;
        }else{
            L->fim = n->ant;
            L->fim->prox = NULL;
        }
        free(n);
        return valor;
    }
}

void* remove_inicio_listad(Listad *L){
    if(L->ini == NULL){
        return NULL;
    }else{
        Nod *n = L->ini;
        void *valor = n->info;
        if(L->ini == L->fim){
            L->ini = NULL;
            L->fim = NULL;
        }else{
            L->ini = n->prox;
            L->ini->ant = NULL;
        }
        free(n);
        return valor;
    }
}

Listad* libera_listad(Listad *L){
    Nod *n = L->ini;
    while(n != NULL){
        Nod *aux = n->prox;
        free(n);
        n = aux;
    }
    free(L);
    return NULL;
}

int eh_valorado(Listad *L){
    if(L->ini == NULL){
        return 0;
    }else{
        return 1;
    }
}

int eh_vazio_listad(Listad *L){
    if(L->ini == NULL){
        return 1;
    }else{
        return 0;
    }
}

//-------- // FILA // --------//
typedef Listad Fila;

Fila* cria_fila(){
    Fila *f = cria_listad();
    return f;
}

Fila* enqueue(Fila *f, void* elemento){
    f = insere_fim_listad(f, elemento);
    return f;
}

Fila* dequeue(Fila *f){
    remove_inicio_listad(f);
    return f;
}

int eh_vazia_fila(Fila *f){
    return eh_vazio_listad(f);
}

//-------- // GRAFO // --------//
typedef struct grafo{
    int ordem;
    int *vertices;
    int **adjacencias;
    int eh_direcionado;
    int eh_valorado;
    int *visitados;
}Grafo;

Grafo *cria_grafo(int n, int valorado, int direcionado);
void preenche_vertices(Grafo *g);
void preenche_arestas(Grafo *g);
void mostra_grafo(Grafo *g);
void percurso_largura(Grafo *g);
void profundidade(Grafo *g);

// criar grafo

Grafo *cria_grafo(int n, int valorado, int direcionado){
    Grafo *g = (Grafo*)malloc(sizeof(Grafo));
    g->ordem = n;
    g->vertices = (int*)malloc(n*sizeof(int));
    g->adjacencias = (int**)malloc(n*sizeof(int*));
    g->eh_direcionado = direcionado;
    g->eh_valorado = valorado;
    g->visitados = (int*)malloc(n*sizeof(int));
    preenche_vertices(g);
    preenche_arestas(g);
    return g;
}

// preencher vertices v1
void preenche_vertices(Grafo *g){
    int i;
    for(i=0; i<g->ordem; i++){
        g->vertices[i] = i;
    }
}

// preencher arestas v1
void preenche_arestas(Grafo *g){
    int i, j;
    for(i=0; i<g->ordem; i++){
        g->adjacencias[i] = (int*)malloc(g->ordem*sizeof(int));
        for(j=0; j<g->ordem; j++){
            g->adjacencias[i][j] = 0;
        }
    }
}

// mostrar grafo
void mostra_grafo(Grafo *g){
    int i, j;
    for(i=0; i<g->ordem; i++){
        printf("%d: ", g->vertices[i]);
        for(j=0; j<g->ordem; j++){
            if(g->adjacencias[i][j] == 1){
                printf("%d ", g->vertices[j]);
            }
        }
        printf("\n");
    }
}

// percurso em largura - BFS
void percurso_largura(Grafo *g){
    int i;
    for(i=0; i<g->ordem; i++){
        g->visitados[i] = 0;
    }
    Fila *f = cria_fila();
    enqueue(f, g->vertices[0]);
    g->visitados[0] = 1;
    while(!eh_vazia_fila(f)){
        int v = dequeue(f);
        printf("%d ", v);
        for(i=0; i<g->ordem; i++){
            if(g->adjacencias[v][i] == 1 && g->visitados[i] == 0){
                enqueue(f, g->vertices[i]);
                g->visitados[i] = 1;
            }
        }
    }
}

// profundidade
void profundidade(Grafo *g){
    int i;
    for(i=0; i<g->ordem; i++){
        g->visitados[i] = 0;
    }
    for(i=0; i<g->ordem; i++){
        if(g->visitados[i] == 0){
            profundidade_aux(g, i);
        }
    }
}

int main(){


    return 0;
}