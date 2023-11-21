#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SIZE = 26;

struct Node{
	char name[101];
	int age;
}*table[SIZE];

Node *createNode(const char name[],int age){
	Node *node = (Node*)malloc(sizeof(Node));
	strcpy(node->name, name);
	node->age = age;
	return node;
}

int hash(const char *name){
	char c = name[0];
	if(c >= 'A' && c<= 'Z'){
		return c - 'A';
	}else if(c >= 'a' && c <= 'z'){
		return c - 'a';
	}
	return c % SIZE;
}


void insertNode(const char *name, int age){
	int key = hash(name);
	
	if(!table[key]){
		table[key] = createNode(name,age);
		return;
	}
	
	int curr = key + 1;
	
	while(key != curr && table[curr]){
		curr = (curr + 1) % SIZE;
	}
	if(curr == key){
		printf("Table Full\n");
		return;
	}
	table[curr] = createNode(name,age);
}

void deleteNode(char *name){
    int key = hash (name);
    if (table[key] && strcmp(table[key]->name, name) == 0){
        free(table[key]);
        table[key] = NULL;
        return;
    }
    int curr = key + 1;
    while (key != curr && (!table[curr] || strcmp(table[curr]->name, name) != 0)){
        curr = (curr + 1) % SIZE;
    }

    if (key == curr){
        printf("%s not found\n", name);
        return;
    }

    free(table[curr]);
    table[curr] = NULL;
}

void view(){
	for (int i=0;i<SIZE;i++){
		printf("%d. ",i);
		Node *curr = table[i];
		if(curr){
			printf("%s - %d\n",curr->name,curr->age);
		}else{
			printf("-\n");
		}
	}
}

int main(){
	
	insertNode("budi", 20);
    insertNode("clara", 25);
    insertNode("abel", 20);
    insertNode("abdul", 26);
	
	// for(int i=0;i<35;i++){
	// 	char name[20];
	// 	sprintf(name, "budi %d",i);
	// 	insertNode(name,20);
	// }
	
	view();
}