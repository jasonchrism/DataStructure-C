#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char insertName[55];
char insertNIM[55];
char delName[55];

struct Node{
    char name[50];
    char NIM[50];
    Node *left, *right;
}*root;

struct Node *createNode(const char name[], const char NIM[]){
    struct Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    strcpy(newNode->NIM, NIM);
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node *insertNode(Node *curr, Node *node){
    if(!curr) return node;
    else if (strcmpi(node->name, curr->name) < 0)
        curr->left = insertNode(curr->left, node);
    else if (strcmpi(node->name, curr->name) > 0)
        curr->right = insertNode(curr->right, node);
    return curr;
}

int searchStudent(struct Node *curr, const char name[]) {
    if (curr == NULL) {
        return 0;
    }

    if (strcmpi(curr->name, name) == 0) {
        return 1;
    }

    if (strcmpi(name, curr->name) < 0) {
        return searchStudent(curr->left, name);
    } else {
        return searchStudent(curr->right,name);
    }
}

void updateStudent(Node *curr, const char name[], const char newNIM[]){
    if (strcmpi(curr->name, name) == 0){
        strcpy(curr->NIM, newNIM);
        return;
    }
    if (strcmpi(name, curr->name) < 0) {
        return updateStudent(curr->left, name, newNIM);
    } else {
        return updateStudent(curr->right,name, newNIM);
    }   
}

Node *deleteNode(Node *curr, const char name[]){
    if (!curr) return curr;
    else if (strcmpi(name, curr->name) < 0)
        curr->left = deleteNode(curr->left, name);
    else if (strcmpi(name, curr->name) > 0)
        curr->right = deleteNode(curr->right, name);
    else {
        if (!curr->left && !curr->right){
            free(curr);
            curr = NULL;
        } else if (!curr->left){
            Node *temp = curr;
            curr = curr->right;
            free(temp);
        } else if (!curr->right){
            Node *temp = curr;
            curr = curr->left;
            free(temp);
        } else {
            Node *temp = curr->left;
            while (temp->right){
                temp = temp->right;
            }
            curr = temp;
            curr->left = deleteNode(curr->left, temp->name);
        }
    }
    return curr;
}

void infix(Node *curr){
    if(!curr){
        return;
    }
    infix(curr->left);
    printf("%s (%s) -> ", curr->name, curr->NIM);
    infix(curr->right);
}

void menu(){
    int input;
    int searchAvail;
    do {
        printf("\n");
        printf("=================\n");
        printf("     Welcome    \n");
        printf("=================\n");
        printf("1. Insert Student\n");
        printf("2. Delete Student\n");
        printf("3. View Student\n");
        printf("0. Exit\n");
        printf(">> ");
        scanf("%d", &input); getchar();
        printf("\n");

        if (input == 1){
            do {
                printf("Input Student Name [3 - 50 characters] : ");
                scanf("%[^\n]", insertName); getchar();
            } while (strlen(insertName) < 3 || strlen(insertName) > 50);

            do {
                printf("Input Student NIM [8 digits] : ");
                scanf("%s", insertNIM); getchar();
            } while (strlen(insertNIM) != 8);

            searchAvail = searchStudent(root, insertName);
            if (searchAvail == 1){
                updateStudent(root, insertName, insertNIM);
                printf("Student Name already exist! updated NIM instead!\n");
            } else {
                root = insertNode(root, createNode(insertName, insertNIM));
            }
        } else if (input == 2){
            do {
                printf("Input Student Name You Want to Delete [case insensitive] (9 to back): ");
                scanf("%[^\n]", delName); getchar();
                searchAvail = searchStudent(root, delName);
                if (strcmp(delName, "9") == 0){
                    menu();
                }

                if (searchAvail == 1){
                    root = deleteNode(root, delName);
                } else {
                    printf("Cannot delete because student name does not exist!\n");
                }
            } while (searchAvail != 1);
        } else if (input == 3){
            infix(root);
            printf("\n");
        }
    } while (input != 0);
}

int main(){

    menu();
    printf("Thank you for using this app!");

}