#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int data;
    struct Node* next;
} Node;

void push(Node** top_ref, int new_data){
     Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL){
        printf("Помилка: не вдалося створити новий елемент\n");
        return ;
    }
    newNode->data=new_data;
    newNode->next=(*top_ref);
    (*top_ref)=newNode;
}

int pop(Node** top_ref){
    if (*top_ref == NULL) {
        printf("Стек порожній!\n");
        return -1;
    }
    Node* temp= *top_ref;
    
    int pop_data= temp->data;

    *top_ref=temp->next;

    free(temp);

    return (pop_data);
}

void print_stack (Node* top){
   if (top == NULL) {
        printf("Стек порожній.\n");
        return;
    } 
    Node* current = top;
    printf("Стек (від вершини до дна): \n");

    while (current != NULL) {
        printf("%d ", current->data); 
        current = current->next;       
    printf("\n");
}
}

 int main() {
    Node* top = NULL;
    Node* tempStack = NULL;
    int n,value;

    printf("Введіть к-сть елементів n: ");
    scanf("%d", &n);

    printf("Введіть %d чисел:\n", n);
    for(int i=0; i<n ; i++){
        scanf("%d", &value);
        push(&top, value);
    }

    int* arr = (int*)malloc(n * sizeof(int));
    int arr_count = 0;

    while(top != NULL) {
        arr[arr_count++] = pop(&top);
    }

    for (int i = arr_count - 1; i >= 0; i--) {
        int is_duplicate = 0;
            for (int j = arr_count - 1; j > i; j--) {
                if (arr[i] == arr[j]) {
                    is_duplicate = 1;
                    break;
                }
            }
            if (is_duplicate == 0) {
                push(&top, arr[i]);
            }
    }
    printf("\n--- Після видалення дублікатів ---\n");
    print_stack(top);
    
    free(arr);
     return 0;
 }