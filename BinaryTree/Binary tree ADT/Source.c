#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"


typedef struct treenode{
	element info;
	struct treenode* left, *right;
}Treenode;

Treenode* createtree(Treenode* left, element info, Treenode* right){
	Treenode* a = (Treenode*)malloc(sizeof(Treenode));
	if (a == NULL)
		return NULL;
	a->left = left;
	a->right = right;
	a->info = info;
	return a;
}

void preorder(Treenode* root){
	if (root == NULL)
		return;
	printf("%s", root->info);
	preorder(root->left);
	preorder(root->right);
}

void postorder(Treenode* root){
	if (root == NULL)
		return;
	postorder(root->left);
	postorder(root->right);
	printf("%s", root->info);
}

void inordertraverse(Treenode* root){
	if (root == NULL)
		return;
	inordertraverse(root->left);
	printf("%s",root->info);
	inordertraverse(root->right);
}

void Destroytree(Treenode* root){
	if (root == NULL)
		return;
	Destroytree(root->left);
	Destroytree(root->right);
	free(root);
}

Treenode* copytree(Treenode* oldroot){
	if (oldroot == NULL)
		return NULL;
	Treenode* newnode= createtree(copytree(oldroot->left), oldroot->info, copytree(oldroot->right));
}

void levelorder(Treenode* root){
	HEAD* a = createqueue();
	Enqueue(a, root);
	while (a->count != 0){
		Treenode* nownode = Dequeue(a);
		printf("%s", nownode->info);
		if (nownode->left != NULL)
			Enqueue(a,nownode->left);
		if (nownode->right != NULL)
			Enqueue(a,nownode->right);
	}
}

void infixtraversal(Treenode* root){
	if (strchr("abcdefghijklmnopqrstuvwxyz", root->info[0]) != NULL){
		printf("%s", root->info);
		return;
	}
	printf("(");
	infixtraversal(root->left);
	printf("%s", root->info);
	infixtraversal(root->right);
	printf(")");
}

void postfixtraversal(Treenode* root){
	if (root == NULL)
		return;
	postfixtraversal(root->left);
	postfixtraversal(root->right);
	printf("%s", root->info);
}

void prefixtraversal(Treenode* root){
	if (root == NULL)
		return;
	printf("%s", root->info);
	prefixtraversal(root->left);
	prefixtraversal(root->right);
}

void Huffman(char* apple){
	apple
}
int main(){
	Treenode* a = createtree(NULL,"a",NULL);
	Treenode* b = createtree(NULL, "b", NULL);
	Treenode* c = createtree(NULL, "c", NULL);
	Treenode* plus1 = createtree(b, "+", c);
	Treenode* multi = createtree(a, "*", plus1);
	Treenode* d = createtree(NULL, "d", NULL);
	Treenode* plus2 = createtree(multi, "+", d);

	//preorder(plus2);
	//inordertraverse(plus2);
	//postorder(plus2);
	//levelorder(plus2);
	//infixtraversal(plus2);
	//postfixtraversal(plus2);
	//prefixtraversal(plus2);
}

