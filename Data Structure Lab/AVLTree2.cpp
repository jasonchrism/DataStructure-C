#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct Food{
	int id;
	char name[101];
	int price;
	int height;
	Food *left, *right;
};

Food *createFood(int id, char *name, int price){
	Food *newFood = (Food*)malloc(sizeof(Food));
	newFood->id = id;
	strcpy(newFood->name, name);
	newFood->price = price;
	newFood->height = 1;
	newFood->left = newFood->right = NULL;
	
	return newFood;
}

Food *insertFood(Food *curr, Food *food){
	if (!curr) return food;
	else if (food->id < curr->id)
		curr->left = insertFood(curr->left, food);
	else if (food->id >= curr->id)
		curr->right = insertFood(curr->right, food);
	return curr;
}

void inOrder(Food *curr){
	if (!curr) return;
	inOrder(curr->left);
	printf("%-3d %-50s %-6d (%d)\n", curr->id, curr->name, curr->price, curr->height);
	inOrder(curr->right);
}

Food *deleteFood(Food *curr, int id){
	if (curr == 0){
		return curr;
	} else if (id < curr->id){
		curr->left = deleteFood(curr->left, id);
	} else if (id > curr->id){
		curr->right = deleteFood(curr->right, id);
	} else {
		// if node has no child 
		if (!curr->right && !curr->left){
			free(curr);
			curr = NULL;
		} else if (!curr->right){
			Food *del = curr;
			curr = curr->left;
			free(del);
			del = NULL;
		} else if (!curr->left){
			Food *del = curr;
			curr = curr->right;
			free(del);
			del = NULL;
		} else {
			Food *temp = curr->left;
			while(temp->right){
				temp = temp->right;
			}
			curr->id = temp->id;
			strcpy(curr->name, temp->name);
			curr->price = temp->price;
			curr->left = deleteFood(curr->left, temp->id);
		}
	}	
	return curr;
}

int main(){
	Food *root = NULL;
	
	root = insertFood(root, createFood(10, "Bakso", 20000));
	root = insertFood(root, createFood(5, "Mie Ayam", 15000));
	root = insertFood(root, createFood(3, "Salad", 10000));
	root = insertFood(root, createFood(20, "Kari", 15000));
	root = insertFood(root, createFood(30, "Nasi Uduk", 25000));
	
	inOrder(root);
}
