#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

struct Property{
	char id[6];
	int N;
	int length;
	char type[20];
	
	int height;
	Property *left, *right;
} *root = NULL;

int max(int a, int b){
	return (a > b) ? a : b;
}

int getHeight(Property* curr){
	if(!curr) return 0;
	return curr->height;
}

int calculateHeight(Property* curr){
	return max(getHeight(curr->left), getHeight(curr->right)) + 1;
}

int getBalanceFactor(Property* curr){
	if(!curr) return 0;
	return getHeight(curr->left) - getHeight(curr->right);
}

Property* leftRotate(Property* curr){
	Property* cR = curr->right;
	Property* cRL = cR->left;
	
	cR->left = curr;
	curr->right = cRL;
	
	curr->height = calculateHeight(curr);
	cR->height = calculateHeight(cR);
	
	return cR;
}

Property* rightRotate(Property* curr){
	Property* cL = curr->left;
	Property* cLR = cL->right;
	
	cL->right = curr;
	curr->left = cLR;
	
	curr->height = calculateHeight(curr);
	cL->height = calculateHeight(cL);
	
	return cL;
}

Property* createProperty(char id[], int N, int length, char type[]){
	Property* temp = (Property*)malloc(sizeof(Property));
	strcpy(temp->id, id);
	strcpy(temp->type, type);
	temp->N = N;
	temp->length = length;
	temp->height = 1;
	temp->left = temp->right = NULL;
	return temp;
}

Property* insertProperty(Property* curr, Property* node){
	if(!curr) return node;
		// kiri lebih besar = positif
		// kanan lebih besar = negatif
	else if (strcmp(curr->id, node->id) > 0){
		curr->left = insertProperty(curr->left, node);
	}
	else if (strcmp(curr->id, node->id) < 0){
		curr->right = insertProperty(curr->right, node);
	}
	
	curr->height = calculateHeight(curr);
	int BF = getBalanceFactor(curr);
	
	if(BF > 1){
		if (strcmp(node->id, curr->left->id) > 0){
			curr->left = leftRotate(curr->left);
		}	
		return rightRotate(curr);
	}
	else if (BF < -1){
		if (strcmp(node->id, curr->right->id) < 0){
			curr->right = rightRotate(curr->right);
		}
		return leftRotate(curr);
	}
	
	return curr;
}

Property* deleteProperty(Property *curr, char *id){
	if(!curr) return curr;
	else if(strcmp(id, curr->id) < 0){
		curr->left = deleteProperty(curr->left, id);
	}	
	else if(strcmp(id, curr->id) > 0){
		curr->right = deleteProperty(curr->right, id);
	}
	else {
		if(!curr->left && !curr->right){
			free(curr);
			curr = NULL;
		}
		else if (!curr->left){
			Property *temp = curr->right; 
			free(curr);
			curr = temp;
		}
		else if (!curr->right){
			Property *temp = curr;
			curr = curr->left;
			free(temp);
			temp = NULL;
		}
		else {
			Property* temp = curr->left;
			while(temp->right){
				temp = temp->right;
			}
			
			strcpy(curr->id, temp->id);
			strcpy(curr->type, temp->type);
			curr->N = temp->N;
			curr->length = temp->length;
			
			curr->left = deleteProperty(curr->left, temp->id);
		}
	}
	
	if(!curr) {
		return curr;
	}
	
	curr->height = calculateHeight(curr);
	int BF = getBalanceFactor(curr);
	
	if(BF > 1){		
		if(getBalanceFactor(curr->left) < 0){
			curr->left = leftRotate(curr->left);
		}
		return rightRotate(curr);
	} else if(BF < -1){
		if(getBalanceFactor(curr->right) > 0){
			curr->right = rightRotate(curr->right);
		}
		return leftRotate(curr);
	}
	
	return curr;
}

Property* searchProperty(Property *curr, char *id){
	if(!curr) return NULL;
	else if(strcmp(id, curr->id) < 0){
		return searchProperty(curr->left, id);
	}	
	else if(strcmp(id, curr->id) > 0){
		return searchProperty(curr->right, id);
	}
	
	return curr;
}

Property* deleteAll(Property* curr){
	while(curr){
		curr = deleteProperty(curr, curr->id);
	}
	return curr;
}

void printProperty(Property* curr){
	int landPrice = 0;
	long long int area = 0;
	const double phi = 3.14;
	
	if(strcmp(curr->type, "rural") == 0){
		landPrice = 2000;
	}
	else if(strcmp(curr->type, "metro") == 0){
		landPrice = 5500;
	} 
	else if(strcmp(curr->type, "capital") == 0){
		landPrice = 10000;
	} 
	
	if(curr->N == 4){
		area = pow(curr->length, 2);
	}
	else {
		area = (curr->N * pow(curr->length, 2)) / (4 * tan(phi / curr->N));
	}
	
	long long int price = area * landPrice;
	
	// Rata kiri kasih minus, rata kanan ga usah minus
	printf("%5s | %-2d | %-4d | %-20s | %d\n", curr->id,
		curr->N, curr->length, curr->type, price);
}

void inOrder(Property* curr){
	if(!curr) return;
	inOrder(curr->left);
	printProperty(curr);
	inOrder(curr->right);
}

void preOrder(Property* curr){
	if(!curr) return;
	printProperty(curr);
	preOrder(curr->left);
	preOrder(curr->right);
}

void menu(){
	printf("Flex Polyperty\n");
	
	printf("1. Insert Property\n");
	printf("2. Change View\n");
	printf("3. Delete Property\n");
	printf("4. Exit\n");
	printf(">> ");
	
}

void menuInsert(){
	char id[6];
	int N;
	int length;
	char type[20];
	
	printf("Insert property location type [capital | metro | rural]: ");
	scanf("%[^\n]", type);
}

int main(){
//	root = insertProperty(root, createProperty("TX003", 5, 10, "capital"));
//	root = insertProperty(root, createProperty("TX001", 7, 100, "rural"));
//	root = insertProperty(root, createProperty("TX005", 5, 15, "rural"));
//	root = insertProperty(root, createProperty("TX006", 4, 5, "capital"));
//	root = insertProperty(root, createProperty("TX002", 10, 20, "metro"));
//	root = insertProperty(root, createProperty("TX004", 8, 8, "metro"));
	
	root = insertProperty(root, createProperty("TX003", 6, 10, "metro"));
	root = insertProperty(root, createProperty("TX002", 4, 5, "capital"));
	root = insertProperty(root, createProperty("TX004", 10, 1000, "capital"));
	root = insertProperty(root, createProperty("TX001", 5, 1, "rural"));
	
	// update TX001 Land type to capital
//	Property *temp = searchProperty(root, "TX001");
//	strcpy(temp->type, "capital");
//	
//	inOrder(root);
	
//	root = deleteProperty(root, "TX006");
//	root = deleteProperty(root, "TX001");
//	root = deleteProperty(root, "TX003");
//	root = deleteProperty(root, "TX002");
//	root = deleteProperty(root, "TX004");
//	root = deleteProperty(root, "TX005");
//	root = deleteAll(root);	
//	printf("\nAFTER DELETE \n");
	inOrder(root);
	
	return 0;
}
