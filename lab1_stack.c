#include <stdio.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void push(Node** top_ref, int new_data){
     Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL){
        printf("Помилка: не вдалося створити новий елемент\n");
        return 1;
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
 int main() {

    

     return 0;
 }