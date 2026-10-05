#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void push(Node** head,Node** tail, int new_data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL){
        printf("Помилка: не вдалося створити новий елемент\n");
        return ;
    }
    if(*(head) == NULL){
        *head=newNode;
        *tail=newNode;
    }
    else{
        newNode->data=new_data;
        *(tail)->next=newNode;
    }
}
int pop(Node** head){
    if(*head == NULL){
        printf("Queue null");
        return -1;
    }
    Node* temp= *head;
    int pop_data=temp->data;
    *(head)=(*head)->next;
    free(temp);
    return(pop_data);
}

 int main() {
    Node* head = NULL;
    Node* tail = NULL;
    int n,value;

    printf("Enter the number of elements n: ");
    scanf("%d", &n);

    

     return 0;
}
