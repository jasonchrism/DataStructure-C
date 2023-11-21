#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Data{
	int value;
	int height;
	
	Data *left, *right;
}*root = 0, *temp;

int max(int a, int b){
	return a > b ? a : b;
}

int getHeight(Data *curr){
	if (curr == 0){
		return 0;
	}
	return curr->height;
}

int getBF(Data *curr){
	if (curr == 0){
		return 0;
	}
	return getHeight(curr->left) - getHeight(curr->right);
	// if BF > 1 --> berat kiri
	// if BF < -1 --> berat kanan
}

Data *rightRotation(Data *t){
	Data *s = t->left;
	Data *b = s->right;
	
	t->left = b;
	s->right = t;
	
	// update height (harus t dulu bru s)
	t->height = 1 + max(getHeight(t->left), getHeight(t->right));
	s->height = 1 + max(getHeight(s->left), getHeight(s->right));
	
	return s;
}

Data *leftRotation(Data *t){
	Data *s = t->right;
	Data *b = s->left;
	
	t->right = b;
	s->left = t;
	
	// update height (harus t dlu bru s)
	t->height = 1 + max(getHeight(t->left), getHeight(t->right));
	s->height = 1 + max(getHeight(s->left), getHeight(s->right));
	
	return s;
}

struct Data *createData(int value){
	temp = (Data*)malloc(sizeof(Data));
	temp->value = value;
	temp->height = 1;
	temp->left = temp->right = 0;
	
	return temp;
}

struct Data *insertData(Data *curr, int value){
	if (curr == 0){
		return createData(value);
	} else if (value < curr->value){
		curr->left = insertData(curr->left, value);
	} else if (value > curr->value){
		curr->right = insertData(curr->right, value);
	} else {
		return curr;
	}
	
	// update height
	curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
	
	// count BF
	int BF = getBF(curr);
	
	// Left Left
	if (BF > 1 && getBF(curr->left) >= 0){
		return rightRotation(curr);
	}
	
	// Right Right
	if (BF < -1 && getBF(curr->right) <= 0){
		return leftRotation(curr);
	}
	
	// Left Right
	if (BF > 1 && getBF(curr->left) < 0){
		curr->left = leftRotation(curr->left);
		return rightRotation(curr);
	}
	
	// Right Left
	if (BF < 1 && getBF(curr->right) > 0){
		curr->right = rightRotation(curr->right);
		return leftRotation(curr);
	}
	
	return curr;
}

void display(Data *curr){
	if (!curr){
		return;
	}
	if (curr){
		printf("%d ", curr->value);
		display(curr->left);
		display(curr->right);
	}
}

Data *deleteData(Data *curr, int value){
	if (curr == 0){
		return curr;
	} else if (value < curr->value){
		curr->left = deleteData(curr->left, value);
	} else if (value > curr->value){
		curr->right = deleteData(curr->right, value);
	} else {
		// if node has no child 
		if (!curr->right && !curr->left){
			free(curr);
			return 0;
		} 
		// if node only has left child
		else if (!curr->right){
			temp = curr->left;
			free(curr);
			return temp;
		}
		// if node only has right child
		else if (!curr->left){
			temp = curr->right;
			free(curr);
			return temp;
		} else {
			temp = curr->left;
			while (temp->right){
				temp = temp->right;
			}
			curr->value = temp->value;
			curr->left = deleteData(curr->left, temp->value);
		}
	}
	// update height
	curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
	
	// count BF
	int BF = getBF(curr);
	
	// Left Left
	if (BF > 1 && getBF(curr->left) >= 0){
		return rightRotation(curr);
	}
	
	// Right Right
	if (BF < -1 && getBF(curr->right) <= 0){
		return leftRotation(curr);
	}
	
	// Left Right
	if (BF > 1 && getBF(curr->left) < 0){
		curr->left = leftRotation(curr->left);
		return rightRotation(curr);
	}
	
	// Right Left
	if (BF < 1 && getBF(curr->right) > 0){
		curr->right = rightRotation(curr->right);
		return leftRotation(curr);
	}
	
	return curr;
}

void peek(){
	if (root){
		printf("\nRoot: %d\n\n", root->value);
	}
}

int main(){
	
	root = insertData(root, 70);
	root = insertData(root, 80);
	root = insertData(root, 90);
	root = insertData(root, 100);
	root = insertData(root, 50);
	display(root);
	peek();

	root = deleteData(root, 80);
	display(root);
	peek();
	
	root = deleteData(root, 50);
	display(root);
	peek();
	
	root = deleteData(root, 90);
	display(root);
	peek();
	
	return 0;
}
