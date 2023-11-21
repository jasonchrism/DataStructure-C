#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
    int value;
    Node *left, *right;
}*root;

Node *createNode(int value){
    Node *node = (Node*)malloc(sizeof(Node));
    node->value  = value;
    node->left = node->right = NULL;
    return node;
}

Node *insertNode(Node *curr, Node *node){
    if(!curr) return node;
    else if (node->value < curr->value)
        curr->left = insertNode(curr->left, node);
    else if (node->value > curr->value)
        curr->right = insertNode(curr->right, node);
    return curr;
}

void infixOrder(Node *curr){
    if (!curr) return;
    infixOrder(curr->left);
    printf("%d ", curr->value);
    infixOrder(curr->right);
}

void prefixOrder(Node *curr){
    if (!curr) return;
    printf("%d ", curr->value);
    prefixOrder(curr->left);
    prefixOrder(curr->right);
}

void postOrder(Node *curr){
    if (!curr) return;
    postOrder(curr->left);
    postOrder(curr->right);
    printf("%d ", curr->value);
}

Node *deleteNode(Node *curr, int value){
    if (!curr) return curr;
    else if (value < curr->value)
        curr->left = deleteNode(curr->left, value);
    else if (value > curr->value)
        curr->right = deleteNode(curr->right, value);
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
            curr->value = temp->value;
            curr->left = deleteNode(curr->left, temp->value);
        }
    }
    return curr;
}

Node *deleteAll(Node *curr){
    while (curr){
        curr = deleteNode(curr, curr->value);
    }
    return curr;
}

Node *search(struct Node *curr, int value) {
    if (curr == NULL) {
        return curr;
    }

    if (curr->value == value) {
        return curr;
    }

    if (value <= curr->value) {
        return search(curr->left, value);
    } else {
        return search(curr->right,value);
    }
}

int main(){
    root = insertNode(root, createNode(20));
    root = insertNode(root, createNode(10));
    root = insertNode(root, createNode(15));
    root = insertNode(root, createNode(25));
    root = insertNode(root, createNode(30));
    root = insertNode(root, createNode(5));
    printf("Infix : ");
    infixOrder(root);
    printf("\n");
    printf("Prefix : ");
    prefixOrder(root);
    printf("\n");
    printf("Postfix : ");
    postOrder(root);

    // root = deleteAll(root);
    // infixOrder(root);
    // postOrder(root);
    // prefixOrder(root);
    // printf("oi");
}
