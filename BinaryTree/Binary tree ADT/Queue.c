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
}HEAD; // queue�� �Ѱ����Ӹ�

HEAD* createqueue(){
	HEAD* a = (HEAD*)malloc(sizeof(HEAD));
	if (a == NULL)
		return NULL; //a�� NULL�̵Ǵ� ����?
	a->count = 0;
	a->front = a->rear = NULL; //�� NULL�̶�� ����� �ϴ� ������ ����? ���ϸ� �ȵǳ�?
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
		head->rear = newnode; // ù ����϶�
	}
	else{
		head->rear->next = newnode;
		head->rear = newnode; // ù ��尡 �ƴҶ�
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
