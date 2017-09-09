#include<stdio.h>
#include<stdlib.h>
#include"listADT.h"
#include<string.h>

typedef int element;

typedef struct node{
	element info;
	struct node* next;
}NODE;

typedef struct head{
	int count;
	NODE* front;
	int (*compare) (void* a, void* b);
}HEAD;

int intcompare(void* a, void* b){
	if (*(int*)a >= *(int*)b)
		return 1;
	else
		return -1;
}

int stringCompare(void*a, void*b){
	int alen = strlen((char*)a);
	int blen = strlen((char*)b);
	if (alen >= blen)
		return 1;
	else
		return -1;
}

int larger(void*a, void*b, int(*fptr)(void*aa, void*bb)){
	if ((*fptr)(a, b) >= 1)
		return 1;
	else
		return -1;
}


HEAD* createList(int(*fptr)(void*a,void*b)){
	HEAD* a = (HEAD*)malloc(sizeof(HEAD));
	if (a == NULL)
		return NULL;
	a->count = 0;
	a->front = NULL;
	a->compare = fptr;
	return a;
}

void destroyList(HEAD* a){
	if (a->front == NULL){
		free(a);
		return;
	}
	NODE* b = a->front;
	while (b->next != NULL){
		NODE* bnext = b->next;
		free(b);
		b = b->next;
	}
	free(b);
	free(a);
}

NODE* front(HEAD* a){
	if (a->front == NULL)
		return NULL;
	else
		return a->front;
}

NODE* back(HEAD* a){
	if (a->front == NULL)
		return NULL;
	NODE* b = a->front;
	while (b->next != NULL){
		b = b->next;
	}
	return b;
}

void pushFront(HEAD* a, element info){
	NODE* newnode = (NODE*)malloc(sizeof(NODE));
	newnode->info = info;
	newnode->next = a->front;
	a->front = newnode;
	a->count++;
}

void pushBack(HEAD* a,element info){
	NODE* newnode = (NODE*)malloc(sizeof(NODE));
	newnode->info = info;
	newnode->next = NULL;
	if (a->front == NULL){
		a->front = newnode;
		a->count++;
		return;
	}
	NODE* b = a->front;
	while (b->next != NULL){
		b = b->next;
	}
	b->next = newnode;
	a->count++;
}

element popFront(HEAD* a){
	if (a->front == NULL)
		return -1;
	a->count--;
	return a->front->info;
}

element popBack(HEAD* a){
	if (a->front == NULL)
		return -1;
	NODE* b = a->front;
	while (b->next != NULL)
		b = b->next;
	a->count--;
	return b->info;
}

int listCount(HEAD* a){
	return a->count;
}

bool isEmptyList(HEAD* a){
	if (a->count == 0)
		return true;
	else return false;
}

void insert(HEAD* a,int nth, element info){
	if (a->count < nth)
		return;
	NODE* newnode = (NODE*)malloc(sizeof(NODE));
	newnode->info = info;
	newnode->next = NULL; //새 노드를 만듬
	NODE* b = a->front;
	if (nth == 1){
		newnode->next = b;
		a->front = newnode;
		a->count++;
		return;
	}//첫번째에 껴넣을 때
	else{
		for (int i = 1; i < nth-1; i++)
			b = b->next; //front node of destination
	}
	newnode->next = b->next;
	b->next = newnode;
	a->count++;
}
//1th, 2th have to be thought

void erase(HEAD* a,int nth){
	if (a->count < nth)
		return;
	NODE* frtnode = a->front;
	if (nth == 1) {
		a->front = frtnode->next;
		free(frtnode);
		a->count--;
		return;
	}
	for (int i = 1; i < nth-1; i++)
		frtnode = frtnode->next;
	NODE* erasenode = frtnode->next;
	frtnode->next = frtnode->next->next;
	a->count--;
	free(erasenode);
}

void remove(HEAD* a, element value){
	NODE* prenode = a->front;//prenode는 바꾸고자 하는 것 앞에 있는 노드이다.
	while (prenode->next !=NULL){
		if (a->count <= 0) return;
		if (a->front->info == value){
			NODE* freenode = a->front;
			a->front = a->front->next;
			free(freenode);
			a->count--;
			prenode = a->front; // while조건문때문에 써준것
			continue;
		}
		if (prenode->next->info == value){
			NODE* freenod = prenode->next;
			prenode->next = freenod->next;
			free(freenod);
			a->count--;
			continue;
		}
		prenode = prenode->next;
	}
}//erase elements that have this value

void unique(HEAD* a){
	NODE* k = a->front;
	if (a->count <= 0) return;
	for (int i = 1; i < a->count; i++){
		NODE* seenode = k->next;
		for (int j = i + 1; j <= a->count; j++){
			if (k->info == seenode->info){
				seenode = seenode->next;
				erase(a, j);
				j--;
				continue;
			}
			seenode = seenode->next;
		}
		k = k->next;
	}
}

void exchange(HEAD* a, int first, int second){ //first보다 second가 더 크다고 가정한다.
	if (first > a->count || second > a->count || second <= 0 || first <= 0) return;
	NODE* ffn = a->front;
	NODE* ssn = a->front;
	if (first == 1);
	for (int i = 1; i < first - 1; i++)
		ffn = ffn->next;
	for (int i = 1; i < second - 1; i++)
		ssn = ssn->next;
	//ffn과 ssn은 목표 노드의 바로 앞 노드이다.
	if (first + 1 == second){
		NODE* tmp = ffn->next;
		if (first == 1){
			a->front = ssn->next;
			tmp = ssn->next->next;
			ssn->next->next = ssn;
			ssn->next = tmp;
			return;
		}
		ffn->next = ffn->next->next;
		tmp->next = ffn->next->next;
		ffn->next->next = tmp;
	}//바꿀게 바로 붙어있을 경우
	else{
		NODE* tmp = ffn->next->next;
		if (first == 1){
			tmp = a->front->next;
			a->front->next = ssn->next->next;
			ssn->next->next = tmp;
			tmp = a->front;
			a->front = ssn->next;
			ssn->next = tmp;
			return;
		}
		ffn->next->next = ssn->next->next;
		ssn->next->next = tmp;
		tmp = ffn->next;
		ffn->next = ssn->next;
		ssn->next = tmp;
	}//바꿀 게 최소 한 칸 이상 떨어져있을 경우
}

void reverse(HEAD* a){
	if (a->count == 0) return;
	for (int i = 1; i<=a->count / 2; i++)
		exchange(a, i, a->count - i + 1);
}

HEAD* merge(HEAD* a,HEAD* b){
	NODE* k = a->front;
	while (k->next != NULL)
		k = k->next;
	k->next = b->front;
	a->count = a->count + b->count;
	free(b);
	return a;
}

void sort(HEAD* a){
	NODE* pre = a->front;
	NODE* next = a->front->next;
	for (int i = a->count-1; i >= 1;i--){
		for (int j = 1; j <= i; j++){
			if (a->compare(&pre->info, &next->info) == 1){
				exchange(a, j, j + 1);
				next = pre->next;
			}
			else{
				pre = pre->next;
				next = pre->next;
			}
		}
		pre = a->front;
		next = a->front->next;
	}
}

int same(void*a){
	if (*(int*)a == 3)
		return 1;
	else 0;
}

void remove_if(HEAD*a, int(*fptr)(void* k)){
	NODE* pre = a->front;
	while (pre != NULL){
		if (fptr(&(pre->info)) == 1){
			NODE* aa = pre->next;
			remove(a, pre->info);
			pre = aa;
			continue;
		}
		pre = pre->next;
	}
}

void showlist(HEAD* a){
	if (a->count == 0){
		printf("Nothing in here");
		return;
	}
	NODE* aa = a->front;
	for (int i = 1; i <= a->count; i++){
		printf("%d ", aa->info);
		aa = aa->next;
	}
}

int main(){
	HEAD* a = createList(intcompare);
	pushFront(a, 3);
	pushFront(a, 7); pushFront(a, 7);
	pushFront(a, 5);
	pushFront(a, 3);
	pushFront(a, 5);
	pushFront(a, 7); pushFront(a, 7);
	pushFront(a, 9);
	pushFront(a, 3);
	unique(a);

	remove_if(a, (*same));
	showlist(a);
}