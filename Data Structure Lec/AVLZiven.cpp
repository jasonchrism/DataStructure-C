#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int currentBookID = 1;

struct Node{
    char title[50];
    char author[50];
    int releaseYear;
    int rating;
    int ID;
    int height;

    int currTotal;
    Node *left, *right;
} *root = NULL;

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int getHeight(Node* curr)
{
    if(!curr)
        return 0;
    return curr->height;
}
int getTotal(Node* curr)
{
    
    if(!curr)
        return 0;
    return curr->currTotal;
}

int getBF(Node* curr)
{
    if(!curr)
        return 0;
    return getHeight(curr->left) - getHeight(curr->right);
}

Node* rightRotate(Node* t)
{
    Node *s = t->left;
    Node *b = s->right;

    t->left = b;
    s->right = t;

    t->height = 1 + max(getHeight(t->left), getHeight(t->right));
    s->height = 1 + max(getHeight(s->left), getHeight(s->right));

    t->currTotal = 1 + getTotal(t->left) + getTotal(t->right);
    s->currTotal = 1 + getTotal(s->left) + getTotal(s->right);
    return s;
}

Node* leftRotate(Node* t)
{
    Node *s = t->right;
    Node *b = s->left;

    t->right = b;
    s->left = t;

    t->height = 1 + max(getHeight(t->left), getHeight(t->right));
    s->height = 1 + max(getHeight(s->left), getHeight(s->right));

    t->currTotal = 1 + getTotal(t->left) + getTotal(t->right);
    s->currTotal = 1 + getTotal(s->left) + getTotal(s->right);
    return s;
}

Node* createNode(char title[], char author[], int releaseYear, int rating)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->title, title);
    strcpy(newNode->author, author);
    newNode->releaseYear = releaseYear;
    newNode->rating = rating;
    newNode->height = newNode->currTotal = 1;
    newNode->ID = currentBookID++;

    newNode->left = newNode->right = 0;
    return newNode;
}

Node* insertNode(Node* curr, Node* newNode)
{
    if(!curr)
    {
        return newNode;
    }
    else if(curr->ID > newNode->ID)
    {
        curr->left = insertNode(curr->left, newNode);
    }
    else if(curr->ID < newNode->ID)
    {
        curr->right = insertNode(curr->right, newNode);
    }
    else
    {
        return curr;
    }

    curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
    curr->currTotal = 1 + getTotal(curr->left) + getTotal(curr->right);

    int bal = getBF(curr);
    if(bal > 1 && getBF(curr->left) >= 0)
    {
        return rightRotate(curr);
    }
    if(bal > 1 && getBF(curr->left) < 0)
    {
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
    }
    if(bal < -1 && getBF(curr->right) <= 0)
    {
        return leftRotate(curr);
    }
    if(bal < -1 && getBF(curr->right) > 0)
    {
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }
    return curr;
}

Node* deleteNode(Node* curr, int ID)
{
    if(!curr)
    {
        return curr;
    }
    else if(curr->ID > ID)
    {
        curr->left = deleteNode(curr->left, ID);
    }
    else if(curr->ID < ID)
    {
        curr->right = deleteNode(curr->right, ID);
    }
    else
    {
        if(!curr->right && !curr->left)
        {
            free(curr);
            return NULL;
        }
        else if(!curr->right)
        {
            Node *temp = curr->left;
            free(curr);
            return temp;
        }
        else if(!curr->left)
        {
            Node *temp = curr->right;
            free(curr);
            return temp;
        }
        else
        {
            Node *temp = curr->left;
            while(temp->right)
            {
                temp = temp->right;
            }

            strcpy(curr->title, temp->title);
            strcpy(curr->author, temp->author);
            curr->ID = temp->ID;
            curr->releaseYear = temp->releaseYear;
            curr->rating = temp->rating;

            curr->left = deleteNode(curr->left, temp->ID);
            // return curr;
        }
        
    }
    
    curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
    curr->currTotal = 1 + getTotal(curr->left) + getTotal(curr->right);

    int bal = getBF(curr);
    if(bal > 1 && getBF(curr->left) >= 0)
    {
        return rightRotate(curr);
    }
    if(bal > 1 && getBF(curr->left) < 0)
    {
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
    }
    if(bal < -1 && getBF(curr->right) <= 0)
    {
        return leftRotate(curr);
    }
    if(bal < -1 && getBF(curr->right) > 0)
    {
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }
    return curr;
}

bool foundExisting;
void validateExisting(Node* curr, char tobeChecked[])
{
    if(curr)
    {
        if(strcmp(curr->title, tobeChecked) == 0)
        {
            foundExisting = true;
            return;
        }
        validateExisting(curr->left, tobeChecked);
        validateExisting(curr->right, tobeChecked);
    }
}

Node *foundExistingNode;
void find(Node* curr, int ID)
{
    if(!curr)
    {
        foundExistingNode = NULL;
        return;
    }
    else if(curr->ID > ID)
    {
        find(curr->left, ID);
    }
    else if(curr->ID < ID)
    {
        find(curr->right, ID);
    }
    else
    {
        foundExistingNode = curr;
    }
    
}

void showall(Node* curr)
{
    if(curr)
    {
        showall(curr->left);
        printf("ID: %d\nTitle: %s\nAuthor: %s\nYear: %d\nRating: %d\n\n", curr->ID, curr->title, curr->author, curr->releaseYear, curr->rating);
        showall(curr->right);
    }
}

int main()
{
    root = insertNode(root, createNode("More Than Balloons", "Gregor", 1997, 4));
    root = insertNode(root, createNode("Dump Truck", "Heimdall", 2000, 3));
    root = insertNode(root, createNode("Hello World", "Travy", 1999, 4));
    root = insertNode(root, createNode("Secret Tetris", "Tetron", 2010, 5));
    root = insertNode(root, createNode("Florian", "Homer", 1997, 2));
    root = insertNode(root, createNode("Sea Gardener", "Garen", 2005, 4));
    root = insertNode(root, createNode("Wild Dog", "Hisna", 2006, 4));
    root = insertNode(root, createNode("Trump Game", "Fiona", 2009, 2));
    root = insertNode(root, createNode("Class Act", "Navi", 2001, 1));
    root = insertNode(root, createNode("Silly Bear", "Garen", 2020, 5));

    int t;
    char command[100] = {};
    scanf("%d", &t);
    getchar();

    while(t--)
    {
        scanf("%[^\n]", command);
        getchar();

        if(!strcmp(command, "INSERT"))
        {
            int q;
            char ttl[100], auth[100];
            int year, rating;
            scanf("%d", &q);
            getchar();

            while(q--)
            {
                scanf("%[^#]#%[^#]#%d#%d", ttl, auth, &year, &rating);
                getchar();

                foundExisting = false;
                validateExisting(root, ttl);

                if(!foundExisting)
                {
                    root = insertNode(root, createNode(ttl, auth, year, rating));
                }
            }
        }
        if(!strcmp(command, "FIND"))
        {
            int q;
            scanf("%d", &q);
            getchar();

            foundExistingNode = NULL;
            find(root, q);

            if(foundExistingNode)
            {
                printf("Book ID %d found:\n", q);
                printf("ID: %d\nTitle: %s\nAuthor: %s\nYear: %d\nRating: %d\n", foundExistingNode->ID, foundExistingNode->title, foundExistingNode->author, foundExistingNode->releaseYear, foundExistingNode->rating);
            }
            else
            {
                printf("Book ID %d not found.\n", q);
            }
            
        }
        if(!strcmp(command, "DELETE"))
        {
            int q;
            scanf("%d", &q);
            getchar();

            root = deleteNode(root, q);
        }
        if(!strcmp(command, "SHOWALL"))
        {
            showall(root);
        }
        if(!strcmp(command, "CHECKLEFTROOT"))
        {
            printf("%d\n", getTotal(root->left));
        }
        if(!strcmp(command, "CHECKRIGHTROOT"))
        {
            printf("%d\n", getTotal(root->right));
        }
    }
}
