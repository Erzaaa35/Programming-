#include <stdio.h>
#include <pthread.h>

void* potok_f(void* arg) {
    int num = *(int*)arg;
    
    for (int i = 1; i <= 10; i++) {
        printf("Поток %d: строка %d\n", num, i);
        sleep(3);
    }
    
    return NULL;
}

int main() {
    pthread_t potoki[4];
    int nomera[4];
    
    for (int i = 0; i < 4; i++) {
        nomera[i] = i + 1;
        pthread_create(&potoki[i], NULL, potok_f, &nomera[i]);
    }
    
    printf("Основной поток ждет 2 секунды...\n");
    sleep(2);
    
    printf("\nОтмена потоков\n");
    for (int i = 0; i < 4; i++) {
        pthread_cancel(potoki[i]);
    }
    
    printf("Все потоки остановлены. Программа завершена.\n");
    
    return 0;
}