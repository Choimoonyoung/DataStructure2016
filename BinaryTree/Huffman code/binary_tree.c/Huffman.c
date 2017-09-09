#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element;

typedef struct treenode{
	element info;
	int frequency;
	struct treenode* left, *right;
}Treenode;//이친구는 tree

typedef struct nodetreenode{
	Treenode* ptr;
	struct nodetreenode* next;
}Node;

typedef struct head{
	Node* front;
	int count;
}Head;//두가지는 list

Head* createlist(){
	Head* a = (Head*)malloc(sizeof(Head));
	a->front = NULL;
	a->count = 0;
	return a;
}

void enlist(Head* a, Treenode* ptr){
	if (a->count == 0){
		Node* newnode = (Node*)malloc(sizeof(Node));
		newnode->next = NULL;
		a->front = newnode;
		a->count++;
		newnode->ptr = ptr;
		return;
	}
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->next = NULL;
	newnode->ptr = ptr;
	Node* now = a->front;
	while (now->next != NULL)
		now = now->next;
	a->count++;
	now->next = newnode;
	return;
}//list의 맨 끝에다가 새로운 node를 만든다

void removetwo(Head* a){
	if (a->count<2)
		return;
	Node* tofree = a->front;
	a->front = a->front->next->next;
	a->count = a->count-2;
	free(tofree->next);
	free(tofree);
}//a->list의 맨 앞 두개를 제거한다.

Treenode* createtree(Treenode* left, element info, int frequency, Treenode* right){
	Treenode* a = (Treenode*)malloc(sizeof(Treenode));
	if (a == NULL)
		return NULL;
	a->left = left;
	a->right = right;
	a->info = info;
	a->frequency = frequency;
	return a;
}

void inordertraverse(Treenode* root){
	if (root == NULL)
		return;
	inordertraverse(root->left);
	printf("%c", root->info);
	inordertraverse(root->right);
}

void Destroytree(Treenode* root){
	if (root == NULL)
		return;
	Destroytree(root->left);
	Destroytree(root->right);
	free(root);
}

Treenode* istherenode(Treenode* root, char a){
	if (root == NULL)
		return NULL;
	if (root->info = a)
		return root;
	istherenode(root->left, a);
} // node가 있나 없나 검사하는 함수 있으면 위치출력 없으면 NULL


Head* sort(Head* a){
	Node* prev = a->front;
	Node* prenode = a->front;
	for (int i = a->count - 1; i > 0; i--){
		int j = 0;
		while (prev->next != NULL && j != i){
			if (prev->ptr->frequency > prev->next->ptr->frequency && j==0){
				prenode = prev->next;
				prev->next = prev->next->next;
				prenode->next = prev;
				a->front = prenode;
				j++;
				continue;
			}
			else if (prev->ptr->frequency > prev->next->ptr->frequency && j != 0){
				Node* tmp = prev->next->next;
				prenode->next = prev->next;
				prenode->next->next = prev;
				prev->next = tmp;
				j++;
				prenode = prenode->next;
				continue;
			}
			else if (j == 0){
				j++;
				prev = prev->next;
				continue;
			}
			else {
				j++;
				prenode = prenode->next;
				prev = prev->next;
			}
		}
		prev = a->front;
		prenode = a->front;
	}
	return a;
}//제일 작은 값이 a->front로 오도록

Head* putfrequency(Head* a, char* exam){
	int len = strlen(exam);
	Node* prev = a->front;
	int tmp = 0;
	for (int i = 0; i < len; i++){
		prev = a->front;
		tmp = 0;
		if (i == 0)
			enlist(a, createtree(NULL, exam[i], 1, NULL));
		while (prev != NULL){
			if (prev->ptr->info == exam[i]){
				prev->ptr->frequency++;
				tmp = 1;//tmp가 1이면 찾았다는 뜻이고, 0이면 그런 노드가 없다는 뜻이다.
				break;
			}
			prev = prev->next;
		} //그런 node가 있나 찾는다.
		if (tmp == 0&&i!=0)
			enlist(a, createtree(NULL, exam[i], 1, NULL)); //없으면 enlist한다.
	}//한글자씩 검사해서, 없으면 list에 넣고, 있으면 frequency를 증가시킨다.
}

Treenode* Huffman(Head* a){
	if (a->count <= 1){
		return a->front->ptr;
	}
	sort(a);
	Treenode* plus = createtree(a->front->next->ptr, '+', ((a->front->ptr->frequency) + (a->front->next->ptr->frequency)), a->front->ptr);
	enlist(a, plus);
	removetwo(a);
	Huffman(a);
}

int num[10000];
Treenode* Search(Treenode* node, element info, int nu){
	if (node == NULL) return NULL;
	Treenode* a;
	Treenode* b;
	while (node->info != info){
		a = Search(node->right,info,nu+1);
		b = Search(node->left,info,nu+1);
		
		if (a == NULL && b == NULL)	{
			return NULL;
		}
		if (a == NULL){
			num[nu] = 0;
			return b;
		}
		num[nu] = 2;
		return a;
	}
	
	return node;
}


int main(){
	Head* a = createlist();
	FILE *rfp;
	fopen_s(&rfp,"Huffman.txt", "r");
	char aaa[100];
	fscanf_s(rfp, "%s", aaa, 100);
	int len = strlen(aaa);
	putfrequency(a, aaa);
	//removetwo(a);
	//sort(a);
	Treenode* aa = Huffman(a); //허프만 트리가 완성되었습니다. 여기까지는 잘 돌아갑니다.
	for (int i = 0; i < len; ++i){
		for (int j = 0; j < 10000; ++j)
			num[j] = -1;
		Search(aa, aaa[i], 0);
		while (num[i] != -1)
			printf("%d", num[i]);
		printf("\n");
	}
 //	inordertraverse(aa);
}

//대체 무슨 코드냐?
//문자열을 받아서 putfrequecy함수로 해당하는 node와 frequency를 전부 집어넣는다.
//그리고 그 list a를 받아서 huffman 트리를 만든다.