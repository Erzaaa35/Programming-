#include <stdio.h>
#include <pthread.h>

void* potok_f(void* arg) {
    for (int i = 1; i <= 5; i++) {
        printf("Дочерний поток: строка %d\n", i);
    }
    return NULL;
}

int main() {
    pthread_t potok;
    
    pthread_create(&potok, NULL, potok_f, NULL);
    
    pthread_join(potok, NULL);

    for (int i = 1; i <= 5; i++) {
        printf("Родительский поток: строка %d\n", i);
    }
    return 0;
}