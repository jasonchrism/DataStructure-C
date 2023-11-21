#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int lastId = 1;
int leftRoot = 0;
int rightRoot = 0;

struct data{
    char title[100];
    char author[100];
    int year;
    int rating;
    int id;
    int height;
    data *left, *right;
} *root = NULL;

data *createData(const char *title, const char *author, int year, int rating){
    data *temp = (data *)malloc(sizeof(data));
    strcpy(temp->title, title);
    strcpy(temp->author, author);
    temp->year = year;
    temp->rating = rating;
    temp->id = lastId;
    lastId++;
    temp->height = 1;
    temp->left = temp->right = NULL;
    return temp;
}

int max(int a, int b){
    return (a >= b ? a : b);
}

int getHeight(data *curr){
    if(!curr){
        return 0;
    }
    return curr->height;
}

int getBf(data *curr){
    if(!curr){
        return 0;
    }
    return getHeight(curr->left) - getHeight(curr->right);
}

data *rightRotate(data *t){
    data *s = t->left;
    data *b = s->right;
    t->left = b;
    s->right = t;

    t->height = 1 + max(getHeight(t->left), getHeight(t->right));
    s->height = 1 + max(getHeight(s->left), getHeight(s->right));
}

data *leftRotate(data *t){
    data *s = t->right;
    data *b = s->left;
    t->right = b;
    s->left = t;

    t->height = 1 + max(getHeight(t->left), getHeight(t->right));
    s->height = 1 + max(getHeight(s->left), getHeight(s->right));
}

int findTitle(data *curr, const char *title){
    if(!curr){
        return 0;
    }else if(strcmp(title, curr->title) < 0){
        findTitle(curr->left, title);
    }else if(strcmp(title, curr->title) > 0){
        findTitle(curr->right, title);
    }else{
        return 1;
    }
}

data *insertData(data *curr, data *newBook){
    if(!curr){
        return newBook;
    }else if(newBook->id < curr->id){
        curr->left = insertData(curr->left, newBook);
    }else if(newBook->id > curr->id){
        curr->right = insertData(curr->right, newBook);
    }else{
        return curr;
    }
    curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
    int bf = getBf(curr);
    if(bf > 1 && getBf(curr->left) >= 0){
        return rightRotate(curr);
    }
    if(bf < -1 && getBf(curr->right) <= 0){
        return leftRotate(curr);
    }
    if(bf > 1 && getBf(curr->left) < 0){
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
    }
    if(bf < -1 && getBf(curr->right) > 0){
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }
    return curr;
}

data *deleteData(data *curr, int id){
    if(!curr){
        return NULL;
    }else if(id < curr->id){
        curr->left = deleteData(curr->left, id);
    }else if(id > curr->id){
        curr->right = deleteData(curr->right, id);
    }else{
        if(!curr->right && !curr->left){
            free(curr);
            curr = NULL;
        }else if(!curr->right){
            data *del = curr;
            curr = curr->left;
            free(del);
            del = NULL;
        }else if(!curr->left){
            data *del = curr;
            curr = curr->right;
            free(del);
            del = NULL;
        }else{
            data *temp = curr->left;
            while(temp->right){
                temp = temp->right;
            }
            strcpy(curr->author, temp->author);
            strcpy(curr->title, temp->title);
            curr->year = temp->year;
            curr->rating = temp->rating;
            curr->id = temp->id;
            curr->left = deleteData(curr->left, temp->id);
        }
        return curr;
    }
    curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
    int bf = getBf(curr);
    if(bf > 1 && getBf(curr->left) >= 0){
        return rightRotate(curr);
    }
    if(bf < -1 && getBf(curr->right) <= 0){
        return leftRotate(curr);
    }
    if(bf > 1 && getBf(curr->left) < 0){
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
    }
    if(bf < -1 && getBf(curr->right) > 0){
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }
    return curr;
}

void display(data *curr){
    if(!curr){
        return;
    }
    display(curr->left);
    printf("ID: %d\n", curr->id);
    printf("Title: %s\n", curr->title);
    printf("Author: %s\n", curr->author);
    printf("Year: %d\n", curr->year);
    printf("Rating: %d\n\n", curr->rating);
    display(curr->right);
}

void insert(){
    int n;
    char title[100] = {};
    char author[100] = {};
    int year, rating;
    scanf("%d", &n); getchar();
    for(int i = 0; i < n; i++){
        scanf("%[^#]#%[^#]#%d#%d", title, author, &year, &rating); getchar();
        if(findTitle(root, title) == 0){
            root = insertData(root, createData(title, author, year, rating));
        }
        
    }
}

void find(data *curr, int search){
    if(!curr){
        printf("Book ID %d not found\n", search);
        return;
    }else if(search < curr->id){
        find(curr->left, search);
    }else if(search > curr->id){
        find(curr->right, search);
    }else{
        printf("Book ID %d found:\n", search);
        printf("ID: %d\n", curr->id);
        printf("Title: %s\n", curr->title);
        printf("Author: %s\n", curr->author);
        printf("Year: %d\n", curr->year);
        printf("Rating: %d\n", curr->rating);
    }
}

void checkLeftRoot(data *curr){
    if(!curr){
        return;
    }
    leftRoot++;
    checkLeftRoot(curr->left);
    checkLeftRoot(curr->right);
}

void checkRightRoot(data *curr){
    if(!curr){
        return;
    }
    rightRoot++;
    checkRightRoot(curr->left);
    checkRightRoot(curr->right);
}


int main(){
    // root = insertData(root, createData("more than ballon", "gregor", 1997, 4));
    // root = insertData(root, createData("dump truck", "heimdall", 2000, 2));
    // root = insertData(root, createData("hello world", "travy", 2010, 4));
    // root = insertData(root, createData("secret tetris", "tetron", 2010, 5));
    // root = insertData(root, createData("florian", "homer", 1990, 5));
    // root = insertData(root, createData("florian", "test", 1990, 5));
    // display(root);
    // printf("\n");
    // root = deleteData(root, 2);
    // display(root);
    char input[100] = {};
    int req;
    scanf("%d", &req); getchar();
    for(int i = 0; i < req; i++){
        scanf("%[^\n]", input); getchar();
        if(strcmp(input, "INSERT") == 0){
            insert();
        }else if(strcmp(input, "FIND") == 0){
            int search;
            scanf("%d", &search); getchar();
            find(root, search);
        }else if(strcmp(input, "DELETE") == 0){
            int del;
            scanf("%d", &del); getchar();
            root = deleteData(root, del);
        }else if(strcmp(input, "SHOWALL") == 0){
            display(root);
        }else if(strcmp(input, "CHECKLEFTROOT") == 0){
            checkLeftRoot(root->left);
            printf("%d\n", leftRoot);
            leftRoot = 0;
        }else if(strcmp(input, "CHECKRIGHTROOT") == 0){
            checkRightRoot(root->right);
            printf("%d\n", rightRoot);
            rightRoot = 0;
        }
    }
    
}