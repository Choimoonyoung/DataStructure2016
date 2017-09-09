#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

//circular queue

typedef int element;

typedef struct queuew{
	element* queue;
	int size;
	int front, rear;
}Queue;

Queue* Createcqueue(int size){
	Queue* ptrqueue = (Queue*)malloc(sizeof(Queue));
	if (ptrqueue == NULL)
		return NULL;
	ptrqueue->queue = (element*)malloc(sizeof(element)*size);
	if (ptrqueue->queue == NULL)
		return NULL;
	ptrqueue->front = ptrqueue->rear = 0;
	ptrqueue->size = size;
}

int isFullqueue(Queue*a){
	if ((a->rear + 1) % a->size == a->front)
		return 1;//true
	else
		return 0;//false
}

int isEmptyqueue(Queue* a){
	if (a->front == a->rear)
		return 1;//true
	else return 0;//false
}

void Encqueue(Queue*a,element item){
	if (isFullqueue(a) == 1)
		printf("Queue is full");
	else{
		a->rear = (a->rear + 1) % a->size;
		a->queue[a->rear] = item;
	}
}

element Decqueue(Queue*a){
	if (isEmptyqueue(a) == 1)
		return -1;
	else{
		a->front = (a->front + 1) % a->size;
		return a->queue[a->front];
	}

}

void josephusPermutation(Queue* a, int k){
	int temp = 0; // k번 도나 체크하는 것
	while (isEmptyqueue(a) != 1){
		if (temp != k-1){
			temp++;
			Encqueue(a,Decqueue(a));
		}//k번 돌기 전
		else{
			printf("%d ", Decqueue(a));
			temp = 0;
		}//k번째
	}
}


int main(){
	int n,k;
	scanf("%d %d", &n,&k);
	Queue* a = Createcqueue(n+1);
	for (int i = 1; i <= n; i++)
		Encqueue(a,i);
	josephusPermutation(a, k);
}

