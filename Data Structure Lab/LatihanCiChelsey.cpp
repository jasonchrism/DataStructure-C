#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int size = 1007;

struct Book{
	char ID[100];
	char title[100];
	char author[100];
	char ISBN[100];
	int page;
	int SUM;
	
	Book *next, *prev;
};

struct Table{
	Book *head, *tail;
}*table[size];

void initialTable(){
	for (int i = 0; i < size; i++){
		table[i] = (Table*)malloc(sizeof(Table));
		table[i]->head = table[i]->tail = NULL;
	}
}

struct Book *createBook(const char ID[], const char title[], const char author[], const char ISBN[], int page, int SUM){
	Book *newBook = (Book*)malloc(sizeof(Book));
	strcpy(newBook->ID, ID);
	strcpy(newBook->title, title);
	strcpy(newBook->author, author);
	strcpy(newBook->ISBN, ISBN);
	newBook->page = page;
	newBook->SUM = SUM;
	return newBook;
}

int hash(const char ID[]){
	int key = 0;
	for (int i = 0; i < strlen(ID); i++){
		key += ID[i];
	}
	return key % size;
}

void pushHead(int key, Book *newBook){
	if (table[key]->head == 0){
		table[key]->head = table[key]->tail = newBook;
	} else {
		newBook->next = table[key]->head;
		table[key]->head->prev = newBook;
		table[key]->head = newBook;
	}
}

void pushTail(int key, Book *newBook){
	if (table[key]->tail == 0){
		table[key]->head = table[key]->tail = newBook;
	} else {
		newBook->prev = table[key]->tail;
		table[key]->tail->next = newBook;
		table[key]->tail = newBook;
	}
}

void pushMid(int key, Book *newBook){
	Book *curr = table[key]->head;
	while (curr != 0 && strcmp(newBook->title, curr->title) >= 0){
		curr = curr->next;
	}
	newBook->next = curr->next;
	newBook->prev = curr;
	curr->next->prev = newBook;
	curr->next = newBook;
}

void insertBook(const char ID[], const char title[], const char author[], const char ISBN[], int page, int SUM){
	int key = hash(ID);
	Book *newBook = createBook(ID, title, author, ISBN, page, SUM);
	if (table[key]->head == 0 || strcmpi(title, table[key]->head->title) < 0){
		pushHead(key, newBook);
	} else if (table[key]->tail == 0 || strcmpi(title, table[key]->tail->title) > 0){
		pushTail(key, newBook);
	} else {
		pushMid(key, newBook);
	}
}

void removeBook(const char ID[]){
	int key = hash(ID);
	Book *curr = table[key]->head;
	if (strcmp(curr->ID, ID) == 0){
		table[key]->head = curr->next;
		free(curr);
		curr = NULL;
		return;
	}
	
	while (strcmp(curr->next->ID, ID) != 0){
		curr = curr->next;
	}
	
	Book *delBook = curr->next;
	curr->next = delBook->next;
	free(delBook);
	delBook = NULL;
}

int validateAuthor(const char* author){
	char buffer[50];
	if (author[2] == 's'){
		sprintf(buffer, "%c""%c""%c""%c", author[0], author[1], author[2], author[3]);
		if (strcmp(buffer, "Mrs.") == 0){
			return 1;
		} else {
			return 0;
		}
		
	} else if (author[2] == '.'){
		sprintf(buffer, "%c""%c""%c", author[0], author[1], author[2]);
		if (strcmp(buffer, "Mr.") == 0){
			return 1;
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}

void view(){
	printf("============================================================================================================================================================\n");
	printf("| Book ID                         | Book Title                                                  | Book Author                    | ISBN            | Page Number |\n");
	for (int i = 0; i < size; i++){
		Book *curr = table[i]->head;
		while (curr){
			printf("| %-20s | %-50s | %-20s | %-12d | %-4d |\n", curr->ID, curr->title, curr->author, curr->ISBN, curr->page);
			curr = curr->next;
		}
		printf("============================================================================================================================================================\n");
	}
	printf("============================================================================================================================================================\n");
}

void menu(){
	int input;
	int lastInc = 1;
	int authorTemp;
	char title[100];
	char author[100];
	char ISBN[100];
	int page;
	char IDTemp[100];
	char IDTemp2[100];
	char ID[100];
	int SUM;
	int check = 0;
	
	do {
		puts("BlueJack Library");
		puts("================");
		puts("1. View Book");
		puts("2. Insert Book");
		puts("3. Remove Book");
		puts("4. Exit");
		printf(">> ");
		scanf("%d", &input); getchar();
		
		if (input == 1){
			view();
		} else if (input == 2){
			do {
				printf("Input Book Title [5 - 50 characters] : ");
				scanf("%[^\n]", title); getchar();
			} while (strlen(title) < 5 || strlen(title) > 50);
			
			do {
				printf("Input Book Author [Mr./Mrs] [3 - 25 characters] : ");
				scanf("%[^\n]", author); getchar();
				authorTemp = validateAuthor(author);
			} while (strlen(author) < 3 || strlen(author) > 25 || authorTemp != 1);
			
			int temp = 0;
			do {
				printf("Input ISBN [10 - 13 digits] : ");
				scanf("%[^\n]", ISBN); getchar();
				temp = 0;
				for (int i = 0; i < strlen(ISBN); i++){
					if (isdigit(ISBN[i])){
						temp++;
					}
				}
			} while (temp != strlen(ISBN) || strlen(ISBN) < 10 || strlen(ISBN) > 13);
			
			do {
				printf("Input Page Number [at least 16] : ");
				scanf("%d", &page); getchar();
			} while (page < 16);
			
			sprintf(IDTemp, "B""%05d", lastInc);
			sprintf(ID, "%s-%s-%c%c", IDTemp, ISBN, toupper(author[0]), toupper(title[0]));
			for (int i = 0; i < strlen(ID); i++){
				SUM = SUM + ID[i];
			}
			insertBook(ID, title, author, ISBN, page, SUM);
			lastInc++;
		} else if (input == 3){
			do {
				printf("Please Input ID you want to delete : ");
				scanf("%s", IDTemp2); getchar();
				removeBook(IDTemp2);				
			} while (check != 1);
			
		}
	} while (input != 4);
}

int main(){
	
	initialTable();
	menu();
	
}
