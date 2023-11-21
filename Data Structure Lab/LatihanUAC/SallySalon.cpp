#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int check = 0;

struct Salon{
	char treatment[50];
	char category[50];
	int price;
	char homeservice[50];
	int height;
	Salon *left, *right;
}*root = NULL;

Salon *createTreatment(const char treatment[], const char category[], int price, const char homeservice[]){
	Salon *newTreatment = (Salon*)malloc(sizeof(Salon));
	strcpy(newTreatment->treatment, treatment);
	strcpy(newTreatment->category, category);
	newTreatment->price = price;
	strcpy(newTreatment->homeservice, homeservice);
	newTreatment->height = 1;
	newTreatment->left = newTreatment->right = NULL;
	
	return newTreatment;
}

int getMax(int a, int b){
	return (a >= b) ? a : b;
}

int calculateHeight(Salon *curr){
	return (!curr) ? 0 : 1 + getMax(calculateHeight(curr->left), calculateHeight(curr->right));
}

int getBalance(Salon *curr){
	return (!curr) ? 0 : calculateHeight(curr->left) - calculateHeight(curr->right);
}

Salon *leftRotate(Salon *curr){
	Salon *newParent = curr->right;
	curr->right = newParent->left;
	newParent->left = curr;
	
	curr->height = calculateHeight(curr);
	newParent->height = calculateHeight(newParent);
	
	return newParent;
}

Salon *rightRotate(Salon *curr){
	Salon *newParent = curr->left;
	curr->left = newParent->right;
	newParent->right = curr;
	
	curr->height = calculateHeight(curr);
	newParent->height = calculateHeight(newParent);
	
	return newParent;
}

Salon *insertTreatment(Salon *curr, Salon *node){
	if (!curr){
		return node;
	} else if (strcmp(curr->treatment, node->treatment) > 0){
		curr->left = insertTreatment(curr->left, node);
	} else if (strcmp(curr->treatment, node->treatment) < 0){
		curr->right = insertTreatment(curr->right, node);
	} 
	
	curr->height = calculateHeight(curr);
	int balanceFactor = getBalance(curr);
	
	if (balanceFactor > 1){
		if (getBalance(curr->left) < 0){
			curr->left = leftRotate(curr->left);
		}
		return rightRotate(curr);
	} else if (balanceFactor < -1){
		if (getBalance(curr->right) > 0){
			curr->right = rightRotate(curr->right);
		}
		return leftRotate(curr);
	}
}

Salon *deleteTreatment(Salon *curr, const char name[]){
	if (!curr){
		return curr;
	} else if (strcmp(name, curr->treatment) < 0){
		curr->left = deleteTreatment(curr->left, name);
	} else if (strcmp(name, curr->treatment) > 0){
		curr->right = deleteTreatment(curr->right, name);
	} else {
		if (!curr->left && !curr->right){
			free(curr);
			curr = NULL;
		} else if (!curr->left){
			Salon *temp = curr;
			curr = curr->right;
			free(temp);
			temp = NULL;
		} else if (!curr->right){
			Salon *temp = curr;
			curr = curr->left;
			free(temp);
			temp = NULL;
		} else {
			Salon *temp = curr->left;
			while (temp->right){
				temp = temp->right;
			}
			strcpy(curr->treatment, temp->treatment);
			strcpy(curr->category, temp->category);
			strcpy(curr->homeservice, temp->homeservice);
			curr->price = temp->price;
			curr->left = deleteTreatment(curr->left, temp->treatment);
		}
	}
	
	if (!curr){
		return curr;
	}
	
	curr->height = calculateHeight(curr);
	int balanceFactor = getBalance(curr);
	
	if (balanceFactor > 1){
		if (getBalance(curr->left) < 0){
			curr->left = leftRotate(curr->left);
		}
		return rightRotate(curr);
	} else if (balanceFactor < -1){
		if (getBalance(curr->right) > 0){
			curr->right = rightRotate(curr->right);
		}
		return leftRotate(curr);
	}
	
	printf("[Delete successfully]\n");
	printf("Press enter to continue.."); getchar();
	return curr;
}

void find(Salon *curr, const char treatmentToDel[]){
	if (!curr){
		return;
	}
	find(curr->left, treatmentToDel);
	if (strcmp(curr->treatment, treatmentToDel) == 0){
		root = deleteTreatment(root, treatmentToDel);
		check = 1;
	}
	find(curr->right, treatmentToDel);
}

void checkExist(Salon *curr, const char treatmentToDel[]){
	check = 0;
	find(curr, treatmentToDel);
	if (check == 0){
		printf("Data not found!\n");
		return;
	}
}

void preOrder(Salon *curr){
	if (!curr){
		return;
	}
	printf("|| %30s || %12s || %10d || %15s ||\n", curr->treatment, curr->category, curr->price, curr->homeservice);
	preOrder(curr->left);
	preOrder(curr->right);
}

void inOrder(Salon *curr){
	if (!curr){
		return;
	}
	inOrder(curr->left);
	printf("|| %-30s || %12s || %10d || %15s ||\n", curr->treatment, curr->category, curr->price, curr->homeservice);
	inOrder(curr->right);
}

void postOrder(Salon *curr){
	if (!curr){
		return;
	}
	postOrder(curr->left);
	postOrder(curr->right);
	printf("|| %30s || %12s || %10d || %15s ||\n", curr->treatment, curr->category, curr->price, curr->homeservice);
}

void display(Salon *curr){
	char view[50];
	if (!curr){
		printf("no data\n");
		return;
	}
	
	printf("input view order [pre | in | post]: \n");
	scanf("%s", view); getchar();
	if (strcmp(view, "pre") == 0){
		preOrder(curr);
	} else if (strcmp(view, "in") == 0){
		inOrder(curr);
	} else if (strcmp(view, "post") == 0){
		postOrder(curr);
	} else {
		return;
	}
}


int main(){
	
	char treatment[50];
	char category[50];
	char treatmentDel[50];
	int price;
	char homeservice[50];
	int input;
	
	do {
		puts("Menu: ");
		puts("1. View Available Treatment");
		puts("2. Insert New Treatment");
		puts("3. Delete Treatment");
		puts("4. Exit");
		puts("[1-4]");
		printf(">> ");
		scanf("%d", &input); getchar();
		
		if (input == 1){
			display(root);
		} else if (input == 2){
			do {
				printf("Input new treatment name: ");
				scanf("%[^\n]", treatment); getchar();			
			} while (!strstr(treatment, "Sally ") || strlen(treatment) < 5 || strlen(treatment) > 20);
			
			do {
				printf("Input treatment price [50000 - 1000000]: ");
				scanf("%d", &price); getchar();
			} while (price < 50000 || price > 1000000);
			
			do {
				printf("Input treatment category [Hair Care | Nail Care | Body Care]: ");
				scanf("%[^\n]", category); getchar();
			} while (strcmp(category, "Hair Care") != 0 && strcmp(category, "Nail Care") != 0 && strcmp(category, "Body Care") != 0);
		
			do {
				printf("Input treatment availability for home service [Available | Unavailable]: ");
				scanf("%s", homeservice); getchar();
			} while (strcmp(homeservice, "Available") != 0 && strcmp(homeservice, "Unavailable") != 0);
			
			char temp[50];
			sprintf(temp, "Sally %s", treatment);
			
			root = insertTreatment(root, createTreatment(treatment, category, price, homeservice));
			
			printf("[New Treatment is Successfully Inserted]\n");
			printf("Press enter to continue..."); getchar();
		} else if (input == 3){
			printf("input treatment name to be deleted: ");
			scanf("%[^\n]", treatmentDel); getchar();
			checkExist(root, treatmentDel);
		}                 
		
	} while (input != 4);
	
}
