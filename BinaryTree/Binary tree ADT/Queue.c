#include<stdio.h>
#include<stdlib.h>

typedef char* element;

typedef struct treenode{
	element info;
	struct treenode* left, *right;
}Treenode;

typedef Treenode* Element;
typedef struct node{
	struct node* next;
	Element info;
}NODE;

typedef struct head{
	NODE* front;
	NODE* rear;
	int count;
}HEAD; // queue의 총관리머리

HEAD* createqueue(){
	HEAD* a = (HEAD*)malloc(sizeof(HEAD));
	if (a == NULL)
		return NULL; //a가 NULL이되는 경우는?
	a->count = 0;
	a->front = a->rear = NULL; //꼭 NULL이라고 해줘야 하는 이유는 뭐지? 안하면 안되나?
	return a;
}

void Enqueue(HEAD* head, Element info){
	NODE* newnode = (NODE*)malloc(sizeof(NODE));
	if (newnode == NULL)
		return;
	newnode->info = info;
	newnode->next = NULL;
	head->count++;
	if (head->rear == NULL){
		head->front = newnode;
		head->rear = newnode; // 첫 노드일때
	}
	else{
		head->rear->next = newnode;
		head->rear = newnode; // 첫 노드가 아닐때
	}
}

Element Dequeue(HEAD* head){
	if (head->count == 0)
		return NULL;

	NODE* oldone = head->front;
	Element a = oldone->info;
	if (head->count == 1)
		head->front = head->rear = NULL;
	else{
		head->front = head->front->next;
	}
	head->count--;
	free(oldone);
	return a;
}

Element QueueFront(HEAD* head){
	if (head->count == 0)
		return NULL;
	else{
		return head->front->info;
	}
}

void destroyqueue(HEAD* head){
	while (head->count != 0){
		NODE* a = head->front;
		head->front = head->front->next;
		head->count--;
		free(a);
	}
	free(head);
}
