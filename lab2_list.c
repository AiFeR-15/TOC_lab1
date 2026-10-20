#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
    
}Node;

void add_node(Node** head, Node** tail, int new_data){

}
void print_list (Node* head){

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
            Node* node_to_move=current->next;
            current->next=node_to_move->next;
            
        }
    }
}