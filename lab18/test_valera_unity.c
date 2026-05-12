#include "unity.h"
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

void setUp(void) {}
void tearDown(void) {}

void test_go_to_work_normal() {
    Valera v;
    valera_init(&v, 100, 30, 0, 10, 1000);
    int r = go_to_work(&v);
    
    TEST_ASSERT_EQUAL_INT(1, r);
    TEST_ASSERT_EQUAL_INT(-3, v.joy);
    TEST_ASSERT_EQUAL_INT(0, v.alcohol);
    TEST_ASSERT_EQUAL_INT(1100, v.money);
    TEST_ASSERT_EQUAL_INT(30, v.fatigue);
}

void test_go_to_work_high_alcohol() {
    Valera v;
    valera_init(&v, 100, 60, 0, 10, 1000);
    int r = go_to_work(&v);
    
    TEST_ASSERT_EQUAL_INT(0, r);
    TEST_ASSERT_EQUAL_INT(60, v.alcohol);
    TEST_ASSERT_EQUAL_INT(1000, v.money);
}

void test_go_to_work_high_fatigue() {
    Valera v;
    valera_init(&v, 100, 30, 0, 90, 1000);
    int r = go_to_work(&v);
    
    TEST_ASSERT_EQUAL_INT(0, r);
    TEST_ASSERT_EQUAL_INT(90, v.fatigue);
}

void test_go_to_work_alcohol_50() {
    Valera v;
    valera_init(&v, 100, 50, 0, 10, 1000);
    int r = go_to_work(&v);
    
    TEST_ASSERT_EQUAL_INT(1, r);
    TEST_ASSERT_EQUAL_INT(20, v.alcohol);
}

void test_go_to_bar() {
    Valera v;
    valera_init(&v, 100, 0, 0, 0, 1000);
    go_to_bar(&v);
    
    TEST_ASSERT_EQUAL_INT(1, v.joy);
    TEST_ASSERT_EQUAL_INT(60, v.alcohol);
    TEST_ASSERT_EQUAL_INT(40, v.fatigue);
    TEST_ASSERT_EQUAL_INT(90, v.health);
    TEST_ASSERT_EQUAL_INT(900, v.money);
}

void test_sleep_low_alcohol() {
    Valera v;
    valera_init(&v, 50, 20, 0, 70, 1000);
    sleep(&v);
    
    TEST_ASSERT_EQUAL_INT(100, v.health);
    TEST_ASSERT_EQUAL_INT(0, v.alcohol);
    TEST_ASSERT_EQUAL_INT(10, v.fatigue);
}

void test_sleep_high_alcohol() {
    Valera v;
    valera_init(&v, 100, 80, 5, 50, 1000);
    sleep(&v);
    
    TEST_ASSERT_EQUAL_INT(2, v.joy);
    TEST_ASSERT_EQUAL_INT(30, v.alcohol);
}

int main() {
    UNITY_BEGIN();
    
    RUN_TEST(test_go_to_work_normal);
    RUN_TEST(test_go_to_work_high_alcohol);
    RUN_TEST(test_go_to_work_high_fatigue);
    RUN_TEST(test_go_to_work_alcohol_50);
    RUN_TEST(test_go_to_bar);
    RUN_TEST(test_sleep_low_alcohol);
    RUN_TEST(test_sleep_high_alcohol);
    
    return UNITY_END();
}