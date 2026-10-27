#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* create_node(int new_data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = new_data;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

Node* insert(Node* root, int new_data) {
    if (root == NULL) return create_node(new_data);
    
    if (new_data < root->data) {
        root->left = insert(root->left, new_data);
    } else {
        root->right = insert(root->right, new_data);
    }
    return root;
}

void split(Node* current, int avg, Node** left_piece, Node** right_piece) {
    if (current == NULL) {
        *left_piece = NULL;
        *right_piece = NULL;
        return;
    }

    if (current->data < avg) {
        *left_piece = current;
        split(current->right, avg, &((*left_piece)->right), right_piece);
    } else {
        *right_piece = current;
        split(current->left, avg, left_piece, &((*right_piece)->left));
    }
}

void print_tree(Node* root, int space) {
    if (root == NULL) return;
    
    space += 5; // Збільшуємо кількість пробілів для кожного наступного рівня
    
    print_tree(root->right, space); // 1. Спочатку йдемо в саму праву гілку
    
    printf("\n");
    for (int i = 5; i < space; i++) printf(" "); // 2. Малюємо відступ
    printf("%d\n", root->data);                  // 3. Друкуємо число
    
    print_tree(root->left, space);  // 4. Потім йдемо в ліву гілку
}

int main() {
    srand(time(NULL));
    
    Node* root = NULL;
    int n, value;
    int sum = 0;
    
    printf("Введіть кількість елементів n: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    printf("Згенеровані числа: ");
    for (int i = 0; i < n; i++) {
        value = rand() % 100;
        printf("%d ", value);
        sum += value;
        root = insert(root, value);
    }
    printf("\n");

    printf("\n--- Початкове дерево ---\n");
    print_tree(root, 0);

    int avg = sum / n;
    printf("\nСереднє арифметичне: %d\n", avg);

    Node* left_subtree = NULL;
    Node* right_subtree = NULL;

    split(root, avg, &left_subtree, &right_subtree);

    Node* newRoot = create_node(avg);
    newRoot->left = left_subtree;
    newRoot->right = right_subtree;
    root = newRoot;

    printf("\n--- Змінене дерево (новий корінь: %d) ---\n", avg);
    print_tree(root, 0);

    return 0;
}