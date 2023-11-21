#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int leftTotal = 0;
int rightTotal = 0;
int check = 0;
int pinkChild = 0;
int yellowChild = 0;
int whiteChild = 0;

struct Data{
	char color[10];
	int value;
	int height;
	Data *left, *right;
}*root = NULL;

Data *createData(int value){
	Data *newData = (Data*)malloc(sizeof(Data));
	strcpy(newData->color, "white");
	newData->value = value;
	newData->height = 1;
	newData->left = newData->right = NULL;
	
	return newData;
}

int getMax(int a, int b){
	return (a >= b) ? a : b;
}

int calculateHeight(Data *curr){
	return (!curr) ? 0 : 1 + getMax(calculateHeight(curr->left), calculateHeight(curr->right));
}

int getBalance(Data *curr){
	return (!curr) ? 0 : calculateHeight(curr->left) - calculateHeight(curr->right);
}

Data *leftRotate(Data *curr){
	Data *newParent = curr->right;
	curr->right = newParent->left;
	newParent->left = curr;
	
	curr->height = calculateHeight(curr);
	newParent->height = calculateHeight(newParent);
	
	return newParent;
}

Data *rightRotate(Data *curr){
	Data *newParent = curr->left;
	curr->left = newParent->right;
	newParent->right = curr;
	
	curr->height = calculateHeight(curr);
	newParent->height = calculateHeight(newParent);
	
	return newParent;
}

void countRightRoot(Data *curr){
	if (!curr){
		return;
	}
	countRightRoot(curr->left);
	rightTotal = rightTotal + curr->value;
	countRightRoot(curr->right);
}

void countLeftRoot(Data *curr){
	if (!curr){
		return;
	}
	countLeftRoot(curr->left);
	leftTotal = leftTotal + curr->value;
	countLeftRoot(curr->right);
}

void assignColor(Data *curr){
	leftTotal = 0;
	rightTotal = 0;
	countLeftRoot(curr->left);
	countRightRoot(curr->right);
	if (rightTotal > leftTotal){
		strcpy(curr->color, "pink");
	} else if (leftTotal < rightTotal){
		strcpy(curr->color, "yellow");
	} else {
		strcpy(curr->color, "white");
	}
	return;
}

void color(Data *curr){
	if (!curr){
		return;
	}
	color(curr->left);
	assignColor(curr);
	color(curr->right);
}

Data *insertData(Data *curr, Data *node){
	if (!curr){
		return node;
	} else if (node->value < curr->value){
		curr->left = insertData(curr->left, node);
	} else if (node->value > curr->value){
		curr->right = insertData(curr->right, node);
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
	color(root);
	return curr;
}

const char* detColor(Data *curr){
	leftTotal = 0;
	rightTotal = 0;
	countLeftRoot(curr->left);
	countRightRoot(curr->right);
	if (rightTotal > leftTotal){
		strcpy(curr->color, "pink");
		return "pink";
	} else if (leftTotal < rightTotal){
		strcpy(curr->color, "yellow");
		return "yellow";
	} else {
		strcpy(curr->color, "white");
		return "white";
	}
}

void view(Data *curr){
	if (!curr){
		return;
	}
	view(curr->left);
	printf("%d %s\n", curr->value, detColor(curr));
	view(curr->right);
}

void countColor(Data *curr){
	if (!curr){
		return;
	}
	countColor(curr->left);
	if (strcmp(curr->color, "pink") == 0){
		pinkChild++;
	} else if (strcmp(curr->color, "white") == 0){
		whiteChild++;
	} else if (strcmp(curr->color, "yellow") == 0){
		yellowChild++;
	}
	countColor(curr->right);
}

void describe(Data *curr, int value){
	whiteChild = 0;
	pinkChild = 0;
	yellowChild = 0;
	printf("value: %d\n", value);
	printf("keyword: %s\n", detColor(curr));
	countColor(curr);
	printf("number of pink children: %d\n", pinkChild);
	printf("number of white children: %d\n", whiteChild);
	printf("number of yellow children: %d\n", yellowChild);
	return;
}

void find(Data *curr, int value){
	if(!curr){
		return;
	}
	find(curr->left, value);
	if (curr->value == value){
		describe(curr, value);
		check = 1;
		return;
	}
	find(curr->right, value);
}

void checkExist(Data *curr, int value){
	check = 0;
	find(curr, value);
	if (check == 0){
		printf("Data not found!\n");
		return;
	}
	return;
}

Data *deleteData(Data *curr, int value){
	if (!curr){
		return curr;
	} else if (value < curr->value){
		curr->left = deleteData(curr->left, value);
	} else if (value > curr->value){
		curr->right = deleteData(curr->right, value);
	} else {
		if (!curr->left && !curr->right){
			free(curr);
			curr = NULL;
		} else if (!curr->left){
			Data *temp = curr;
			curr = curr->right;
			free(temp);
			temp = NULL;
		} else if (!curr->right){
			Data *temp = curr;
			curr = curr->left;
			free(temp);
			temp = NULL;
		} else {
			Data *temp = curr->left;
			while (temp->right){
				temp = temp->right;
			}
			strcpy(curr->color, temp->color);
			curr->value = temp->value;
			curr->left = deleteData(curr->left, temp->value);
		}
	}
	
	if (!curr){
		return curr;
	}
	
	curr->height = calculateHeight(curr);
	int balanceFactor = getBalance(curr);
	
	if (balanceFactor > 1){
		if (getBalance(curr->left) < 0){
			curr->left - leftRotate(curr->left);
		}
		return rightRotate(curr);
	} else if (balanceFactor < -1){
		if (getBalance(curr->right) > 0){
			curr->right = rightRotate(curr->right);
		}
		return leftRotate(curr);
	}
	
	return curr;
}

void findDelete(Data *curr, int value){
	if (!curr){
		return;
	}
	findDelete(curr->left, value);
	if (curr->value == value){
		check = 1; 
		return;
	}
	findDelete(curr->right, value);
}

void checkDelete(Data *curr, int value){
	check = 0;
	findDelete(curr, value);
	if (check != 0){
		root = deleteData(curr, value);
	}
	printf("Data not found!\n");
	return;
}

const char *removeSpace(char *str){
	int len = strlen(str);
	for (int i = 0; i < len; i++){
		if (str[i] == ' '){
			for (int j = i; j < len; j++){
				str[j] = str[j+1];
			}
			len--;
		}
	}
	return str;
}

int main(){
	
	int input;
	char command[50];
	char temp[50];
	int num = 0;
	int count = 0;
	
	scanf("%d", &input); getchar();
	for (int i = 0; i < input; i++){
		scanf("%[^\n]", command); getchar();
		if (strstr(command, "INSERT")) {
			count = 0;
			for (int i = 6; i < strlen(removeSpace(command)); i++){
				temp[count] = command[i];
				count++;
			}
			sscanf(temp, "%d", &num);
			root = insertData(root, createData(num));
		} else if (strcmp(command, "VIEW") == 0){
			view(root);
		} else if (strstr(command, "DELETE")){
			count = 0;
			for (int i = 6; i < strlen(removeSpace(command)); i++){
				temp[count] = command[i];
				count++;
			}
			sscanf(temp, "%d", &num);
			checkDelete(root, num);
		} else if (strstr(command, "DESCRIBE")){
			count = 0;
			for (int i = 8; i < strlen(removeSpace(command)); i++){
				temp[count] = command[i];
				count++;
			}
			sscanf(temp, "%d", &num);
			checkExist(root, num);
		}
	}
	
}
