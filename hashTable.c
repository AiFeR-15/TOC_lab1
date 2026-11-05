#include <stdio.h>
#include <stdlib.h>
#define TABLE_SIZE 10

typedef struct Order {
    int order_id;
    char manufactirer[50];
    float cost;
    struct Order* next;
} Order;

int get_hash(int order_id){
    return order_id % TABLE_SIZE;
}

void insert_order(Order* hashTable[]){
    Order* new_order = (Order*)malloc(sizeof(Order));
    if (new_order == NULL) {
        printf("Помилка: не вдалося виділити пам'ять!\n");
        return;
    }
    printf("\nВведіть номер замовлення (ціле число): ");
    scanf("%d", &new_order->order_id);

    // Очищаємо буфер від залишків Enter (щоб наступний scanf для тексту не зламався)
    while (getchar() != '\n'); 

    printf("Введіть фірму-виробника: ");
    // %[^\n] дозволяє вводити текст із пробілами до натискання Enter
    scanf("%[^\n]", new_order->manufactirer); 

    printf("Введіть вартість ремонту(грн): ");
    scanf("%f", &new_order->cost);

    // 3. Знаходимо, в яку шухляду (сегмент) його покласти
    int index = get_hash(new_order->order_id);

    new_order->next=hashTable[index];
    hashTable[index]=new_order;

    printf("-> Замовлення №%d успішно додано в сегмент [%d]!\n", new_order->order_id, index);
}

void delete_order(Order* hashTable[]){
    int delete_id;
    printf("Введіть номер ID для видалення: ");
    scanf("%d",&delete_id);

    int index = get_hash(delete_id);

    Order* current =hashTable[index];
    Order* prev = NULL;

    while (current!=NULL){
        if (delete_id == current->order_id){
            if (prev==NULL){
                hashTable[index]=current->next;
            }
            else{
                prev->next=current->next;
            }
            free(current);
            printf("Замовлення №%d успішно видалено!\n", delete_id);
            return;
        }

        prev=current;
        current=current->next;

    }
    printf("Замовлення №%d не знайдено в базі!\n", delete_id);
}
void print_table(Order* hashTable[]){
    for(int i; i<TABLE_SIZE;i++){
        Order* current =hashTable[i];
        if (current==NULL){
            printf("Порожньо!\n");
        }
        else{
            while(current!=NULL){
                printf("[ID: %d | Фірма: %s | Ціна: %.2f] -> ", 
                       current->order_id, current->manufactirer, current->cost);
                current = current->next;
            }
            printf("NULL\n");
        }
    }
    printf("--------------------");
}
int main(){
    Order* hashTable[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
    int choice;
    while(1) {
        printf("\n--- Меню Сервісу ---\n");
        printf("1. Додати замовлення\n");
        printf("2. Видалити замовлення\n");
        printf("3. Показати всю таблицю\n");
        printf("4. Вийти\n");
        printf("Ваш вибір: ");
        
        if (scanf("%d", &choice) != 1) break;
        switch(choice){
            case 1:
                insert_order(hashTable);
                break;
            case 2:
                delete_order(hashTable);
                break;
            case 3:
                print_table(hashTable);
                break;
            case 4:
                printf("Вихід з меню!");
                break;
        }
    }
    return 0;
}