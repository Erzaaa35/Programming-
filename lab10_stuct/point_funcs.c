#include <stdio.h>
#include "point.h"

// Функция 1: создает и возвращает структуру Point
struct Point createPoint(double x, double y) {
    struct Point p;
    p.x = x;
    p.y = y;
    return p;
}

// Функция 2: принимает две структуры и проверяет параллельность осям
void checkParallel(struct Point p1, struct Point p2) {
    if (p1.x == p2.x) {
        printf("Прямая параллельна оси ординат (вертикальная)\n");
    }
    
    if (p1.y == p2.y) {
        printf("Прямая параллельна оси абсцисс (горизонтальная)\n");
    }
}