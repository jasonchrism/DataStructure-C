#include <stdio.h>
#include <stdlib.h>
#include <String.h>

const int SIZE = 26;

struct Food{
	char name[100];
	int price;
	Food *next, *prev;
};

struct Table{
	Food *head, *tail;
}*table[SIZE];

void initializeTable(){
	for (int i = 0; i < SIZE; i++){
		table[i] = (Table*)malloc(sizeof(Table));
		table[i]->head = table[i]->tail = NULL;
	}
	return;
}

int hash(const char name[]){
	char firstChar = name[0];
	if (firstChar  >= 'A' && firstChar <= 'Z'){
		return (firstChar - 'A') % SIZE;
	} else if (firstChar >= 'a' && firstChar <= 'z'){
		return (firstChar - 'a') % SIZE;
	}
	return firstChar % SIZE;
}

struct Food *createFood(const char name[], int price){
	Food *newFood = (Food*)malloc(sizeof(Food));
	strcpy(newFood->name, name);
	newFood->price = price;
	return newFood;
}

void pushHead(int key, Food *newFood){
	if (table[key]->head == NULL){
		table[key]->head = table[key]->tail = newFood;
	} else {
		newFood->next = table[key]->head;
		table[key]->head->prev = newFood;
		table[key]->head = newFood;
	}
	return;
}

void pushTail(int key, Food *newFood){
	if (table[key]->head == NULL){
		table[key]->head = table[key]->tail = newFood;
	} else {
		newFood->prev = table[key]->tail;
		table[key]->tail->next = newFood;
		table[key]->tail = newFood;
	}
	return;
}

void pushMid(int key, Food *newFood){
	Food *curr = table[key]->head;
	while (strcmp(newFood->name, curr->next->name) >= 0){
		curr = curr->next;
	}
	newFood->next = curr->next;
	newFood->prev = curr;
	curr->next->prev = newFood;
	curr->next = newFood;
	return;
}

void popHead(const char name[]){
	int key = hash(name);
	if (table[key]->head == NULL){
		return;
	} else if (table[key]->head == table[key]->tail){
		free(table[key]->head);
		table[key]->head = table[key]->tail = NULL;
	} else {
		Food *newHead = table[key]->head->next;
		newHead->prev = NULL;
		free(table[key]->head);
		table[key]->head = newHead;
	}
	return;
}

void popTail(const char name[]){
	int key = hash(name);
	if (table[key]->head == NULL){
		return;
	} else if (table[key]->head == table[key]->tail){
		free(table[key]->head);
		table[key]->head = NULL;
	} else {
		Food *newTail = table[key]->tail->prev;
		newTail->next = NULL;
		free(table[key]->tail);
		table[key]->tail = newTail;
	}
	return;
}

void popMid(int key, const char name[]){
	Food *curr = table[key]->head;
	while (curr && strcmp(name, curr->name) != 0){
		curr = curr->next;
	}
	if (curr == NULL){
		return;
	}
	curr->prev->next = curr->next;
	curr->next->prev = curr->prev;
	free(curr);
	return;
}

void deleteFood(const char name[]){
	int key = hash(name);
	
	if (table[key]->head == NULL){
		return;
	} else if (strcmp(name, table[key]->head->name) == 0){
		popHead(name);
	} else if (strcmp(name, table[key]->tail->name) == 0){
		popTail(name);
	} else {
		popMid(key, name);
	}
}

void insertFood(const char name[], int price){
	int key = hash(name);
	Food *newFood = createFood(name, price);
	if (table[key]->head == NULL || strcmp(name, table[key]->head->name) < 0){
		pushHead(key, newFood);
	} else if (table[key]->tail == NULL || strcmp(name, table[key]->tail->name) >= 0){
		pushTail(key, newFood);
	} else {
		pushMid(key, newFood);
	}
}

void view(){
	for (int i = 0; i < SIZE; i++){
		Food *curr = table[i]->head;
		while (curr){
			printf("%s %d\n", curr->name, curr->price);
			curr = curr->next;
		}
	}
	return;
}

int main(){
	
	initializeTable();
//	view();
	insertFood("Sate Padang",29000);
	insertFood("Sup Jagung",29000);
	insertFood("Sate Ayam",29000);
	insertFood("Sate Kambing",29000);
	view();
	
	printf("\n");
	
	deleteFood("Sate Padang");
	view();
	
}
