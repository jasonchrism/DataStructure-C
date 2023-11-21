#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Food{
	char name[100];
	int price;
	Food *left, *right;
}*root;

struct Food *createFood(const char name[], int price){
	struct Food *newFood = (Food*)malloc(sizeof(Food));
	strcpy(newFood->name, name);
	newFood->price = price;
	newFood->right = newFood->left = NULL;
	return newFood;
}

struct Food *insertFood(Food *curr, Food *food){
	if (!curr){
		return food;
	} else if (strcmp(food->name, curr->name) < 0){
		curr->left = insertFood(curr->left, food);
	} else if (strcmp(food->name, curr->name) > 0){
		curr->right = insertFood(curr->right, food);
	}
	return curr;
}

void infix(Food *curr){
	if (!curr){
		return;
	}
	infix(curr->left);
	printf("%s %d -> ", curr->name, curr->price);
	infix(curr->right);
}

void prefix(Food *curr){
	if (!curr){
		return;
	}
	printf("%s %d -> ", curr->name, curr->price);
	prefix(curr->left);
	prefix(curr->right);
}

void postfix(Food *curr){
	if (!curr){
		return;
	}
	postfix(curr->left);
	postfix(curr->right);
	printf("%s %d -> ", curr->name, curr->price);
}

struct Food *deleteFood(Food *curr, const char name[]){
	if (!curr){
		return curr;
	} else if (strcmp(name, curr->name) < 0){
		curr->left = deleteFood(curr->left, name);
	} else if (strcmp(name, curr->name) > 0){
		curr->right =deleteFood(curr->right, name);
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
			curr->left = deleteFood(curr->left, temp->name);
		}
	}
	return curr;
}

struct Food *searchFood(Food *curr, const char name[]){
	if (!curr){
		return curr;
	}
	if (strcmp(curr->name, name) == 0){
		return curr;
	}
	if (strcmp(name, curr->name) < 0){
		return searchFood(curr->left, name);
	} else {
		return searchFood(curr->right, name);
	}
}

Food *deleteAll(Food *curr){
	while (curr){
		deleteFood(curr, curr->name);
	}
	return curr;
}

int main(){
	
	root = insertFood(root, createFood("Nasi Goreng", 20000));
	root = insertFood(root, createFood("Mie Goreng", 25000));
	root = insertFood(root, createFood("Kwetiau Goreng", 15000));
	root = insertFood(root, createFood("Bakso Goreng", 22000));
	root = insertFood(root, createFood("Babi Goreng", 18000));
	root = insertFood(root, createFood("Kucing Goreng", 20000));
	
	infix(root);
	
}
