#include <stdio.h>
#include <stdlib.h>

// Esta função ordena um vetor de inteiros usando o algoritmo gnome sort.
// Ela recebe um ponteiro para o vetor e o tamanho do vetor como parâmetros.
void gnome_sort(int *vetor, int n){
    int i = 0;
    while(i < n){
        // Se o índice i for igual a 0 ou o elemento anterior for menor ou igual ao elemento atual,
        // incrementa o índice i para comparar o próximo par de elementos.
        if(i == 0 || vetor[i - 1] <= vetor[i]){
            i++;
        }else{
            // Se o elemento anterior for maior que o elemento atual,
            // troca as posições dos elementos.
            // Decrementa o índice i para comparar o elemento atual com o seu antecessor novamente.
            int aux = vetor[i];
            vetor[i] = vetor[i - 1];
            vetor[i - 1] = aux;
            i--;
        }
    }
}

// Esta é a função principal que chama a função gnome_sort para ordenar um vetor de inteiros.
int main(){
    // Cria um vetor de inteiros desordenado.
    int vetor[] = {5, 2, 4, 3, 1};

    // Calcula o tamanho do vetor.
    int n = sizeof(vetor) / sizeof(vetor[0]);

    // Chama a função gnome_sort para ordenar o vetor.
    gnome_sort(vetor, n);

    // Imprime o vetor ordenado.
    for(int i = 0; i < n; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");
    return 0;
}