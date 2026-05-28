#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct sneakers {
    char brand[35];
    int model;
    int size;
    int price;
};

#define N 5

struct sneakers sneakers[N];

void fill() {
    char *brands[] = {"Nike", "Adidas", "Puma"};
    int num_brands = sizeof(brands) / sizeof(brands[0]);
    
    for(int i = 0; i < N; i++) {
        strcpy(sneakers[i].brand, brands[rand() % num_brands]);
        sneakers[i].model = 1 + rand() % 5;
        sneakers[i].size = 35 + rand() % 10;
        sneakers[i].price = 2000 + rand() % 13001;
    }
}

void print() {
    printf("\n Бренд   Модель   Размер   Цена\n");
    
    for(int i = 0; i < N; i++) {
        printf(" %-9s  %-5d  %-5d  %-5d \n", sneakers[i].brand, sneakers[i].model, sneakers[i].size, sneakers[i].price);
    }
}

void bubble_sort() {
    for(int i = 0; i < N - 1; i++) {
        for(int j = 0; j < N - i - 1; j++) {
            if(sneakers[j].price > sneakers[j + 1].price) {
                struct sneakers temp = sneakers[j];
                sneakers[j] = sneakers[j + 1];
                sneakers[j + 1] = temp;
            }
        }
    }
}

int main() {
    srand(time(NULL));
    
    fill();
    print();
    bubble_sort();
    print();
    
    return 0;
}

















