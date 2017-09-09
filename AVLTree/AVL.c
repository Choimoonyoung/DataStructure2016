#include<stdio.h>
#include<stdlib.h>

typedef int element;


typedef struct node{
	void* info;
	struct node* left, *right;
	int bal;
}Node;

typedef struct head{
	int count;
	Node* root;
	int(*compare) (void* a, void* b);
}Head; //AVL tree�� head

int compare(void* a, void* b);

Head* AVL_create(){
	Head* a = (Head*)malloc(sizeof(Head));
	a->count = 0;
	a->root = NULL;
	a->compare = compare;
	return a;
}

int intcompare(int a, int b);

int compare(void* a, void* b){
	if (intcompare(*(int*)a, *(int*)b) == 1)
		return 1;//true
	else
		return -1;//false
}

int intcompare(int a, int b){
	if (a >= b)
		return 1;//true
	else
		return -1;//false
}

Node* createnode(void* element){
	Node* newnode = (Node*)malloc(sizeof(Node));
	if (newnode = NULL)
		return NULL;
	newnode->bal = 0;
	newnode->info = element;
	newnode->left = newnode->right = NULL;
	return newnode;
} // ���ο� node�� ����� �Լ�

Node* rotateRight(Node* root){
	Node* tmp = root->left;
	root->left = tmp->right;
	tmp->right = root;
	return tmp;
}

Node* rotateLeft(Node* root){
	Node* tmp = root->right;
	root->right = tmp->left;
	tmp->left = root;
	return tmp;
}

Node* rightChange(Node* root, int* fix){
	switch (root->right->bal){
	case 1: //RL rotation
		switch (root->right->left->bal){
		case 1:
			root->bal = 1;
			root->right->bal = 0;
			break;
		case 0: //
			root->bal = 0;
			root->right->bal = 0;
			break;
		case -1:
			root->bal = 0;
			root->right->bal = -1;
			break;
		}
		root->right->left->bal = 0;
		root->right = rotateRight(root->right);
		root = rotateLeft(root);
		*fix = 0;
		break;
	case 0: //error
		printf("Error\n");
		*fix = 0;
		break;
	case -1://RR rotation
		root->bal = 0;
		root->right->bal = 0;
		root = rotateRight(root);
		*fix = 0;
		break;
	}
	return root;
}

Node* changeLeft(Node* root, int* fix){
	switch (root->left->bal){
	case 1://LL rotation
		root->bal = 0;
		root->left->bal = 0;
		root = rotateRight(root);
		*fix = 0;
		break;
	case 0:
		printf("error\n");
		*fix = 0;
		break;
	case -1:
		switch (root->left->right->bal){
		case 1:
			root->bal = -1;
			root->left->bal = 0;
			break;
		case 0:
			root->bal = 0;
			root->left->bal = 0;
			break;
		case -1:
			root->bal = 0;
			root->left->bal = 1;
			break;
		}
		root->left->right->bal = 0;
		root->left = rotateLeft(root->left);
		root = rotateRight(root);
		*fix = 0;
		break;
	}
	return root;
}

Node* AVL_insert(Head* AVL, Node* root, void* element, int* fix){ 
	if (root == NULL){
		root = createnode(element);
		*fix = 1;
		AVL->count++;
		return root;
	}
	
	if (compare(element, root->info) == 1){//element�� right tree�� ��
		root->right = AVL_insert(AVL,root->right, element, fix);
		if (*fix = 1){
			switch (root->bal){
			case 1: //���� LH�̹Ƿ�, ���� EH �� �Ǿ��ڴ�!
				root->bal = 0;
				*fix = 0;
				break;
			case 0: //���� EH�̹Ƿ�, ���� RH�� �Ǿ�����!
				root->bal = -1;
				break;
			case -1://���� RH�̹Ƿ�, ���� -2�� �Ǿ��� ��!
				root = rightChange(root,fix);//�� ���ο��� bal ����
				break;
			}
		}
		return root;
	}

	else{//element�� root info���� ���� ->left 
		root->left = AVL_insert(AVL,root->left, element, fix);
		if (*fix == 1){
			switch (root->bal){
			case 1://LH 2�ܰ�
				root = changeLeft(root, fix);
				break;
			case 0://
				root->bal = 1;
				break;
			case -1:
				root->bal = 0;
				*fix = 0;
				break;
			}
		}
		return root;
	}
}

Node* balRight(Node* root, int* shorter){//left�� ���ŵ� ��Ȳ
	Node* righttree = NULL;
	Node* lefttree = NULL;

	switch (root->bal){
	case 1: 
		root->bal = 0;
		break;
	case 0:
		//������ righthigh
		root->bal = -1;
		break;
	case -1:
		//������ -2�Ǿ ����������..... leftrotate���ش�
		righttree = root->right;
		if (righttree->bal == 1){
			//RLrotation�� �ʿ��ϴ�
			lefttree = righttree->left;
			switch (lefttree->bal){
			case 1:
				righttree->bal = -1;
				root->bal = 0;
				break;
			case 0:
				root->bal = 0;
				righttree->bal = 0;
				break;
			case -1:
				root->bal = 1;
				righttree->bal = 0;
				break;
			}
			lefttree->bal = 0;
			root->right = rotateRight(righttree);
			root = rotateLeft(root);
		}
		
		else{
			switch (righttree->bal){
			case 1:
				printf("error");
				break;
			case 0:
				righttree->bal = -1;
				root->bal = 1;
				*shorter = 0;
				break;
			case -1:
				root->bal = 0;
				righttree->bal = 0;
				break;
			}
			root = rotateLeft(root);

		}
		return root;
	}
}

Node* balLeft(Node* root, int* shorter){//right�� ���ŵ� ��Ȳ
	Node* righttree = NULL;
	Node* lefttree = NULL;

	switch (root->bal){
	case 1: 
		//�� ��� 2�� �Ǿ� left high�� �ȴ�
		lefttree = root->left;
		if (lefttree->bal == -1){
			//Double rotation required
			righttree = lefttree->right;
			switch (righttree->bal){
			case 1:
				root->bal = 0;
				lefttree->bal = 1;
				break;
			case 0:
				root->bal = 0;
				lefttree->bal = 0;
				break;
			case -1:
				root->bal = -1;
				lefttree->bal = 0;
				break;
			}
			righttree->bal = 0;
			root->left = rotateLeft(root->left);
			root = rotateRight(root);
		}
		else{
			switch (lefttree->bal){
			case 1:
				root->bal = 0;
				lefttree->bal = 0;
				break;
			case 0:
				lefttree->bal = -1;
				root->bal = 1;
				break;
			case -1:
				printf("error");
				break;
			}
			root = rotateRight(root);
		}
	case 0:
		root->bal = 1;
		*shorter = -1;
		break;
	case -1: 
		root->bal = 0;
		break;
	}
	return root;
}
Node* AVL_delete(Head* AVL, Node* root, void* info, int* shorter, int* success){
	if (root == NULL){
		*shorter = 0;
		*success = 0;
		return NULL;
	}

	if (AVL->compare(info, root->info) == 1){
		root->right = AVL_delete(AVL, root->right, info, shorter, success);
		if (*shorter)
			root = balLeft(root, shorter);
	}
	else if (AVL->compare(info, root->info) == -1){
		root->left = AVL_delete(AVL, root->left, info, shorter, success);
		if (*shorter)
			root = balRight(root, shorter);
	}
	else{
		Node* delPtr = root;
		if (root->right == NULL){
			Node* newroot = root->left;
			*success = 1;
			*shorter = 1;
			free(delPtr);
			return newroot;
		}
		else if (root->left == NULL){
			Node* newroot = root->right;
			*success = 1;
			*shorter = 1;
			free(delPtr);
			return newroot;
		}
		else{
			//���� root�� ���ʰ� �������� ��� ������ ���� ���
			Node* exchPtr = root->left;
			while (exchPtr != NULL)
				exchPtr = exchPtr->right;
			root->info = exchPtr->info;
			root->left = AVL_delete(AVL, root->left, exchPtr->info, shorter, success);
			if (*shorter)
				root = balRight(root,shorter);
		}
	}
	return root;
}

int AVL_search(Node* root, void* element){
	if (*(int*)(root->info) == *(int*)element){
		return 1;
	}
	else if (compare(root, element) == 1){
		AVL_search(root->left, element);
	}
	else
		AVL_search(root->right, element);

	if (root == NULL)
		return 0;
}

int AVL_count(Head* AVL){
	return AVL->count;
}

int AVL_empty(Head* AVL){
	if (AVL->count == 0)
		return 1;
	else return 0;
}

void AVL_printTree(Node* root){
	if (root == NULL)
		return;
	AVL_printTree(root->left);
	printf("%d", *(int*)root->info);
	AVL_printTree(root->right);
}//left, root, right������ ����Ѵ�


int main(){

}