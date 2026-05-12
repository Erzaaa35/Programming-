#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

struct sort {
    int value;
};

void* sleep_sort_func(void* arg) {
    struct sort* data = (struct sort*)arg;
    int num = data->value;
    
    sleep(num);
    
    printf("%d\n", num);
    
    free(data);
    return NULL;
}

int main() {
    int array[] = {5, 2, 8, 1, 9, 3, 7, 4, 6, 0};
    int n = sizeof(array) / sizeof(array[0]);
    
    printf("Исходный массив: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    printf("Sleepsort результат: ");
    
    pthread_t threads[n];
    
    for (int i = 0; i < n; i++) {
        struct sort* data = malloc(sizeof(struct sort));
        data->value = array[i];
        pthread_create(&threads[i], NULL, sleep_sort_func, data);
    }
    
    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("\n");
    
    return 0;
}