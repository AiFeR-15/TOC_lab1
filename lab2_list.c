#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
    
}Node;

void add_node(Node** head, Node** tail, int new_data){
    Node* newNode= (Node*)malloc(sizeof(Node));

    if (newNode==NULL){
        printf("Помилка пам'яті\n");
        return;
    }
    newNode->data=new_data;
    newNode->next=NULL;

    if(*head==NULL){
        *head=newNode;
        *tail=newNode;
    }
    else{
        (*tail)->next=newNode;
        *tail=newNode;
    }
}
void print_list (Node* head){
    Node* current=head;
    while(current != NULL){
        printf("%d ", current->data);
        current=current->next;
    }
    printf("\n");
}

void free_list(Node* head){
    Node* current = head;
    Node* next_node=NULL;

    while (current != NULL){
        next_node=current->next;
        free(current);
        current=next_node;
    }
}

int main(){
    Node* head = NULL;
    Node* tail = NULL;

    int n, value, E;
    printf("Введіть к-сть елементів n: ");
    scanf("%d", &n);

    printf("Введіть %d числе: \n", n);
    for (int i=0; i<n; i++){
       scanf("%d",&value);
       add_node(&head, &tail, value);
    }

    printf("Початковий спсиок L: ");
    print_list(head);

    printf("Введть значенння Е:");
    scanf("%d", &E);

    Node* ext_head=NULL;
    Node* ext_tail=NULL;
    Node* current=head;

    while(current !=NULL){
        if(current->data == E && current->next != NULL){
            Node* node_to_move=current->next; // 1. Захопили "2"
            current->next=node_to_move->next; // 2. Зшили розрив: "5" вказує на "3"
            node_to_move->next=NULL; // 3. Відірвали "2" остаточно
        
            if (ext_head==NULL){
                ext_head=node_to_move;
                ext_tail=node_to_move;
            }
            else{
                ext_tail->next=node_to_move;
                ext_tail=node_to_move;
            }
            current=current->next;
        }
        else current=current->next;
    }

    if(ext_head!=NULL){
        ext_tail->next=head;
        head = ext_head;
    }
    else printf("НЕ було вилучених елементів!");

    printf("Список після переміщення елементів: ");
    print_list(head);

    free_list(head);
    return 0;
}