#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element;

typedef struct treenode{
	element info;
	int frequency;
	struct treenode* left, *right;
}Treenode;//��ģ���� tree

typedef struct nodetreenode{
	Treenode* ptr;
	struct nodetreenode* next;
}Node;

typedef struct head{
	Node* front;
	int count;
}Head;//�ΰ����� list

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
}//list�� �� �����ٰ� ���ο� node�� �����

void removetwo(Head* a){
	if (a->count<2)
		return;
	Node* tofree = a->front;
	a->front = a->front->next->next;
	a->count = a->count-2;
	free(tofree->next);
	free(tofree);
}//a->list�� �� �� �ΰ��� �����Ѵ�.

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
} // node�� �ֳ� ���� �˻��ϴ� �Լ� ������ ��ġ��� ������ NULL


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
}//���� ���� ���� a->front�� ������

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
				tmp = 1;//tmp�� 1�̸� ã�Ҵٴ� ���̰�, 0�̸� �׷� ��尡 ���ٴ� ���̴�.
				break;
			}
			prev = prev->next;
		} //�׷� node�� �ֳ� ã�´�.
		if (tmp == 0&&i!=0)
			enlist(a, createtree(NULL, exam[i], 1, NULL)); //������ enlist�Ѵ�.
	}//�ѱ��ھ� �˻��ؼ�, ������ list�� �ְ�, ������ frequency�� ������Ų��.
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
	Treenode* aa = Huffman(a); //������ Ʈ���� �ϼ��Ǿ����ϴ�. ��������� �� ���ư��ϴ�.
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

//��ü ���� �ڵ��?
//���ڿ��� �޾Ƽ� putfrequecy�Լ��� �ش��ϴ� node�� frequency�� ���� ����ִ´�.
//�׸��� �� list a�� �޾Ƽ� huffman Ʈ���� �����.