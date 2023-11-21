#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// 13 Maret 2023 - BST Self Balancing
// AVL, Heap, Disjoint Set
// Insert, Update

// define struct
struct food {
	char name[100];
	int price;
	int height;
	food *left, *right;
};

// bikin data baru
food* createFood(const char *name, int price){
	// memory allocation
	food* newFood = (food*) malloc (sizeof(food));
	
	// masukkin data
	strcpy(newFood->name, name);
	newFood->price = price;
	newFood->height = 1;
	newFood->left = newFood->right = NULL;
	
	return newFood;
}

// 2, 1
int getMax(int a, int b){
	return (a >= b) ? a : b; 
}

int calculateHeight(food* node){
	// Versi singkatnya
	return (!node) ? 0 : 1 + getMax(calculateHeight(node->left), calculateHeight(node->right));
		
//	if(!node){
//		return 0;
//	}
//	
//	// Bandingin tinggi anak kiri dan anak kanan
//	// ambil yang lebih gede yg mana terus ditambah 1
//	
//	int leftHeight = calculateHeight(node->left);
//	int rightHeight = calculateHeight(node->right);
//	
//	// Bandingin
//	// Tambah 1
//	return 1 + getMax(leftHeight, rightHeight);

}

// Balance itu kalau -1, 0, 1
int getBalance(food* node){
	return (!node) ? 0 : (calculateHeight(node->left) - calculateHeight(node->right));
}

food* rightRotate(food* node){
	food* newParent = node->left;
	node->left = newParent->right;
	newParent->right = node;
	
	// Update Height
	node->height = calculateHeight(node);
	newParent->height = calculateHeight(newParent);

	return newParent;
}

food* leftRotate(food* node){
	food* newParent = node->right;
	node->right = newParent->left;
	newParent->left = node;
	
	// Update Height
	node->height = calculateHeight(node);
	newParent->height = calculateHeight(newParent);
	
	return newParent;
	
}

food* insertFood (food* root, const char *name, int price){
	// kalau rootnya belum ada data (root == NULL)
	if (!root){
		// langsung masukkin data barunya
		return createFood(name, price);
	}
	// kalau rootnya ada dan data yang mau dimasukkin lebih kecil
	else if (price < root->price){
		root->left = insertFood(root->left, name, price);	
	}
	// kalau rootnya ada dan data yang mau dimasukkin lebih besar
	else if (price > root->price){
		root->right = insertFood(root->right, name, price);
	}	
	
	// Update Height
	root->height = calculateHeight(root);
	
	// Cek Balance
	int balance = getBalance(root);

	// berat di kiri
	if(balance > 1){
		// kalau price > root->price (ada belok)
		// left rotate dulu
		if(price > root->price){
			root->left = leftRotate(root->left);
		}
		
		// right rotate
		return rightRotate(root);
	}
	// berat di kanan
	else if (balance < -1){
		// kalau price < root->price (ada belok)
		// right rotate 
		if(price < root->price){
			root->right = rightRotate(root->right);
		}
		// left rotate
		return leftRotate(root);
	}
	
	return root;
}

food* updateFood(food* root, int price, const char* newName){
	// udah nyari sampe ujung tapi datanya ga ketemu
	if(!root){
		printf("Data not found!\n");
		return root;
	}
	
	// data yang dicari lebbih kecil
	else if(price < root->price){
		root->left = updateFood(root->left, price, newName);
	}
	
	// data yang dicari lebih besar
	else if(price > root->price){
		root->right = updateFood(root->right, price, newName);
	}
	
	else{
		strcpy(root->name, newName);
		printf("Successfully updated!\n");	
	}
	// jangan lupa return balik rootnya
	return root;
}

// preOrder, inOrder, postOrder
// awal, tengah, akhir (Bagian printnya)

void inOrder(food* root){
	// udah ga ada data
	if(!root){
		return;
	}
	
	inOrder(root->left);
	printf("%s %d | height: %d | balance: %d\n", root->name, root->price, root->height, getBalance(root));
	inOrder(root->right);
	
	return;
}

int main(){
	// declare root (pertama kali masukkin data
	food* root = insertFood(NULL, "Sate Padang", 34000);
	root = insertFood(root, "Sate Kambing", 30000);
	root = insertFood(root, "Sate Ayam", 28000);
	root = insertFood(root, "Sate Kelinci", 26000);
	root = insertFood(root, "Sate Taichan", 24000);
	root = insertFood(root, "Sate Kuda", 22000);
	
	// tampilin data
	inOrder(root);	
	
	root = updateFood(root, 24000, "Sate Taichan Pedas");
	printf("\nAfter Update\n");
	inOrder(root);

	printf("\n");
	root = updateFood(root, 40000, "Sate Taichan Pedas Banget");
	inOrder(root);
	return 0;
}
