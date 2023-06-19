/* 

Andrea, Carlos e Marcelo são muito amigos e passam todos os finais de semana à beira da piscina. Enquanto Andrea se bronzeia ao sol, os dois ficam jogando Bolhas. Andrea, uma cientista da computação muito esperta, já disse a eles que não entende por que passam tanto tempo jogando um jogo tão primário.

Usando o computador portátil dela, os dois geram um inteiro aleatório N e uma seqüência de inteiros, também aleatória, que é uma permutação de 1, 2, . . . ,N.

O jogo então começa, cada jogador faz um movimento, e a jogada passa para o outro jogador. Marcelo é sempre o primeiro a começar a jogar. Um movimento de um jogador consiste na escolha de um par de elementos consecutivos da seqüência que estejam fora de ordem e em inverter a ordem dos dois elementos. Por exemplo, dada a seqüência 1, 5, 3, 4, 2, o jogador pode inverter as posições de 5 e 3 ou de 4 e 2, mas não pode inverter as posições de 3 e 4, nem de 5 e 2. Continuando com o exemplo, se o jogador decide inverter as posições de 5 e 3 então a nova seqüência será 1, 3, 5, 4, 2.

Mais cedo ou mais tarde, a seqüência ficará ordenada. Perde o jogador impossibilitado de fazer um movimento. Andrea, com algum desdém, sempre diz que seria mais simples jogar cara ou coroa, com o mesmo efeito. Sua missão, caso decida aceitá-la, é determinar quem ganha o jogo, dada a seqüência inicial.
Entrada

A entrada contém vários casos de teste. Os dados de cada caso de teste estão numa única linha, e são inteiros separados por um espaço em branco. Cada linha contém um inteiroN (2 ≤ N ≤ 105), seguido da seqüência inicial P = (X1, X2, ...,XN) de N inteiros distintos dois a dois, onde1 ≤ Xi ≤ N para 1 ≤ i ≤ N.

O final da entrada é indicado por uma linha que contém apenas o número zero.
Saída

Para cada caso de teste da entrada seu programa deve imprimir uma única linha, com o nome do vencedor, igual a Carlos ou Marcelo., sem espaços em branco.
*/


#include <stdio.h>
#include <stdlib.h>


// Função que faz a intercalação de dois subvetores ordenados
void merge(int vet[], int left, int middle, int right, int *contador) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    int *L = (int*) malloc(n1 * sizeof(int));
    int *R = (int*) malloc(n2 * sizeof(int));

    // Copia os elementos do subvetor esquerdo para o vetor L
    for (i = 0; i < n1; i++)
        L[i] = vet[left + i];

    // Copia os elementos do subvetor direito para o vetor R
    for (j = 0; j < n2; j++)
        R[j] = vet[middle + 1 + j];

    i = 0;
    j = 0;
    k = left;

    // Intercala os elementos dos subvetores L e R no vetor
    while (i < n1 && j < n2) {
        if (L[i] < R[j]) {
            vet[k] = L[i];
            i++;
        } else {
            vet[k] = R[j];
            (*contador) += n1 - i; // Incrementa o contador de inversões
            j++;
        }
        k++;
    }

    // Copia os elementos restantes do subvetor esquerdo para o vetor
    while (i < n1) {
        vet[k] = L[i];
        i++;
        k++;
    }

    // Copia os elementos restantes do subvetor direito para o vetor
    while (j < n2) {
        vet[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

// Função que implementa o algoritmo de ordenação Merge Sort
void mergeSort(int vet[], int left, int right, int *counter) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        // Ordena o subvetor esquerdo
        mergeSort(vet, left, middle, counter);

        // Ordena o subvetor direito
        mergeSort(vet, middle + 1, right, counter);

        // Intercala os subvetores esquerdo e direito
        merge(vet, left, middle, right, counter);
    }
}

int main() {
    int n, i;
    int *arr;
    int contador;

    // Lê vários casos de teste da entrada padrão
    while (scanf("%d", &n) == 1 && n != 0) {
        contador = 0;

        // Aloca memória para a sequência de inteiros
        arr = (int*) malloc(n * sizeof(int));

        // Lê a sequência de inteiros
        for (i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }

        // Ordena a sequência usando o Merge Sort e conta o número de inversões
        mergeSort(arr, 0, n - 1, &contador);

        // Determina o vencedor do jogo
        if (contador % 2)
            printf("Marcelo\n");
        else
            printf("Carlos\n");

        // Libera a memória alocada para a sequência de inteiros
        free(arr);
    }

    return 0;
}