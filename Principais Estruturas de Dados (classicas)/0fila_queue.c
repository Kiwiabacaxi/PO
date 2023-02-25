#include <stdlib.h>
#include <stdio.h>

// Definição da estrutura de dados node_simples, com uma implementação genérica
typedef struct node_s {
    void *dado;
    struct node_s *prox;
} node_s;

// Definição da estrutura de dados fila, com uma implementação genérica
typedef struct fila {
    node_s *inicio;
    node_s *fim;
    int tamanho;
} fila;

// Função para criar uma fila
fila *criar_fila() {
    fila *f = (fila *) malloc(sizeof(fila));                    // Aloca memória para a fila
    f->inicio = NULL;                                           // Inicializa o início da fila
    f->fim = NULL;                                              // Inicializa o fim da fila
    f->tamanho = 0;                                             // Inicializa o tamanho da fila
    return f;
}

// Função para enfileirar um elemento na fila
void enqueue(fila *f, void *elemento) {
    node_s *novo = (node_s *) malloc(sizeof(node_s));           // Aloca memória para o novo nó
    novo->dado = elemento;                                      // Inicializa o dado do novo nó
    novo->prox = NULL;                                          // Inicializa o próximo do novo nó
    if (f->inicio == NULL) {                                    // Verifica se a fila está vazia
        f->inicio = novo;                                       // Inicializa o início da fila
    } else {
        f->fim->prox = novo;                                    // Atualiza o próximo do nó final da fila
    }
    f->fim = novo;                                              // Atualiza o fim da fila
    f->tamanho++;                                               // Incrementa o tamanho da fila
}

// Função para desenfileirar um elemento da fila
void *dequeue(fila *f) {
    if (f->inicio == NULL) {                                    // Verifica se a fila está vazia
        printf("Fila vazia! Não é possível desenfileirar um elemento. \n");
        return NULL;
    }
    node_s *primeiro = f->inicio;                               // Pega o primeiro nó da fila
    void *elemento = primeiro->dado;                            // Pega o dado do primeiro nó da fila
    f->inicio = primeiro->prox;                                 // Atualiza o início da fila
    if (f->inicio == NULL) {                                    // Verifica se a fila ficou vazia
        f->fim = NULL;                                          // Atualiza o fim da fila
    }
    free(primeiro);                                             // Libera a memória do primeiro nó da fila
    f->tamanho--;                                               // Decrementa o tamanho da fila
    return elemento;
}

// Função para dar peek no elemento do início da fila
void *peek(fila *f) {
    if (f->inicio == NULL) {                                    // Verifica se a fila está vazia
        printf("Fila vazia! Não é possível dar peek no elemento do início da fila. \n");
        return NULL;
    }
    return f->inicio->dado;                                     // Retorna o elemento do início da fila
}

// Função para imprimir os elementos da fila
void imprimir_fila(fila *f) {
    if (f->inicio == NULL) {                                    // Verifica se a fila está vazia
        printf("Fila vazia! Não é possível imprimir os elementos da fila. \n");
        return;
    }
    node_s *atual = f->inicio;                                  // Pega o primeiro nó da fila
    while (atual != NULL) {                                     // Percorre a fila
        printf("%d ", *(int *) atual->dado);                    // Imprime o elemento do nó atual
        atual = atual->prox;                                    // Atualiza o nó atual
    }
    printf("\n");
}

// Função para liberar a memória da fila
void liberar_fila(fila *f) {
    node_s *atual = f->inicio;                                  // Pega o primeiro nó da fila
    while (atual != NULL) {                                     // Percorre a fila
        node_s *proximo = atual->prox;                          // Pega o próximo nó da fila
        free(atual);                                            // Libera a memória do nó atual
        atual = proximo;                                        // Atualiza o nó atual
    }
    free(f);                                                    // Libera a memória da fila
}

// Função para verificar se a fila está vazia
int fila_vazia(fila *f) {
    return f->inicio == NULL;
}

int main(){
    fila *f = criar_fila();                                     // Cria uma fila
    
    // enqueue 5 elementos na fila
    int i;
    for (i = 1; i <= 5; i++) {
        int *elemento = (int *) malloc(sizeof(int));            // Aloca memória para o elemento
        *elemento = i;                                          // Inicializa o elemento
        enqueue(f, elemento);                                   // Enfileira o elemento
    }

    printf("\n");
    printf("Tamanho da fila: %d", f->tamanho);                   // Imprime o tamanho da fila
    printf("\n");

    printf("imprimir_fila usando a função: ");                  // Imprime o cabeçalho
    imprimir_fila(f);                                           // Imprime os elementos da fila

    printf("imprimir_fila usando o peek: ");                    // Imprime o cabeçalho
    // imprimir a fila atraves do peek
    while (!fila_vazia(f)) {
        printf("%d ", *(int *) peek(f));                        // Imprime o elemento do início da fila
        dequeue(f);                                             // Desenfileira o elemento do início da fila
    }
    printf("\n");

    printf("imprimir_fila usando o dequeue: ");                 // Imprime o cabeçalho
    // imprimir a fila atraves do dequeue
    for (i = 1; i <= 5; i++) {
        int *elemento = (int *) malloc(sizeof(int));            // Aloca memória para o elemento
        *elemento = i;                                          // Inicializa o elemento
        enqueue(f, elemento);                                   // Enfileira o elemento
    }
    printf("\n");

    printf("imprimir_fila usando o dequeue: ");                 // Imprime o cabeçalho
    while (!fila_vazia(f)) {
        printf("%d ", *(int *) dequeue(f));                     // Imprime o elemento do início da fila e desenfileira o elemento do início da fila
    }
    printf("\n");

    liberar_fila(f);                                            // Libera a memória da fila

    return 0;
}