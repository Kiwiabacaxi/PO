/* 
exemplo de infecção na arvore do exemplo 
7
1 1 1 2 2 4

      1
    / | \
    2  3  4
    / \    |
    5  6   7

vertice 2, Injection (1º segundo)

vertice 5, Injection (2º segundos)
vertice 3, spread    (2º segundos)

vertice 7, Injection (3º segundos)
vertice 6, spread    (3º segundos)
vertice 4, spread    (3º segundos)

vertice 1, Injection (4º segundos)


A tree is a connected graph without cycles. A rooted tree has a special vertex called the root. The parent of a vertex v (different from root) is the previous to v vertex on the shortest path from the root to the vertex v. Children of the vertex v are all vertices for which v

is the parent.

You are given a rooted tree with n
vertices. The vertex 1

is the root. Initially, all vertices are healthy.

Each second you do two operations, the spreading operation and, after that, the injection operation:

    Spreading: for each vertex v

, if at least one child of v is infected, you can spread the disease by infecting at most one other child of v

    of your choice.
    Injection: you can choose any healthy vertex and infect it. 

This process repeats each second until the whole tree is infected. You need to find the minimal number of seconds needed to infect the whole tree.
Input

The input consists of multiple test cases. The first line contains a single integer t
(1≤t≤104

) — the number of test cases. Description of the test cases follows.

The first line of each test case contains a single integer n
(2≤n≤2⋅105

) — the number of the vertices in the given tree.

The second line of each test case contains n−1
integers p2,p3,…,pn (1≤pi≤n), where pi is the ancestor of the i

-th vertex in the tree.

It is guaranteed that the given graph is a tree.

It is guaranteed that the sum of n
over all test cases doesn't exceed 2⋅105

.
Output

For each test case you should output a single integer — the minimal number of seconds needed to infect the whole tree.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef struct nod {
    struct arvn *numero_vertice; // aponta para o nó
    int info;
    struct nod *ant;
    struct nod *prox;
} Nod;

    
typedef struct listad{
    Nod *ini;
    Nod *fim;
    int tam;
} Listad;

typedef struct arvn {
    int vertice; // 1 2 3 4 5 6 7 8 9 10... , 1 = raiz
    // aponta para os seus filhos
    

    int qtd_filhos; // quantidade de filhos
    bool infectado; // se estiver infectado 0 = não, 1 = sim, apenas infectados podem dar spread
    int nivel; // qual o nivel que ele esta
    Listad *filhos; // aponta para a lista
} ArvN;

// criar lista
Listad *criar_lista() {
    Listad *lista = (Listad*) malloc(sizeof(Listad));
    lista->ini = NULL;
    lista->fim = NULL;
    lista->tam = 0;
    return lista;
}

// criar no
Nod *criar_no(int info) {
    Nod *no = (Nod*) malloc(sizeof(Nod));
    no->info = info;
    no->ant = NULL;
    no->prox = NULL;
    return no;
}

// inserir no inicio
void inserir_inicio(Listad *lista, int info) {
    Nod *no = criar_no(info);
    if (lista->ini == NULL) {
        lista->fim = no;
    } else {
        lista->ini->ant = no;
    }
    no->prox = lista->ini;
    lista->ini = no;
    lista->tam++;
}

// inserir no fim
void inserir_fim(Listad *lista, int info) {
    Nod *no = criar_no(info);
    if (lista->fim == NULL) {
        lista->ini = no;
    } else {
        lista->fim->prox = no;
    }
    no->ant = lista->fim;
    lista->fim = no;
    lista->tam++;
}

// inserir na lista a partir de um vetor
void inserir_lista(Listad *lista, int *vetor, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        inserir_fim(lista, vetor[i]);
    }
}

// remover no inicio
int remover_inicio(Listad *lista) {
    if (lista->ini == NULL) {
        return -1;
    }
    Nod *no = lista->ini;
    int info = no->info;
    if (lista->ini == lista->fim) {
        lista->fim = NULL;
    } else {
        lista->ini->prox->ant = NULL;
    }
    lista->ini = lista->ini->prox;
    free(no);
    lista->tam--;
    return info;
}

// remover no fim
int remover_fim(Listad *lista) {
    if (lista->fim == NULL) {
        return -1;
    }
    Nod *no = lista->fim;
    int info = no->info;
    if (lista->ini == lista->fim) {
        lista->ini = NULL;
    } else {
        lista->fim->ant->prox = NULL;
    }
    lista->fim = lista->fim->ant;
    free(no);
    lista->tam--;
    return info;
}

// eh vazia
bool eh_vazia(Listad *lista) {
    return lista->ini == NULL;
}

// limpar lista
void limpar_lista(Listad *lista) {
    Nod *no_atual = lista->ini;
    Nod *no_proximo = NULL;
    while (no_atual != NULL) {
        no_proximo = no_atual->prox;
        free(no_atual);
        no_atual = no_proximo;
    }
    lista->ini = NULL;
    lista->fim = NULL;
    lista->tam = 0;
}

// imprimir lista
void imprimir_lista(Listad *lista) {
    Nod *no_atual = lista->ini;
    while (no_atual != NULL) {
        printf("%d ", no_atual->info);
        no_atual = no_atual->prox;
    }
    printf("\n");
}

// -----------------// arvore // ----------------- //

// criar arvore
ArvN *criar_arvore(int numero_vertices) {
    ArvN *arvore = (ArvN*) malloc(sizeof(ArvN) * numero_vertices);
    for (int i = 0; i < numero_vertices; i++) {
        arvore[i].vertice = i + 1;
        arvore[i].qtd_filhos = 0;
        arvore[i].infectado = false;
        arvore[i].nivel = 0;
        arvore[i].filhos = criar_lista();
    }
    return arvore;
}

// adicionar filhos
void adicionar_filhos(ArvN *arvore, int pai, int filho) {
/*     // ordenar - pai sempre menor que filho
    if (pai > filho) {
        int aux = pai;
        pai = filho;
        filho = aux;
    } */
    // adicionar

    inserir_fim(arvore[pai - 1].filhos, filho);
    arvore[pai - 1].qtd_filhos++;
}

// busca na arvore
void busca_arvore(ArvN *arvore, int numero_vertices, int nivel) {
    for (int i = 0; i < numero_vertices; i++) {
        if (arvore[i].nivel == nivel) {
            printf("%d ", arvore[i].vertice);
        }
    }
    printf("\n");
}

// imprimir arvore
void imprimir_arvore(ArvN *arvore, int numero_vertices) {
    for (int i = 0; i < numero_vertices; i++) {
        printf("vertice: %d, qtd_filhos: %d, infectado: %d, nivel: %d, filhos: ", arvore[i].vertice, arvore[i].qtd_filhos, arvore[i].infectado, arvore[i].nivel);
        imprimir_lista(arvore[i].filhos);
    }
}

// limpar arvore
void limpar_arvore(ArvN *arvore, int numero_vertices) {
    for (int i = 0; i < numero_vertices; i++) {
        limpar_lista(arvore[i].filhos);
    }
    free(arvore);
}

// contar infectados
int contar_infectados(ArvN *arvore, int numero_vertices) {
    int infectados = 0;
    for (int i = 0; i < numero_vertices; i++) {
        if (arvore[i].infectado) {
            infectados++;
        }
    }
    return infectados;
}

// contar filhos
int contar_filhos(ArvN *arvore, int numero_vertices) {
    int filhos = 0;
    for (int i = 0; i < numero_vertices; i++) {
        filhos += arvore[i].qtd_filhos;
    }
    return filhos;
}

// contar nivel
int contar_nivel(ArvN *arvore, int numero_vertices) {
    int nivel = 0;
    for (int i = 0; i < numero_vertices; i++) {
        if (arvore[i].nivel > nivel) {
            nivel = arvore[i].nivel;
        }
    }
    return nivel;
}

// busca em largura - deixa o nivel de cada vertice - demorou so 3 horas pra fazer essa porra 🐊🐊🐊🐊🐊🐊🐊🐊🐊🐊🐊🐊
ArvN *bfs(ArvN *arvore, int n) {
    Listad *fila = criar_lista();
    int nivel_atual = 0;
    arvore[0].nivel = 1;
    inserir_fim(fila, 1);

    while (!eh_vazia(fila)) {
        int vertice = remover_inicio(fila);
        Nod *no_atual = arvore[vertice - 1].filhos->ini;
        while (no_atual != NULL) {
            arvore[no_atual->info - 1].nivel = arvore[vertice - 1].nivel + 1;
            inserir_fim(fila, no_atual->info);
            no_atual = no_atual->prox;
        }
    }
    limpar_lista(fila);
    return arvore;
    // return arvore[n].nivel;
}

// desinfectar a arvore
void desinfectar(ArvN *arvore, int n) {
    for (int i = 0; i < n; i++) {
        arvore[i].infectado = false;
    }
}

// infecta a arvore toda
void infectar_arvore_toda(ArvN *arvore, int n) {
    for (int i = 0; i < n; i++) {
        arvore[i].infectado = true;
    }
}

// get lista do vertice com mais filhos
Listad *get_lista_mais_filhos(ArvN *arvore, int n) {
    int mais_filhos = 0;
    int vertice = 0;
    for (int i = 0; i < n; i++) {
        if (arvore[i].qtd_filhos > mais_filhos) {
            mais_filhos = arvore[i].qtd_filhos;
            vertice = i;
        }
    }
    return arvore[vertice].filhos;
}

// separa todos os niveis em listas
Listad **separar_niveis(ArvN *arvore, int n) {
    int nivel = contar_nivel(arvore, n);
    Listad **niveis = (Listad **) malloc(nivel * sizeof(Listad *));
    for (int i = 0; i < nivel; i++) {
        niveis[i] = criar_lista();
    }
    for (int i = 0; i < n; i++) {
        inserir_fim(niveis[arvore[i].nivel - 1], arvore[i].vertice);
    }
    return niveis;
}

// imprime todos os niveis
void imprimir_niveis(Listad **niveis, int n) {
    for (int i = 0; i < n; i++) {
        imprimir_lista(niveis[i]);
    }
}


// find the level with the most nodes
int get_level_with_most_nodes(ArvN *arvore, int n) {
    int nivel = contar_nivel(arvore, n);
    int *qtd_nos = (int *) malloc(nivel * sizeof(int));
    for (int i = 0; i < nivel; i++) {
        qtd_nos[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        qtd_nos[arvore[i].nivel - 1]++;
    }
    int maior = 0;
    int nivel_maior = 0;
    for (int i = 0; i < nivel; i++) {
        if (qtd_nos[i] > maior) {
            maior = qtd_nos[i];
            nivel_maior = i;
        }
    }
    return nivel_maior;
}

// -----------------// :?::::???? // ----------------- //

/* 
ex1:
1
7
1 1 1 2 2 4
[3,2,1]
*/

// retornar o numero de filho de cada vertice em um array
int *get_qtd_filhos(ArvN *arvore, int n) {
    int *qtd_filhos = (int *) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        qtd_filhos[i] = arvore[i].qtd_filhos;
    }
    return qtd_filhos;
}

// transformar a arvore em um array de inteiro
int *arvore_para_array(ArvN *arvore, int n) {
    int *array = (int *) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        array[i] = arvore[i].vertice;
    }
    return array;
}

// retorna o maior valor de um array
int max(int x, int y){
    // se x for maior que y, retorna x
    if(x > y){
        return x;
    }
    // se não, retorna y
    return y;
}

// cmp
int cmp(const void *a, const void *b) {
    return (*(int *) a - *(int *) b);
}

// cmp reverso
int cmp_reverse(const void *a, const void *b) {
    return (*(int *) b - *(int *) a);
}

// imprimir array de forma [] separado por espaço
void imprimir_array(int *array, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", array[i]);
        if (i != n - 1) {
            printf(" "); // simbolo que separa os elementos
        }
    }
    printf("]\n");
}

#define SIZE 200000


/* 
loop de testes
    ler numero de vertices
    criar arvore
    ler filhos
    bfs
    infectar
    tempo minimo para infectar todos
    limpar arvore

*/

        /* 
        Logica para infectar:
            * tipos de infecção
                - injecao = acontece uma vez por segundo em todos segundos sem exceção
                - espalhamento = acontece uma vez por segundo para cada vertice infectado no segundo anterior
            * infectar
                - infectar um vertice de um nivel
                - espalhar para os filhos de um nivel abaixo ou no mesmo nivel
                - se o vertice de origem estiver infectado espalha para UM filho

            * tempo minimo para infectar todos
                - percorrer a arvore ate todos os vertices estiverem infectados
                - percorrer a arvore por niveis, infectar um vertice de cada nivel e espalhar para os filhos
                - se o vertice de origem estiver infectado espalha para UM filho
                - incrementar o tempo

            * tempo minimo usando a recursao
                - primeiro segundo - pode infectar 1 vertice
                - segundo segundo - pode infectar 1 vertice e espalhar para um filho de um nivel abaixo ou no mesmo nivel
                - n segundos - pode infectar 1 vertice e espalhar para n filhos de um nivel abaixo ou no mesmo nivel

                - quando todos os vertices estiverem infectados retorna o tempo

                - percorrer a arvore ate todos os vertices estiverem infectados
                - percorrer a arvore por niveis, infectar um vertice de cada nivel e espalhar para os filhos
                - se o vertice de origem estiver infectado espalha para UM filho
                - incrementar o tempo
        */

int main() {
    // 1665C - Infection Tree (https://codeforces.com/contest/1665/problem/C)
    
    // numero de testes
    int numero_testes;
    scanf("%d", &numero_testes);

    // loop de testes
    while(numero_testes--){

        // numero de vertices
        int numero_vertices;
        scanf("%d", &numero_vertices);
        

        // criar arvore e a raiz é 1
        ArvN *arvore = criar_arvore(numero_vertices);

        // array para guardar os filhos numero de vertices - 1
        // int filhos[numero_vertices-1];
        int vetor[20000];

        // array dinamico para guardar os filhos numero de vertices - 1
        int *filhos = (int *) malloc((numero_vertices - 1) * sizeof(int));
        // int *vetor = (int *) malloc((numero_vertices - 1) * sizeof(int));
        // int *vetor = (int *) malloc((20000) * sizeof(int));

        int aux = 0;

        // zerar filhos
        memset(filhos, 0, sizeof(filhos));
        memset(vetor, 0, sizeof(vetor));


        // ler os filhos
        for(int i = 1; i < numero_vertices; i++){
            int filho;
            scanf("%d", &filho);
            // volta uma posição no index
            filhos[i-1] = filho;
            //printf("filhos[%d] = %d \n", i-1, filhos[i-1]);

            // se o filho não tiver sido lido ainda, incrementa o aux
            if(vetor[filho-1] == 0){
                aux++;
            }
            // incrementa o vetor
            vetor[filho-1]++;
        }

        //qsort(filhos, numero_vertices - 1, sizeof(int), cmp_reverse);
        qsort(vetor, numero_vertices, sizeof(int), cmp_reverse);
        // printf("filhos ordenados: ");
        // imprimir_array(filhos, numero_vertices - 1);

        // adicionar filhos na arvore
        for (int i = 0; i < numero_vertices - 1; i++) {
            //printf("filhos[%d] = %d\n", i, filhos[i]);
            adicionar_filhos(arvore, filhos[i], i + 2);

        }

        // bfs
        //bfs(arvore, numero_vertices);
        // recebe o retorno de bfs
        //ArvN *arvore_bfs = bfs(arvore, numero_vertices);

        int maior = 0;
        int index_maior = 0;
        int len = 0;
        int resposta = 0;

        // printf("\nPRIMEIRA VERIFICA: ");
        for(int i = 0; i < numero_vertices; i++){
            // se o numero de filhos for maior que 0
            if(vetor[i] > 0) {
                // o certo e -= aux - i, porque ele vale pra casos extremos
                vetor[i] -= aux -i; // (aux -1 = erro em caso grande d+)diminui o numero de filhos do parente
            
                vetor[i] = max(0, vetor[i]); // se o numero de filhos for menor que 0, ele vira 0

                resposta++; // incrementa a resposta
            
                if(vetor[i] > maior){ // se o numero de filhos for maior que o maior
                    maior = vetor[i]; // o maior recebe o numero de filhos
                    index_maior = i; // o index do maior recebe o index do numero de filhos
                
                }
            }
            len++;
        }
/* 
        // primeira verificação com filhos, faz igual ao de cima mas com filhos
        for (int i = 0; i < numero_vertices - 1; i++) {
            // se o numero de filhos for maior que 0
            if(filhos[i] > 0) {
                // o certo e -= aux - i, porque ele vale pra casos extremos
                filhos[i] -= aux -i; // (aux -1 = erro em caso grande d+)diminui o numero de filhos do parente
            
                filhos[i] = max(0, filhos[i]); // se o numero de filhos for menor que 0, ele vira 0

                resposta++; // incrementa a resposta
            
                if(filhos[i] > maior){ // se o numero de filhos for maior que o maior
                    maior = filhos[i]; // o maior recebe o numero de filhos
                    index_maior = i; // o index do maior recebe o index do numero de filhos
                
                }
            }
            len++;
        }
 */

        // printf("maior = %d index_maior = %d len = %d resposta = %d \n", maior, index_maior, len, resposta);

        qsort(vetor, numero_vertices, sizeof(int), cmp_reverse);

        // get nivel
        //int nivel = contar_nivel(arvore, numero_vertices);

        // printf("\nSEGUNDA VERIFICA: ");
        while(maior > 0) {
            maior = 0;  // zera o maior numero de filhos
            index_maior = 0;    // zera o indice do maior numero de filhos

            // loop para percorrer o vetor
            for(int i = 0; i < len; i++) {

                // se o numero de filhos for maior que 0
                if(vetor[i] > 0) {
                    vetor[i]--; // diminui o numero de filhos

                    // se o numero de filhos for maior que o maior numero de filhos
                    if(vetor[i] > maior) {
                        maior = vetor[i]; // atualiza o maior numero de filhos
                        index_maior = i; // atualiza o indice do maior numero de filhos
                    }
                }
            }

            // se o maior numero de filhos for maior que 0
            if(maior > 0) {
                maior--;    // diminui o maior numero de filhos
                vetor[index_maior]--;   // diminui o numero de filhos do indice do maior numero de filhos
                resposta++;     // aumenta o numero de segundos
            }
        }

        // segunda verificação com filhos, faz igual ao de cima mas com filhos
/*         while(maior > 0) {
            maior = 0;  // zera o maior numero de filhos
            index_maior = 0;    // zera o indice do maior numero de filhos

            // loop para percorrer o vetor
            for(int i = 0; i < len; i++) {

                // se o numero de filhos for maior que 0
                if(filhos[i] > 0) {
                    filhos[i]--; // diminui o numero de filhos

                    // se o numero de filhos for maior que o maior numero de filhos
                    if(filhos[i] > maior) {
                        maior = filhos[i]; // atualiza o maior numero de filhos
                        index_maior = i; // atualiza o indice do maior numero de filhos
                    }
                }
            }

            // se o maior numero de filhos for maior que 0
            if(maior > 0) {
                maior--;    // diminui o maior numero de filhos
                filhos[index_maior]--;   // diminui o numero de filhos do indice do maior numero de filhos
                resposta++;     // aumenta o numero de segundos
            }
        } */




        // get quantidade de niveis - aux
        // int quantidade_de_niveis = contar_nivel(arvore_bfs, numero_vertices);
        // //printf("quantidade_de_niveis: %d\n", quantidade_de_niveis);
        // //printf("aux = %d\n", aux);

        // // get qnt de filhos
        // int *qtd_filhos = get_qtd_filhos(arvore, numero_vertices);
        // ordenar o array de forma decrescente
        // qsort(qtd_filhos, numero_vertices, sizeof(int), cmp_reverse);
        

        // imprimir_array(qtd_filhos, numero_vertices);

/* 
        quantidade_de_niveis: 3 
        aux 3 
        Vetor2: 3 2 1 0 0 0 0 
        resposta:4

        quantidade de niveis 3 
        aux 3 
        Vetor2: 2 1 1 0 0 
        resposta:4

        quantidade de niveis 1 
        aux 1 
        Vetor2: 1 0 
        resposta:2

        quantidade de niveis 3
        aux 2
        Vetor2: 1 1 0 
        resposta:3

        quantidade de niveis 2 
        aux 1 
        Vetor2: 5 0 0 0 0 0 
        resposta:4 
*/

/* 
aux 3 
Vetor2: 3 2 1 0 0 0 0 
resposta:4

aux 3 
Vetor2: 2 1 1 0 0 
resposta:4

aux 1 
Vetor2: 1 0 
resposta:2

aux 2 
Vetor2: 1 1 0 
resposta:3

aux 1 
Vetor2: 5 0 0 0 0 0 
resposta:4
 
*/

/* 
        qtd_filhos: 3 2 1 0 0 0 0 
        resposta:4

        qtd_filhos: 2 1 1 0 0 
        resposta:4

        qtd_filhos: 1 0 
        resposta:2

        qtd_filhos: 1 1 0 
        resposta:3

        qtd_filhos: 5 0 0 0 0 0 
        resposta:4

        3 2 0 1 0 0 0 
        1 0 0 1 2 
        1 0 
        1 0 1 
        5 0 0 0 0 0
        
*/





        // imprimir todos os niveis
        // Listad **niveis = separar_niveis(arvore, numero_vertices);
        // imprimir_niveis(niveis, contar_nivel(arvore, numero_vertices));
        // printf("\n");


        // imprimir arvore
        // imprimir_arvore(arvore, numero_vertices);
        // printf("\n\n");

        printf("%d\n", resposta+1);
        
        // desinfectar arvore
        desinfectar(arvore, numero_vertices);

        // limpar arvore
        limpar_arvore(arvore, numero_vertices);

        // free nos arrays
        free(filhos);
        //free(vetor);
    }
    

    return 0;
}