#include<stdio.h>
#include<string.h>
#include<stdlib.h>

const int SIZE = 26;

struct Food{
	char name[100];
	int price;
	struct Food *next , *prev;
};

struct Table{
	struct Food *head, *tail;
}*table[SIZE];

void initializeTable(){
	for(int i=0; i<SIZE ; i++){
		table[i] = (Table*)malloc(sizeof(Table));
		table[i]->head = table[i]->tail = NULL;
	}
	return;
}

struct Food *createFood(const char *name, int price){
	struct Food *newFood = (Food*)malloc(sizeof(Food));
	strcpy(newFood->name , name);
	newFood->price = price;
	newFood->next = newFood->prev = NULL;
	return newFood;
}

void view(){
	for(int i=0; i<SIZE ; i++){
		struct Food *curr = table[i]->head;
		
		while(curr){
			printf("%s %d\n",curr->name , curr->price);
			curr = curr->next;
		}
	}
	return;
}

int hash(const char *name){
	char firstChar = name[0];
	if(firstChar >= 'A' && firstChar <= 'Z'){
		return (firstChar - 'A') % SIZE;
	}
	else if(firstChar >= 'a' && firstChar <= 'z'){
		return (firstChar - 'a') % SIZE;
	}
	return firstChar % SIZE;
}

void pushHead(int key, struct Food *newFood){
	if(table[key]->head == NULL){
		table[key]->head = table[key]->tail = newFood;
	}
	else{
		newFood->next = table[key]->head;
		table[key]->head->prev = newFood;
		table[key]->head = newFood;
	}
	return;
}

void pushTail(int key, struct Food *newFood){
	if(table[key]->head == NULL){
		table[key]->head = table[key]->tail = newFood;
	}
	else{
		newFood->prev = table[key]->tail;
		table[key]->tail->next = newFood;
		table[key]->tail = newFood;
	}
	return;
}

void pushMid(int key , struct Food *newFood){
	struct Food *curr = table[key]->head;
	
	while(curr && strcmp(newFood->name, curr->next->name)>=0){
		curr = curr->next;
	}
	newFood->next = curr->next;
	newFood->prev = curr;
	curr->next->prev = newFood;
	curr->next = newFood;
}

void insertFood(const char *name , int price){
	int key = hash(name);
	struct Food *newFood = createFood(name , price);
	if(table[key]->head == NULL || strcmp(name,table[key]->head->name) < 0){
		pushHead(key, newFood);
	}
	else if(strcmp(name,table[key]->tail->name)>=0){
		pushTail(key,newFood);
	}
	else{
		pushMid(key,newFood);
	}
}

void popHead(int key){
	if(table[key]->head==NULL){
		return;
	}
	else if(table[key]->head == table[key]->tail){
		free(table[key]->head);
		table[key]->head = table[key]->tail = NULL;
	}
	else{
		struct Food *newHead = table[key]->head->next;
		newHead->prev = NULL;
		free(table[key]->head);
		table[key]->head = newHead;
	}
}

void popTail(int key){
	if(table[key]->tail==NULL){
		return;
	}
	else if(table[key]->head == table[key]->tail){
		free(table[key]->tail);
		table[key]->head = table[key]->tail = NULL;
	}
	else{
		struct Food *newTail = table[key]->tail->prev;
		newTail->next = NULL;
		free(table[key]->tail);
		table[key]->tail = newTail;
	}
}

void popMid(int key , const char *name){
	struct Food *curr = table[key]->head;
	while(curr && strcmp(name, curr->name)!=0){
		curr = curr->next;
	}
	if(curr==NULL){
		return;
	}
	curr->prev->next = curr->next;
	curr->next->prev = curr->prev;
	free(curr);
	
	return;
}

void deleteFood(const char *name){
	int key = hash(name);
	
	if(table[key]->head==NULL){
		return;
	}
	else if(strcmp(name,table[key]->head->name)==0){
		popHead(key);
	}
	else if(strcmp(name,table[key]->tail->name)==0){
		popTail(key);
	}
	else{
		popMid(key , name);
	}
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
//	printf("%s %d\n",table[18]->head->name, table[18]->head->price);
	
	
}
