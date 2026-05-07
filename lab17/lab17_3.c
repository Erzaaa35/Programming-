#include <stdio.h>
#include <pthread.h>

struct data {
    int nomer;
    char stroki[5][100];
};

void* potok_f(void* arg) {
    int num = *(int*)arg; 
    
    for (int i = 1; i <= 5; i++) {
        printf("Поток %d: строка %d\n", num, i);
    }
    return NULL;
}

int main() {
    pthread_t potoki[4];
    int nomera[4];
    
    for (int t = 0; t < 4; t++) {
        nomera[t] = t + 1;
        pthread_create(&potoki[t], NULL, potok_f, &nomera[t]);
    }
    
    for (int t = 0; t < 4; t++) {
        pthread_join(potoki[t], NULL);
    }
    
    return 0;
}