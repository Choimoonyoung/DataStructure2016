#include<stdio.h>
#include<stdlib.h>

typedef int element;

typedef struct tHeap{
	element* heaparray;
	int maxsize; // 최대 원소 개수
	int idx;//지금 index
}Heap;

Heap* heapCreate(int max){
	Heap* a = (Heap*)malloc(sizeof(Heap));
	if (!a)
		return NULL;
	element* heaparray = (element*)malloc(sizeof(element)*max);
	a->heaparray = heaparray;
	a->idx = 0;
	a->maxsize = max;
	return a;
}

void heapDestroy(Heap* a){
	free(a->heaparray);
	free(a);
}

int heapCount(Heap* a){
	return a->idx+1;
}

int heapFull(Heap* a){
	if (a->idx+1 == a->maxsize)
		return 1;//true
	else
		return 0;//false
}

int heapEmpty(Heap* a){
	if (a->idx == 0)
		return 1;
	else
		return 0;
}

void reheapUp(Heap* a, int index){
	int parentidx = (index - 1) / 2;
	if (index <= 0 || index >= a->maxsize || a->heaparray[parentidx] >= a->heaparray[index]){
		return;
	}
	element tmp;
	tmp = a->heaparray[parentidx];
	a->heaparray[parentidx] = a->heaparray[index];
	a->heaparray[index] = tmp;
	reheapUp(a, parentidx);
}//recursive

void reheapDown(Heap* a, int nowidx){
	if (nowidx >= a->maxsize - 1)
		return;
	if (a->heaparray[nowidx * 2 + 1] > a->heaparray[nowidx]){
		element tmp = a->heaparray[nowidx];
		a->heaparray[nowidx] = a->heaparray[nowidx * 2 + 1];
		a->heaparray[nowidx * 2 + 1] = tmp;
		reheapDown(a, nowidx * 2 + 1);
	}
	if (a->heaparray[nowidx * 2 + 2] > a->heaparray[nowidx]){
		element tmp = a->heaparray[nowidx];
		a->heaparray[nowidx] = a->heaparray[nowidx * 2 + 2];
		a->heaparray[nowidx * 2 + 2] = tmp;
		reheapDown(a, nowidx * 2 + 2);
	}
	else
		return;
}
Heap* heapInsert(Heap* a, element info){
	if (heapFull(a)){
		printf("There's no space to insert");
		return NULL;
	}
	a->heaparray[a->idx+1] = info;
	a->idx++;
	reheapUp(a, a->idx);
	return a;
}

Heap* heapDelete(Heap* a){
	if (heapEmpty(a)){
		printf("There's nothing to delete");
		return NULL;
	}
	a->heaparray[0] = a->heaparray[a->idx];
	a->idx--;
	reheapDown(a,0);
	return a;
}
Heap* combineHeap(Heap* a, Heap* b){
	if (a->maxsize < a->idx + 1 + b->idx + 1){
		printf("a size is too small");
		return NULL;
	}
	for (int i = 0; i <= b->idx; i++){
		heapInsert(a, b->heaparray[i]);
	}
	return a;
}

void heapSort(Heap* a){
	int i = 0;
	for (i = 0; i <= a->idx; i++){
		reheapUp(a, i);
	}
}

int main(){

}
