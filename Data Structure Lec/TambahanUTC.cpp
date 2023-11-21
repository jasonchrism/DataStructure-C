#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

struct Game{
	char name[105];
	int rating;
    int hours;
	Game *left, *right;
}*root;

struct Rating{
    char name[105];
    int rating;
    int hours;
    struct Rating *next, *prev;
}*head = 0, *tail = 0;

struct Game *createNode(const char name[], int rating, int hours){
    struct Game *newNode = (Game*)malloc(sizeof(Game));
    strcpy(newNode->name, name);
    newNode->rating = rating;
    newNode->hours = hours;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Game *insertGame(Game *curr, Game *node){
	if(!curr){
		return node;
	} else if (strcmpi(node->name, curr->name) > 0){
		curr->left = insertGame(curr->left, node);
	} else if (strcmpi(node->name, curr->name) < 0){
		curr->right = insertGame(curr->right, node);
	}
	return curr;
}

struct Game *deleteNode(Game *curr, const char name[]){
	if (!curr){
		return curr;
	} else if (strcmpi(name, curr->name) > 0){
		curr->left = deleteNode(curr->left, name);
	} else if (strcmpi(name, curr->name) < 0){
		curr->right = deleteNode(curr->right, name);
	} else {
		if (!curr->right && !curr->left){
			free(curr);
			curr = NULL;
		} else if (!curr->left){
			Game *temp = curr;
			curr = curr->right;
			free(temp);
		} else if (!curr->right){
			Game *temp = curr;
			curr = curr->left;
			free(temp);
		} else {
			Game *temp = curr->left;
			while (temp->right){
				temp = temp->right;
			}
			strcpy(curr->name, temp->name);
			curr->rating = temp->rating;
            curr->hours = temp->hours;
			curr->left = deleteNode(curr->left, temp->name);
		}
	}
	return curr;
}

int searchName(Game *curr, const char name[]){
    if (!curr){
		return 0;
	}
	if (strcmpi(name, curr->name) == 0){
		return 1;
	}
	if (strcmpi(name, curr->name) > 0){
		return searchName(curr->left, name);
	} else {
		return searchName(curr->right, name);
	}
}

void updateData(Game *curr, const char name[], int rating){
if (strcmpi(name, curr->name) == 0){   
		curr->rating = rating;
        return;
	}
	if (strcmpi(name, curr->name) > 0){
		return updateData(curr->left, name, rating);
	} else {
		return updateData(curr->right, name, rating);
	}   
}

void inOrder(Game *curr){
    if (!curr){
        return;
    }
    inOrder(curr->left);
    printf("Name         : %s\n", curr->name);
    printf("Rating       : %d\n", curr->rating);
    printf("Played Hours : %d\n", curr->hours);
    printf("\n");
    inOrder(curr->right);
}

void push(const char name[], int rating, int hours){
    // priority based on rating descending
    struct Rating *temp = (struct Rating*)malloc(sizeof(Rating));
    strcpy(temp->name, name);
    temp->rating = rating;
    temp->hours = hours;
    temp->next = temp->prev = NULL;

    if (head == NULL){
        head = tail = temp;
    } else if (rating > head->rating){
        temp->next = head;
        head = temp;
    } else if (rating <= tail->rating){
        tail->next = temp;
        tail->prev = temp->prev;
        tail = temp;
    } else {
        struct Rating *curr = head;
        while (curr->next->rating >= rating){
            curr = curr->next;
        }
        temp->next = curr->next;
        curr->next = temp;
    }
}

void pop(const char name[100], int rating, int hours){
    if(head == NULL){
        return;
    }
    else if(head == tail){
        free(head);
        head = NULL;
    }
    else if (strcmpi(head->name, name) == 0){
        Rating *curr = head->next;
        curr->prev = 0;
        free(head);
        head = curr;
    } else if (strcmpi(tail->name, name) == 0){
        Rating *curr = tail->prev;
        curr->next = 0;
        free(tail);
        tail = curr;
    } else {
        Rating *curr = head;
        while (!curr && strcmpi(name, curr->next->name) != 0){
            curr = curr->next;
        }
        if (curr == 0){
            return;
        }
        Rating *del = curr->next;
        curr->next = del->next;
        curr->next->prev = curr;
        free(del);
        return;
    }
}

//            del
// // 1   2    3    4    5

void viewByRating(Game *curr){
    struct Rating *temp = head;
    printf("\n");
    printf("View By Rating\n");
    printf("===========================\n");
    while (temp){
        printf("Name         : %s\n", temp->name);
        printf("Rating       : %d\n", temp->rating);
        printf("Played Hours : %d\n", temp->hours);
        printf("\n");
        temp = temp->next;
    }
    printf("===========================\n");
}

int inputRating(int min, int max){
    char tempChar[100];
    int check;
    int result;

    do {
        printf("Input Game Rating [1 - 10][numeric only] : ");
        scanf("%[^\n]", tempChar); getchar();
        check = 1;

        if (!strlen(tempChar)){
            check = 0;
            break;
        } else {
            for (int i = 0; i < strlen(tempChar); i++){
                if (!isdigit(tempChar[i])){
                    check = 0;
                    break;
                }
            }
            result = atoi(tempChar);
        }
    } while (result < min || result > max || check == 0);

    return result;
}

int inputHours(int min, int max){
    char tempChar[100];
    int check;
    int result;

    do {
        printf("Input Played Hours [0 - 2000][numeric only] : ");
        scanf("%[^\n]", tempChar); getchar();
        check = 1;

        if (!strlen(tempChar)){
            check = 0;
            break;
        } else {
            for (int i = 0; i < strlen(tempChar); i++){
                if (!isdigit(tempChar[i])){
                    check = 0;
                    break;
                }
            }
            result = atoi(tempChar);
        }
    } while (result < min || result > max || check == 0);

    return result;
}

bool inputName(const char name[]){
    for (int i = 0; i < strlen(name); i++){
        if (ispunct(name[i])){
            return false;
        }
    }
    return true;
}

void menu(){
    int input;
    char name[105] = {};
    int rating;
    int hours;
    bool checkName;
    char delName[105] = {};

    do {
        inOrder(root);
        puts("1. Insert");
        puts("2. Delete");
        puts("3. View by Rating");
        puts("0. Exit");
        printf(">> ");
        scanf("%d", &input); getchar();

        if (input == 1){
            do {
                printf("Input Name [1 - 100] [alphanumeric only] : ");
                scanf("%[^\n]", name); getchar();
                checkName = inputName(name);
            } while (strlen(name) < 1 || strlen(name) > 100 || !checkName);

            rating = inputRating(1, 10);
            hours = inputHours(0, 2000);

            int searchExist = searchName(root, name);
            if (searchExist == 1){
                updateData(root, name, rating);
                pop(name, rating, hours);
                push(name, rating, hours);
            } else {
                root = insertGame(root, createNode(name, rating, hours));
                push(name, rating, hours);
            }
        } else if (input == 2){
            do {
                printf("Input Name [1 - 100] [alphanumeric only] : ");
                scanf("%[^\n]", delName); getchar();
                checkName = inputName(delName);
            } while (strlen(delName) < 1 || strlen(delName) > 100 || !checkName);
            
            int searchExist = searchName(root, delName);
            if (searchExist == 1){
                root = deleteNode(root, delName);
                pop(delName, rating, hours);
            } else {
                printf("Game name does not exist!\n");
            }
        } else if (input == 3){
            viewByRating(root);
        }
    } while (input != 0);
}

int main(){
    menu();
}