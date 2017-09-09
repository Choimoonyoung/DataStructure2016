#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int element;

typedef struct node{
	element info;
	struct node* next;
}NODE;

typedef struct head{
	int count;
	NODE* front;
	int(*compare) (void* a, void* b);
}HEAD;

#define bool int
#define true 1
#define false 0

int intcompare(void* a, void* b);
int stringCompare(void*a, void*b);
int larger(void*a, void*b, int(*fptr)(void*aa, void*bb));
HEAD* createList(int(*fptr)(void*a, void*b));
void destroyList(HEAD* a);
NODE* front(HEAD* a);
NODE* back(HEAD* a);
void pushBack(HEAD* a, element info);
void pushFront(HEAD* a, element info);
element popFront(HEAD* a);
element popBack(HEAD* a);
int listCount(HEAD* a);
bool isEmptyList(HEAD* a);
void insert(HEAD* a, int nth, element info);
void erase(HEAD* a, int nth);
void remove(HEAD* a, element value);
void unique(HEAD* a);
void exchange(HEAD* a, int first, int second);
void reverse(HEAD* a);
HEAD* merge(HEAD* a, HEAD* b);
void sort(HEAD* a);
int same(void*a);
void remove_if(HEAD*a, int(*fptr)(void* k));
void showlist(HEAD* a);