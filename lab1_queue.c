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
    newNode->data=new_data;
    newNode->next=NULL;
    if(*(head) == NULL){
        *head=newNode;
        *tail=newNode;
    }
    else{
        newNode->data=new_data;
        (*tail)->next=newNode;
        *tail=newNode;
    }
}
int pop(Node** head, Node** tail){
    if(*head == NULL){
        printf("Queue null");
        return -1;
    }
    Node* temp= *head;
    int pop_data=temp->data;
    *(head)=(*head)->next;

    if (*head == NULL) {
        *tail = NULL;
    }

    free(temp);
    return(pop_data);
}

 int main() {
    Node* head = NULL;
    Node* tail = NULL;
    int n,value,k;

    printf("Enter the number of elements n: ");
    scanf("%d", &n);

    printf("Enter %d numbers: \n", n);

    for(int i = 0 ; i < n ; i++){
        scanf("%d", &value);
        push(&head, &tail, value);
    }

    printf("Queue output:");
    for(int i=0; i<n; i++){
        int current=pop(&head,&tail);
        printf("%d ", current);
        push(&head, &tail, current);
    }
    printf("\n");

    printf("Enter the divisor k: ");
    scanf("%d", &k);
    int original_n = n;
    for (int i=0;i<original_n;i++){
        int new=pop(&head,&tail);
        if(new % k !=0){
            push(&head, &tail, new);
        }
        else n=n-1;
    }
    printf("Queue output(multiples %d): ", k);
    for(int i=0; i<n; i++){
        printf("%d ", pop(&head,&tail));
    }
    printf("\n");

     return 0;
}
