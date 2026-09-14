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

int simile (int arr[], int n, int value){
    for(int i=0; i<n; i++){
        if(arr[i]==value){
            return 1;
        }
    }
    return 0;
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

    while(top != NULL){
        int val = pop(&top);
        push(&tempStack, val);
    }

    while (tempStack != NULL){
        int current = pop(&tempStack);

        if(simile(arr,arr_count,current)==0){
            arr[arr_count++]=current;
            push(&top,current);
        }
    }
    printf("\n--- Після видалення дублікатів ---\n");
    print_stack(top);
    
    free(arr);
     return 0;
 }