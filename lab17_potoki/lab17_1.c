#include <stdio.h>
#include <pthread.h>

void* potok_f(void* arg) {
    for (int i = 1; i <= 5; i++) {
        printf("Дочерний поток: строка %d\n", i);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t potok;
    
    pthread_create(&potok, NULL, potok_f, NULL);
    
    for (int i = 1; i <= 5; i++) {
        printf("Родительский поток: строка %d\n", i);
        sleep(1);
    }
    sleep(1);
    return 0;
}