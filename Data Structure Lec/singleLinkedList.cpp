#include <stdio.h>
#include <stdlib.h>

struct node{
    int value;
    struct node *next;
}*head = NULL;

struct node *newNode(int value){
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp->value = value;
    temp->next = NULL;
    return temp;
}

void insertNode(int value){
    struct node *temp = newNode(value);

    //if inserting the first data
    if (head == NULL){
        head = temp;
    }
    //if inserting the second or more data
    else {
        temp->next = head;
        head = temp;
    }
}

void displayAll(){
    struct node *curr = head;
    while (curr != NULL){
        printf("%d\n", curr->value);
        curr = curr->next;
    }
}

void deleteNode(int value){ 
    struct node *curr = head;
    
    // if value to delete is in head
    if (head->value == value){
        head = curr->next;
        free(curr);
    }

    // if value to delete is in mid or last of linked list
    else {
        while (curr->next != NULL && curr->next->value != value){
            curr = curr->next;
        }

        if (curr->next != NULL){
            struct node *del = curr->next;
            curr->next = del->next;
            free(del);
        }
    }
}

int main(){

    insertNode(15);
    insertNode(20);
    insertNode(25);
    insertNode(5);

    deleteNode(5);
    deleteNode(15);
    deleteNode(35);

    displayAll();

    return 0;

}