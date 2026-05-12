#include <stdio.h>

typedef struct {
    int health;
    int alcohol;
    int joy;
    int fatigue;
    int money;
} Valera;

void valera_init(Valera* v, int health, int alcohol, int joy, int fatigue, int money) {
    v->health = health;
    v->alcohol = alcohol;
    v->joy = joy;
    v->fatigue = fatigue;
    v->money = money;
}

int go_to_work(Valera* v) {
    if (v->alcohol > 50 || v->fatigue > 80) {
        return 0;
    }
    
    v->joy -= 5;
    if (v->alcohol - 30 < 0) v->alcohol = 0;
    else v->alcohol -= 30;
    v->money += 100;
    v->fatigue += 20;
    return 1;
}

void go_to_bar(Valera* v) {
    v->joy += 1;
    v->alcohol += 60;
    v->fatigue += 40;
    v->health -= 10;
    v->money -= 100;
}

void sleep(Valera* v) {
    if (v->alcohol <= 30) {
        v->health = 100;
        v->alcohol = 0;
        v->fatigue = 10;
    } else {
        v->joy -= 3;
        v->alcohol -= 50;
    }
}