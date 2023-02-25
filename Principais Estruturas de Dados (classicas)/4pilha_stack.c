#include <stdlib.h>
#include <stdio.h>

// Definição da estrutura de dados pilha, com uma implementação genérica
typedef struct pilha {
    int topo;
    int tamanho;
    void **dados;
} pilha;

// Função para criar uma pilha
pilha *criar_pilha(int tamanho) {
    pilha *p = (pilha *) malloc(sizeof(pilha));                 // Aloca memória para a pilha
    p->topo = -1;                                               // Inicializa o topo da pilha
    p->tamanho = tamanho;                                       // Inicializa o tamanho da pilha
    p->dados = (void **) malloc(tamanho * sizeof(void *));      // Aloca memória para os dados da pilha
    return p;

}

// Função para empilhar um elemento na pilha
void push_p(pilha *p, void *elemento) {
    if (p->topo == p->tamanho - 1) {                            // Verifica se a pilha está cheia
        printf("Pilha cheia! Não é possível empilhar o elemento %d na pilha. \n", elemento);
        return;
    }
    p->topo++;                                                  // Incrementa o topo da pilha
    p->dados[p->topo] = elemento;                               // Empilha o elemento

}

// Função para desempilhar um elemento da pilha
void *pop_p(pilha *p) {
    if (p->topo == -1) {                                        // Verifica se a pilha está vazia
        printf("Pilha vazia! Não é possível desempilhar um elemento. \n");
        return NULL;
    }
    void *elemento = p->dados[p->topo];                         // Desempilha o elemento
    p->topo--;                                                  // Decrementa o topo da pilha
    return elemento;

}

// Função para dar peek no elemento do topo da pilha
void *peek_p(pilha *p) {
    if (p->topo == -1) {                                        // Verifica se a pilha está vazia
        printf("Pilha vazia! Não é possível dar peek no elemento do topo da pilha. \n");
        return NULL;
    }
    return p->dados[p->topo];                                   // Retorna o elemento do topo da pilha

}

// Função para imprimir os elementos da pilha
void imprimir_pilha(pilha *p) {
    if (p->topo == -1) {                                        // Verifica se a pilha está vazia
        printf("Pilha vazia! Não é possível imprimir os elementos da pilha. \n");
        return;
    }
    printf("Pilha: [ ");
    for (int i = 0; i <= p->topo; i++) {
        printf("%d ", p->dados[i]);
    }
    printf("] \n");

}

// Função para liberar a memória alocada para a pilha
void liberar_pilha(pilha *p) {
    free(p->dados);                                             // Libera a memória alocada para os dados da pilha
    free(p);                                                    // Libera a memória alocada para a pilha

}

// Função principal
int main() {
    pilha *p = criar_pilha(5);                                  // Cria uma pilha com capacidade para 5 elementos

    // 5 elementos são empilhados na pilha
    for(int i = 1; i <= 5; i++) {
        push_p(p, (int)i);
    }


    // imprimir os elementos da pilha com o pop
    printf("Desempilhando os elementos da pilha: \n");
    for(int i = 1; i <= 5; i++) {
        printf("%d ", pop_p(p));
    }

    // imprimir usando o peek
    printf(" \nImprimindo os elementos da pilha usando o peek: \n");
    for(int i = 1; i <= 5; i++) {
        push_p(p, i);
        printf("%d ", peek_p(p));
    }

    // imprimindo usando a função imprimir_pilha
    printf(" \nImprimindo os elementos da pilha usando a função imprimir_pilha: \n");
    imprimir_pilha(p);

    liberar_pilha(p);                                           // Libera a memória alocada para a pilha

    return 0;
}