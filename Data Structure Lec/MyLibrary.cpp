#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int lastID = 0;
int found = 0;

struct data{
	char title[50];
	char author[50];
	int year;
	int rating;
	int bookID;
	
	int height;
	
	struct data *left, *right;
}*root = 0;

struct titleNode{
	char title[50];
	struct titleNode *next;
}*head = 0;

struct titleNode *createTitleNode(char title[50]){
	struct titleNode *temp = (struct titleNode*)malloc(sizeof(struct titleNode));
	strcpy(temp->title, title);
	temp->next = 0;
	
	return temp;
}

struct titleNode *insertTitleNode(char title[50]){
	//insert head
	if(head == 0){
		head = createTitleNode(title);
	}
	else{
		struct titleNode *t = createTitleNode(title);
		t->next = head;
		head = t;
	}
}

int validateTitle(char newTitle[50]){
	struct titleNode *c = head;
	while(c){
		if(strcmp(c->title, newTitle) == 0){
			return 1; //if found duplicate title
		}
		c = c->next;
	}
	return 0; //if NOT found duplicate title
}

int max(int a, int b){
	return a > b ? a : b;
}

int getHeight(struct data *curr){
	if(curr == 0){
		return 0;
	}
	else return curr->height;
}

int getBF(struct data *curr){
	if(curr == 0){
		return 0;
	}
	else return getHeight(curr->left) - getHeight(curr->right);
}

struct data *rightRotate(struct data *t){
	struct data *a = t->left;
	struct data *b = a->right;
	
	t->left = b;
	a->right = t;
	
	t->height = max(getHeight(t->left), getHeight(t->right)) + 1;
	a->height = max(getHeight(a->left), getHeight(a->right)) + 1;
	
	return a;
}

struct data *leftRotate(struct data *t){
	struct data *a = t->right;
	struct data *b = a->left;
	
	t->right = b;
	a->left = t;
	
	t->height = max(getHeight(t->left), getHeight(t->right)) + 1;
	a->height = max(getHeight(a->left), getHeight(a->right)) + 1;
	
	return a;
}

struct data *createData(char title[50], char author[50], int year, int rating, int bookID){
	
	struct data *temp = (struct data*)malloc(sizeof(struct data));
	strcpy(temp->title, title);
	strcpy(temp->author, author);
	temp->year = year;
	temp->rating = rating;
	temp->bookID = bookID;
	
	temp->height = 1;
	temp->left = temp->right = 0;
	
	return temp;
}

struct data *insertData(struct data *curr, char title[50], char author[50], int year, int rating){
	
	if(curr == 0){
		lastID += 1;
		return createData(title, author, year, rating, lastID);
	}
	else if(lastID+1 < curr->bookID && strcmp(title, curr->title) != 0){
		curr->left = insertData(curr->left, title, author, year, rating);
	}
	else if(lastID+1 > curr->bookID && strcmp(title, curr->title) != 0){
		curr->right = insertData(curr->right, title, author, year, rating);
	}
	
	curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
	
	int bf = getBF(curr);
	
	//left left
	if(bf > 1 && getBF(curr->left) >= 0){
		return rightRotate(curr);
	}
	//right right
	else if(bf < -1 && getBF(curr->right) < 0){
		return leftRotate(curr);
	}
	//left right
	else if(bf > 1 && getBF(curr->left) <= 0){
		curr->left = leftRotate(curr->left);
		return rightRotate(curr);
	}
	//right left
	else if(bf < -1 && getBF(curr->right) > 0){
		curr->right = rightRotate(curr->right);
		return leftRotate(curr);
	}
	
	return curr;
}

struct data *delData(struct data *curr, int bookID){
	if(curr == 0){
		printf("Book ID %d not found.\n", bookID);
		return curr;
	}
	else if(bookID < curr->bookID){
		curr->left = delData(curr->left, bookID);
	}
	else if(bookID > curr->bookID){
		curr->right = delData(curr->right, bookID);
	}
	else{
		if(!curr->left && !curr->right){
			free(curr);
			return 0;
		}
		else if(!curr->left && curr->right){
			struct data *t = curr->right;
			free(curr);
			return t;
		}
		else if(curr->left && !curr->right){
			struct data *t = curr->left;
			free(curr);
			return t;
		}
		else{
			struct data *t = curr->left;
			struct data *tp = curr;
			
			while(t->right){
				tp = t;
				t = t->right;
			}
			
			//copy data
			strcpy(curr->title, t->title);
			strcpy(curr->author, t->author);
			curr->year = t->year;
			curr->rating = t->rating;
			curr->bookID = t->bookID;
			
			curr->left = delData(curr->left, t->bookID);
		}
	}
	
	curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
	
	int bf = getBF(curr);
	
	//left left
	if(bf > 1 && getBF(curr->left) >= 0){
		return rightRotate(curr);
	}
	//right right
	else if(bf < -1 && getBF(curr->right) < 0){
		return leftRotate(curr);
	}
	//left right
	else if(bf > 1 && getBF(curr->left) <= 0){
		curr->left = leftRotate(curr->left);
		return rightRotate(curr);
	}
	//right left
	else if(bf < -1 && getBF(curr->right) > 0){
		curr->right = rightRotate(curr->right);
		return leftRotate(curr);
	}
	
	return curr;
}

void findTravel(struct data *curr, int bookID){
	if(curr){
		findTravel(curr->left, bookID);
		if(curr->bookID == bookID){
			printf("Book ID %d found:\n", bookID);
			printf("ID: %d\nTitle: %s\nAuthor: %s\nYear: %d\nRating: %d\n", curr->bookID, curr->title, curr->author, curr->year, curr->rating);
			found = 1;
			return;			
		} 
		findTravel(curr->right, bookID);
	}
}

void displayInfix(struct data *curr){
	if(curr != 0){
		displayInfix(curr->left);			
		printf("ID: %d\nTitle: %s\nAuthor: %s\nYear: %d\nRating: %d\n\n", curr->bookID, curr->title, curr->author, curr->year, curr->rating);
		displayInfix(curr->right);
	}
}

void findCommand(int bookID){
	found = 0;
	findTravel(root, bookID);
	if(found == 0){
		printf("Book ID %d not found.\n", bookID);
	}
}

void showAllCommand(){
	displayInfix(root);		
}

int checkChildRoot(struct data *curr){
	if(curr){
		return 1 + checkChildRoot(curr->left) + checkChildRoot(curr->right);
	}
	else{
		return 0;
	}
}

int main(){
	
	int c = 0, val;
	char command[20];
	char title[50];
	char author[50];
	int year;
	int rating;
	
	root = insertData(root, "More Than Balloons", "Gregor", 1997, 4);
	root = insertData(root, "Dump Truck", "Heimdall", 2000, 3);	
	root = insertData(root, "Hello World", "Travy", 1999, 4);	
	root = insertData(root, "Secret Tetris", "Tetron", 2010, 5);	
	root = insertData(root, "Florian", "Homer", 1997, 2);	
	root = insertData(root, "Sea Gardener", "Garen", 2005, 4);
	root = insertData(root, "Wild Dog", "Hisna", 2006, 4);
	root = insertData(root, "Trump Game", "Fiona", 2009, 2);
	root = insertData(root, "Class Act", "Navi", 2001, 1);
	root = insertData(root, "Silly Bear", "Garen", 2020, 5);
		
	scanf("%d", &c);
	getchar();
	for(int i=0; i<c; i++){
		scanf("%s", command);
		getchar();
		
		if(strcmp(command, "INSERT") == 0){
			scanf("%d", &val);
			getchar();
			for(int j=0; j<val; j++){
				scanf("%[^#]#%[^#]#%d#%d", title, author, &year, &rating);
				
				if(validateTitle(title) == 0)	
					root = insertData(root, title, author, year, rating);
			}
		}
		else if(strcmp(command, "FIND") == 0){
			scanf("%d", &val);
			getchar();
			findCommand(val);
		}
		else if(strcmp(command, "DELETE") == 0){
			scanf("%d", &val);
			getchar();
			delData(root, val);
		}
		else if(strcmp(command, "SHOWALL") == 0){
			showAllCommand();
		}
		else if(strcmp(command, "CHECKLEFTROOT") == 0){
			printf("%d\n", checkChildRoot(root->left));
		}
		else if(strcmp(command,"CHECKRIGHTROOT") == 0){
			printf("%d\n", checkChildRoot(root->right));
		}
	}

	return 0;
}
