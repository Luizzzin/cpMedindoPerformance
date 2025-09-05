#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//=========ALUNOS========== 
//Luiz Henrique Barbosa Dias RM:562399
//Kenzo de Melo Sato RM:563648
//Gregory Debom RM:562346
//Nathan Lopes RM: 563507
 //==========================


// Variável global para contar as comparações
long long comparacoes = 0;
long long comparacoesDois = 0;
long long comparacoesTres= 0;

// função para o qsort---

int comparador(const void* a, const void* b){
    const int* variA = a;
    const int* variB = b;
    comparacoesTres++;
    return *variA - *variB;
}

// --- Funções para Geração de Dados ---

void gerarAleatorio(int arr[], int n) {
    srand(42);
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % n;
    }
}

void gerarOrdenado(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
}

void gerarReverso(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - 1 - i;
    }
}

void gerarQuaseOrdenado(int arr[], int n) {
    gerarOrdenado(arr, n);
    int numTrocas = n * 0.1;
    srand(42);
    for (int i = 0; i < numTrocas; i++) {
        int idx1 = rand() % n;
        int idx2 = rand() % n;
        int temp = arr[idx1];
        arr[idx1] = arr[idx2];
        arr[idx2] = temp;
    }
}

// --- Implementação do Bubble Sort ---

void bubbleSort(int arr[], int n) {
    int i, j, temp;
    int trocado;
    comparacoes = 0;
    trocado = 0;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (arr[j] > arr[j + 1]) {
                
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                trocado = 1;
            }
        }
        if (trocado == 0) {
            break;
        }
    }
}
// agora insertion sort

void insertionSort(int arr[], int n)
{
    comparacoesDois = 0;
    for (int i = 1; i < n; ++i) {
        
        int key = arr[i];
        comparacoesDois++;
        int j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            comparacoesDois++;
            arr[j + 1] = arr[j];
            j = j - 1;
            
        }
        arr[j + 1] = key;
    }
}


// --- Função Principal

int main() {
    int tamanhos[] = {1000, 5000, 8000};
    int numTamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);
    char* cenarios[] = {"Aleatorio", "Ordenado", "Reverso", "Quase Ordenado"};
    
    printf("Coleta de Dados Brutos para os argoritmos:\n\n");

    for (int i = 0; i < numTamanhos; i++) {
        int n = tamanhos[i];
        for (int j = 0; j < 4; j++) {
            printf("----------------------------------------\n");
            printf("Cenário: %s, Tamanho: %d\n", cenarios[j], n);
            printf("\n=============bubble sort==============\n");
            for (int k = 0; k < 5; k++) {
                int* arr = (int*)malloc(n * sizeof(int));
                
                if (j == 0) gerarAleatorio(arr, n);
                else if (j == 1) gerarOrdenado(arr, n);
                else if (j == 2) gerarReverso(arr, n);
                else if (j == 3) gerarQuaseOrdenado(arr, n);
                
                clock_t start = clock();
                bubbleSort(arr, n);
                clock_t end = clock();

                double tempo = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
                
                printf("Execução %d: Tempo = %.2f ms, Comparações = %lld\n", k + 1, tempo, comparacoes);
                
                free(arr);
            }
            printf("\n============Insertion Sort===========\n");
            for (int l = 0; l < 5; l++) {
                int* arr = (int*)malloc(n * sizeof(int));
                
                if (j == 0) gerarAleatorio(arr, n);
                else if (j == 1) gerarOrdenado(arr, n);
                else if (j == 2) gerarReverso(arr, n);
                else if (j == 3) gerarQuaseOrdenado(arr, n);
                
                clock_t start = clock();
                insertionSort(arr, n);
                clock_t end = clock();
    
                double tempo = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
                
                printf("Execução %d: Tempo = %.2f ms, Comparações = %lld\n", l + 1, tempo, comparacoesDois);
                
                free(arr);
            }
            
            printf("\n============QSort===========\n");
            for (int m = 0; m < 5; m++) {
                int* arr = (int*)malloc(n * sizeof(int));
                
                if (m == 0) gerarAleatorio(arr, n);
                else if (m == 1) gerarOrdenado(arr, n);
                else if (m == 2) gerarReverso(arr, n);
                else if (m == 3) gerarQuaseOrdenado(arr, n);
                
                clock_t start = clock();
                qsort(arr, n, sizeof(arr[0]), comparador); // qsort aqui!!
                clock_t end = clock();
    
                double tempo = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
                
                printf("Execução %d: Tempo = %.2f ms, Comparações = %lld\n", m + 1, tempo, comparacoesTres);
                
                free(arr);
            }
            printf("\n");
        }
    }
    
    return 0;
}