#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data{
    char name[20];
    int age;
    struct data *next;
}*head = 0;

void push(const char name[], int age){
    // create new node
    struct data *temp = (struct data*)malloc(sizeof(struct data));
    // fill the node with required data
    temp->age = age;
    temp->next = 0;
    strcpy(temp->name, name);

    // check if stack / linked list is null / empty
    if (head == 0){
        head = temp;
    } else {
        temp->next = head;
        head = temp;
    }
}

void popHead(){
    if (head == NULL){
        printf("Stack is empty!\n");
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

    push("Jason", 18);
    push("Chrisbellno", 30);
    push("Mackenzie", 40);

    popHead(); 

    display();

}