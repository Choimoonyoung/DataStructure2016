#include <stdio.h>
#include <stdlib.h>


typedef struct arc{
	struct arc* next;
	int weight;
	struct vertex* dest;
}Arc;

typedef struct vertex{
	struct vertex* next;//vertex들을 무작위 순서로 연결해놓은 것
	int processed;
	Arc* arc; //linked list형태로 연결된 vertex들을 표현함
	void* dataPtr;//vertex 이름
}Vertex;


typedef struct graph{
	int count;
	Vertex* first;
	int(*compare)(void* arg1, void* arg2);
}Graph;


typedef struct node{
	Vertex* info;
	struct node* next;
}Node;


typedef struct head{
	Node* front, *rear;
	int count;
}Head;

Graph* graphCreate(int(*compare)(void* a, void* b)){
	Graph* a = (Graph*)malloc(sizeof(Graph));
	if (a == NULL)
		return NULL;
	a->compare = compare;
	a->count = 0;
	a->first = NULL;
	return a;
}

Head* createqueue(){
	Head* a = (Head*)malloc(sizeof(Head));
	a->count = 0;
	a->front = a->rear = NULL;
	return a;
}

void enqueue(Head* head, Vertex* a){
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->info = a;
	newnode->next = NULL;
	if (head->count == 0){
		head->count++;
		head->front = head->rear = newnode;
		return;
	}
	head->count++;
	head->rear->next = newnode;
	head->rear = newnode;
	return;
}

Vertex* graphInsertVertex(Graph* a, void* info){
	Vertex* newvtx = (Vertex*)malloc(sizeof(Vertex));
	newvtx->arc = NULL;
	newvtx->next = NULL;
	newvtx->processed = 0;
	newvtx->dataPtr = info;
	a->count++;
	Vertex* node = a->first;
	if (node == NULL){
		a->first = newvtx;
		return newvtx;
	}
	while (node->next != NULL)
		node = node->next;
	node->next = newvtx;
	return newvtx;
}

void _insertArc(Graph* a, Vertex* start, Vertex* end, int weight){
	if (a == NULL)
		return;
	Vertex* find = a->first;
	while (find != NULL){
		if (start == find){
			Arc* a = find->arc;
			Arc *newnode = (Arc*)malloc(sizeof(Arc));
			newnode->dest = end;
			newnode->weight = weight;
			newnode->next = NULL;
			if (a == NULL){
				find->arc = newnode;
				return;
			}
			while (a->next != NULL)
				a = a->next;
			a->next = newnode;
			return;
		}
		find = find->next;
	}
}

void _removeArc(Graph* a, Vertex* start, Vertex* end){
	Vertex* findvtx = a->first;
	while (findvtx != NULL){
		if (findvtx == start){//만약 시작 vertex를 찾았다면
			Arc* findarc = findvtx->arc;
			Arc* prefindarc = NULL;
			for (; findarc != NULL; prefindarc = findarc, findarc = findarc->next){
				if (findarc->dest == end){//만약 끝 vertex arc를 찾았다면
					if (prefindarc == NULL){//시작일경우
						findvtx->arc = findarc->next;
						free(findarc);
						return;
					}
					//시작 아닐경우
					prefindarc->next = findarc->next;
					free(findarc);
					return;
				}
			}
		}
		findvtx = findvtx->next;
	}
	printf("There is no arc inside this Graph");
}

void graphInsertArc(Graph* a, Vertex* start, Vertex* end, int weight){
	_insertArc(a, start, end, weight);
	_insertArc(a, end, start, weight);
}

void graphRemoveArc(Graph* a, Vertex* start, Vertex* end){
	_removeArc(a, start, end);
	_removeArc(a, end, start);
}
int charCompare(void* a, void* b){
	if (*(char*)a > *(char*)b)
		return 1;
	else if (*(char*)a == *(char*)b)
		return 0;
	else
		return -1;
}

void deleteVertex(Graph* a, Vertex* todelete){
	if (a == NULL)
		return;
	Vertex* prevtx = NULL;
	Vertex* nowvtx = a->first;
	while (nowvtx != NULL){
		if (todelete == nowvtx){
			a->count--;
			if (prevtx == NULL)//맨 앞이라면?
				a->first = nowvtx->next;
			else
				prevtx->next = nowvtx->next;
			Arc* prearc;
			Arc* nowarc;
			for (prearc = NULL, nowarc = nowvtx->arc; nowarc != NULL; prearc = nowarc, nowarc = nowarc->next){
				if (nowarc == NULL)
					break;//arc가 아무것도 없었다면?
				else if (prearc == NULL){//맨 앞이라면?
					free(nowarc);
					break;
				}
				else
					free(prearc);
			}
			if (prearc != NULL)
				free(prearc); //arc가 2개 이상이었을 때
			free(nowvtx);
			if (prevtx == NULL)//맨 앞 vtx
				nowvtx = a->first;
			else//아닐때
				nowvtx = prevtx->next;
			continue;
		}//같은 vertex를 발견했다면

		Arc* prearc = NULL;
		Arc* nowarc = nowvtx->arc;
		while (nowarc != NULL){
			if (nowarc->dest == todelete){//지우고자 하는arc일때
				if (prearc == NULL){//첫번째거이면
					nowvtx->arc = nowarc->next;
					free(nowarc);
					nowarc = nowvtx->arc;
					continue;
				}
				//첫번째가 아니면
				prearc->next = nowarc->next;
				free(nowarc);
				nowarc = prearc->next;
				continue;
			}
			prearc = nowarc;
			nowarc = nowarc->next;
		}
		//같은 vertex가 아닐때는 arc를 지운다.
		prevtx = nowvtx;
		nowvtx = nowvtx->next;
	}
}

void graphDestroy(Graph* a){
	Vertex* pDel = NULL;
	Vertex* pNext = NULL;
	for (pDel = a->first; pDel != NULL; pDel = pNext){
		pNext = pDel->next;
		Arc* arcDel = NULL;
		Arc* arcNext = NULL;
		for (arcDel = pDel->arc; arcDel != NULL; arcDel = arcNext){
			arcNext = arcDel->next;
			free(arcDel);
		}
		free(pDel);
	}
	free(a);
}

void graphRemoveVertex(Graph* a, Vertex* todelete){
	Vertex* pPrev = NULL;
	Vertex* pDel = NULL;
	for (pDel = a->first; pDel != NULL; pPrev = pDel, pDel = pDel->next){
		if (todelete == pDel){
			a->count--;
			if (pDel->arc != NULL){
				printf("It has an arc, so can't erase");
				return;
			}
			if (pPrev == NULL){
				a->first = pDel->next;
				free(pDel);
			}
			else{
				pPrev->next = pDel->next;
				free(pDel);
			}
			return;
		}
	}
	printf("No vertex inside here");
}//Vertex가 arc를 가지고 있지 않을 경우만 지운다.

Vertex* dequeue(Head* a){
	if (a->count == 0)
		return NULL;
	Node* freenode;
	if (a->count == 1){
		freenode = a->front;
		a->count--;
		a->front = a->rear = NULL;
		Vertex* tmp = freenode->info;
		free(freenode);
		return tmp;
	}
	freenode = a->front;
	a->front = a->front->next;
	a->count--;
	Vertex* tmp = freenode->info;
	free(freenode);
	return tmp;
}

void dfs(Vertex* a){
	if (a->processed == 1){ // 방문한 적이 있으면
		return;
	}
	a->processed = 1;
	printf("%c", *(char*)a->dataPtr);
	Arc* nowarc = a->arc;
	while (nowarc != NULL){
		if (nowarc->dest->processed == 0)
			dfs(nowarc->dest);
		nowarc = nowarc->next;
	}
}
void bfs(Head* a, Vertex* start){
	if (start->processed == 1)
		return;
	start->processed = 1;
	enqueue(a, start);
	while (a->count != 0){
		Vertex* aa = dequeue(a);
		printf("%c", *(char*)aa->dataPtr);
		Arc* nowver = aa->arc;
		while (nowver != NULL){
			if (nowver->dest->processed != 1){
				nowver->dest->processed = 1;
				enqueue(a, nowver->dest);
			}
			nowver = nowver->next;
		}
	}
}

int isVertexIn(void* a, Graph* b){
	Vertex* nowver = NULL;
	for (nowver = b->first; nowver != NULL; nowver = nowver->next){
		if (b->compare(nowver->dataPtr, a) == 0)
			return 1;
	}
	return 0;
}//그래프 b 안에 저 void를 가진 vertex가 존재하는가?

Vertex* vertexIn(void* a, Graph* b){
	Vertex* nowver = NULL;
	for (nowver = b->first; nowver != NULL; nowver = nowver->next){
		if (b->compare(nowver->dataPtr, a) == 0)
			return nowver;
	}
	return NULL;
}//그래프 b 안에 저 void를 가진 vertex가 존재하는가?

Graph* PrimAlgorithm(Graph* a){
	Graph* b = graphCreate((*charCompare));
	graphInsertVertex(b, a->first->dataPtr);
	Arc* max = (Arc*)malloc(sizeof(Arc));
	max->weight = 99999999;
	max->dest = NULL;
	max->next = NULL;
	while (a->count != b->count){
		Vertex* nowvtx = NULL;
		Vertex* minvtx = NULL;
		Arc* nowarc = NULL;
		Arc* min = max;
		for (nowvtx = a->first; nowvtx != NULL; nowvtx = nowvtx->next){
			if (isVertexIn(nowvtx->dataPtr, b) == 1){//만약 이 vertex가 b 안에 있다면!
				for (nowarc = nowvtx->arc; nowarc != NULL; nowarc = nowarc->next){
					if (nowarc->weight < min->weight && isVertexIn(nowarc->dest->dataPtr, b) != 1){
						min = nowarc;
						minvtx = nowvtx;
					}
				}
			}
		}
		graphInsertArc(b, vertexIn(minvtx->dataPtr, b), graphInsertVertex(b, min->dest->dataPtr), min->weight);
	}
	return b;
}

int main(){
	Graph * aa = graphCreate((*charCompare));
	Head* queue = createqueue();
	Vertex* a = graphInsertVertex(aa, "A");
	Vertex* b = graphInsertVertex(aa, "B");
	Vertex* c = graphInsertVertex(aa, "C");
	Vertex* d = graphInsertVertex(aa, "D");
	Vertex* e = graphInsertVertex(aa, "E");
	Vertex* f = graphInsertVertex(aa, "F");
	graphRemoveVertex(aa, f);
	graphInsertArc(aa, a, b, 6);
	graphInsertArc(aa, a, c, 3);
	graphInsertArc(aa, c, b, 2);
	graphInsertArc(aa, d, b, 5);
	graphInsertArc(aa, c, d, 3);
	graphInsertArc(aa, c, e, 4);
	graphRemoveArc(aa, c, e);
	graphInsertArc(aa, c, e, 4);
	graphInsertArc(aa, d, e, 2);
	graphInsertArc(aa, d, f, 3);
	graphInsertArc(aa, e, f, 5);
	Graph*bb = PrimAlgorithm(aa);
	dfs(bb->first);
	printf("\n");
	//bfs(queue,bb->first);
}