#include <stdio.h>
#include <stdlib.h>

// Скомпилируй и запусти меня

void init(int **arr, int *n) { 
    *arr = malloc(n * sizeof(int));

    for (long i = 0; i < n; ++i) { 
        (*arr)[i] = i;    
    }
    n = 5;
} 

int main() {    
    int n = 10;

    int *arr = NULL; // malloc(n * sizeof(int));

    init(&arr, &n);
    for (int i = 0; i < n; ++i) {
        printf("%d\n", arr[i]);
    }
    free(arr);
    return 0;
}


// Выделил память под массив 