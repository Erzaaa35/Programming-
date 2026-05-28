#include <stdio.h>
#include <string.h>
#include "palindrome.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Использование: %s <файл>\n", argv[0]);
    }

    return check_file(argv[1]);
}