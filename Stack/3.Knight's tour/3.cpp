#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef int element;

typedef struct node{
	struct node *a;
	element i,j;
}Node;
//�ϳ��� node�ȿ� 2���� element ����

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
} //�� �� ����� i ���

element StackTopj(Head* top){
	if (top->count <= 0)
		return -1;
	else{
		return top->top->j;
	}

}//�� �� ����� j ���


int visit[100][100]; // �湮����

int dirx[8] = { -2, -2, -1, 1, 2, 2, 1, -1 };
int diry[8] = { -1, 1, 2, 2, 1, -1, -2, -2 }; //���� �������� ����


void printchess(int n){
	for (int i =1 ; i <= n; i++){
		for (int j = 1; j <= n; j++)
			printf("%d ", visit[i][j]);
		printf("\n");
	}
} // ü���� ���

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
			if (nx < 1 || nx >n || ny < 1 || ny > n) continue; // �ٵ��� �ȿ� ������
			if (visit[nx][ny] == 1) continue; // �湮����������
			//printchess(n);
			//printf("\n");
			if (dfs(a, n, nx, ny) == 1) return 1; // ������ ���
			//�ȳ����µ� �ٵ��Ǿȿ� �հ� �湮�� �� ������

		}
		pop(a);
		visit[x][y] = 0;
		return 0;//8���� ������ ��� ������

	}

}


int main(){
	int n, i, j;
	scanf("%d %d %d", &n, &i, &j); //n,i,j �Է¹ޱ�
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
	} // �ڵ� count ���� ���
}