#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct arvn {
    int numero; // numero do no
    int qtd; // quantidade de filhos
    bool infectado; // 0 - nao infectado, 1 - infectado
    struct lista *filhos; // lista de filhos
} ArvN;

typedef struct nod {
    struct arvn *info;
    struct nod *prox;
} Nod;

typedef struct lista {
    struct nod *ini;
    struct nod *fim;
    int tam;
} Listad;

void adiciona_lista(Listad *lista, ArvN *no) {
    Nod *novo_no = (Nod*) malloc(sizeof(Nod));
    novo_no->info = no;
    novo_no->prox = NULL;
    if (lista->fim == NULL) {
        lista->ini = novo_no;
    } else {
        lista->fim->prox = novo_no;
    }
    lista->fim = novo_no;
    lista->tam++;
}

void remove_lista(Listad *lista, ArvN *no) {
    Nod *no_atual = lista->ini;
    Nod *no_anterior = NULL;
    while (no_atual != NULL && no_atual->info != no) {
        no_anterior = no_atual;
        no_atual = no_atual->prox;
    }
    if (no_atual == NULL) {
        return;
    }
    if (no_anterior == NULL) {
        lista->ini = no_atual->prox;
    } else {
        no_anterior->prox = no_atual->prox;
    }
    if (no_atual->prox == NULL) {
        lista->fim = no_anterior;
    }
    free(no_atual);
    lista->tam--;
}

// criar lista
Listad *criar_lista() {
    Listad *lista = (Listad*) malloc(sizeof(Listad));
    lista->ini = NULL;
    lista->fim = NULL;
    lista->tam = 0;
    return lista;
}

// cria uma arvore com um no
ArvN *criar_arvore(int numero) {
    ArvN *arvore = (ArvN*) malloc(sizeof(ArvN));
    arvore->numero = numero;
    arvore->qtd = 0;
    arvore->infectado = false;
    arvore->filhos = (Listad*) malloc(sizeof(Listad));
    arvore->filhos->ini = NULL;
    arvore->filhos->fim = NULL;
    arvore->filhos->tam = 0;
    return arvore;
}


// insere un no na arvore v2
void inserir(ArvN *arvore, int pai, int filho) {
    
    if (pai == filho) {
        // Evita adicionar o nó pai como filho de si mesmo
        return;
    }

    ArvN *no_pai = NULL;
    ArvN *no_filho = NULL;
    // Nod *no_atual = arvore->filhos->ini;
    Nod *no_atual = arvore->filhos ? arvore->filhos->ini : NULL;

    // procura o no pai e o no filho
    while (no_atual != NULL && (no_pai == NULL || no_filho == NULL)) {
        if (no_atual->info->numero == pai) {
            no_pai = no_atual->info;
        }
        if (no_atual->info->numero == filho) {
            no_filho = no_atual->info;
        }
        no_atual = no_atual->prox;
    }

    // se nao encontrou o no pai ou o no filho, cria um novo no
    if (no_pai == NULL) {
        no_pai = criar_arvore(pai);
        adiciona_lista(arvore->filhos, no_pai);
    }

    // se nao encontrou o no filho, cria um novo no
    if (no_filho == NULL) {
        no_filho = criar_arvore(filho);
        adiciona_lista(arvore->filhos, no_filho);
    }
    // adiciona o no filho na lista de filhos do no pai
    adiciona_lista(no_pai->filhos, no_filho);
    no_pai->qtd++;
}

// inserir filho
void inserir_filho(ArvN *arvore, int filho) {
    ArvN *no_filho = NULL;
    Nod *no_atual = arvore->filhos->ini;
    // procura o no filho
    while (no_atual != NULL && no_filho == NULL) {
        if (no_atual->info->numero == filho) {
            no_filho = no_atual->info;
        }
        no_atual = no_atual->prox;
    }
    // se nao encontrou o no filho, cria um novo no
    if (no_filho == NULL) {
        no_filho = criar_arvore(filho);
        adiciona_lista(arvore->filhos, no_filho);
    }
    no_filho->qtd++;
}

// 2 3 4 5 6 7 (vertices)
// 1 1 1 2 2 4 (2 é filho de 1, 3 é filho de 1, 4 é filho de 1, 5 é filho de 2, 6 é filho de 2, 7 é filho de 4)
// adiciona os filhos na arvore
void adiciona_filhos(ArvN *arvore, int *vertices, int *filhos, int n) {
    for (int i = 0; i < n; i++) {
        inserir(arvore, filhos[i], vertices[i]);
    }
}

// busca em largura (BFS) na árvore.
// A ideia é iniciar a busca pelo nó raiz e, em seguida, explorar seus filhos em ordem, inserindo-os em uma fila e marcando-os como visitados. 
// Em seguida, repita o processo para cada nó na fila até que todos os nós sejam visitados.
// BFS v3
int bfs(ArvN *raiz, int tempo_max, int n) {
    int tempo_atual = 0;
    int infectados = 0;
    Listad *lista = criar_lista();
    adiciona_lista(lista, raiz);
    while (lista->tam > 0 && tempo_atual <= tempo_max) {
        Nod *no_atual = lista->ini;
        while (no_atual != NULL) {
            ArvN *no = no_atual->info;
            if (no->infectado == false) {
                no->infectado = true;
                infectados++;
                tempo_atual = no->qtd;
            }
            Nod *no_filho = no->filhos->ini;
            while (no_filho != NULL) {
                ArvN *filho = no_filho->info;
                if (filho->infectado == false) {
                    adiciona_lista(lista, filho);
                    filho->qtd = no->qtd + 1;
                }
                no_filho = no_filho->prox;
            }
            no_atual = no_atual->prox;
            remove_lista(lista, no);
        }
    }
    return infectados;
}

// printar a arvore
void printar_arvore(ArvN *arvore) {
    if (arvore != NULL) {
        printf("%d ", arvore->numero);
        Nod *no_atual = arvore->filhos->ini;
        while (no_atual != NULL) {
            printar_arvore(no_atual->info);
            no_atual = no_atual->prox;
        }
    }
}

// libera a lista
void liberar_lista(Listad *lista) {
    if (lista != NULL) {
        Nod *no_atual = lista->ini;
        while (no_atual != NULL) {
            Nod *no = no_atual;
            no_atual = no_atual->prox;
            free(no);
        }
        free(lista);
    }
}

// libera a arvore
void liberar_arvore(ArvN *arvore) {
    if (arvore != NULL) {
        Nod *no_atual = arvore->filhos->ini;
        while (no_atual != NULL) {
            liberar_arvore(no_atual->info);
            no_atual = no_atual->prox;
        }
        liberar_lista(arvore->filhos);
        free(arvore);
    }
}

/* 
input:
1
7
1 1 1 2 2 4
expected output:
4

desenho da arvore:
      1
    / | \
  2   3  4
 /\      |
5  6     7

porque a arvore tem 7 vertices
começando do 1, o 1 tem 3 filhos, o 2 tem 2 filhos, o 4 tem 1 filho
e a paternidade e definida
1 1 1 2 2 4
2 3 4 5 6 7

///////////////////////////
input:
1
5
5 5 1 4
expected output:
4

desenho da arvore:
    1
     \
      4
       \
        5
       / \
      2  3

porque a arvore tem 5 vertices
começando do 1, o 1 tem 1 filho, o 4 tem 1 filho, o 5 tem 2 filhos
e a paternidade e definida
5 5 1 4
2 3 4 5

 */


int main() {
    // 1665C - Infection Tree (https://codeforces.com/contest/1665/problem/C)
    
    int numero_testes;
    scanf("%d", &numero_testes);
    while (numero_testes--) {
        int numero_vertices = 0;
        int tempo_max = 0;

        // lendo o numero de vertices
        scanf("%d", &numero_vertices);

        // tempo max é o ceil(numero_vertices / 2.0);
        tempo_max = ceil(numero_vertices/2.0);

        // criando a arvore
        // ArvN *arvore = (ArvN*) malloc(sizeof(ArvN));
        // primeiro no da arvore sempre é o no raiz que é o no 1
        ArvN *arvore = criar_arvore(1);
    
        // lendo a arvore a partir do no 2 porque o no 1 ja foi criado como raiz
        for (int i = 2; i <= numero_vertices; i++) {
            // 2 3 4 5 6 7 (vertices)
            // 1 1 1 2 2 4 (2 é filho de 1, 3 é filho de 1, 4 é filho de 1, 5 é filho de 2, 6 é filho de 2, 7 é filho de 4)

            // lendo o pai do no i
            int pai = 0;
            scanf("%d", &pai);

            // adicionando o no i como filho do no pai
            // adiciona_filhos(arvore, pai, i);
            inserir(arvore, pai, i);

                        int pai;
            scanf("%d", &pai);
            inserir_filho(arvore, pai);
            printf("pai: %d, filho: %d \n", pai, i);


        }
        
        

        // printando a arvore
        printf("\narvore: ");
        printar_arvore(arvore);
        printf("\n");

        // bfs
        int infectados = bfs(arvore, tempo_max, numero_vertices);

        printf("%d\n", infectados + 1);

        // liberando a arvore
        liberar_arvore(arvore);
        


    }

    return 0;
}
        