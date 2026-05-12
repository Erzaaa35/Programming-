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

void test(char* name, int ok) {
    if (ok) {
        printf("[OK] %s\n", name);
    } else {
        printf("[FAIL] %s\n", name);
    }
}

void test_go_to_work_normal() {
    Valera v;
    valera_init(&v, 100, 30, 0, 10, 1000);
    int r = go_to_work(&v);
    test("go_to_work норма", r == 1 && v.joy == -3 && v.alcohol == 0 && v.money == 1100 && v.fatigue == 30);
}

void test_go_to_work_high_alcohol() {
    Valera v;
    valera_init(&v, 100, 60, 0, 10, 1000);
    int r = go_to_work(&v);
    test("go_to_work алкоголь > 50", r == 0 && v.alcohol == 60 && v.money == 1000);
}

void test_go_to_work_high_fatigue() {
    Valera v;
    valera_init(&v, 100, 30, 0, 90, 1000);
    int r = go_to_work(&v);
    test("go_to_work усталость > 80", r == 0 && v.fatigue == 90);
}

void test_go_to_work_alcohol_50() {
    Valera v;
    valera_init(&v, 100, 50, 0, 10, 1000);
    int r = go_to_work(&v);
    test("go_to_work алкоголь 50", r == 1 && v.alcohol == 20);
}

void test_go_to_bar() {
    Valera v;
    valera_init(&v, 100, 0, 0, 0, 1000);
    go_to_bar(&v);
    test("go_to_bar", v.joy == 1 && v.alcohol == 60 && v.fatigue == 40 && v.health == 90 && v.money == 900);
}

void test_sleep_low_alcohol() {
    Valera v;
    valera_init(&v, 50, 20, 0, 70, 1000);
    sleep(&v);
    test("sleep алкоголь <= 30", v.health == 100 && v.alcohol == 0 && v.fatigue == 10);
}

void test_sleep_high_alcohol() {
    Valera v;
    valera_init(&v, 100, 80, 5, 50, 1000);
    sleep(&v);
    test("sleep алкоголь > 30", v.joy == 2 && v.alcohol == 30);
}

int main() {
    test_go_to_work_normal();
    test_go_to_work_high_alcohol();
    test_go_to_work_high_fatigue();
    test_go_to_work_alcohol_50();
    test_go_to_bar();
    test_sleep_low_alcohol();
    test_sleep_high_alcohol();
    printf("\n");
    return 0;
}