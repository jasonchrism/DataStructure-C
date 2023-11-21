#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bookCount = 1;

struct Book{
    char title[100];
    char author[100];
    int release;
    int rating;
    int ID;
    int height;

    Book *left, *right;
}*root, *temp;

int getMax(int a, int b){
	return a > b ? a : b;
}

int calculateHeight(Book *node){
	return (!node) ? 0 : 1 + getMax(calculateHeight(node->left), calculateHeight(node->right));
}

int getBalance(Book *node){
    return (!node) ? 0 : calculateHeight(node->left) - calculateHeight(node->right);
}

Book *rightRotate(Book *node){
	Book *newParent = node->left;
	node->left = newParent->right;
	newParent->right = node;
	
	node->height = calculateHeight(node);
	newParent->height = calculateHeight(newParent);
	
	return newParent;
}

Book *leftRotate(Book *node){
	Book *newParent = node->right;
	node->right = newParent->left;
	newParent->left = node;
	
	node->height = calculateHeight(node);
	newParent->height = calculateHeight(newParent);
	
	return newParent;
}

Book *insertBook(Book *curr, Book *newBook){
    if (!curr){
        return newBook;
    } else if (curr->ID > newBook->ID){
        curr->left = insertBook(curr->left, newBook);
    } else if (curr->ID < newBook->ID){
        curr->right = insertBook(curr->right, newBook);
    }

    curr->height = calculateHeight(curr);
    int balanceFactor = getBalance(curr);
    if (balanceFactor > 1){
        if (getBalance(curr->left) <= 0){
            curr->left = leftRotate(curr->left);
        }
        return rightRotate(curr);
    } else if (balanceFactor < -1){
		if (getBalance(curr->right) >= 0){
			curr->right = rightRotate(curr->right);
		}
		return leftRotate(curr);
	}

    return curr;
}

Book *createBook(const char title[], const char author[], int release, int rating){
    Book *newBook = (Book *) malloc(sizeof(Book));
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->release = release;
    newBook->rating = rating;
    newBook->ID = bookCount;
    newBook->left = newBook->right = NULL;
    newBook->height = 1;

    bookCount++;
    return insertBook(root, newBook);
}

void inOrder(Book *curr){
    if (!curr){
        return;
    }
    inOrder(curr->left);
    printf("ID: \n", curr->ID);
    printf("Title: \n", curr->title);
    printf("Author: \n", curr->author);
    printf("Year: \n", curr->release);
    printf("Rating: \n\n", curr->rating);
    inOrder(curr->right);
}

int main(){
    int input;
    char command[100];
    int totalInsert;
    int find;
    int deleteBook;
    char title[100];
    char author[100];
    int release;
    int rating;

    root = createBook("More Than Balloons", "Gregor", 1997, 4);
    root = createBook("Dump Truck", "Heimdall", 2000, 3);
    root = createBook("Hello World", "Travy", 1999, 4);
    root = createBook("Secret Tetris", "Tetron", 2010, 5);
    root = createBook("Florian", "Homer", 1997, 2);
    root = createBook("Sea Gardener", "Garen", 2005, 4);
    root = createBook("Wild Dog", "Hisna", 2006, 4);
    root = createBook("Trump Game", "Fiona", 2009, 2);
    root = createBook("Class Act", "Navi", 2002, 1);
    root = createBook("Silly Bear", "Garen", 2020, 5);

    scanf("%d", &input); getchar();
    for (int i = 0; i < input; i++){
        scanf("%s", command); getchar();
        if (strcmp("INSERT", command) == 0){
            scanf("%d", &totalInsert); getchar();
            for (int j = 0; j < totalInsert; j++){
                scanf("%[^#]#%[^#]#%d#%d", title, author, &release, &rating); getchar();
            }
        } else if (strcmp("FIND", command) == 0){

        } else if (strcmp("DELTE", command) == 0){

        } else if (strcmp("SHOWALL", command) == 0){
            inOrder(temp);
        } else if (strcmp("CHECKLEFTROOT", command) == 0){

        } else if (strcmp("CHECKRIGHTROOT", command) == 0){

        }
    }
}