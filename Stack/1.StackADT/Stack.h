#include<stdio.h>
#include<stdlib.h>

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

void pop(Head*top);

void push(Head* stack, element a, int num);

Head* CreateStack();

Head* CatStack(Head*a, Head*b);

void DestroyStack(Head* stack);

element StackTop(Head* top);