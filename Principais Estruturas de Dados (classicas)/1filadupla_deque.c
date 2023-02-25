#include <stdlib.h>
#include <stdio.h>

// Definição da estrutura de dados: node_duplo (doubly linked list) com uma implementação genérica
typedef struct node_d {
    void *dado;
    struct node_d *prox;
    struct node_d *ant;
} node_d;

// Definição da estrutura de dados deque (double ended queue) com uma implementação genérica
typedef struct deque {
    node_d *inicio;
    node_d *fim;
    int tamanho;
} deque;

// Função para criar um deque
deque *criar_deque() {
    deque *d = (deque *) malloc(sizeof(deque));                  // Aloca memória para o deque
    d->inicio = NULL;                                           // Inicializa o início do deque
    d->fim = NULL;                                              // Inicializa o fim do deque
    d->tamanho = 0;                                             // Inicializa o tamanho do deque
    return d;
}

// Função para inserir um elemento no início do deque enqueue_front
void enqueue_front(deque *d, void *elemento) {
    node_d *novo = (node_d *) malloc(sizeof(node_d));           // Aloca memória para o novo nó
    novo->dado = elemento;                                      // Inicializa o dado do novo nó
    novo->prox = d->inicio;                                     // Inicializa o próximo do novo nó
    novo->ant = NULL;                                           // Inicializa o anterior do novo nó
    if (d->inicio == NULL) {                                    // Verifica se o deque está vazio
        d->fim = novo;                                          // Inicializa o fim do deque
    } else {
        d->inicio->ant = novo;                                  // Atualiza o anterior do nó inicial do deque
    }
    d->inicio = novo;                                           // Atualiza o início do deque
    d->tamanho++;                                               // Incrementa o tamanho do deque
}

// Função para inserir um elemento no fim do deque enqueue_rear
void enqueue_rear(deque *d, void *elemento) {
    node_d *novo = (node_d *) malloc(sizeof(node_d));           // Aloca memória para o novo nó
    novo->dado = elemento;                                      // Inicializa o dado do novo nó
    novo->prox = NULL;                                          // Inicializa o próximo do novo nó
    novo->ant = d->fim;                                         // Inicializa o anterior do novo nó
    if (d->inicio == NULL) {                                    // Verifica se o deque está vazio
        d->inicio = novo;                                       // Inicializa o início do deque
    } else {
        d->fim->prox = novo;                                    // Atualiza o próximo do nó final do deque
    }
    d->fim = novo;                                              // Atualiza o fim do deque
    d->tamanho++;                                               // Incrementa o tamanho do deque
}

// Função para remover um elemento do início do deque dequeue_front
void *dequeue_front(deque *d) {
    if (d->inicio == NULL) {                                    // Verifica se o deque está vazio
        return NULL;                                            // Retorna NULL
    }
    node_d *aux = d->inicio;                                    // Cria um nó auxiliar para o início do deque
    void *elemento = aux->dado;                                 // Cria um ponteiro genérico para o dado do nó auxiliar
    d->inicio = aux->prox;                                      // Atualiza o início do deque
    if (d->inicio == NULL) {                                    // Verifica se o deque ficou vazio
        d->fim = NULL;                                          // Atualiza o fim do deque
    } else {
        d->inicio->ant = NULL;                                  // Atualiza o anterior do novo nó inicial do deque
    }
    free(aux);                                                  // Libera a memória do nó auxiliar
    d->tamanho--;                                               // Decrementa o tamanho do deque
    return elemento;                                            // Retorna o elemento removido
}

// Função para remover um elemento do fim do deque dequeue_rear
void *dequeue_rear(deque *d) {
    if (d->inicio == NULL) {                                    // Verifica se o deque está vazio
        return NULL;                                            // Retorna NULL
    }
    node_d *aux = d->fim;                                       // Cria um nó auxiliar para o fim do deque
    void *elemento = aux->dado;                                 // Cria um ponteiro genérico para o dado do nó auxiliar
    d->fim = aux->ant;                                          // Atualiza o fim do deque
    if (d->fim == NULL) {                                       // Verifica se o deque ficou vazio
        d->inicio = NULL;                                       // Atualiza o início do deque
    } else {
        d->fim->prox = NULL;                                    // Atualiza o próximo do novo nó final do deque
    }
    free(aux);                                                  // Libera a memória do nó auxiliar
    d->tamanho--;                                               // Decrementa o tamanho do deque
    return elemento;                                            // Retorna o elemento removido
}

// Função para imprimir o deque
void imprimir_deque(deque *d, void (*imprimir)(void *)) {
    node_d *aux = d->inicio;                                    // Cria um nó auxiliar para o início do deque
    while (aux != NULL) {                                       // Percorre o deque
        imprimir(aux->dado);                                    // Imprime o dado do nó auxiliar
        aux = aux->prox;                                        // Atualiza o nó auxiliar para o próximo nó
    }
}

// Função para front
void *front(deque *d) {
    if (d->inicio == NULL) {                                    // Verifica se o deque está vazio
        return NULL;                                            // Retorna NULL
    }
    return d->inicio->dado;                                     // Retorna o dado do início do deque
}

// Função para back
void *back(deque *d) {
    if (d->inicio == NULL) {                                    // Verifica se o deque está vazio
        return NULL;                                            // Retorna NULL
    }
    return d->fim->dado;                                        // Retorna o dado do fim do deque
}

// Função para size
int size(deque *d) {
    return d->tamanho;                                          // Retorna o tamanho do deque
}

// Função para empty
int empty(deque *d) {
    return d->inicio == NULL;                                   // Retorna 1 se o deque estiver vazio e 0 caso contrário
}

// Função para limpar o deque
void clear(deque *d) {
    node_d *aux = d->inicio;                                    // Cria um nó auxiliar para o início do deque
    while (aux != NULL) {                                       // Percorre o deque
        node_d *aux2 = aux->prox;                               // Cria um nó auxiliar para o próximo nó
        free(aux);                                              // Libera a memória do nó auxiliar
        aux = aux2;                                             // Atualiza o nó auxiliar para o próximo nó
    }
    d->inicio = NULL;                                           // Atualiza o início do deque
    d->fim = NULL;                                              // Atualiza o fim do deque
    d->tamanho = 0;                                             // Atualiza o tamanho do deque
}

// Função para imprimir um inteiro
void imprimir_inteiro(void *elemento) {
    printf("%d ", *(int *) elemento);                           // Imprime o inteiro
}

// Função para imprimir um caractere
void imprimir_caractere(void *elemento) {
    printf("%c ", *(char *) elemento);                          // Imprime o caractere
}

// Função para imprimir um float
void imprimir_float(void *elemento) {
    printf("%f ", *(float *) elemento);                         // Imprime o float
}

// Função para imprimir um double
void imprimir_double(void *elemento) {
    printf("%lf ", *(double *) elemento);                       // Imprime o double
}

// Função para imprimir um inteiro
void imprimir_string(void *elemento) {
    printf("%s ", (char *) elemento);                           // Imprime a string
}

// Função para imprimir um inteiro
void imprimir_ponteiro(void *elemento) {
    printf("%p ", elemento);                                    // Imprime o ponteiro
}


int main(){
    deque *d = criar_deque();                                   // Cria um deque

    // teste com 5 inteiros
    for (int i = 0; i < 5; i++) {
        int *n = (int *) malloc(sizeof(int));                   // Aloca memória para o inteiro
        *n = i;                                                 // Inicializa o inteiro
        enqueue_front(d, n);                                    // Insere o inteiro no início do deque
    }

    // imprime o deque usando a função imprimir_deque
    printf("Imprimindo o deque usando a função imprimir: ");
    imprimir_deque(d, imprimir_inteiro);                        // Imprime o deque
    printf("\n");

    // imprime o deque usando a função front
    printf("Imprimindo o deque usando a função front: ");
    while (!empty(d)) {                                         // Enquanto o deque não estiver vazio
        int *n = (int *) front(d);                              // Obtém o elemento do início do deque
        printf("%d ", *n);                                      // Imprime o elemento do início do deque
        dequeue_front(d);                                       // Remove o elemento do início do deque
    }
    printf("\n");

    // teste com 5 caracteres
    for (int i = 0; i < 5; i++) {
        char *c = (char *) malloc(sizeof(char));                // Aloca memória para o caractere
        *c = 'a' + i;                                           // Inicializa o caractere
        enqueue_rear(d, c);                                     // Insere o caractere no fim do deque
    }

    // imprime o deque usando a função imprimir_deque
    printf("Imprimindo o deque usando a função imprimir: ");
    imprimir_deque(d, imprimir_caractere);                      // Imprime o deque
    printf("\n");

    // imprime o deque usando a função back
    printf("Imprimindo o deque usando a função back: ");
    while (!empty(d)) {                                         // Enquanto o deque não estiver vazio
        char *c = (char *) back(d);                             // Obtém o elemento do fim do deque
        printf("%c ", *c);                                      // Imprime o elemento do fim do deque
        dequeue_rear(d);                                        // Remove o elemento do fim do deque
    }
    printf("\n");


    // apagar o deque
    clear(d);                                                   // Limpa o deque

    

    return 0;
}
