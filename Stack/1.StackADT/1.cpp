#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef char element;

typedef struct node{
	struct node *a;
	element b;
	int num;
}Node;

typedef struct head{
	struct node *top;
	int count;
}Head;

void pop(Head*top){
	if (top->count == 0)
		printf("Nothing to pop\n");
	else{
		printf("%c\n", top->top->b);
		Node*oldone = top->top;
		top->top = top->top->a;
		(top->count)--;
		free(oldone);
	}
}


void push(Head* stack, element a, int num){
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->a = stack->top;
	newnode->b = a;
	newnode->num = num;
	stack->top = newnode;
	stack->count++;
}

Head* CreateStack(){
	Head* head;
	head = (Head*)malloc(sizeof(Head));
	head->count = 0;
	head->top = NULL;
	return head;
}

void DestroyStack(Head* stack){
	Node*a = stack->top;
	while (a != NULL){
		a = stack->top;
		stack->top = stack->top->a;
		free(a);
	}
	free(stack);
}

element StackTop(Head* top){
	if (top->count <= 0)
		return -1;
	else{
		return top->top->b;
	}
}

Head* CatStack(Head*a, Head*b){ // b를 중심으로 a를 합치는 것
	Node* oldone = b->top->a;
	while (oldone->a != NULL){
		oldone = oldone->a;
	}
	oldone->a = a->top;
	b->count = a->count + b->count;
	free(a);
	return b;
}