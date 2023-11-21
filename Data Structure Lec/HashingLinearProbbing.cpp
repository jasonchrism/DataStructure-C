#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxArrSize = 20;

struct data{
	char heroName[20];
	char heroType[5];
	int level;
};

struct data *dataArr[maxArrSize];

int hashFunc(char heroName[]){
	char first = heroName[0];
	char last = heroName[strlen(heroName)-1];
	
	int res = (first + last) % maxArrSize;
	return res;
}

void insert(char heroName[], char heroType[], int level){
	struct data *temp = (struct data*)malloc(sizeof(struct data));
	strcpy(temp->heroName, heroName);
	strcpy(temp->heroType, heroType);
	temp->level = level;
	
	//	get hash / value from hash function
	int idx = hashFunc(heroName);
	printf("%s %d\n", temp->heroName, idx);
	// if current index is NULL
	if (dataArr[idx] == 0){
		dataArr[idx] = temp;
	}
	// if current index is NOT NULL
	else {
		int currIdx = idx + 1;
		// loop until found empty spot
		while (dataArr[currIdx] != NULL) {
			currIdx++;
			if (currIdx >= maxArrSize) currIdx = 0;
			if (currIdx == idx) break;
		}
		// if array is full
		if (currIdx == idx) printf("Array is full!\n");
		//if found empty spot
		else {
			dataArr[currIdx] = temp;
		}
	}
}

void display(){
	for (int i = 0; i < maxArrSize; i++){
		if (dataArr[i] != NULL){
			printf("%s \n", dataArr[i]->heroName);	
		}
	}
}

int main(){
	insert("axe", "str", 1);
	insert("axe", "str", 1);
	insert("axe", "str", 1);
}
