#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int lastID = 0;
int count = 0;
int check = 0;

struct Property{
    char ID[50];
    int N;
    int length;
    char type[50];
    int price;
    int height;

    Property *left, *right;
}*root = NULL;

Property *createProperty(const char *ID, int N, int length, const char *type){
    Property *newProperty = (Property*)malloc(sizeof(Property));
    lastID++;
    // if (count < 4){
    strcpy(newProperty->ID, ID);
    //     count++;
    //     lastID++;
    // } else {
    //     char tempID[50];
    //     sprintf(tempID, "TX%03d", &lastID);
    //     lastID++;
    //     strcpy(newProperty->ID, tempID);
    // }
    strcpy(newProperty->type, type);
    newProperty->N = N;
    newProperty->length = length;
    newProperty->height = 1;
    if (N == 4){
        double area = (double) (length*length);
        if (strcmp(newProperty->type, "rural") == 0){
            newProperty->price = (int)(area * 2000);
        } else if (strcmp(newProperty->type, "metro") == 0){
            newProperty->price = (int)(area * 5500);
        } else if (strcmp(newProperty->type, "capital") == 0){
            newProperty->price = (int)(area * 10000);
        }
    } else {
        double area = (double)((N * length * length) / (4 * tan(3.14/N)));
        if (strcmp(newProperty->type, "rural") == 0){
            newProperty->price = (int) ((area * 2000));
        } else if (strcmp(newProperty->type, "metro") == 0){
            newProperty->price =(int) ((area * 5500));
        } else if (strcmp(newProperty->type, "capital") == 0){
            newProperty->price = (int)((area * 10000));
        }
    }

    newProperty->left = newProperty->right = NULL;

    return newProperty;
}

int getMax(int a, int b){
    return (a >= b) ? a : b;
}

int calcHeight(Property *curr){
    return (!curr) ? 0 : 1 + getMax(calcHeight(curr->left), calcHeight(curr->right));
}

int getBalance(Property *curr){
    return (!curr) ? 0 : calcHeight(curr->left) - calcHeight(curr->right);
}

Property *leftRotate(Property *curr){
    Property *newParent = curr->right;
    curr->right = newParent->left;
    newParent->left = curr;

    curr->height = calcHeight(curr);
    newParent->height = calcHeight(newParent);

    return newParent;
}

Property *rightRotate(Property *curr){
    Property *newParent = curr->left;
    curr->left = newParent->right;
    newParent->right = curr;

    curr->height = calcHeight(curr);
    newParent->height = calcHeight(newParent);

    return newParent;
}

Property *insertProperty(Property *curr, Property *node){
    if (!curr){
        return node;
    } else if (strcmp(node->ID, curr->ID) < 0){
        curr->left = insertProperty(curr->left, node);
    } else if (strcmp(node->ID, curr->ID) > 0){
        curr->right = insertProperty(curr->right, node);
    } 

    curr->height = calcHeight(curr);
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

Property *deleteProperty(Property *curr, const char *ID){
    if (!curr){
        return curr;
    } else if (strcmp(ID, curr->ID) < 0){
        curr->left = deleteProperty(curr->left, ID); 
    } else if (strcmp(ID, curr->ID) > 0){
        curr->right = deleteProperty(curr->right, ID);
    } else {
        if (!curr->left && !curr->right){
            free(curr);
            curr = NULL;
        } else if (!curr->left){
            Property *temp = curr;
            curr = curr->right;
            free(temp);
            temp = NULL;
        } else if (!curr->right){
            Property *temp = curr;
            curr = curr->left;
            free(temp);
            temp = NULL;
        } else {
            Property *temp = curr->left;
            while (temp->right){
                temp = temp->right;
            }
            strcpy(curr->ID, temp->ID);
            strcpy(curr->type, temp->type);
            curr->N = temp->N;
            curr->length = temp->length;
            curr->price = temp->price;
            curr->left = deleteProperty(curr->left, temp->ID);
        }
    }

    if (!curr){
        return curr;
    }

    curr->height = calcHeight(curr);
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

void find(Property *curr, const char *ID){
    if (curr){
        find(curr->left, ID);
        if (strcmp(ID, curr->ID) == 0){
            check = 1;
            root = deleteProperty(root, ID);
        }
        find(curr->right, ID); 
    }
    return;
}

void checkExist(Property *curr, const char *ID){
    check = 0;
    find(curr, ID);
    if (check == 0){
        printf("No Property!\n");
    }
    return;
}

void inOrder(Property *curr){
    if (!curr){
        return;
    }
    inOrder(curr->left);
    printf("| %5s | %-3d | %-5d | %-8s | %-10d |\n", curr->ID, curr->N, curr->length, curr->type, curr->price);
    inOrder(curr->right);
}

void preOrder(Property *curr){
    if(!curr){
        return;
    }
    printf("| %5s | %-3d | %-5d | %-8s | %-10d |\n", curr->ID, curr->N, curr->length, curr->type, curr->price);
    preOrder(curr->left);
    preOrder(curr->right);
}

int main(){

    int input;
    char type[50];
    int N;
    int length;
    char show[50];
    char idToDelete[50];

    root = insertProperty(root, createProperty("TX003", 6, 10, "metro"));
	root = insertProperty(root, createProperty("TX002", 4, 5, "capital"));
	root = insertProperty(root, createProperty("TX004", 10, 100, "capital"));
	root = insertProperty(root, createProperty("TX001", 5, 1, "rural"));

    do {
        printf("FleX polyperty\n");
        inOrder(root);
        printf("\n");
        puts("1. Insert Property");
        puts("2. Change View");
        puts("3. Delete Property");
        puts("4. Exit");
        printf(">> "); scanf("%d", &input); getchar();
        if (input == 1){
            do {
                printf("Input property location type [capital|metro|rural]: ");
                scanf("%s", type); getchar();
            } while (strcmp(type, "capital") != 0 || strcmp(type, "metro") != 0 || strcmp(type, "rural") != 0);

            do {
                printf("Input number of sides [4-10]: ");
                scanf("%d", &N); getchar();
            } while (N < 4 || N > 10);

            do {
                printf("Input side's length [1 - 1000]: ");
                scanf("%d", &length); getchar();
            } while (length < 1 || length > 1000);

            printf("Property Inserted!\n");
            printf("Press Enter to Continue!\n"); getchar();

            char tempID[50];
            sprintf(tempID, "TX%03d", &lastID);
            root = insertProperty(root, createProperty(tempID, N, length, type));
        } else if (input == 2){
            printf("Select view option [pre|in] (Case Sensitive): ");
            scanf("%s", show); getchar();
            if (strcmp(show, "pre") == 0){
                preOrder(root);
            } else if (strcmp(show, "in") == 0){
                inOrder(root);
            }
        } else if (input == 3){
            printf("Input property id (Case Sensitive): ");
            scanf("%s", idToDelete); getchar();
            checkExist(root, idToDelete);
        }
    } while (input != 4);

}