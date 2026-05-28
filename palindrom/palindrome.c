#include "palindrome.h"
#include <stdio.h>
#include <string.h>

// Переводит кириллицу в нижний регистр 
void cyr_tolower(char *s, int pos)
{
    unsigned char b1 = (unsigned char)s[pos];
    unsigned char b2 = (unsigned char)s[pos + 1];

    // А-П 
    if (b1 == 0xD0 && b2 >= 0x90 && b2 <= 0x9F) {
        s[pos + 1] = b2 + 0x20;
    }
    // Р-Я 
    if (b1 == 0xD0 && b2 >= 0xA0 && b2 <= 0xAF) {
        s[pos] = 0xD1;
        s[pos + 1] = b2 - 0x20;
    }
    // Ё 
    if (b1 == 0xD0 && b2 == 0x81) {
        s[pos] = 0xD1;
        s[pos + 1] = 0x91;
    }
}

// Убирае пробелы и знаки препинания и в нижний регистр 
void podgotovka(char *src, char *res)
{
    int i = 0;
    int j = 0;
    int len = strlen(src);

    while (i < len) {
        unsigned char c = (unsigned char)src[i];
        if (c == ' ' || c == ',' || c == '.' || c == '!'|| c == '?' || c == '\n'|| c == '-' || c == ';' || c == ':') {
            i++;
            continue;
        } 
 
        if ((c & 0xE0) == 0xC0) { //двухбайтовый
            res[j] = src[i];
            res[j + 1] = src[i + 1];
            cyr_tolower(res, j);
            j += 2;
            i += 2;
        }

        else {
            i++;
        }
    }
    res[j] = '\0';
}

// Сравниваем символы UTF-8 с двух концов 
int is_palindrome(char *str)
{
    int len = strlen(str);
    int left = 0;
    int right = len - 2;  // -2, потому что каждый символ - 2 байта
    
    while (left < right) {
        if (str[left] != str[right] || str[left+1] != str[right+1])
            return 0;
        left += 2;
        right -= 2;
    }
    return 1;
}

/* читает файл и проверяет весь текст на палиндром */
int check_file(char *filename)
{
    FILE *f;
    char buf[1024];
    char clean[1024];
    int n;

    f = fopen(filename, "r");
    if (f == NULL) {
        printf("Ошибка: не удалось открыть файл \"%s\"\n", filename);
        return -1;
    }

    n = fread(buf, 1, sizeof(buf) - 1, f);
    fclose(f);

    if (n <= 0) {
        printf("Ошибка: файл пустой\n"); 
        return -1;
    }
    buf[n] = '\0';

    podgotovka(buf, clean);

    if (is_palindrome(clean)) {
        printf("Текст является палиндромом\n");
    } else {
        printf("Текст не является палиндромом\n");
    }

    return 0;
}