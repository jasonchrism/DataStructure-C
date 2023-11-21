#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int check = 0;
char type[50];
int stockToUpdate;

struct Game{
    char title[50];
    char genre[50];
    int stock;

    int height;
    Game *left, *right;
}*root = NULL;

int getMax(int a, int b){
    return (a >= b) ? a : b;
}

int calculateHeight(Game *curr){
    return (!curr) ? 0 : 1 + getMax(calculateHeight(curr->left), calculateHeight(curr->right));
}

int getBalance(Game *curr){
    return (!curr) ? 0 : calculateHeight(curr->left) - calculateHeight(curr->right);
}

Game *leftRotate(Game *curr){
    Game *newParent = curr->right;
    curr->right = newParent->left;
    newParent->left = curr;

    curr->height = calculateHeight(curr);
    newParent->height = calculateHeight(curr);

    return newParent;
}

Game *rightRotate(Game *curr){
    Game *newParent = curr->left;
    curr->left = newParent->right;
    newParent->right = curr;

    curr->height = calculateHeight(curr);
    newParent->height = calculateHeight(newParent);

    return newParent;
}

Game *createGame(const char *title, const char *genre, int stock){
    Game *newGame = (Game*)malloc(sizeof(Game));
    strcpy(newGame->title, title);
    strcpy(newGame->genre, genre);
    newGame->stock = stock;
    newGame->height = 1;
    newGame->left = newGame->right = NULL;
    return newGame;
}

Game *insertGame(Game *curr, Game *node){
    if (!curr){
        return node;
    } else if (strcmp(node->title, curr->title) < 0){
        curr->left = insertGame(curr->left, node);
    } else if (strcmp(node->title, curr->title) > 0){
        curr->right = insertGame(curr->right, node);
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

Game *deleteGame(Game *curr, const char *title){
    if (!curr){
        return curr;
    } else if (strcmp(title, curr->title) < 0){
        curr->left = deleteGame(curr->left, title);
    } else if (strcmp(title, curr->title) > 0){
        curr->right = deleteGame(curr->right, title);
    } else {
        if (!curr->left && !curr->right){
            free(curr);
            curr = NULL;
        } else if (!curr->left){
            Game *temp = curr;
            curr = curr->right;
            free(temp);
            temp = NULL;
        } else if (!curr->right){
            Game *temp = curr;
            curr = curr->left;
            free(temp);
            temp = NULL; 
        } else {
            Game *temp = curr->left;
            while (temp->right){
                temp = temp->right;
            }
            strcpy(curr->title, temp->title);
            strcpy(curr->genre, temp->genre);
            curr->stock = temp->stock;
            curr->left = deleteGame(curr->left, temp->title);
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

    return curr;
}

void checkUnique(Game *curr, const char *title){
    if (!curr){
        return;
    }
    checkUnique(curr->left, title);
    if (strcmp(curr->title, title) == 0){
        check = 1;
        return;
    }
    checkUnique(curr->right, title);
}

int checkUniqueTitle(Game *curr, const char *title){
    check = 0;
    checkUnique(root, title);
    if (check == 1){
        printf("Game Title must be unique!\n\n");
        return 0;
    }
    return 1;
}

void display(Game *curr){
    if (!curr){
        return;
    }
    display(curr->left);
    printf("| %-30s | %-15s | %5d |\n", curr->title, curr->genre, curr->stock);
    display(curr->right);
}

void checkExist(Game *curr){
    if (!curr){
        printf("Warehouse is empty !\n");
        printf("Press enter to continue...\n"); getchar();
        return;
    } else {
        display(root);
    }
}

void updateData(Game *curr, const char *title){
    do {
        printf("Input update type [add|remove][case insensitive]: ");
        scanf("%s", type); getchar();
    } while (strcmpi(type, "add") != 0 && strcmpi(type, "remove") != 0);
    do {
        printf("Input stock to remove[1-50]: ");
        scanf("%d", &stockToUpdate); getchar();
    } while (stockToUpdate < 1 || stockToUpdate > 50);
    if (strcmpi(type, "add") == 0){
        curr->stock = curr->stock + stockToUpdate;
    } else if (strcmpi(type, "remove") == 0){
        curr->stock = curr->stock - stockToUpdate;
        if (curr->stock < 1){
            printf("%s is removed from the warehouse !\n", curr->title); 
            root = deleteGame(root, title);
            printf("Press enter to continue...\n"); getchar();
        }
    }
    return;
}

void checkUpdate(Game *curr, const char *title){
    if (!curr){
        return;
    }
    checkUpdate(curr->left, title);
    if (strcmp(curr->title, title) == 0){
        check = 1;
        printf("Current stock: %d\n\n", curr->stock);
        updateData(curr, title);
    }
    checkUpdate(curr->right, title);
}

void checkAvailable(const char *title){
    check = 0;
    checkUpdate(root, title);
    if (check == 0){
        printf("Data not found!\n");
        printf("Press enter to continue...\n"); getchar();
        return;
    }
    return;
}

int main(){

    int input;
    char title[50];
    char genre[50];
    int stock;
    int temp = 1;
    char deleteTitle[50];

    do {
        puts("Bluejack GShop");
        puts("==============");
        puts("1. Insert Game");
        puts("2. View Game");
        puts("3. Update Stock");
        puts("4. Exit");
        scanf("%d", &input); getchar();

        if (input == 1){
            do {
                printf("Input game title[5-25][unique]: ");
                scanf("%[^\n]", title); getchar();
                temp = checkUniqueTitle(root, title);
            } while (strlen(title) < 5 || strlen(title) > 25 || temp == 0);

            do {
                printf("Input game type[Action|RPG|Adventure|Card Game]: ");
                scanf("%[^\n]", genre); getchar();
            } while (strcmp(genre, "Action") != 0 && strcmp(genre, "RPG") != 0 && strcmp(genre, "Adventure") != 0 && strcmp(genre, "Card Game") != 0);

            do {
                printf("Input game stock[>= 1]: ");
                scanf("%d", &stock); getchar();
            } while (stock < 1);

            printf("Insert Success !\n");
            root = insertGame(root, createGame(title, genre, stock));

        } else if (input == 2){
            checkExist(root);
        } else if (input == 3){
            scanf("%[^\n]", deleteTitle); getchar();
            checkAvailable(deleteTitle);
        }
    } while (input != 4);

}