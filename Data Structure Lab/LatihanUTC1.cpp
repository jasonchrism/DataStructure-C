#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int size = 26;

struct Food{
	char name[100];
	int price;
	Food *next, *prev;
};

struct Table{
	Food *head, *tail;
}*table[size];


void initialTable(){
	for (int i = 0; i < size; i++){
		table[i] = (Table*)malloc(sizeof(Table));
		table[i]->head = table[i]->tail = NULL;
	}
}

struct Food *createFood(const char name[], int price){
	Food *newFood = (Food*)malloc(sizeof(Food));
	strcpy(newFood->name, name);
	newFood->price = price;
	newFood->next = newFood->prev = NULL;
	return newFood;
}

int hash(const char name[]){
	int firstChar = name[0];
	if (firstChar >= 'A' && firstChar <= 'Z'){
		return (firstChar - 'A') % size;
	} else if (firstChar >= 'a' && firstChar <= 'z'){
		return (firstChar - 'a') % size;
	}
	return firstChar % size;
}

void pushHead(int key, Food *newFood){
	if (table[key]->head == 0){
		table[key]->head = table[key]->tail = newFood;
	} else {
		newFood->next = table[key]->head;
		table[key]->head->prev = newFood;
		table[key]->head = newFood;
	}
}

void pushTail(int key, Food *newFood){
	if (table[key]->tail == 0){
		table[key]->head = table[key]->tail = newFood;
	} else {
		newFood->prev = table[key]->tail;
		table[key]->tail->next = newFood;
		table[key]->tail = newFood;
	}
}

void pushMid(int key, Food *newFood){
	struct Food *curr = table[key]->head;
	while (curr != 0 && strcmpi(newFood->name, curr->next->name) >= 0){
		curr = curr->next;
	}
	newFood->next = curr->next;
	newFood->prev = curr;
	curr->next->prev = newFood;
	curr->next = newFood;
}

void insertFood(const char name[], int price){
	int key = hash(name);
	struct Food *newFood = createFood(name, price);
	
	if (table[key]->head == 0 || strcmpi(name, table[key]->head->name) < 0){
		pushHead(key, newFood);
	} else if (table[key]->tail == 0 || strcmpi(name, table[key]->tail->name) >= 0){
		pushTail(key, newFood);
	} else {
		pushMid(key, newFood);
	}
}

void view(){
	for (int i = 0; i < size; i++){
		struct Food *curr = table[i]->head;
		while (curr != 0){
			printf("%s %d -> ", curr->name, curr->price);
			curr =  curr->next;
		}
		printf("\n");
	}
}

int main(){
	
	initialTable();
    insertFood("A", 29000);
    insertFood("B", 29000);
    insertFood("C", 29000);
    insertFood("B", 30);
    insertFood("C", 9);
    insertFood("Sate Kambing", 29000);
    insertFood("Ayam Bakar", 20000);
	view();
	
}

