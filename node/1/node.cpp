#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	void* datalink;
	struct node* newlink;
}NODE;


NODE* createnode(void* link){
	NODE* nodeptr = NULL;
	nodeptr = (NODE*)malloc(sizeof(NODE));
	nodeptr->datalink = link;
	nodeptr->newlink = NULL;
	return nodeptr;

}


int main(){
	int* newdata = NULL;
	float* nodedata = NULL;
	newdata = (int*)malloc(sizeof(int));
	*newdata = 11;
	nodedata = (float*)malloc(sizeof(float));
	*nodedata = 11.6;

	NODE* newnode1 = createnode(newdata);
	NODE* newnode2 = createnode(nodedata);

	newnode1->newlink = newnode2;

	printf("Data from first node:%d\n", *(int*)newnode1->datalink);
	printf("Data from second node:%.1f\n", *(float*)newnode2->datalink);
	printf("What is the %p of first node connection\n", (double*)newnode1->newlink);
	printf("What is the %p of second node", (double*)newnode2);

	

}