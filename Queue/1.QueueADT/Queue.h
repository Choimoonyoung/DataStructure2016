#include<stdio.h>
#include<stdlib.h>

typedef int element;

typedef struct node{
	struct node* next;
	element info;
}NODE;

typedef struct head{
	NODE* front;
	NODE* rear;
	int count;
}HEAD; // queue의 총관리머리

HEAD* createqueue();

void Enqueue(HEAD* head, element info);

element Dequeue(HEAD* head);
element QueueFront(HEAD* head);

void destroyqueue(HEAD* head);
