#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxArrSize = 20;

struct data{
	char heroName[20];
	char heroType[5];
	int level;
	
	struct data *next;
};

struct data *dataArr[maxArrSize];

int hashFunc(char heroName[]){
	char first = heroName[0];
	char last = heroName[strlen(heroName)-1];
	
	int res = (first + last) % maxArrSize;
	return res;
}

void insert(char heroName[], const char heroType[], int level){
	struct data *temp = (struct data*)malloc(sizeof(struct data));
	strcpy(temp->heroName, heroName);
	strcpy(temp->heroType, heroType);
	temp->level = level;
	temp->next = NULL;
	
//	get hash / value from hash function
	int idx = hashFunc(heroName);
//	printf("%d\n", idx);
// insert to hash value, apply chaining if needed
// if current idx in hash table is empty
	if (dataArr[idx] == 0){
		dataArr[idx] = temp;
	}
// if current idx in hash table is not empty
	else {
		struct data *curr = dataArr[idx];
		while (curr->next != NULL) {
			curr = curr->next;
		}
		curr->next = temp;
	}
}

void display(){
	for (int i = 0; i < maxArrSize; i++){
		// if current idx is not empty
		if (dataArr[i] != 0){
			struct data *curr = dataArr[i];
			while (curr){
				printf("%s -> ", curr->heroName);
				curr = curr->next;
			}
			printf("\n");
		}
	}
}

int main(){
	insert("axe", "str", 1);
	insert("invoker", "int", 1);
	insert("sven", "str", 1);
	insert("axe", "str", 1);
	insert("sven", "str", 1);
	insert("magnus", "str", 1);	
	insert("juggernaut", "agi", 1);
	insert("sniper", "agi", 1);
	insert("andre", "str", 1);
	insert("junt", "int", 1);
	
	display();
}
