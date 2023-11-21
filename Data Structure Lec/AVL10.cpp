#include<iostream>
#include<string.h>
#include<stdlib.h>

using namespace std;
int idx = 1; 



struct Book{ 
	char tittle[100]; 
	char author[100];
	int release_year; 
	int rating;
	int book_id; 
	int value;
	Book* left, *right;
}*root, *temp;


int get_height(Book* temp){
	if(temp==0)return 0;
	return temp->value;
}
int get_max(int a, int b){
	return (a > b)? a : b; 
}
int get_balance_factor(Book* curr){ 
	if(curr==0){
		return 0;
	}
	return get_height(curr->left) - get_height(curr->right);
}

struct Book* left_rotation(Book* curr){
	struct Book* child = curr->right;
	struct Book* left_child = child->left; 
	
	curr->right = left_child;
	child->left = curr;
	
	child->value = 1 + get_max(get_height(child->left), get_height(child->right));
	curr->value = 1 + get_max(get_height(curr->left), get_height(curr->right));
	
	return child; 
}
struct Book* right_rotation(Book* curr){
	struct Book* child = curr->left;
	struct Book* right_child = child->right;
	
	curr->left = right_child;
	child->right = curr;
	
	curr->value = 1 + get_max(get_height(curr->left), get_height(curr->right));
	child->value = 1 + get_max(get_height(child->left), get_height(child->right));
	return child;		
}


struct Book* insert_new_book(Book* curr, Book* new_book){
	if(curr == 0){
		return new_book;
	}
	else if(curr->book_id > new_book->book_id){
		curr->left = insert_new_book(curr->left, new_book);
	}
	else if(curr->book_id < new_book->book_id){
		curr->right = insert_new_book(curr->right, new_book);
	}
	curr->value = 1 + get_max(get_height(curr->left) , get_height(curr->right));
	int balance_factor = get_balance_factor(curr);
	
	if(balance_factor>1){
		if(get_balance_factor(curr->left) <= 0){
			curr->left = left_rotation(curr->left);	
		}
		return right_rotation(curr);
	}
	if(balance_factor<-1){
		if(get_balance_factor(curr->right) >= 0){	
			curr->right = right_rotation(curr->right);
		}
		return left_rotation(curr);
	}
	return curr; 
}

struct Book* deleted_book(Book* curr, int book_id){ 
	if(curr == 0){
		return 0;
	}
	else if(curr->book_id < book_id){
		curr->right = deleted_book(curr->right, book_id);
	}
	else if(curr->book_id > book_id){
		curr->left = deleted_book(curr->left, book_id);
	}
	else{
		if(curr->left == 0 && curr->right == 0){
			return 0;
		}
		else if(curr->left == 0 && curr->right != 0){
			free(curr);
			return curr->right;
		}
		else if(curr->left != 0 && curr->right == 0){
			free(curr);
			return curr->left;

		}
		else{
			temp = curr->left; 
			while(temp){
				temp = temp->right;
			}
			strcpy(curr->author, temp->author);
			strcpy(curr->tittle, temp->tittle);
			curr->book_id = temp->book_id; 
			curr->release_year = temp->release_year; 
			curr->rating = temp->rating;
			curr->left = deleted_book(curr->left, book_id);
		}		
	}
	curr->value = 1 + get_max(get_height(curr->left) , get_height(curr->right));
	int balance_factor = get_balance_factor(curr);
	
	
	if(balance_factor>1){
		if(get_balance_factor(curr->left) <= 0){
			curr->left = left_rotation(curr->left);	
		}
		return right_rotation(curr);
	}
	if(balance_factor<-1){
		if(get_balance_factor(curr->right) >= 0){	
			curr->right = right_rotation(curr->right);
		}
		return left_rotation(curr);
	}
	return curr; 
	
	return curr;
}

struct Book* make_new_book(const char* tittle, const char* author, int release, int rating){
	temp = (Book*)malloc(sizeof(Book));
	strcpy(temp->tittle, tittle);
	strcpy(temp->author, author);
	temp->release_year = release;
	temp->rating = rating;
	temp->book_id = idx;
	temp->value = 1;
	temp->left = temp->right = 0;
	idx++;
	return insert_new_book(root, temp);
}

void print(Book* temp){
	if(temp == 0){
		return;
	}
	print(temp->left);
	printf("%s\n", temp->author);
	print(temp->right);
}
int main(){
	root = make_new_book("some", "yoga", 2002, 2);
	root = make_new_book("you", "jason", 2002, 3);
	root = make_new_book("make", "thing", 2002, 1);
	
	root = deleted_book(root, 1);
	print(root);
}