#include<stdio.h>
#include<string.h>


int compare(void* a, void*b){
	if (*(int*)a >= *(int*)b)
		return 1;
	else
		return -1;
}

int stringCompare(void*a, void*b){
	int alen = strlen((char*)a);
	int blen = strlen((char*)b);
	if (alen >= blen)
		return 1;
	else
		return -1;
}

void* larger(void*a, void*b, int(*fptr)(void*aa, void*bb)){
	if ((*fptr)(a, b) >= 1)
		return a;
	else
		return b;
}

int main(){
	int a = 9;
	int b = 8;
	char aa[] = "abcd";
	char bb[] = "efffffff";
	int * ptr1 = NULL;
	char * ptr2 = NULL;
	ptr1 = (int*)larger(&a, &b, compare);
	ptr2 = (char*)larger(aa, bb, stringCompare);

	printf("Larger Value is %d\n", *ptr1);
	printf("Longer String is %s", ptr2);