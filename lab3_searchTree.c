#include <stdio.h>
#include <stdlib.h>

typedef struct Person {
    char name[100];       // Прізвище/ім'я особи
    char birth_date[10];  // Число та місяць (наприклад "15.05")
    char city[50];        // Місто проживання
    char workplace[100];  // Місце роботи
} Person;

typedef struct TreeNode {
    char key[100];              // Ключ пошуку (назва міста, дата або робота)
    int count;                  // Частота (кількість осіб)
    
    struct TreeNode* left;      // Вказівник на ліву гілку (менші значення)
    struct TreeNode* right;     // Вказівник на праву гілку (більші значення)
} TreeNode;


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
                
                break;
            case 2:
                
                break;
            case 3:
                
                break;
            case 4:
                printf("Вихід з меню!");
                break;
        }
    }
    return 0;
}