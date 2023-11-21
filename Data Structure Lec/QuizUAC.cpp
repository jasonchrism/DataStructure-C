#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int lastId = 1;
int check = 0;

struct Book{
    char title[50];
    char author[50];
    int year;
    int rating;
    int ID;
    int height;

    Book *left, *right;
}*root = 0;

int getMax(int a, int b){
    return (a >= b) ? a : b;
}

int calculateHeight(Book *curr){
    return (!curr) ? 0 : 1 + getMax(calculateHeight(curr->left), calculateHeight(curr->right));
}

int getBalance(Book *curr){
    return (!curr) ? 0 : calculateHeight(curr->left) - calculateHeight(curr->right);
}

Book *rightRotate(Book *curr){
    Book *newParent = curr->left;
    curr->left = newParent->right;
    newParent->right = curr;

    curr->height = calculateHeight(curr);
    newParent->height = calculateHeight(newParent);
    return newParent;
}

Book *leftRotate(Book *curr){
    Book *newParent = curr->right;
    curr->right = newParent->left;
    newParent->left = curr;

    curr->height = calculateHeight(curr);
    newParent->height = calculateHeight(newParent);
    return newParent;
}

Book *createBook(const char *title, const char *author, int year, int rating){
    Book *newBook = (Book*)malloc(sizeof(Book));
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->year = year;
    newBook->rating = rating;
    newBook->ID = lastId;
    newBook->height = 1;
    newBook->left = newBook->right = NULL;
    lastId++;

    return newBook;
}

Book *insertBook(Book *curr, Book *node){
    if(curr == NULL){
        return node;
    } else if (curr->ID > node->ID){
        curr->left = insertBook(curr->left, node);
    } else if (curr->ID < node->ID){
        curr->right = insertBook(curr->right, node);
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

    return curr;
}

Book *deleteBook(Book *curr, int bookID){
    if (!curr){
        return curr;
    } else if (curr->ID < bookID){
        curr->right = deleteBook(curr->right, bookID);
    } else if (curr->ID > bookID){
        curr->left = deleteBook(curr->left, bookID);
    } else {
        if (!curr->right && !curr->left){
            free(curr);
            curr = NULL;
        } else if (!curr->right){
            // Book *temp = curr;
            // curr = curr->left;
            // free(temp);
            // temp = NULL;
            return curr->left;
        } else if (!curr->left){
            // Book *temp = curr;
            // curr = curr->right;
            // free(temp);
            // temp = NULL;
            return curr->right;
        } else {
            Book *temp = curr->left;
            while (temp->right){
                temp = temp->right;
            }
            strcpy(curr->title, temp->title);
            strcpy(curr->author, temp->author);
            curr->year = temp->year;
            curr->rating = temp->rating;
            curr->ID = temp->ID;
            curr->left = deleteBook(curr->left, temp->ID);
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

    } else if (balanceFactor < -1) {
        if (getBalance(curr->right) > 0){
            curr->right = rightRotate(curr->right);
        }
        return leftRotate(curr);
    }

    return curr;
}

void displayDescendant(Book *curr){
    if(!curr){
        return;
    }
    displayDescendant(curr->left);
    printf("%s\n", curr->title);
    displayDescendant(curr->right);
}

void findDescendant(Book *curr, const char *title){
    if (!curr){
        return ;
    } 
    findDescendant(curr->left, title);
    if (strcmp(curr->title, title) == 0){
        displayDescendant(curr);
        check = 1;
    }
    findDescendant(curr->right, title);
}

void findExistTitle(Book *curr, const char *title){
    if (!curr){
        return;
    }
    findExistTitle(curr->left, title);
    if (strcmp(curr->title, title) == 0){
        check = 1;
        return;
    }
    findExistTitle(curr->right, title);
}

int checkExistTitle(const char *title){
    check = 0;
    findExistTitle(root, title);
    if (check == 1){
        return 0;
    }
    return 1;
}

void checkExistDescendant(const char *title){
    check = 0;
    findDescendant(root, title);
    if (check == 0){
        printf("No Data Found!\n");
    }
    return;
}

void findID(int bookID, Book *curr){
    if (curr){
        findID(bookID, curr->left);
        if (curr->ID == bookID){
            printf("Book ID %d found:\nID: %d\nTitle: %s\nAuthor: %s\nYear: %d\nRating: %d\n", bookID, bookID, curr->title, curr->author, curr->year, curr->rating);
            check = 1;
        }
        findID(bookID, curr->right);
    }
}

void checkExist(int bookID){
    check = 0;
    findID(bookID, root);
    if (check == 0){
        printf("The data not found!\n");
    }
    return;
}

void inOrder(Book *curr){
    if (!curr){
        return;
    }
    inOrder(curr->left);
    printf("ID: %d\nTitle: %s\nAuthor: %s\nYear: %d\nRating: %d (%d)\n\n", curr->ID, curr->title, curr->author, curr->year, curr->rating, curr->height);
    inOrder(curr->right);
}

int totalChild(Book *curr){
    if (curr){
        return 1 + totalChild(curr->left) + totalChild(curr->right);
    } else {
        return 0;
    }
}

int main(){

    char command[50];
    char title[50];
    char checkTitle[50];
    char author[50];
    int input, totalInsert, year, rating, idToFind, idToDelete, total, temp;

    root = insertBook(root, createBook("More Than Balloons", "Gregor", 1997, 4));
	root = insertBook(root, createBook("Dump Truck", "Heimdall", 2000, 3));	
	root = insertBook(root, createBook("Hello World", "Travy", 1999, 4));	
	root = insertBook(root, createBook("Secret Tetris", "Tetron", 2010, 5));	
	root = insertBook(root, createBook("Florian", "Homer", 1997, 2));	
	root = insertBook(root, createBook("Sea Gardener", "Garen", 2005, 4));
	root = insertBook(root, createBook("Wild Dog", "Hisna", 2006, 4));
	root = insertBook(root, createBook("Trump Game", "Fiona", 2009, 2));
	root = insertBook(root, createBook("Class Act", "Navi", 2001, 1));
	root = insertBook(root, createBook("Silly Bear", "Garen", 2020, 5));

    scanf("%d", &input); getchar();
    for (int i = 0; i < input; i++){
        scanf("%s", command); getchar();
        if (strcmp(command, "INSERT") == 0){
            scanf("%d", &totalInsert); getchar();
            for (int j = 0; j < totalInsert; j++){
                do {
                    scanf("%[^#]#%[^#]#%d#%d", title, author, &year, &rating); getchar();
                    temp = checkExistTitle(title);
                    if (temp == 0){
                        printf("Title already exist!\n");
                    }
                } while (temp != 1);
                root = (insertBook(root, createBook(title, author, year, rating)));
            }
        } else if (strcmp(command, "FIND") == 0){
            scanf("%d", &idToFind); getchar();
            checkExist(idToFind);
        } else if (strcmp(command, "DELETE") == 0){
            scanf("%d", &idToDelete); getchar();
            root = deleteBook(root, idToDelete);
        } else if (strcmp(command, "SHOWALL") == 0){
            inOrder(root);
        } else if (strcmp(command, "CHECKLEFTROOT") == 0){
            total = totalChild(root->left);
            printf("%d\n", total);
        } else if (strcmp(command, "CHECKRIGHTROOT") == 0){
            total = totalChild(root->right);
            printf("%d\n", total);
        } else if (strcmp(command, "CHECKTITLE") == 0){
            scanf("%[^\n]", checkTitle); getchar();
            checkExistDescendant(checkTitle);
        }
    }

}