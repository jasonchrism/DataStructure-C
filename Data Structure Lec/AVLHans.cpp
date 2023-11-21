#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Book{
    char title[50];
    char author[50];
    int year;
    int rating;
    int ID;
    int height;
    Book *left, *right;
} *root = NULL;

int booksQuantity = 0;
int found = 0;

Book *createBook(const char title[], const char author[], int year, int rating) {
    Book *newBook = (Book*) malloc (sizeof(Book));
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->year = year;
    newBook->rating = rating;
    newBook->ID = booksQuantity + 1;
    newBook->height = 1;
    newBook->left = newBook->right = NULL;

    booksQuantity++;
    return newBook;
}

int getHeight(Book *book) {
    if (book == NULL) {
        return 0;
    }

    return book->height;
}

int calcHeight(Book *book) {
    if (book == NULL) {
        return 0;
    }

    int left = getHeight(book->left);
    int right = getHeight(book->right);

    if (left > right) {
        return left + 1;
    } else {
        return right + 1;
    }
}

int getBF(Book *book) {
    if (book == NULL) {
        return 0;
    }

    return getHeight(book->left) - getHeight(book->right);
}

Book *rotateLeft(Book *curr) {
    Book *rc = curr->right;
    Book *rlc = rc->left;

    rc->left = curr;
    curr->right = rlc;

    curr->height = calcHeight(curr);
    rc->height = calcHeight(rc);

    return rc;
}

Book *rotateRight(Book *curr) {
    Book *lc = curr->left;
    Book *lrc = lc->right;

    lc->right = curr;
    curr->left = lrc;

    curr->height = calcHeight(curr);
    lc->height = calcHeight(lc);

    return lc;
}

Book *insertBook(Book *curr, Book *newBook) {
    if (curr == NULL) {
        return newBook;
    } else if (newBook->ID < curr->ID) {
        curr->left = insertBook(curr->left, newBook);
    } else if (newBook->ID > curr->ID) {
        curr->right = insertBook(curr->right, newBook);
    }

    curr->height = calcHeight(curr);
    int BF = getBF(curr);

    if (BF > 1) {
        if (getBF(curr->left) < 0) {
            curr->left = rotateLeft(curr->left);
        }
        return rotateRight(curr);
    }

    if (BF < -1) {
        if (getBF(curr->right) > 0) {
            curr->right = rotateRight(curr->right);
        }
        return rotateLeft(curr);
    }

    return curr;
}

Book *delBook(Book *curr, int ID) {
    if (curr == NULL) {
        return curr;
    } else if (ID < curr->ID) {
        curr->left = delBook(curr->left, ID);
    } else if (ID > curr->ID) {
        curr->right = delBook(curr->right, ID);
    } else {
        if (curr->left == NULL && curr->right == NULL) {
            free(curr);
            curr = NULL;
            return curr;
        } else if (curr->left == NULL) {
            Book *del = curr;
            curr = curr->right;
            free(del);
            del = NULL;
        } else if (curr->right == NULL) {
            Book *del = curr;
            curr = curr->left;
            free(del);
            del = NULL;
        } else {
            Book *temp = curr->left;
            while (temp->right != NULL) {
                temp = temp->right;
            }

            strcpy(curr->title, temp->title);
            strcpy(curr->author, temp->author);
            curr->year = temp->year;
            curr->rating = temp->rating;

            curr->left = delBook(curr->left, temp->ID);
        }
    }

    if (curr == NULL) {
        return curr;
    }

    curr->height = calcHeight(curr);
    int BF = getBF(curr);

    if (BF > 1) {
        if (getBF(curr->left) < 0) {
            curr->left = rotateLeft(curr->left);
        }
        return rotateRight(curr);
    }

    if (BF < -1) {
        if (getBF(curr->right) > 0) {
            curr->right = rotateRight(curr->right);
        }
        return rotateLeft(curr);
    }

    return curr;
}

int childCount(Book *curr) {
    if (curr == NULL) {
        return 0;
    }

    return childCount(curr->left) + childCount(curr->right) + 1;
}

void view(Book *curr) {
    if (curr == NULL) {
        return;
    }

    view(curr->left);
    printf("ID: %d\n", curr->ID);
    printf("Title: %s\n", curr->title);
    printf("Author: %s\n", curr->author);
    printf("Year: %d\n", curr->year);
    printf("Rating: %d\n", curr->rating);
    printf("=========\n");
    view(curr->right);
}

void validateBook(Book *curr, const char title[]) {
    if (curr == NULL) {
        return;
    }

    if (strcmp(curr->title, title) == 0) {
        found = 1;
    }

    validateBook(curr->left, title);
    validateBook(curr->right, title);
}

void findBook(Book *curr, int ID) {
    if (curr == NULL) {
        printf("Book ID %d not found\n", ID);
    } else if (ID < curr->ID) {
        findBook(curr->left, ID);
    } else if (ID > curr->ID) {
        findBook(curr->right, ID);
    } else {
        printf("Book ID %d found:\n", ID);
        printf("ID: %d\n", curr->ID);
        printf("Title: %s\n", curr->title);
        printf("Author: %s\n", curr->author);
        printf("Year: %d\n", curr->year);
        printf("Rating: %d\n", curr->rating);
        printf("=========\n");
    }
}

int main() {
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

    int repeat = 0;
    scanf("%d", &repeat); getchar();
    
    for (int i = 0; i < repeat; i++) {
        char command[20];
        scanf("%s", command); getchar();

        if (strcmpi(command, "INSERT") == 0) {
            int books = 0;
            scanf("%d", &books); getchar();

            for (int j = 0; j < books; j++) {
                found = 0;
                char title[50], author[50];
                int year = 0, rating = 0;

                scanf("%[^#]#%[^#]#%d#%d", title, author, &year, &rating); getchar();
                validateBook(root, title);

                if (found == 0) {
                    root = insertBook(root, createBook(title, author, year, rating));
                }
            }
        } else if (strcmpi(command, "FIND") == 0) {
            int ID = 0;
            scanf("%d", &ID); getchar();

            findBook(root, ID);
        } else if (strcmpi(command, "DELETE") == 0) {
            int ID = 0;
            scanf("%d", &ID); getchar();

            root = delBook(root, ID);
        } else if (strcmpi(command, "SHOWALL") == 0) {
            view(root);
        } else if (strcmpi(command, "CHECKLEFTROOT") == 0) {
            printf("left: %d\n", childCount(root->left));
        } else if (strcmpi(command, "CHECKRIGHTROOT") == 0) {
            printf("right: %d\n", childCount(root->right));
        }
    }
}