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
    // struct arvn *numero_vertice; // aponta para o nó - nao precisa e nao consegui usar
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

// busca em largura - deixa o nivel de cada vertice - demorou so 3 horas pra fazer essa gambiarra 🐊🐊🐊🐊🐊🐊🐊🐊🐊🐊🐊🐊
ArvN *bfs(ArvN *arvore, int n) {
    Listad *fila = criar_lista();
    int nivel_atual = 0;
    arvore[0].nivel = 1;
    inserir_fim(fila, 1);

    // percorrer a arvore
    while (!eh_vazia(fila)) {
        int vertice = remover_inicio(fila); // remover da fila
        Nod *no_atual = arvore[vertice - 1].filhos->ini; // pegar os filhos do vertice

        // percorrer os filhos
        while (no_atual != NULL) {
            // se o vertice nao tiver nivel, setar o nivel dele
            arvore[no_atual->info - 1].nivel = arvore[vertice - 1].nivel + 1; // setar o nivel do vertice
            inserir_fim(fila, no_atual->info); // inserir na fila
            no_atual = no_atual->prox; // proximo filho
        }
    }
    limpar_lista(fila);
    return arvore;
    // return arvore[n].nivel; // retorna o nivel da arvore mas nao sei pq nao funciona
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

// imprime todos os niveis - melhor funçao que eu ja fiz na minha vida GIGAKEK
void imprimir_niveis(Listad **niveis, int n) {
    for (int i = 0; i < n; i++) {
        imprimir_lista(niveis[i]);
    }
}

// printar o ponteiro da arvore
void print_arvore(ArvN *arvore, int n) {
    for (int i = 0; i < n; i++) {
        printf("%p ", &arvore[i]);
    }
    printf("\n");
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

// percorrer os niveis da arvore
void percorrer_niveis(ArvN *arvore, int n) {
    int nivel = contar_nivel(arvore, n);
    for (int i = 0; i < nivel; i++) {
        for (int j = 0; j < n; j++) {
            if (arvore[j].nivel == i + 1) {
                printf("%d ", arvore[j].vertice);
            }
        }
        printf(" | ");
    }
    printf("\n");
}






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

        // array dinamico para guardar os filhos numero de vertices - 1
        int *filhos = (int *) malloc((numero_vertices - 1) * sizeof(int));

        // zerar filhos
        memset(filhos, 0, sizeof(filhos));

        // ler filhos
        for(int i = 0; i < numero_vertices - 1; i++){
            scanf("%d", &filhos[i]);
        }

        // inserir filhos na arvore
        for (int i = 0; i < numero_vertices - 1; i++) {
            adicionar_filhos (arvore, filhos[i], i+2);
        }

        // imprimir arvore
        // imprimir_arvore(arvore, numero_vertices);

        // bfs
        bfs(arvore, numero_vertices);
        // recebe o retorno de bfs
        ArvN *arvore_bfs = bfs(arvore, numero_vertices);

        // imprimir arvore bfs
        // imprimir_arvore(arvore_bfs, numero_vertices);

        // ler a quantidade de segundos
        int segundos = 0;

        // cada nivel da arvore é um segundo, e cada nivel com mais de 2 vertices é um segundo a mais
        // percorrer a arvore em niveis, cada nivel é um segundo, mas se o nivel tiver mais de 2 vertices, é um segundo a mais

        
        // percorrer os niveis da arvore
        for(int i = 0; i < contar_nivel(arvore, numero_vertices); i++){
            // percorrer a arvore
            for(int j = 0; j < numero_vertices; j++){
                // se o nivel do vertice for igual ao nivel atual
                if(arvore_bfs[j].nivel == i+1){
                    // isso aqui pode ser feito com um switch case ou com recursao
                    // se o vertice tiver mais de 2 filhos
                    if(arvore_bfs[j].qtd_filhos > 2){
                        // incrementar o tempo
                        segundos++;
                    }
                    // se o vertice tiver mais de 4 filhos
                    if(arvore_bfs[j].qtd_filhos > 4){
                        // incrementar o tempo
                        segundos++;
                    }
                    // se o vertice tiver mais de 6 filhos
                    if(arvore_bfs[j].qtd_filhos > 6){
                        // incrementar o tempo
                        segundos++;
                    }
                    // se o vertice tiver mais de 8 filhos
                    if(arvore_bfs[j].qtd_filhos > 8){
                        // incrementar o tempo
                        segundos++;
                    }
                }
            }
            // incrementar o tempo
            segundos++;
        }

        printf("%d\n", segundos);


        // desinfectar arvore
        desinfectar(arvore, numero_vertices);

        // limpar arvore
        limpar_arvore(arvore, numero_vertices);

        // free nos arrays
        free(filhos);
        
    }
    

    return 0;
}