#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data{
    char name[20];
    int age;
    struct data *next;
}*head = 0, *tail = 0;

void pushTail(const char name[], int age){
    struct data *temp = (struct data*)malloc(sizeof(struct data));
    temp->age = age;
    temp->next = 0;
    strcpy(temp->name, name);

    // if queue of linked list is empty
    if (tail == 0){
        head = tail = temp;
    } else {
        tail->next = temp;
        tail = temp;
    }
}

void popHead(){
    if (head == 0){
        printf("Queue is empty!\n");
    } else {
        struct data *del = head;
        head = head->next;
        free(del);
    }
}

void display(){
    struct data *curr = head;
    while (curr != NULL){
        printf("%s %d\n", curr->name, curr->age);
        curr = curr->next;
    }
}

int main(){

    pushTail("Jason", 20);
    pushTail("Chrisbellno", 25);
    pushTail("Mackenzie", 30);
    
    popHead();

    display();

}