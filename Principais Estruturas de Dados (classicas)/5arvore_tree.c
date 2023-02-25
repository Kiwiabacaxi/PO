#include <stdlib.h>
#include <stdio.h>

// Definição de uma árvore binária de busca
typedef struct arvore {
    int dado;
    struct arvore *esq;
    struct arvore *dir;
} arvore;

// Função para criar uma árvore binária de busca
arvore *criar_arvore() {
    return NULL;
}

// Função para inserir um elemento na árvore binária de busca
arvore *inserir_arvore(arvore *a, int elemento) {
    if (a == NULL) {                                             // Verifica se a árvore está vazia
        a = (arvore *) malloc(sizeof(arvore));                   // Aloca memória para a árvore
        a->dado = elemento;                                      // Inicializa o dado da árvore
        a->esq = NULL;                                           // Inicializa a subárvore esquerda da árvore
        a->dir = NULL;                                           // Inicializa a subárvore direita da árvore
    } else if (elemento < a->dado) {                             // Verifica se o elemento é menor que o dado da árvore
        a->esq = inserir_arvore(a->esq, elemento);               // Insere o elemento na subárvore esquerda da árvore
    } else if (elemento > a->dado) {                             // Verifica se o elemento é maior que o dado da árvore
        a->dir = inserir_arvore(a->dir, elemento);               // Insere o elemento na subárvore direita da árvore
    }
    return a;
}

// Função para imprimir uma árvore binária de busca
// Pre Order
void pre_order(arvore *a) {
    if (a != NULL) {                                             // Verifica se a árvore não está vazia
        printf("%d ", a->dado);                                  // Imprime o dado da árvore
        pre_order(a->esq);                                       // Imprime a subárvore esquerda da árvore
        pre_order(a->dir);                                       // Imprime a subárvore direita da árvore
    }
}

// In Order
void in_order(arvore *a) {
    if (a != NULL) {                                             // Verifica se a árvore não está vazia
        in_order(a->esq);                                        // Imprime a subárvore esquerda da árvore
        printf("%d ", a->dado);                                  // Imprime o dado da árvore
        in_order(a->dir);                                        // Imprime a subárvore direita da árvore
    }
}

// Post Order
void post_order(arvore *a) {
    if (a != NULL) {                                             // Verifica se a árvore não está vazia
        post_order(a->esq);                                      // Imprime a subárvore esquerda da árvore
        post_order(a->dir);                                      // Imprime a subárvore direita da árvore
        printf("%d ", a->dado);                                  // Imprime o dado da árvore
    }
}

// Função para buscar um elemento na árvore binária de busca
arvore *buscar_arvore(arvore *a, int elemento) {
    if (a == NULL) {                                             // Verifica se a árvore está vazia
        return NULL;                                             // Retorna NULL
    } else if (elemento < a->dado) {                             // Verifica se o elemento é menor que o dado da árvore
        return buscar_arvore(a->esq, elemento);                  // Busca o elemento na subárvore esquerda da árvore
    } else if (elemento > a->dado) {                             // Verifica se o elemento é maior que o dado da árvore
        return buscar_arvore(a->dir, elemento);                  // Busca o elemento na subárvore direita da árvore
    } else {
        return a;                                                // Retorna a árvore
    }
}

// Função para buscar o menor elemento da árvore binária de busca
arvore *menor_arvore(arvore *a) {
    if (a == NULL) {                                             // Verifica se a árvore está vazia
        return NULL;                                             // Retorna NULL
    } else if (a->esq == NULL) {                                 // Verifica se a subárvore esquerda da árvore é NULL
        return a;                                                // Retorna a árvore
    } else {
        return menor_arvore(a->esq);                             // Busca o menor elemento na subárvore esquerda da árvore
    }
}

// Função para buscar o maior elemento da árvore binária de busca
arvore *maior_arvore(arvore *a) {
    if (a == NULL) {                                             // Verifica se a árvore está vazia
        return NULL;                                             // Retorna NULL
    } else if (a->dir == NULL) {                                 // Verifica se a subárvore direita da árvore é NULL
        return a;                                                // Retorna a árvore
    } else {
        return maior_arvore(a->dir);                             // Busca o maior elemento na subárvore direita da árvore
    }
}

// Função para buscar o sucessor de um elemento da árvore binária de busca
arvore *sucessor_arvore(arvore *a, int elemento) {
    arvore *aux = buscar_arvore(a, elemento);                    // Busca o elemento na árvore
    if (aux == NULL) {                                           // Verifica se o elemento não foi encontrado
        return NULL;                                             // Retorna NULL
    } else if (aux->dir != NULL) {                               // Verifica se a subárvore direita da árvore não é NULL
        return menor_arvore(aux->dir);                           // Retorna o menor elemento da subárvore direita da árvore
    } else {
        arvore *p = a;                                           // Cria um ponteiro para a árvore
        arvore *s = NULL;                                        // Cria um ponteiro para o sucessor
        while (p != aux) {                                       // Enquanto o ponteiro não for o elemento
            if (aux->dado < p->dado) {                           // Verifica se o elemento é menor que o dado do ponteiro
                s = p;                                           // Atribui o ponteiro para o sucessor
                p = p->esq;                                      // Atribui a subárvore esquerda do ponteiro para o ponteiro
            } else {
                p = p->dir;                                      // Atribui a subárvore direita do ponteiro para o ponteiro
            }
        }
        return s;                                                // Retorna o sucessor
    }
}

// Função para buscar o antecessor de um elemento da árvore binária de busca
arvore *antecessor_arvore(arvore *a, int elemento) {
    arvore *aux = buscar_arvore(a, elemento);                    // Busca o elemento na árvore
    if (aux == NULL) {                                           // Verifica se o elemento não foi encontrado
        return NULL;                                             // Retorna NULL
    } else if (aux->esq != NULL) {                               // Verifica se a subárvore esquerda da árvore não é NULL
        return maior_arvore(aux->esq);                           // Retorna o maior elemento da subárvore esquerda da árvore
    } else {
        arvore *p = a;                                           // Cria um ponteiro para a árvore
        arvore *s = NULL;                                        // Cria um ponteiro para o antecessor
        while (p != aux) {                                       // Enquanto o ponteiro não for o elemento
            if (aux->dado > p->dado) {                           // Verifica se o elemento é maior que o dado do ponteiro
                s = p;                                           // Atribui o ponteiro para o antecessor
                p = p->dir;                                      // Atribui a subárvore direita do ponteiro para o ponteiro
            } else {
                p = p->esq;                                      // Atribui a subárvore esquerda do ponteiro para o ponteiro
            }
        }
        return s;                                                // Retorna o antecessor
    }
}

// Função para remover um elemento da árvore binária de busca
arvore *remover_arvore(arvore *a, int elemento) {
    if (a == NULL) {                                             // Verifica se a árvore está vazia
        return NULL;                                             // Retorna NULL
    } else if (elemento < a->dado) {                             // Verifica se o elemento é menor que o dado da árvore
        a->esq = remover_arvore(a->esq, elemento);               // Remove o elemento da subárvore esquerda da árvore
    } else if (elemento > a->dado) {                             // Verifica se o elemento é maior que o dado da árvore
        a->dir = remover_arvore(a->dir, elemento);               // Remove o elemento da subárvore direita da árvore
    } else {
        if (a->esq == NULL && a->dir == NULL) {                  // Verifica se a árvore é uma folha
            free(a);                                             // Libera a memória alocada para a árvore
            a = NULL;                                            // Retorna NULL
        } else if (a->esq == NULL) {                             // Verifica se a subárvore esquerda da árvore é NULL
            arvore *t = a;                                       // Cria um ponteiro temporário para a árvore
            a = a->dir;                                          // Atribui a subárvore direita da árvore para a árvore
            free(t);                                             // Libera a memória alocada para o ponteiro temporário
        } else if (a->dir == NULL) {                             // Verifica se a subárvore direita da árvore é NULL
            arvore *t = a;                                       // Cria um ponteiro temporário para a árvore
            a = a->esq;                                          // Atribui a subárvore esquerda da árvore para a árvore
            free(t);                                             // Libera a memória alocada para o ponteiro temporário
        } else {
            arvore *f = a->esq;                                  // Cria um ponteiro para a subárvore esquerda da árvore
            while (f->dir !=
                     NULL) {                                      // Percorre a subárvore esquerda da árvore até encontrar o maior elemento
                 f = f->dir;
                }
            a->dado = f->dado;                                   // Atribui o maior elemento da subárvore esquerda da árvore para o dado da árvore
            f->dado = elemento;                                  // Atribui o elemento para o dado do ponteiro para a subárvore esquerda da árvore
            a->esq = remover_arvore(a->esq, elemento);           // Remove o elemento da subárvore esquerda da árvore
        }
    }
    return a;
}

// Função que verifica se uma árvore binária de busca é vazia
int vazia_arvore(arvore *a) {
    return a == NULL;                                            // Retorna 1 se a árvore for vazia e 0 caso contrário
}

// Função para liberar a memória alocada para uma árvore binária de busca
void liberar_arvore(arvore *a) {
    if (a != NULL) {                                             // Verifica se a árvore não está vazia
        liberar_arvore(a->esq);                                  // Libera a memória alocada para a subárvore esquerda da árvore
        liberar_arvore(a->dir);                                  // Libera a memória alocada para a subárvore direita da árvore
        free(a);                                                 // Libera a memória alocada para a árvore
    }
}

// Função principal
int main() {
    arvore *a = criar_arvore();                                  // Cria uma árvore binária de busca
    a = inserir_arvore(a, 10);                                   // Insere o elemento 10 na árvore
    a = inserir_arvore(a, 5);                                    // Insere o elemento 5 na árvore
    a = inserir_arvore(a, 15);                                   // Insere o elemento 15 na árvore
    a = inserir_arvore(a, 3);                                    // Insere o elemento 3 na árvore
    a = inserir_arvore(a, 7);                                    // Insere o elemento 7 na árvore
    a = inserir_arvore(a, 12);                                   // Insere o elemento 12 na árvore
    a = inserir_arvore(a, 18);                                   // Insere o elemento 18 na árvore
    a = inserir_arvore(a, 1);                                    // Insere o elemento 1 na árvore
    a = inserir_arvore(a, 4);                                    // Insere o elemento 4 na árvore
    a = inserir_arvore(a, 6);                                    // Insere o elemento 6 na árvore
    a = inserir_arvore(a, 9);                                    // Insere o elemento 9 na árvore
    a = inserir_arvore(a, 11);                                   // Insere o elemento 11 na árvore
    a = inserir_arvore(a, 13);                                   // Insere o elemento 13 na árvore
    a = inserir_arvore(a, 16);                                   // Insere o elemento 16 na árvore
    a = inserir_arvore(a, 19);                                   // Insere o elemento 19 na árvore
    // Imprime a árvore
    in_order(a);
    printf("\n");

    a = remover_arvore(a, 10);                                   // Remove o elemento 10 da árvore
    in_order(a);                                                 // Imprime a árvore
    printf("\n");

    a = remover_arvore(a, 5);                                    // Remove o elemento 5 da árvore
    in_order(a);                                                 // Imprime a árvore
    printf("\n");

    a = remover_arvore(a, 15);                                   // Remove o elemento 15 da árvore
    in_order(a);                                                 // Imprime a árvore
    printf("\n");

    // Busca o elemento 3 na árvore
    if (buscar_arvore(a, 3) != NULL) {
        printf("Elemento 3 encontrado na arvore a = %p e no no = %p \n", a, buscar_arvore(a, 3));
    } else {
        printf("Elemento 3 nao encontrado na arvore a = %p \n", a);
    }

    // Libera a memória alocada para a árvore
    liberar_arvore(a);

    return 0;
}
