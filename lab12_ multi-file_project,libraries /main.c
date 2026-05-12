#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main() {
    srand(time(NULL));
    
    fill();
    print();
    bubble_sort();
    print();
    
    return 0;
}