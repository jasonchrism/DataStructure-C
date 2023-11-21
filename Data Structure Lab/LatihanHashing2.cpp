#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

int hash(const char name[]){
	int firstChar = name[0];
	if (firstChar >= 'A' && firstChar <= 'Z')
    {
        return (firstChar - 'A') % size;
    }
    else if (firstChar >= 'a' && firstChar <= 'z')
    {
        return (firstChar - 'a') % size;
    }
    return firstChar % size;
}

struct Food *createFood(const char name[], int price){
	Food *newFood = (Food*)malloc(sizeof(Food));
	strcpy(newFood->name, name);
	newFood->price = price;
	return newFood;
}

void pushHead(int key, Food *newFood){
	if (table[key]->head == 0){
		table[key]->head = table[key]->tail = newFood;
	}
}

void insertFood(const char name[], int price){
	int key = hash(name);
	Food *newFood = createFood(name, price);
	if (table[key]->head == 0 || strcmp(name, table[key]->head->name) < 0){
		pushHead(key, newFood);
	} else if (table[key]->tail == 0 || strcmp(name, table[key]->tail->name) > 0){
		pushTail(key, newFood);
	} else {
		pushMid(key, newFood);
	}
}

int main(){
	
	
	
}
