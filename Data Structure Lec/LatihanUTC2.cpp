#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

struct Student{
	char name[100];
	char ID[100];
	int assets;
	int liability;
	int equity;
	
	Student *left, *right;
}*root;

Student *createRoot(const char name[], const char ID[], int liabilities, int equity){
	Student *newRoot = (Student*)malloc(sizeof(Student));
	strcpy(newRoot->name, name);
	strcpy(newRoot->ID, ID);
	newRoot->assets = liabilities + equity;
	return newRoot;
}

Student *insertRoot(Student *curr, Student *node){
	if (!curr){
		return node;
	} else if (strcmp(curr->name, node->name) > 0){
		curr->left = insertRoot(curr->left, node);
	} else if (strcmp(curr->name, node->name) < 0){
		curr->right = insertRoot(curr->right, node);
	}
	return curr;
}

Student *deleteRootName(Student *curr, const char tempSearch[]){
	if (!curr){
		return curr;
	} else if (strcmp(curr->name, tempSearch) > 0){
		curr->left = deleteRootName(curr->left, tempSearch);
	} else if (strcmp(curr->name, tempSearch) < 0){
		curr->right = deleteRootName(curr->right, tempSearch);
	} else {
		if (!curr->right && !curr->left){
			free(curr);
			curr = NULL;
		} else if (!curr->right){
			Student *temp = curr;
			curr = curr->left;
			free(temp);
		} else if (!curr->left){
			Student *temp = curr;
			curr = curr->right;
			free(temp);
		} else {
			Student *temp = curr->left;
			while (curr->right){
				curr = curr->right;
			}
			strcpy(curr->name, temp->name);
			strcpy(curr->ID, temp->ID);
			curr->assets = temp->assets;
			curr->left = deleteRootName(curr->left, temp->name);
		}
	}
	return curr;
}

Student *deleteRoot(Student *curr, char delName[]){
	if (!curr){
		return curr;
	} else if (strcmp(curr->name, delName) > 0){
		curr->left = deleteRoot(curr->left, delName);
	} else if (strcmp(curr->name, delName) < 0){
		curr->right = deleteRoot(curr->right, delName);
	} else {
		if (!curr->right && !curr->left){
			free(curr);
			curr = NULL;
		} else if (!curr->left){
			Student *temp = curr;
			curr = curr->left;
			free(temp);
		} else if (!curr->right){
			Student *temp = curr;
			curr = curr->left;
		} else {
			Student *temp = curr->left;
			while (temp->right){
				temp = temp->right;
			}
			strcpy(curr->name, temp->name);
			strcpy(curr->ID, temp->ID);
			curr->assets = temp->assets;
			curr->left = deleteRoot(curr->left, temp->name);
		}
	}
	return curr;
}

int searchByName(Student *curr, const char tempSearch[], int tempLia){
	if (!curr){
		return 0;
	} 
	if (strcmp(curr->name, tempSearch) == 0){
		curr->assets = curr->assets + tempLia;
		deleteRootName(root, tempSearch);
		root = insertRoot(root, curr);
	}
	
	if (strcmp(curr->name, tempSearch) > 0){
		return searchByName(curr->left, tempSearch, tempLia);
	} else {
		return searchByName(curr->right, tempSearch, tempLia);
	}
}

int searchByID(Student *curr, const char tempSearch[], int tempLia){
	if (!curr){
		return 0;
	}
	
	if (strcmp(curr->ID, tempSearch) == 0){
		curr->assets = curr->assets + tempLia;
		deleteRootName(root, tempSearch);
		root = insertRoot(root, curr);
	}
	
	if (strcmp(tempSearch, curr->ID) <= 0){
		return searchByName(curr->left, tempSearch, tempLia);
	} else {
		return searchByName(curr->right, tempSearch, tempLia);
	}	
}

void view(Student *curr){
	if (!curr){
		return;
	}
	view(curr->left);
	printf("Name	: %s\n", curr->name);
	printf("ID      : %s\n", curr->ID);
	printf("Assets 	: %d\n", curr->assets);
	printf("\n");
	view(curr->right);
}

void menu(){
	int input;
	char name[100];
	int liabilities;
	int equity;
	char ID[100];
	char tempSearch[100];
	int checkAvail;
	int tempLia;
	char delName[100];
	
	do {
		puts("Gators Accounting");
		puts("=================");
		puts("1. Add");
		puts("2. View");
		puts("3. Edit");
		puts("4. Delete");
		puts("0. Exit");
		printf(">> ");
		scanf("%d", &input); getchar();
	
		if (input == 1){
			printf("Input Student Name : ");
			scanf("%[^\n]", name); getchar();
			
			printf("Input Current Liabilities : ");
			scanf("%d", &liabilities); getchar();
			
			printf("Input Current Equity : ");
			scanf("%d", &equity); getchar();
			
			int temp = (rand() % 80000) + 10000;
			
			sprintf(ID, "ST-%d-%c%c", temp, toupper(name[0]), toupper(name[strlen(name)-1]));
			
			root = insertRoot(root, createRoot(name, ID, liabilities, equity));
		} else if (input == 2){
			view(root);
		} else if (input == 3){
			printf("Input Name or ID : ");
			scanf("%[^\n]", tempSearch); getchar();
			
			printf("Input Liabilities or Equity : ");
			scanf("%d", &tempLia); getchar();
			
			if (tempSearch[0] == 'S' && tempSearch[1] == 'T' && tempSearch[2] == '-'){
				checkAvail = searchByID(root, tempSearch, tempLia);
			} else {
				checkAvail = searchByName(root, tempSearch, tempLia);
			}
			
			if (checkAvail == 0){
				printf("Data Not Found!\n");
			}
		} else if (input == 4){
			printf("Input Name or ID want to delete : ");
			scanf("%[^\n]", delName); getchar();
			root = deleteRoot(root, delName);
		}
	} while (input != 0);
}

int main(){
	
	menu()
;	
}
