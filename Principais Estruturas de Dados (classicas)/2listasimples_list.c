#include <stdlib.h>
#include <stdio.h>

// Definição da estrutura de dados para um no da lista encadeada genérica
typedef struct no {
    void *dado;
    struct no *prox;
} no;

// Definição da estrutura de dados para uma lista encadeada genérica
typedef struct lista {
    no *inicio;
    no *fim;
    int tamanho;
} lista;

// Função para criar uma lista encadeada genérica
lista *criar_lista() {
    lista *l = (lista *) malloc(sizeof(lista));                  // Aloca memória para a lista
    l->inicio = NULL;                                            // Inicializa o início da lista
    l->fim = NULL;                                               // Inicializa o fim da lista
    l->tamanho = 0;                                              // Inicializa o tamanho da lista
    return l;
}

// Função para inserir um elemento no início da lista encadeada genérica
void inserir_inicio_simples(lista *l, void *elemento) {
    no *novo = (no *) malloc(sizeof(no));                        // Aloca memória para o novo nó
    novo->dado = elemento;                                       // Inicializa o dado do novo nó
    novo->prox = l->inicio;                                      // Inicializa o próximo do novo nó
    if (l->inicio == NULL) {                                     // Verifica se a lista está vazia
        l->fim = novo;                                           // Inicializa o fim da lista
    }
    l->inicio = novo;                                            // Atualiza o início da lista
    l->tamanho++;                                                // Incrementa o tamanho da lista
}

// Função para inserir um elemento no fim da lista encadeada genérica
void inserir_fim_simples(lista *l, void *elemento) {
    no *novo = (no *) malloc(sizeof(no));                        // Aloca memória para o novo nó
    novo->dado = elemento;                                       // Inicializa o dado do novo nó
    novo->prox = NULL;                                           // Inicializa o próximo do novo nó
    if (l->inicio == NULL) {                                     // Verifica se a lista está vazia
        l->inicio = novo;                                        // Inicializa o início da lista
    } else {
        l->fim->prox = novo;                                     // Atualiza o próximo do nó final da lista
    }
    l->fim = novo;                                               // Atualiza o fim da lista
    l->tamanho++;                                                // Incrementa o tamanho da lista
}

// Função para remover um elemento do início da lista encadeada genérica
void *remover_inicio_simples(lista *l) {
    if (l->inicio == NULL) {                                     // Verifica se a lista está vazia
        printf("Lista vazia! Não é possível remover um elemento do início da lista. \n");
        return NULL;
    }
    no *primeiro = l->inicio;                                    // Pega o primeiro nó da lista
    void *elemento = primeiro->dado;                             // Pega o dado do primeiro nó da lista
    l->inicio = primeiro->prox;                                  // Atualiza o início da lista
    if (l->inicio == NULL) {                                     // Verifica se a lista ficou vazia
        l->fim = NULL;                                           // Atualiza o fim da lista
    }
    free(primeiro);                                              // Libera a memória do primeiro nó da lista
    l->tamanho--;                                                // Decrementa o tamanho da lista
    return elemento;
}

// Função para remover um elemento do fim da lista encadeada genérica
void *remover_fim_simples(lista *l) {
    if (l->inicio == NULL) {                                     // Verifica se a lista está vazia
        printf("Lista vazia! Não é possível remover um elemento do fim da lista. \n");
        return NULL;
    }
    no *penultimo = l->inicio;                                   // Pega o primeiro nó da lista
    while (penultimo->prox != l->fim) {                          // Percorre a lista até o penúltimo nó
        penultimo = penultimo->prox;
    }
    void *elemento = l->fim->dado;                               // Pega o dado do último nó da lista
    free(l->fim);                                                // Libera a memória do último nó da lista
    l->fim = penultimo;                                          // Atualiza o fim da lista
    if (l->fim == NULL) {                                        // Verifica se a lista ficou vazia
        l->inicio = NULL;                                        // Atualiza o início da lista
    } else {
        l->fim->prox = NULL;                                     // Atualiza o próximo do penúltimo nó da lista
    }
    l->tamanho--;                                                // Decrementa o tamanho da lista
    return elemento;
}

// Função para imprimir os elementos da lista encadeada genérica
void imprimir_lista_simples(lista *l) {
    no *atual = l->inicio;                                       // Pega o primeiro nó da lista
    while (atual != NULL) {                                      // Percorre a lista até o último nó
        printf("%d ", *(int *) atual->dado);                     // Imprime o dado do nó atual
        atual = atual->prox;                                     // Atualiza o nó atual
    }
    printf("\n");
}

// Função para liberar a memória alocada para a lista encadeada genérica
void liberar_lista_simples(lista *l) {
    no *atual = l->inicio;                                       // Pega o primeiro nó da lista
    while (atual != NULL) {                                      // Percorre a lista até o último nó
        no *proximo = atual->prox;                               // Pega o próximo nó da lista
        free(atual);                                             // Libera a memória do nó atual
        atual = proximo;                                         // Atualiza o nó atual
    }
    free(l);                                                     // Libera a memória da lista
}



int main(){
    lista *l = criar_lista();

    // Inserindo 5 elementos no início da lista
    for (int i = 1; i <= 5; i++) {
        int *elemento = (int *) malloc(sizeof(int));             // Aloca memória para o elemento
        *elemento = i;                                           // Inicializa o elemento
        inserir_inicio_simples(l, elemento);                     // Insere o elemento no início da lista
    }

    // Inserindo 5 elementos no fim da lista
    for (int i = 5; i < 10; i++) {
        int *elemento = (int *) malloc(sizeof(int));             // Aloca memória para o elemento
        *elemento = i;                                           // Inicializa o elemento
        inserir_fim_simples(l, elemento);                        // Insere o elemento no fim da lista
    }

    // Quantos elementos tem na lista?
    printf("Tamanho da lista: %d \n", l->tamanho);

    // Imprimindo a lista
    imprimir_lista_simples(l);

    // Removendo 5 elementos do início da lista
    for (int i = 0; i < 5; i++) {
        int *elemento = (int *) remover_inicio_simples(l);       // Remove o elemento do início da lista
        printf("Elemento removido do início da lista: %d \n", *elemento);
        free(elemento);                                          // Libera a memória do elemento
    }

    // removendo 4 elementos do fim da lista
    for (int i = 0; i < 4; i++) {
        int *elemento = (int *) remover_fim_simples(l);          // Remove o elemento do fim da lista
        printf("Elemento removido do fim da lista: %d \n", *elemento);
        free(elemento);                                          // Libera a memória do elemento
    }

    // Quantos elementos tem na lista?
    printf("Tamanho da lista: %d \n", l->tamanho);

    // removendo 1 elemento do início da lista
    int *elemento = (int *) remover_inicio_simples(l);           // Remove o elemento do início da lista

    // Quantos elementos tem na lista?
    printf("Tamanho da lista: %d \n", l->tamanho);

    // Imprimindo a lista
    imprimir_lista_simples(l);

    // Liberando a memória alocada para a lista
    liberar_lista_simples(l);

    return 0;
}