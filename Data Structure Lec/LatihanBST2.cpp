#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Food{
	char name[100];
	int price;
	Food *left, *right;
}*root;

struct Food *createFood(const char name[], int price){
	Food *newFood = (Food*)malloc(sizeof(Food));
	strcpy(newFood->name, name);
	newFood->price = price;
	newFood->right = newFood->left = NULL;
	return newFood;
}

struct Food *insertFood(Food *curr, Food *node){
	if(!curr){
		return node;
	} else if (strcmp(node->name, curr->name) < 0){
		curr->left = insertFood(curr->left, node);
	} else if (strcmp(node->name, curr->name) > 0){
		curr->right = insertFood(curr->right, node);
	}
	return curr;
}

struct Food *deleteNode(Food *curr, const char name[]){
	if (!curr){
		return curr;
	} else if (strcmp(name, curr->name) < 0){
		curr->left = deleteNode(curr->left, name);
	} else if (strcmp(name, curr->name) > 0){
		curr->right = deleteNode(curr->right, name);
	} else {
		if (!curr->right && !curr->left){
			free(curr);
			curr = NULL;
		} else if (!curr->left){
			Food *temp = curr;
			curr = curr->right;
			free(temp);
		} else if (!curr->right){
			Food *temp = curr;
			curr = curr->left;
			free(temp);
		} else {
			Food *temp = curr->left;
			while (temp->right){
				temp = temp->right;
			}
			strcpy(curr->name, temp->name);
			curr->price = temp->price;
			curr->left = deleteNode(curr->left, temp->name);
		}
	}
	return curr;
}


int search(Food *curr, const char name[]){
	if (!curr){
		return 0;
	}
	if (strcmp(name, curr->name) == 0){
		return 1;
	}
	if (strcmp(name, curr->name) < 0){
		return search(curr->left, name);
	} else {
		return search(curr->right, name);
	}
}

void infix(Food *curr){
	if (!curr){
		return;
	}
	infix(curr->left);
	printf("%s %d -> ", curr->name, curr->price);
	infix(curr->right);
}

int main(){
	
	root = insertFood(root, createFood("Sate", 20000));
	root = insertFood(root, createFood("Babi", 20000));
	root = insertFood(root, createFood("Ayam", 20000));
	root = insertFood(root, createFood("Kucing", 20000));
	root = insertFood(root, createFood("Naga", 20000));	
	
	infix(root);
	
	root = deleteNode(root, "Kucing");
	printf("\n");
	infix(root);
}
