#include "point.h"

int main() {
    struct Point A = createPoint(3.0, 5.0);
    struct Point B = createPoint(3.0, 8.0);
    
    checkParallel(A, B);
    
    return 0;
}