#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Membership{
	char membName[100];
	Membership *left, *right;
}*membRoot;

struct Customer{
	char custName[100];
	char membName[100];	
	Customer *left, *right;
}*custRoot;

struct Membership *createMemb(const char name[]){
	Membership *newRoot = (Membership*)malloc(sizeof(Membership));
	strcpy(newRoot->membName, name);
	newRoot->left = newRoot->right = NULL;
	return newRoot;
}

struct Customer *createCust(const char custName[], const char custMemb[]){
	Customer *newRoot = (Customer*)malloc(sizeof(Customer));
	strcpy(newRoot->custName, custName);
	strcpy(newRoot->membName, custMemb);
	newRoot->left = newRoot->right = NULL;
	return newRoot;
}

struct Membership *insertMemb(Membership *curr, Membership *node){
	if (!curr){
		return node;
	} else if (strcmp(node->membName, curr->membName) < 0){
		curr->left = insertMemb(curr->left, node);
	} else if (strcmp(node->membName, curr->membName) > 0){
		curr->right = insertMemb(curr->right, node);
	}
	return curr;
}

struct Customer *insertCust(Customer *curr, Customer *node){
	if (!curr){
		return node;
	} else if (strcmp(node->custName, curr->custName) < 0){
		curr->left = insertCust(curr->left, node);
	} else if (strcmp(node->custName, curr->custName) > 0){
		curr->right = insertCust(curr->right, node);
	}
	return curr;
}

void updateMemb(Customer *curr, const char name[], const char memb[]){
	if (strcmp(curr->custName, name) == 0){
		strcpy(curr->membName, memb);
		printf("Membership updated!\n");
		return;
	}
	if (strcmp(curr->custName, name) > 0){
		return updateMemb(curr->left, name, memb);
	} else {
		return updateMemb(curr->right, name, memb);
	}
}

int searchMemb(Membership *curr, const char name[]){
	if (!curr){
		return 0;
	}
	if (strcmp(curr->membName, name) == 0){
		return 1;
	} 
	if (strcmp(curr->membName, name) > 0){
		return searchMemb(curr->left, name);
	} else {
		return searchMemb(curr->right, name);
	}
}

int searchCust(Customer *curr, const char name[]){
	if (!curr){
		return 0;
	}
	if (strcmp(curr->custName, name) == 0){
		return 1;
	} 
	if (strcmp(curr->custName, name) > 0){
		return searchCust(curr->left, name);
	} else {
		return searchCust(curr->right, name);
	}
}

struct Customer *deleteCust(Customer *curr, const char name[]){
	if (!curr){
		printf("Customer not found, delete customer canceled!");
		return curr;
	} else if (strcmp(curr->custName, name) > 0){
		curr->left = deleteCust(curr->left, name);
	} else if (strcmp(curr->custName, name) < 0){
		curr->right = deleteCust(curr->right, name);
	} else {
		if (!curr->left && !curr->right){
			free(curr);
			curr = NULL;
		} else if (!curr->left){
			Customer *temp = curr;
			curr = curr->right;
			free(temp);
		} else if (!curr->right){
			Customer *temp = curr;
			curr = curr->left;
			free(temp);
		} else {
			Customer *temp = curr->left;
			while (temp->right){
				temp = temp->right;
			}
				curr = temp;
				curr->left = deleteCust(curr->left, temp->custName);
		}
	}
	return curr;
}

void infix(Customer *curr){
	if (!curr){
		return;
	}
	infix(curr->left);
	printf("%s (%s) -> ", curr->custName, curr->membName);
	infix(curr->right);
}

void menu(){
	
	membRoot = insertMemb(membRoot, createMemb("Non-Member"));
	membRoot = insertMemb(membRoot, createMemb("Bronze"));
	membRoot = insertMemb(membRoot, createMemb("Silver"));
	membRoot = insertMemb(membRoot, createMemb("Gold"));
	membRoot = insertMemb(membRoot, createMemb("Platinum"));
	
	int input;
	int searchAvail;
	int searchAvailMemb;
	char addName[100];
	char addMemb[100];
	char delName[100];
	
	do{
		printf("\n");
		printf("==============================\n");
		printf("|     	  AYO DIPILIH        |\n");
		printf("==============================\n");
		printf("| 1. Add Customer            |\n");
		printf("| 2. View Customer           |\n");
		printf("| 3. Delete Customer         |\n");
		printf("| 4. Exit                    |\n");
		printf("==============================\n");
		printf(">> ");
		scanf("%d", &input); getchar();
		if (input == 1){
			do {
			printf("Input customer name [must be 3 - 50 characters] : ");
			scanf("%[^\n]", addName); getchar();				
			} while (strlen(addName) < 3 || strlen(addName) > 50);
			searchAvail = searchCust(custRoot, addName);
			
			do {
				printf("\n");
				printf("Membership List : \n");
				printf("1. Non-Member\n");
				printf("2. Bronze\n");
				printf("3. Silver\n");
				printf("4. Gold\n");
				printf("5. Platinum\n");
				printf("Input membership [case sensitive] : ");
				scanf("%[^\n]", addMemb); getchar();
				searchAvailMemb = searchMemb(membRoot, addMemb);
			} while (searchAvailMemb != 1);
			
			if (searchAvail == 1){
				updateMemb(custRoot, addName, addMemb);
				printf("Press enter to continue..."); getchar();
				system("cls");
			} else {
				custRoot = insertCust(custRoot, createCust(addName, addMemb));
				printf("Customer added successfully!\n");
				printf("Press enter to continue..."); getchar();
				system("cls");
			}
		} else if (input == 2){
			infix(custRoot);
			printf("\n");
			printf("Press enter to continue..."); getchar();
			system("cls");
		} else if (input == 3){
			do {
				printf("Input customer name you want to delete : ");
				scanf("%[^\n]", delName); getchar();
			} while (strlen(delName) < 3 || strlen(delName) > 50);
				searchAvail = searchCust(custRoot, delName);
			if (searchAvail == 1){
				custRoot = deleteCust(custRoot, delName);
				printf("Press enter to continue..."); getchar();
				system("cls");
			} else {
				printf("There are no customer!\n");
				printf("Press enter to continue..."); getchar();
				system("cls");
			}
		}
	} while (input != 4);
}

int main(){
	
	menu();
	
}
