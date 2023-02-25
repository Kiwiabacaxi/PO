#include <stdlib.h>
#include <stdio.h>

// Definição da estrutura de dados para um no da lista dupla encadeada genérica
typedef struct no {
    void *dado;
    struct no *prox;
    struct no *ant;
} no;

// Definição da estrutura de dados para uma lista dupla encadeada genérica
typedef struct lista {
    no *inicio;
    no *fim;
    int tamanho;
} lista;

// Função para criar uma lista dupla encadeada genérica
lista *criar_lista() {
    lista *l = (lista *) malloc(sizeof(lista));                  // Aloca memória para a lista
    l->inicio = NULL;                                            // Inicializa o início da lista
    l->fim = NULL;                                               // Inicializa o fim da lista
    l->tamanho = 0;                                              // Inicializa o tamanho da lista
    return l;
}

// Função para inserir um elemento no início da lista dupla encadeada genérica
void inserir_inicio_dupla(lista *l, void *elemento) {
    no *novo = (no *) malloc(sizeof(no));                        // Aloca memória para o novo nó
    novo->dado = elemento;                                       // Inicializa o dado do novo nó
    novo->prox = l->inicio;                                      // Inicializa o próximo do novo nó
    novo->ant = NULL;                                            // Inicializa o anterior do novo nó
    if (l->inicio == NULL) {                                     // Verifica se a lista está vazia
        l->fim = novo;                                           // Inicializa o fim da lista
    } else {
        l->inicio->ant = novo;                                   // Atualiza o anterior do nó inicial da lista
    }
    l->inicio = novo;                                            // Atualiza o início da lista
    l->tamanho++;                                                // Incrementa o tamanho da lista
}

// Função para inserir um elemento no fim da lista dupla encadeada genérica
void inserir_fim_dupla(lista *l, void *elemento) {
    no *novo = (no *) malloc(sizeof(no));                        // Aloca memória para o novo nó
    novo->dado = elemento;                                       // Inicializa o dado do novo nó
    novo->prox = NULL;                                           // Inicializa o próximo do novo nó
    novo->ant = l->fim;                                          // Inicializa o anterior do novo nó
    if (l->inicio == NULL) {                                     // Verifica se a lista está vazia
        l->inicio = novo;                                        // Inicializa o início da lista
    } else {
        l->fim->prox = novo;                                     // Atualiza o próximo do nó final da lista
    }
    l->fim = novo;                                               // Atualiza o fim da lista
    l->tamanho++;                                                // Incrementa o tamanho da lista
}

// Função para inserir um elemento na lista dupla encadeada genérica em uma posição específica
void inserir_posicao_dupla(lista *l, void *elemento, int posicao) {
    if (posicao < 0 || posicao > l->tamanho) {                   // Verifica se a posição é válida
        printf("Posição inválida! Não é possível inserir o elemento %d na lista. \n", elemento);
        return;
    }
    if (posicao == 0) {                                          // Verifica se a posição é o início da lista
        inserir_inicio_dupla(l, elemento);                       // Chama a função para inserir no início da lista
        return;
    }
    if (posicao == l->tamanho) {                                 // Verifica se a posição é o fim da lista
        inserir_fim_dupla(l, elemento);                          // Chama a função para inserir no fim da lista
        return;
    }
    no *novo = (no *) malloc(sizeof(no));                        // Aloca memória para o novo nó
    novo->dado = elemento;                                       // Inicializa o dado do novo nó
    no *atual = l->inicio;                                       // Inicializa o nó atual
    int i;
    for (i = 0; i < posicao; i++) {                              // Percorre a lista até a posição desejada
        atual = atual->prox;
    }
    novo->prox = atual;                                          // Inicializa o próximo do novo nó
    novo->ant = atual->ant;                                      // Inicializa o anterior do novo nó
    atual->ant->prox = novo;                                     // Atualiza o próximo do nó anterior ao nó atual
    atual->ant = novo;                                           // Atualiza o anterior do nó atual
    l->tamanho++;                                                // Incrementa o tamanho da lista
}

// Função para remover um elemento do início da lista dupla encadeada genérica
void remover_inicio_dupla(lista *l) {
    if (l->inicio == NULL) {                                     // Verifica se a lista está vazia
        printf("A lista está vazia! Não é possível remover o elemento do início da lista. \n");
        return;
    }
    no *remover = l->inicio;                                     // Inicializa o nó a ser removido
    l->inicio = l->inicio->prox;                                 // Atualiza o início da lista
    if (l->inicio == NULL) {                                     // Verifica se a lista ficou vazia
        l->fim = NULL;                                           // Atualiza o fim da lista
    } else {
        l->inicio->ant = NULL;                                   // Atualiza o anterior do novo nó inicial da lista
    }
    free(remover);                                               // Libera a memória do nó a ser removido
    l->tamanho--;                                                // Decrementa o tamanho da lista
}

// Função para remover um elemento do fim da lista dupla encadeada genérica
void remover_fim_dupla(lista *l) {
    if (l->inicio == NULL) {                                     // Verifica se a lista está vazia
        printf("A lista está vazia! Não é possível remover o elemento do fim da lista. \n");
        return;
    }
    no *remover = l->fim;                                        // Inicializa o nó a ser removido
    l->fim = l->fim->ant;                                        // Atualiza o fim da lista
    if (l->fim == NULL) {                                        // Verifica se a lista ficou vazia
        l->inicio = NULL;                                        // Atualiza o início da lista
    } else {
        l->fim->prox = NULL;                                     // Atualiza o próximo do novo nó final da lista
    }
    free(remover);                                               // Libera a memória do nó a ser removido
    l->tamanho--;                                                // Decrementa o tamanho da lista
}

// Função para remover um elemento da lista dupla encadeada genérica em uma posição específica
void remover_posicao_dupla(lista *l, int posicao) {
    if (posicao < 0 || posicao >= l->tamanho) {                  // Verifica se a posição é válida
        printf("Posição inválida! Não é possível remover o elemento da lista. \n");
        return;
    }
    if (posicao == 0) {                                          // Verifica se a posição é o início da lista
        remover_inicio_dupla(l);                                 // Chama a função para remover do início da lista
        return;
    }
    if (posicao == l->tamanho - 1) {                             // Verifica se a posição é o fim da lista
        remover_fim_dupla(l);                                    // Chama a função para remover do fim da lista
        return;
    }
    no *remover = l->inicio;                                     // Inicializa o nó a ser removido
    int i;
    for (i = 0; i < posicao; i++) {                              // Percorre a lista até a posição desejada
        remover = remover->prox;
    }
    remover->ant->prox = remover->prox;                           // Atualiza o próximo do nó anterior ao nó a ser removido
    remover->prox->ant = remover->ant;                           // Atualiza o anterior do nó posterior ao nó a ser removido
    free(remover);                                               // Libera a memória do nó a ser removido
    l->tamanho--;                                                // Decrementa o tamanho da lista
}

// Função para imprimir a lista dupla encadeada genérica
void imprimir_lista_dupla(lista *l) {
    if (l->inicio == NULL) {                                     // Verifica se a lista está vazia
        printf("A lista está vazia! \n");
        return;
    }
    no *atual = l->inicio;                                       // Inicializa o nó atual
    while (atual != NULL) {                                      // Percorre a lista
        printf("%d ", atual->dado);                              // Imprime o dado do nó atual
        atual = atual->prox;                                     // Atualiza o nó atual
    }
    printf("\n");
}

// Função para imprimir a lista dupla encadeada genérica de trás para frente
void imprimir_lista_dupla_tras(lista *l) {
    if (l->inicio == NULL) {                                     // Verifica se a lista está vazia
        printf("A lista está vazia! \n");
        return;
    }
    no *atual = l->fim;                                          // Inicializa o nó atual
    while (atual != NULL) {                                      // Percorre a lista
        printf("%d ", atual->dado);                              // Imprime o dado do nó atual
        atual = atual->ant;                                      // Atualiza o nó atual
    }
    printf("\n");
}

// Função para liberar a memória alocada para a lista dupla encadeada genérica
void liberar_lista_dupla(lista *l) {
    no *atual = l->inicio;                                       // Inicializa o nó atual
    while (atual != NULL) {                                      // Percorre a lista
        no *remover = atual;                                     // Inicializa o nó a ser removido
        atual = atual->prox;                                     // Atualiza o nó atual
        free(remover);                                           // Libera a memória do nó a ser removido
    }
    free(l);                                                     // Libera a memória da lista
}

// criar_lista_dupla: função para criar uma lista dupla encadeada genérica
lista *criar_lista_dupla() {
    lista *l = (lista *) malloc(sizeof(lista));                  // Aloca memória para a lista
    l->inicio = NULL;                                            // Inicializa o início da lista
    l->fim = NULL;                                               // Inicializa o fim da lista
    l->tamanho = 0;                                              // Inicializa o tamanho da lista
    return l;                                                    // Retorna a lista criada
}

int main(){
    lista *l = criar_lista_dupla();                              // Cria a lista dupla encadeada genérica
    
    // Inserir 5 elementos no início da lista
    for (int i = 0; i < 5; i++) {
        inserir_inicio_dupla(l, i);
    }
    printf("Tamanho da lista: %d \n", l->tamanho);                // Imprime o tamanho da lista
    printf("Inseridos 5 elementos no início da lista. \n");
    imprimir_lista_dupla(l);                                     // Imprime a lista
    imprimir_lista_dupla_tras(l);                                // Imprime a lista de trás para frente

    // Inserir 5 elementos no fim da lista
    for (int i = 0; i < 5; i++) {
        inserir_fim_dupla(l, i);
    }

    printf("Tamanho da lista: %d \n", l->tamanho);                // Imprime o tamanho da lista
    printf("Inseridos 5 elementos no fim da lista. \n");
    imprimir_lista_dupla(l);                                     // Imprime a lista
    imprimir_lista_dupla_tras(l);                                // Imprime a lista de trás para frente

    // Inserir 5 elementos em uma posição específica da lista
    for (int i = 0; i < 5; i++) {
        inserir_posicao_dupla(l, i, i);
    }

    printf("Tamanho da lista: %d \n", l->tamanho);                // Imprime o tamanho da lista
    printf("Inseridos 5 elementos em uma posição específica da lista. \n");
    imprimir_lista_dupla(l);                                     // Imprime a lista
    imprimir_lista_dupla_tras(l);                                // Imprime a lista de trás para frente

    // Remover 5 elementos do início da lista
    for (int i = 0; i < 5; i++) {
        remover_inicio_dupla(l);
    }

    printf("Tamanho da lista: %d \n", l->tamanho);                // Imprime o tamanho da lista
    printf("Removidos 5 elementos do início da lista. \n");
    imprimir_lista_dupla(l);                                     // Imprime a lista
    imprimir_lista_dupla_tras(l);                                // Imprime a lista de trás para frente

    // Remover 5 elementos do fim da lista
    for (int i = 0; i < 5; i++) {
        remover_fim_dupla(l);
    }

    printf("Tamanho da lista: %d \n", l->tamanho);                // Imprime o tamanho da lista
    printf("Removidos 5 elementos do fim da lista. \n");
    imprimir_lista_dupla(l);                                     // Imprime a lista
    imprimir_lista_dupla_tras(l);                                // Imprime a lista de trás para frente

    // Remover 5 elementos de uma posição específica da lista
    for (int i = 0; i < 5; i++) {
        remover_posicao_dupla(l, i);
    }

    printf("Tamanho da lista: %d \n", l->tamanho);                // Imprime o tamanho da lista
    printf("Removidos 5 elementos de uma posição específica da lista. \n");
    imprimir_lista_dupla(l);                                     // Imprime a lista
    imprimir_lista_dupla_tras(l);                                // Imprime a lista de trás para frente

    

    liberar_lista_dupla(l);                                      // Libera a memória alocada para a lista



    return 0;
}
