/* Uma árvore é um grafo conexo sem ciclos. Uma árvore enraizada tem um vértice especial chamado raiz. O pai de um vértice v (diferente de raiz) é o vértice anterior a v no caminho mais curto da raiz ao vértice v. filhos do vértice v são todos os vértices para os quais v é o pai.

Você recebe uma árvore enraizada com n vértices. O vértice 1 é a raiz. Inicialmente, todos os vértices são saudáveis.

A cada segundo você faz duas operações, a operação de espalhamento e, depois disso, a operação de injeção:

    1- Espalhamento: para cada vértice v, se pelo menos um filho de v está infectado, você pode espalhar a doença infectando no máximo um outro filho de v da sua escolha.
    2 -Injeção: você pode escolher qualquer vértice saudável e infectá-lo.
    *********************** acontecem simultaneamente *******************************
Esse processo se repete a cada segundo até que toda a árvore esteja infectada. Você precisa encontrar o número mínimo de segundos necessários para infectar toda a árvore.

Entrada

A entrada consiste em vários casos de teste. 
A primeira linha contém um único inteiro t (1 ≤ t ≤ 104) — o número de casos de teste. Segue a descrição dos casos de teste.
A primeira linha de cada caso de teste contém um único inteiro n (2 ≤ n ≤ 2*105) — o número de vértices na árvore fornecida.
A segunda linha de cada caso de teste contém n – 1 inteiros p2, p3, …, pn (1 ≤ pi ≤n), onde pi é o ancestral do i-ésimo vértice na árvore.
É garantido que o grafo dado é uma árvore.
É garantido que a soma de n em todos os casos de teste não exceda 2*105.

Saída

Para cada caso de teste, você deve gerar um único inteiro — o número mínimo de segundos necessários para infectar toda a árvore.

Exemplo

entrada

5

7
1 1 1 2 2 4

5
5 5 1 4

2
1

3
3 1

6
1 1 1 1 1

saída

4
4
2
3
4

Observação

A imagem representa a árvore do primeiro caso de teste durante cada segundo.

Um vértice é preto se não estiver infectado. Um vértice é azul se for infectado por injeção durante o segundo anterior. 
Um vértice é verde se for infectado por propagação durante o segundo anterior. 
Um vértice é vermelho se for infectado antes do segundo anterior. 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// limite do inteiro
#define MAX_INT 250000


// maior valor entre dois inteiros
int max(int x, int y){
    // se x for maior que y, retorna x
    if(x > y){
        return x;
    }
    // se não, retorna y
    return y;
}

// cmpfunc para ordenar o vetor
int cmpfunc(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

// cmpfunc_reverse para ordenar o vetor em ordem decrescente
int cmpfunc_reverse(const void *a, const void *b){
    return *(int*)b - *(int*)a;
}


// funcao quicksort para ordenar um vetor
void quicksort(int *vetor, int inicio, int fim){
    // se o inicio for menor que o fim
    if(inicio < fim){
        // pivo recebe o inicio
        int pivo = inicio;
        // i recebe o inicio + 1
        int i = inicio + 1;
        // j recebe o fim
        int j = fim;
        // enquanto i for menor que j
        while(i <= j){
            // enquanto o valor de vetor[i] for menor que o valor de vetor[pivo]
            while(vetor[i] < vetor[pivo]){
                // incrementa i
                i++;
            }
            // enquanto o valor de vetor[j] for maior que o valor de vetor[pivo]
            while(vetor[j] > vetor[pivo]){
                // decrementa j
                j--;
            }
            // se i for menor ou igual a j
            if(i <= j){
                // troca os valores de vetor[i] e vetor[j]
                int aux = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = aux;
                // incrementa i
                i++;
                // decrementa j
                j--;
            }
        }
        // troca os valores de vetor[pivo] e vetor[j]
        int aux = vetor[pivo];
        vetor[pivo] = vetor[j];
        vetor[j] = aux;
        // recursão
        quicksort(vetor, inicio, j-1);
        quicksort(vetor, j+1, fim);
    }
}

// inverter o vetor
void inverter(int *vetor, int inicio, int fim){
    // se o inicio for menor que o fim
    if(inicio < fim){
        // troca os valores de vetor[inicio] e vetor[fim]
        int aux = vetor[inicio];
        vetor[inicio] = vetor[fim];
        vetor[fim] = aux;
        // recursão
        inverter(vetor, inicio+1, fim-1);
    }
}



int main(){

    // leitura do número de casos de teste
    int t;
    scanf("%d", &t);




    while(t--){
        // leitura do número de vértices
        int n;
        scanf("%d", &n);

        int resposta = 0;
        int vetor[MAX_INT];


        // zerar o vetor
/*         for(int j = 0; j < n; j++){
            vetor[j] = 0;
        } */
        memset(vetor, 0, sizeof(vetor));
        
        // segunda linha (de parentesco)
        int parente;
        int aux = 0;
        // leitura dos vértices
        // loop para ler os n-1 vértices
        for(int i = 1; i < n; i++){   // for loop para ler os n-1 vértices
            scanf("%d", &parente);

            if(vetor[parente-1] == 0){  // checa se o parente nao tem filhos
                aux++;
            }
        
            vetor[parente-1]++;         // aumenta o numero de mininu
        }

/*         // ordenar o vetor em ordem decrescente
        quicksort(vetor, 0, n-1);
        // inverter o vetor
        inverter(vetor, 0, n-1); */
        qsort(vetor, n, sizeof(int), cmpfunc_reverse);

        int maior = 0; // maior numero de elementos iguais
        int index_maior = 0; // indice do maior numero de elementos iguais
        int len = 0;    // tamanho do vetor

        for(int i = 0; i < n; i++){

            // se o numero de filhos for maior que 0
            if(vetor[i] > 0) {
                // o certo e -= aux - i, porque ele vale pra casos extremos
                vetor[i] -= aux -i; // (*****aux -1 = erro em caso grande pqp)diminui o numero de filhos do parente
                
                
                vetor[i] = max(0, vetor[i]); // se o numero de filhos for negativo, torna 0
                resposta++; // aumenta o numero de segundos
            
                if(vetor[i] > maior){ // se o numero de filhos for maior que o maior numero de filhos
                    maior = vetor[i]; // atualiza o maior numero de filhos
                    index_maior = i; // atualiza o indice do maior numero de filhos
                }
                
            }

            if(vetor[i] > 0){
                len++;
            }

        }

/*         // ordenar o vetor em ordem - caso seja necessario, em um caso de teste
        quicksort(vetor, 0, n-1);
        // inverter o vetor - caso seja necessario
        inverter(vetor, 0, n-1); */
        qsort(vetor, n, sizeof(int), cmpfunc_reverse);

        // enquanto o maior numero de filhos for maior que 0
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

        printf("%d", resposta + 1); // Adiciona 1 ao resultado final, porque o primeiro segundo nao conta
        printf("\n");
    }

    return 0;
}

/* 
5
7
1 1 1 2 2 4
5
5 5 1 4
2
1
3
3 1
6
1 1 1 1 1


///////////

1
7
1 1 1 2 2 4

3 2 1

   	1()
2(v1) 3(i2) 4(v2) 5(i3) 6(v3)7 (v4) 8(i4)

1-
2-
3-
4-
5-


   	1(v1)
2 3 4 5 6 7 8
*/