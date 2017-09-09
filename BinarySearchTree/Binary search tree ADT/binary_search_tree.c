#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int element;

typedef struct treenode{
	element info;
	struct treenode* left, *right;
}Treenode;

Treenode* createtree(Treenode* left, element info, Treenode* right){
	Treenode* a = (Treenode*)malloc(sizeof(Treenode));
	if (a == NULL)
		return NULL;
	a->info = info;
	a->left = left;
	a->right = right;
}

Treenode* FindSmallestBST(Treenode* root){
	if (root == NULL)
		return NULL;
	if (root != NULL&&root->left == NULL)
		return root;
	FindSmallestBST(root->left);
}

Treenode* FindLargestBST(Treenode* root){
	if (root == NULL)
		return NULL;
	if (root != NULL &&root->right == NULL)
		return root;
	FindLargestBST(root->right);
	
}

Treenode* searchBST(Treenode* root, element key){
	if (root == NULL)
		return NULL;
	if (root->info == key)
		return root;
	if (key < root->info)
		return searchBST(root->left,key);
	if (key> root->info)
		return searchBST(root->right,key);
}

Treenode* insertion(Treenode* root, element info){
	if (root == NULL)
		return NULL;
	if (root->info > info){
		if (root->left == NULL){
			root->left = createtree(NULL, info, NULL);
			return root->left;
		}
		insertion(root->left, info);
	}
	else{
		if (root->right == NULL){
			root->right = createtree(NULL, info, NULL);
			return root->right;
		}
		insertion(root->right, info);
	}
}

int success = -1;

Treenode* Deletion(Treenode* root, element data){
	if (root == NULL){
		*success = -1;
		return root;
	}

	if (data < root->info)
		root->left = Deletion(root->left, data, success);
	else if (data>root->info)
		root->right = Deletion(root->right, data, success);
	else{
		Treenode *delPtr = NULL; 
		*success = 0;
		if (!root->right){
			delPtr = root;
			root = root->left;
			free(delPtr);
			return root;
		}
		else if (!root->left){
			delPtr = root;
			root = root->right;
			free(delPtr);
			return root;
		}
		else{
			for (delPtr = root->left; delPtr->right != NULL; delPtr = delPtr->right);
			root->info = delPtr->info;
			root->left = Deletion(root->left, delPtr->info, success);
		}
	}
	return root;
}

int main(){
	Treenode* leaf1 = createtree(NULL, 12, NULL);
	Treenode* leaf2 = createtree(NULL, 20, NULL);
	Treenode* leaf3 = createtree(NULL, 35, NULL);
	Treenode* leaf4 = createtree(NULL, 52, NULL);
	Treenode* inter1 = createtree(leaf1, 18, leaf2);
	Treenode* inter2 = createtree(leaf3, 44, leaf4);
	Treenode* root = createtree(inter1, 23, inter2);

	insertion(root, 53);

	printf("%d", FindLargestBST(root)->info);
}