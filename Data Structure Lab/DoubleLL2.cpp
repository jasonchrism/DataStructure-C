#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data{
    char name[100];
    int age;
    struct data *next, *prev;
};

struct data *createNode(const char name[], int age){
    data *temp = (data*)malloc(sizeof(data));
    strcpy(temp->name, name);
    temp->age = age;
    temp->prev = temp->next = NULL;
    return temp;
}

void pushHead(data **head, data **tail, data *temp){
    if (!*head){
        *head = *tail = temp;
    } else {
        (*head)->prev = temp;
        temp->next = *head;
        *head = temp;
    }
}

void pushTail(data **head, data **tail, data *temp){
    if (!*head){
        *head = *tail = temp;
    } else {
        (*tail)->next = temp;
        temp->prev = *tail;
        *tail = temp;
    }
}

void pushValue(data **head, data **tail, data *temp){
    if (!*head || strcmp(temp->name, (*head)->name) < 0){
        pushHead(head, tail, temp);
    } else if (strcmp(temp->name, (*tail)->name) >= 0){
        pushTail(head, tail, temp);
    } else {
        data *curr = *head;
        while (strcmp(temp->name, curr->next->name) >= 0){
            curr = curr->next;
        }
        temp->next = curr->next;
        curr->next->prev = temp;
        temp->prev = curr;
        curr->next = temp;
    }
}

void popHead(data **head, data **tail){
    if (!*head) return;
    else if (*head == *tail){
        free(*head);
        *head = *tail = NULL;
    } else {
        *head = (*head)->next;
        free((*head)->prev);
        (*head)->prev = NULL;
    }
}

void popTail(data **head, data **tail){
    if (!*head) return;
    else if (*head == *tail){
        free(*head);
        *head = *tail = NULL;
    } else {
        *tail = (*tail)->prev;
        free((*tail)->next);
        (*tail)->next = NULL;
    }
}

void popValue(data **head, data **tail, char *name){
    if (!*head) return;
    else if (strcmp(name, (*head)->name) == 0)
        popHead(head, tail);
    else if (strcmp(name, (*tail)->name) == 0)
        popTail(head, tail);
    else {
        data *curr = *head;
        while (strcmp(curr->name, name) != 0)
            curr = curr->next;
        if (curr->next == NULL){
            printf("%s not found!\n", name);
            return;
        }
        curr->next->prev = curr->prev;
        curr->prev->next = curr->next;
        free(curr);
        curr = NULL;
    }
}

void popAll(data **head, data **tail){
    while (*head != NULL){
        popHead(head, tail);
    }
}

void view(data *head){
    data *curr = head;
    while (curr != NULL){
        printf("%s | %d\n", curr->name, curr->age);
        curr = curr->next;
    }
}

int main(){
    data *head = NULL, *tail = NULL;

    // pushHead(&head, &tail, createNode("Jason", 18));
    // pushTail(&head, &tail, createNode("Chrisbellno", 20));
    // pushTail(&head, &tail, createNode("Mackenzie", 22));
    pushValue(&head, &tail, createNode("erik", 30));
    pushValue(&head, &tail, createNode("abdul", 22));
    pushValue(&head, &tail, createNode("zefa", 19));
    pushValue(&head, &tail, createNode("budi", 22));
    pushValue(&head, &tail, createNode("xavier", 22));
    pushValue(&head, &tail, createNode("sapi", 25));
    // popHead(&head, &tail);
    // popValue(&head, &tail, "abdul");
    popTail(&head, &tail);
    popAll(&head, &tail);
    view(head);

}