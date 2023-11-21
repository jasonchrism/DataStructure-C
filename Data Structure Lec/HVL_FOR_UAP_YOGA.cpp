#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;

struct Player{ 
	char username[20]; 
	char job[20]; 
	int score;
	int value;
	double match_count;
	double WinCount;
	double WinRate; 
	int LoseCount;
	int DrawCount; 
	Player* left, *right, *next;
}*root = 0, *temp;

//this is for get height of node
int GetHeight(Player* temp){
	if(temp==0)return 0;
	return temp->value;
}
int GetMax(int a, int b){
	return (a > b)? a : b; 
}
int BalanceFactor(Player* curr){ 
	if(curr==0){
		return 0;
	}
	return GetHeight(curr->left) - GetHeight(curr->right);
}	
struct Player* LeftRotation(Player* curr){
	struct Player* child = curr->right;
	struct Player* left_child = child->left;
	
	//this is for rotating thing
	curr->right = left_child;
	child->left = curr;
	
	curr->value = 1 + GetMax(GetHeight(curr->left), GetHeight(curr->right));
	child->value = 1 + GetMax(GetHeight(child->left), GetHeight(child->right));
	return child;
}
struct Player* RightRotation(Player* curr){
	struct Player* child = curr->left;
	struct Player* right_child = child->right;
	
	curr->left = right_child;
	child->right = curr;
	
	curr->value = 1 + GetMax(GetHeight(curr->left), GetHeight(curr->right));
	child->value = 1 + GetMax(GetHeight(child->left), GetHeight(child->right));
	return child;		
}
// this is for  insert the chaning
void PushBack(Player* root, Player* newPlayer){
	Player* temp = root;
	while(temp->next != NULL && temp->next->WinRate >= newPlayer->WinRate){
		if(temp->next == NULL){
			break;
		}
		temp = temp->next;
	}
	newPlayer->next = temp->next;
	temp->next = newPlayer; 
}

//this is for inserting
struct Player* InsertPlayer(struct Player* root, Player* newPlayer){
	if(root == 0){
		return newPlayer;
	}
	else if(newPlayer->score > root->score){
		root->right = InsertPlayer(root->right, newPlayer);
	}
	else if(newPlayer->score < root->score){
		root->left = InsertPlayer(root->left, newPlayer);
	}
	else{ 
		PushBack(root, newPlayer);
	}
//	printf("testsing");
	root->value = 1 + GetMax(GetHeight(root->left) , GetHeight(root->right));
	int balance_factor = BalanceFactor(root);
	
	if(balance_factor>1){
		if(BalanceFactor(root->left) <= 0){
			root->left = LeftRotation(root->left);	
		}
		return RightRotation(root);
	}
	if(balance_factor<-1){
		if(BalanceFactor(root->right) >= 0){	
			root->right = RightRotation(root->right);
		}
		return LeftRotation(root);
	}
	return root; 
}
struct Player* deleted_Player(Player* root, int score){ 
	if(root == 0){
		return 0;
	}
	else if(root->score < score){
		root->right = deleted_Player(root->right, score);
	}
	else if(root->score > score){
		root->left = deleted_Player(root->left, score);
	}
	else{
		if(root->next != NULL){
			Player* del = root;
			root = root->next;
			root->left = del->left;
			root->right = del->right;
			free(del);
			return root;
		}
		if(root->left == 0 && root->right == 0){
			return 0;
		}
		else if(root->left == 0 && root->right != 0){
			free(root);
			return root->right;
		}
		else if(root->left != 0 && root->right == 0){
			free(root);
			return root->left;

		}
		else{
			temp = root->left; 
			while(temp){
				temp = temp->right;
			}
			strcpy(root->username, temp->username);
			strcpy(root->job, temp->job); 
			root->score = temp->score; 
			root->WinCount = temp->WinCount;
			root->LoseCount = temp->LoseCount;
			root->DrawCount = temp->DrawCount;
			root->WinRate = temp->WinRate;
			root->left = deleted_Player(root->left, score);
		}
	}
	root->value = 1 + GetMax(GetHeight(root->left) , GetHeight(root->right));
	int balance_factor = BalanceFactor(root);
		
	if(balance_factor>1){
		if(BalanceFactor(root->left) <= 0){
			root->left = LeftRotation(root->left);	
		}
		return RightRotation(root);
	}
	if(balance_factor<-1){
		if(BalanceFactor(root->right) >= 0){	
			root->right = RightRotation(root->right);
		}
		return LeftRotation(root);
	}
	return root;
}
struct Player* make_newPlayer(const char* username, const char* job, int score, double match_count, double WinCount, int LoseCount, int DrawCount){ 
	temp = (Player*)malloc(sizeof(Player));
	strcpy(temp->username, username);
	strcpy(temp->job, job); 
	temp->score = score; 
	temp->right = temp->left = temp->next = NULL;
	temp->WinCount = WinCount;
	temp->LoseCount = LoseCount;
	temp->DrawCount = DrawCount;
	temp->WinRate = (WinCount/match_count)* 100; 
	temp->value = 1;
	return InsertPlayer(root, temp); 
}

void ViewAll(struct Player* curr){
	int count = 0;
	if(curr == 0){
		return;
	}
	ViewAll(curr->left);
	Player* temp = curr;
	printf("Score %d\n",temp->score);
	while(temp){
		count++;
		printf("%d. %s [%s](%.f%%)\n", count, temp->username, temp->job, temp->WinRate);
		temp = temp->next;
	}
	printf("\n\n");
	ViewAll(curr->right);
}

void NodeToFind(Player* root, int score){
	if(root == 0){
		return; 
	}
	else if(root->score == score){
		Player* temp = root;
		while(temp){
			cout << temp->username << endl;
			temp = temp->next;
		}
	}
	NodeToFind(root->left, score); 
	NodeToFind(root->right, score);
}
int main(){
	
	char Command[100];
	int input, UserValue , CountToFind, DeletedScore;
	char username[100];
	char job[100];
	int JobChoose, score, LoseCount, DrawCount;
	double MatchCount, WinRate;
	
	//DUMMY DATA
	root = make_newPlayer("Gregor", "Sniper", 111, 10, 9, 1, 0);
	root = make_newPlayer("Heimdall", "Druid", 300, 100, 50, 50, 0);
	root = make_newPlayer("Travy", "Warrior", 300, 200, 100, 100, 0);
	root = make_newPlayer("Tetron", "Novice", 300, 50, 25, 25, 0);
	root = make_newPlayer("Homer", "Druid", 111, 10, 8, 2, 0);
	root = make_newPlayer("Garen", "Warrior", 111, 100, 70, 30, 0);

	scanf("%d", &input); getchar();
	for (int i = 0; i < input; i++){
		scanf("%s", Command); getchar();
		if (strcmp("INSERT", Command) == 0){
			scanf("%d", &UserValue ); getchar();
			for (int j = 0; j < UserValue ; j++){
				scanf("%[^#]#%d#%d#%lf#%lf#%d#%d", username, &JobChoose, &score, &MatchCount, &WinRate, &LoseCount, &DrawCount); getchar();
				if (JobChoose == 0){
					strcpy(job, "Novice");
				} else if (JobChoose == 1){
					strcpy(job, "Warrior");
				} else if (JobChoose == 2){
					strcpy(job, "Sniper");
				} else if (JobChoose == 3){
					strcpy(job, "Wizard");
				} else if (JobChoose == 4){
					strcpy(job, "Druid");
				} else if (JobChoose == 5){
					strcpy(job, "Assassin");
				}
			root = make_newPlayer(username, job ,score, MatchCount ,WinRate,LoseCount,DrawCount);
			}
		} else if (strcmp("FIND", Command) == 0){
			scanf("%d", &CountToFind); getchar();
			NodeToFind(root, CountToFind); 
		} else if (strcmp("DELETE", Command) == 0){
			scanf("%d", &DeletedScore); getchar();
			root = deleted_Player(root, DeletedScore);
		} else if (strcmp("SHOWALL", Command) == 0){
			ViewAll(root);
		}
	}
}
