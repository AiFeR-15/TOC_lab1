#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Структура для загальних даних
typedef struct Person {
    char name[100];
    char birth_date[10];
    char city[50];
    char workplace[100];
} Person;

// Структура вузла для нашого дерева (частотного словника)
typedef struct TreeNode {
    char key[100];          // Ключ (назва міста, організація або дата)
    int count;              
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

void insert_node(TreeNode** root, const char* key){
    if (*root == NULL){
        *root = (TreeNode*)malloc(sizeof(TreeNode));
        strcpy((*root)->key, key);
        (*root)->count = 1;
        (*root)->left=NULL;
        (*root)->right=NULL;
    }
    else{
        int cmp = strcmp(key, (*root)->key);
        if (cmp==0) (*root)->count++;
        else if (cmp>0) insert_node(&((*root)->right), key);
        else insert_node(&((*root)->left), key);
    }
}

int search_count(TreeNode* root, const char* key){
    if ((root)==NULL) return 0;
    int cmp =strcmp(key, root->key);
    if (cmp==0) return root->count;
    else if (cmp>0) return search_count(root->right, key);
    else return search_count(root->left, key);
}

int main() {
    
    TreeNode* city_tree = NULL;
    TreeNode* org_tree = NULL;
    TreeNode* date_tree = NULL;

    int choice;


    while (1) {
        printf("\n=== Інформаційна система БЛОКНОТ ===\n");
        printf("1. Додати особу в Блокнот\n");
        printf("2. Знайти кількість осіб за містом\n");
        printf("3. Знайти кількість осіб за організацією (місцем роботи)\n");
        printf("4. Знайти кількість осіб за днем народження\n");
        printf("5. Вийти з програми\n");
        printf("Ваш вибір: ");

        // Захист від введення літер замість цифр
        if (scanf("%d", &choice) != 1) {
            printf("Помилка вводу. Введіть число.\n");
            while (getchar() != '\n'); // Очищаємо буфер
            continue; // Повертаємося на початок циклу
        }

        switch (choice) {
            case 1:
                Person p;
                printf("\n--- Додавання нової особи ---\n");

                printf("Введіть прізвище та ім'я: ");
                scanf(" %[^\n]", p.name);

                printf("Введіть число та місяць народження (наприклад, 15.05): ");
                scanf(" %[^\n]", p.birth_date);

                printf("Введіть місто проживання: ");
                scanf(" %[^\n]", p.city);

                printf("Введіть організацію (місце роботи): ");
                scanf(" %[^\n]", p.workplace);

                insert_node(&city_tree, p.city);
                insert_node(&org_tree, p.workplace);
                insert_node(&date_tree, p.birth_date);
                break;
            case 2:
                {char search_city[50];
                printf("\n--- Пошук за містом ---\n");
                printf("Введіть назву міста для пошуку: ");
                scanf(" %[^\n]", search_city);

                int count =search_count(city_tree, search_city);
                printf("-> К-сть осіб, що мешкають у місті %s: %d\n",search_city,count);
                break;}
            case 3:
                {char search_org[50];
                printf("\n--- Пошук за організацією ---\n");
                printf("Введіть назву органцізації для пошуку: ");
                scanf(" %[^\n]", search_org);

                int count=search_count(org_tree, search_org);
                printf("-> К-сть осіб, що працюють у '%s': %d\n",search_org,count);
                break;}
            case 4:
                {char search_birth_date[50];
                printf("\n--- Пошук за днем народження ---\n");
                printf("Введіть число та місяць народження (наприклад, 15.05) для пошуку: ");
                scanf(" %[^\n]", search_birth_date);

                int count=search_count(date_tree, search_birth_date);
                printf("-> К-сть осіб, що народилися у %s: %d\n",search_birth_date,count);
                break;}
            case 5:
                printf("Вихід з меню!");
                return 0; 
            default:
                printf("\nНевірний вибір. Спробуйте ще раз (1-5).\n");
        }
    }

    return 0;
}