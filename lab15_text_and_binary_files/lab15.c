#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define max_line 135
#define max_name 135 
#define max_level 135 

struct Worker{
    int id;
    char name[135];
    char level[135];
};

int main(int count, char *file_name[]) { 
    if (count !=2) {
        printf("Ты указал имя файла не правильно\n");
        return 1;
    }

    FILE *file = fopen(file_name[1], "r");
    if (file == NULL) {
        printf("Ошибка,файл нельзя открыть\n");
        return 1; 
    }

    struct Worker workers[135];
    int worker_count = 0; 

    char line[max_line];
    char name[max_name];
    int id;
    char level[max_level]; 
    printf("\n%-30s | %-10s | %-10s\n", "Name", "ID", "Level");
    printf("--------------------------------------------------\n");
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        int result = sscanf(line, "%[^;];%d;%s", name , &id , level); // пропускает всё до ; , прочитать целое число , прочитать строку
        if (result == 3) {
            printf("%-30s | %-10d | %-10s\n", name , id , level);
            
            workers[worker_count].id = id;
            strcpy(workers[worker_count].name, name);
            strcpy(workers[worker_count].level, level);
            worker_count++; 
        }
    }
    printf("-------------------------------------------------\n");

    fclose(file);
    if (worker_count > 0) {
        FILE *bin = fopen("database.dat", "wb");
        if (bin != NULL) {
            fwrite(workers, sizeof(struct Worker), worker_count, bin);
            fclose(bin);
        }
    }

    FILE *bin = fopen("database.dat", "rb");
    if (bin == NULL) {
        return 1;
    }
    
    fseek(bin, 0, SEEK_END);
    long file_size = ftell(bin);
    int record_count = file_size / sizeof(struct Worker);
    rewind(bin);

    int search_id;
    scanf("%d", &search_id);

    struct Worker temp;
    int found = 0; 

    for (int i = 0; i < record_count; i++) {
        fread(&temp, sizeof(struct Worker), 1, bin);
        if (temp.id == search_id) {
            found = 1;
            break;
        }
    }

    if (found == 1) {
        printf("Найден: %s ID: %d, Уровень: %s\n", temp.name, temp.id, temp.level);
    } else {
        printf("Сотрудник с ID %d не найден\n", search_id);
    }
    fclose(bin);

    return 0;
} 


