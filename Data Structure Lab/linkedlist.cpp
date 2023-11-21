#include<stdio.h>
#include<stdlib.h>

struct Edge{
	int src, dst, weight;
};

struct Node{
	Edge edge;
	Node *next, *prev;
};

Edge createEdge(int src, int dst, int weight){
	Edge edge;
	edge.src = src;
	edge.dst = dst;
	edge.weight = weight;
	return edge;
}

Node *createNode(Edge edge){
	Node *node = (Node*)malloc(sizeof(Node));
	node->edge = edge;
	node->next = node->prev = NULL;
	return node;
}

void pushHead(Node **head, Node **tail, Edge edge){
	Node *node = createNode(edge);
	if(*head == NULL){
		*head = *tail = node;
		return;
	}
	
	node->next = *head;
	(*head)->prev = node;
	*head = node;
}

void pushTail(Node **head, Node **tail, Edge edge){
	Node *node = createNode(edge);
	if(*head == NULL){
		*head = *tail = node;
		return;
	}
	
	(*tail)->next = node;
	node->prev = *tail;
	*tail = node;
}

void pushValue(Node **head, Node **tail, Edge edge){
	if(*head == NULL || edge.weight < (*head)->edge.weight){
		pushHead(head, tail, edge);
		return;
	}
	else if(edge.weight >= (*tail)->edge.weight){
		pushTail(head, tail, edge);
		return;
	}
		
	//push mid
	Node *curr = *head;
	while(edge.weight >= curr->next->edge.weight){
		curr = curr->next;
	}
	
	Node *node = createNode(edge);
	
	curr->next->prev = node;
	node->next = curr->next;
	node->prev = curr;
	curr->next = node;
}

void viewNode(Node *head){
	Node *curr = head;
	while(curr){
		printf("src: %d\t dst: %d\t weight: %d\n", curr->edge.src, curr->edge.dst, curr->edge.weight);
		curr = curr->next;
	}
}

void popHead(Node **head, Node **tail){
	if(*head == NULL) return;
	else if(*head == *tail){
		free(*head);
		*head = *tail = NULL;
		return;
	}
	
	*head = (*head)->next;
	free((*head)->prev);
	(*head)->prev = NULL;
}

void popTail(Node **head, Node **tail){
	if(*head == NULL) return;
	else if(*head == *tail){
		free(*head);
		*head = *tail = NULL;
		return;
	}
	
	*tail = (*tail)->prev;
	free((*tail)->next);
	(*tail)->next = NULL;
}

void popValue(Node **head, Node **tail, int src, int dst){
	if(*head == NULL) return;
	else if((*head)->edge.src == src && (*head)->edge.dst == dst){
		popHead(head, tail);
		return;
	}else if((*tail)->edge.src == src && (*tail)->edge.dst == dst){
		popTail(head, tail);
		return;
	}
	
	//pop mid
	Node *curr = *head;
	while(curr && !(curr->edge.src == src && curr->edge.dst == dst)){
		curr = curr->next;
	}
	
	if(!curr) return;
	
	curr->next->prev = curr->prev;
	curr->prev->next = curr->next;
	free(curr);
	curr = NULL;
}

/*
int main(){
	Node *head = NULL, *tail = NULL;
	pushValue(&head, &tail, createEdge(2, 3, 3));
	pushValue(&head, &tail, createEdge(0, 1, 1));
	pushValue(&head, &tail, createEdge(3, 0, 4));
	pushValue(&head, &tail, createEdge(1, 2, 2));
	
	popValue(&head, &tail, 0, 1);
	popValue(&head, &tail, 3, 0);
	popValue(&head, &tail, 1, 2);
	popValue(&head, &tail, 2, 3);
			
	viewNode(head);
	return 0;
}
*/


