#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef int element;

typedef struct node{
	struct node *a;
	element i,j;
}Node;
//하나의 node안에 2개의 element 저장

typedef struct head{
	struct node *top;
	int count;
}Head;

element StackTopi(Head*top);
element StackTopj(Head*top);

void pop(Head*top){
	if (top->count == 0);
	else{
		Node*oldone = top->top;
		top->top = top->top->a;
		(top->count)--;
		free(oldone);
	}
}

void push(Head* stack, element i, element j){
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->a = stack->top;
	newnode->i = i;
	newnode->j = j;
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

element StackTopi(Head* top){
	if (top->count <= 0)
		return -1;
	else{
		return top->top->i;
	}
} //맨 위 노드의 i 출력

element StackTopj(Head* top){
	if (top->count <= 0)
		return -1;
	else{
		return top->top->j;
	}

}//맨 위 노드의 j 출력


int visit[100][100]; // 방문여부

int dirx[8] = { -2, -2, -1, 1, 2, 2, 1, -1 };
int diry[8] = { -1, 1, 2, 2, 1, -1, -2, -2 }; //방향 전역변수 선언


void printchess(int n){
	for (int i =1 ; i <= n; i++){
		for (int j = 1; j <= n; j++)
			printf("%d ", visit[i][j]);
		printf("\n");
	}
} // 체스판 출력

int dfs(Head*a,int n,int x, int y){
	push(a,x,y);
	visit[x][y] = 1;
	if (a->count == n*n)
		return 1;
	//base case
	else{
		int nx, ny;
		for (int i = 0; i <= 7; i++){
			nx = x + dirx[i];
			ny = y + diry[i]; 
			if (nx < 1 || nx >n || ny < 1 || ny > n) continue; // 바둑판 안에 없을때
			if (visit[nx][ny] == 1) continue; // 방문한적있을때
			//printchess(n);
			//printf("\n");
			if (dfs(a, n, nx, ny) == 1) return 1; // 끝났을 경우
			//안끝낫는데 바둑판안에 잇고 방문한 적 없을때

		}
		pop(a);
		visit[x][y] = 0;
		return 0;//8가지 방향이 모두 없을때

	}

}


int main(){
	int n, i, j;
	scanf("%d %d %d", &n, &i, &j); //n,i,j 입력받기
	Head*a = CreateStack();
	int k = dfs(a,n,i,j);
	int count = n*n;
	if (k <= 0) printf("There's no way to go everywhere");
	else{
		while (a->count > 0){
			visit[StackTopi(a)][StackTopj(a)] = count--;
			pop(a);
		}
		printchess(n);
	} // 코드 count 세서 출력
}