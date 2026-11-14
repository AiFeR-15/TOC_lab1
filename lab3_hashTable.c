#include <stdio.h>
#include <stdlib.h>

int table_size = 5;
int element_count = 0;

typedef struct Order {
    int order_id;
    char manufactirer[50];
    float cost;
    struct Order* next;
} Order;

int get_hash(int order_id) {
    return order_id % table_size;
}

int next_prime(int n) {
    while (1) {
        int prime = 1;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                prime = 0;
                break;
            }
        }
        if (prime) return n;
        n++;
    }
}

Order** restructure(Order** hashTable) {
    int old_size = table_size;
    table_size = next_prime(old_size * 2);

    Order** new_table = (Order**)calloc(table_size, sizeof(Order*));

    for (int i = 0; i < old_size; i++) {
        Order* current = hashTable[i];
        while (current != NULL) {
            Order* next = current->next;
            int index = get_hash(current->order_id);
            current->next = new_table[index];
            new_table[index] = current;
            current = next;
        }
    }

    free(hashTable);
    printf("-> Реструктуризація! Новий розмір таблиці: %d\n", table_size);
    return new_table;
}

Order** insert_order(Order** hashTable) {
    Order* new_order = (Order*)malloc(sizeof(Order));
    if (new_order == NULL) return hashTable;

    printf("\nВведіть номер замовлення: ");
    scanf("%d", &new_order->order_id);
    while (getchar() != '\n');

    printf("Введіть фірму-виробника: ");
    scanf("%[^\n]", new_order->manufactirer);

    printf("Введіть вартість ремонту(грн): ");
    scanf("%f", &new_order->cost);

    int index = get_hash(new_order->order_id);
    new_order->next = hashTable[index];
    hashTable[index] = new_order;
    element_count++;

    printf("-> Додано в сегмент [%d] (замовлень: %d)\n", index, element_count);

    if (element_count > table_size * 3) {
        hashTable = restructure(hashTable);
    }

    return hashTable;
}

void delete_order(Order** hashTable) {
    int delete_id;
    printf("Введіть ID для видалення: ");
    scanf("%d", &delete_id);

    int index = get_hash(delete_id);
    Order* current = hashTable[index];
    Order* prev = NULL;

    while (current != NULL) {
        if (delete_id == current->order_id) {
            if (prev == NULL) hashTable[index] = current->next;
            else prev->next = current->next;

            free(current);
            element_count--;
            printf("Замовлення №%d видалено!\n", delete_id);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Замовлення №%d не знайдено!\n", delete_id);
}

void print_table(Order** hashTable) {
    printf("\n--- Таблиця (m = %d, N = %d) ---\n", table_size, element_count);
    for (int i = 0; i < table_size; i++) {
        printf("[%d]: ", i);
        Order* current = hashTable[i];
        if (current == NULL) {
            printf("Порожньо\n");
        } else {
            while (current != NULL) {
                printf("[ID: %d | %s | %.2f] -> ", current->order_id, current->manufactirer, current->cost);
                current = current->next;
            }
            printf("NULL\n");
        }
    }
    printf("--------------------------------\n");
}

int main() {
    Order** hashTable = (Order**)calloc(table_size, sizeof(Order*));
    int choice;

    while (1) {
        printf("\n--- Меню Сервісу ---\n");
        printf("1. Додати замовлення\n");
        printf("2. Видалити замовлення\n");
        printf("3. Показати всю таблицю\n");
        printf("4. Примусова реструктуризація\n");
        printf("5. Вийти\n");
        printf("Ваш вибір: ");
        
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                hashTable = insert_order(hashTable);
                break;
            case 2:
                delete_order(hashTable);
                break;
            case 3:
                print_table(hashTable);
                break;
            case 4:
                hashTable = restructure(hashTable);
                break;
            case 5:
                for (int i = 0; i < table_size; i++) {
                    while (hashTable[i] != NULL) {
                        Order* temp = hashTable[i];
                        hashTable[i] = hashTable[i]->next;
                        free(temp);
                    }
                }
                free(hashTable);
                return 0;
        }
    }
    return 0;
}