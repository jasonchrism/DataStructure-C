#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int SIZE = 26;

struct Food
{
	char name[100];
	int price;
	struct Food *next,*prev;
};

struct Table
{
	struct Food *head,*tail;
}*table[SIZE];

void initializeTable()
{
	for (int i = 0; i<SIZE;i++)
	{
		table[i] = (struct Table*)malloc(sizeof(struct Table));
		table[i]->head = table[i]->tail = 0;
	}
}

struct Food *createData(char name[],int price)
{
	struct Food *temp = (struct Food*)malloc(sizeof(struct Food));
	strcpy(temp->name,name);
	temp->price = price;
	temp->next = temp->prev = 0;
	return temp;	
}

void pushHead(int key, struct Food *newData)
{
	if(table[key]->head == 0)
	{
		table[key]->head = table[key]->tail = newData;
	}else
	{
		newData->next = table[key]->head;
		table[key]->head->prev = newData;
		table[key]->head = newData;
	}
}

void pushTail(int key, struct Food *newData)
{
	if(table[key]->head == 0)
	{
		table[key]->head = table[key]->tail = newData;
	}else
	{
		newData->prev = table[key]->tail;
		table[key]->tail->next = newData;
		table[key]->tail = newData;
	}
}

void pushMid(int key, struct Food *newData)
{
	struct Food *curr = table[key]->head;
	while(curr != 0 && strcmpi(newData->name,curr->next->name) >=0)
	{
		curr = curr->next;
	}
	newData->next = curr->next;
	curr->next->prev = newData;
	newData->prev = curr;
	curr->next = newData;
}
int hash(const char *name)
{
    char firstChar = name[0];
    if (firstChar >= 'A' && firstChar <= 'Z')
    {
        return (firstChar - 'A') % SIZE;
    }
    else if (firstChar >= 'a' && firstChar <= 'z')
    {
        return (firstChar - 'a') % SIZE;
    }
    return firstChar % SIZE;
}

void insertData(char name[],int price)
{
	int key = hash(name);
	struct Food *newData = createData(name,price);
	
	if(table[key]->head == 0 || strcmpi(name,table[key]->head->name) < 0)
	{
		pushHead(key,newData);
	}else if(table[key]->tail == 0 || strcmpi(name,table[key]->tail->name)>=0)
	{
		pushTail(key,newData);
	}else
	{
		pushMid(key,newData);
	}
}

void view()
{
	for (int i = 0; i< SIZE;i++)
	{
		struct Food *curr = table[i]->head;
		while(curr!=0)
		{
			printf("%s %d\n",curr->name,curr->price);
			curr = curr->next;
		}
	}
}
void popHead(int key)
{
	if(table[key]->head == 0)
	{
		printf("data tidak ada\n");
		return;
	}else if(table[key]->head == table[key]->tail)
	{
		free(table[key]->head);
		table[key]->head = table[key]->tail =0;
	}else
	{
		struct Food *curr = table[key]->head->next;
		curr->prev = 0;
		free(table[key]->head);
		table[key]->head = curr;
	}
}

void popTail(int key)
{
	if(table[key]->tail == 0)
	{
		printf("data tidak ada\n");
		return;
	}
	else if(table[key]->head == table[key]->tail)
	{
		free(table[key]->head);
		table[key]->head = table[key]->tail = 0;
	}else
	{
		struct Food *curr = table[key]->tail->prev;
		curr->next = 0;
		free(table[key]->tail);
		table[key]->tail = curr;
	}
}

void popMid(int key, char name[])
{
	struct Food *curr = table[key]->head;
	while(curr != 0 && strcmpi(name, curr->next->name) != 0)
	{
		curr = curr->next;
	}
	if(curr == 0)
	{
		printf("tidak ada datanya\n");
		return;
	}
	curr->next->prev = curr->prev;   // 1     2       3       4       5
	curr->prev->next = curr->next;
	free(curr);
	curr=0;
	return;
	
}
void deleteData(char name[])
{
	int key = hash(name);
	if(table[key] == 0)
	{
		printf("data tidak ada\n");
		return;
	}else if(strcmpi(name,table[key]->head->name)==0)
	{
		popHead(key);
	}else if(strcmpi(name,table[key]->tail->name) == 0)
	{
		popTail(key);
	}else
	{
		popMid(key,name);
	}
}

int main()
{
	initializeTable();
    
    view();
    insertData("a", 29000);
    insertData("b", 29000);
    insertData("c", 29000);
    insertData("e", 30);
    insertData("f", 9);
    insertData("g", 29000);
    view();	
    printf("\n");

	deleteData("o");
	view();
}