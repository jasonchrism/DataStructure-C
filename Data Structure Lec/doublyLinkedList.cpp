#include <stdio.h>
#include <stdlib.h>

struct node{
    int value;
    struct node *next;
    struct node *prev;
}*head = 0, *tail = 0;
struct node *newNode(int value){
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp->value = value;
    temp->next = temp->prev = 0;
    return temp;
}

void insertTail(int value){
    struct node *temp = newNode(value);

    // if insert 1st data
    if (head == 0){
        head = tail = temp;
    }
    // if insert >= 2nd data
    else {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
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

    if (head == 0){
        printf("Linked List is empty\n");
        return;
    }

    // if delete the only node in double LL
    if (head->value == value && head == tail){
        free(head);
        head = tail = 0;
    }
    // if delete head node
    else if (head->value == value){
        head = head->next;
        free(head->prev);
        head->prev = 0;
    }
    // if delete tail node
    else if (tail->value == value){
        tail = tail->prev;
        free(tail->next);
        tail->next = 0;
    }
    // if delete nod head or tail (somewhere in the middle)
    else {
        while (curr->next != NULL && curr->next->value != value){
            curr = curr->next;
        }

        if (curr->next != NULL){
            struct node *del = curr->next;
            curr->next = del->next;
            del->next->prev = curr;
            free(del);
        }
    }
}

int main(){

    insertTail(40);
    insertTail(30);
    insertTail(25);
    insertTail(20);

    deleteNode(90);

    displayAll();

}