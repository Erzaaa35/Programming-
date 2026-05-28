#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct sneakers {
    char brand[35];
    int model;
    int size;
    int price;
};

typedef struct LowerNode {
    struct sneakers *data;
    struct LowerNode *next;
    int idx;
} LowerNode;

typedef struct UpperNode {
    struct sneakers *data;
    struct UpperNode *next;
    struct UpperNode *prev;
    LowerNode *down;
    int idx;
} UpperNode;

struct sneakers *create_sneakers() {
    char *brands[] = {"Nike", "Adidas", "Puma", "Qeo", "Lbo"};
    
    struct sneakers *s = malloc(sizeof(struct sneakers));
    strcpy(s->brand, brands[rand() % 5]);
    s->model = 1 + rand() % 5;
    s->size = 35 + rand() % 10;
    s->price = 2000 + rand() % 13001;
    return s;
}

void print_node( char *row, int idx, struct sneakers *s) {
    printf("[%s][N=%d] brand=%-12s model=%d size=%d price=%d\n",
           row, idx, s->brand, s->model, s->size, s->price);
}

LowerNode *lower_append(LowerNode *head, struct sneakers *data, int idx) {
    LowerNode *node = malloc(sizeof(LowerNode));
    node->data = data;
    node->next = NULL;
    node->idx = idx;
    
    if (head == NULL) {
        return node;
    }
    
    LowerNode *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    return head;
}

UpperNode *upper_append(UpperNode **head, struct sneakers *data, int idx) {
    UpperNode *node = malloc(sizeof(UpperNode));
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    node->down = NULL;
    node->idx = idx;
    
    if (*head == NULL) {
        *head = node;
        return node;
    }
    
    UpperNode *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    node->prev = current;
    return node;
}

UpperNode *build_list(int n) {
    struct sneakers **a = malloc((n + 1) * sizeof(struct sneakers *));
    for (int i = 1; i <= n; i++) {
        a[i] = create_sneakers();
    }
    
    UpperNode *S = NULL;
    LowerNode *lower_head = NULL;
    
    UpperNode **upper_arr = NULL;
    int upper_count = 0;
    
    LowerNode **lower_arr = NULL;
    int lower_count = 0;
    
    for (int i = n; i >= 2; i -= 2) {
        upper_arr = realloc(upper_arr, (upper_count + 1) * sizeof(UpperNode *));
        upper_arr[upper_count] = upper_append(&S, a[i], i);
        upper_count++;
    }
    
    for (int i = n - 1; i >= 1; i -= 2) {
        lower_head = lower_append(lower_head, a[i], i);
        
        LowerNode *current = lower_head;
        while (current->next != NULL) {
            current = current->next;
        }
        lower_arr = realloc(lower_arr, (lower_count + 1) * sizeof(LowerNode *));
        lower_arr[lower_count] = current;
        lower_count++;
    }
    
    int pairs = upper_count;
    if (lower_count < pairs) pairs = lower_count;
    
    for (int i = 0; i < pairs; i++) {
        upper_arr[i]->down = lower_arr[i];
    }
    
    free(upper_arr);
    free(lower_arr);
    free(a);
    return S;
}

void print_list(UpperNode *S) {
    printf("\n=== Список ===\n");
    UpperNode *current = S;
    while (current != NULL) {
        print_node("ВЕРХ", current->idx, current->data);
        if (current->down != NULL) {
            print_node("НИЗ ", current->down->idx, current->down->data);
        } else {
            printf("[НИЗ ][N=-] NULL\n");
        }
        printf("\n");
        current = current->next;
    }
}

void navigate(UpperNode *S) {
    UpperNode *current = S;
    int in_lower = 0; 
    
    printf("d-вправо  a-влево  s-вниз  w-вверх  q-выход\n");
    
    char ch;
    while (1) {
        if (in_lower == 0) {
            print_node("ВЕРХ", current->idx, current->data);
        } else {
            print_node("НИЗ ", current->down->idx, current->down->data);
        }
        
        printf("Команда: ");
        scanf(" %c", &ch);
        
        if (ch == 'q') {
            break;
        } else if (ch == 'd') {
            if (in_lower == 0 && current->next != NULL) {
                current = current->next;
            } else if (in_lower == 1 && current->next != NULL && current->next->down != NULL) {
                current = current->next;
            } else {
                printf("Невозможно.\n");
            }
        } else if (ch == 'a') {
            if (current->prev != NULL) {
                current = current->prev;
            } else {
                printf("Невозможно.\n");
            }
        } else if (ch == 's') {
            if (in_lower == 0 && current->down != NULL) {
                in_lower = 1;
            } else {
                printf("Невозможно.\n");
            }
        } else if (ch == 'w') {
            if (in_lower == 1) {
                in_lower = 0;
            } else {
                printf("Невозможно.\n");
            }
        }
    }
}

void free_list(UpperNode *S) {
    UpperNode *current = S;
    while (current != NULL) {
        free(current->data);
        if (current->down != NULL) {
            free(current->down->data);
            free(current->down);
        }
        UpperNode *temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    srand(time(NULL));
    
    int n = 0;
    printf("Введите N: ");
    scanf("%d", &n);
    
    UpperNode *S = build_list(n);
    print_list(S);
    navigate(S);
    
    return 0;
}