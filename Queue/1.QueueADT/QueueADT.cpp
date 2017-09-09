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
}HEAD; // queue�� �Ѱ����Ӹ�

HEAD* createqueue(){
	HEAD* a = (HEAD*)malloc(sizeof(HEAD));
	if (a == NULL)
		return NULL; //a�� NULL�̵Ǵ� ����?
	a->count = 0;
	a->front = a->rear = NULL; //�� NULL�̶�� ����� �ϴ� ������ ����? ���ϸ� �ȵǳ�?
	return a;
}

void Enqueue(HEAD* head, element info){
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

element Dequeue(HEAD* head){
	if (head->count == 0)
		return -1;

	NODE* oldone = head->front;
	element a = oldone->info;
	if (head->count == 1)
		head->front = head->rear = NULL;
	else{
		head->front = head->front->next;
	}
	head->count--;
	free(oldone);
	return a;
}

element QueueFront(HEAD* head){
	if (head->count == 0)
		return -1;
	else{
		return head->front->info;
	}
}

void destroyqueue(HEAD* head){
	while (head->count!=0){
		NODE* a = head->front;
		head->front = head->front->next;
		head->count--;
		free(a);
	}
	free(head);
}

/*int main(){
	HEAD* a = createqueue();
	Enqueue(a,1);
	Enqueue(a, 2);
	printf("%d ",Dequeue(a));
	printf("%d ",QueueFront(a));
	printf("%d ", Dequeue(a));
	destroyqueue(a);
}*/