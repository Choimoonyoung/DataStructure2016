#include<stdio.h>
#include<stdlib.h>
#include"Stack.h"

#pragma warning(disable:4996

void nopop(Head*top){
	if (top->count == 0)
		printf("Nothing to pop\n");
	else{
		Node*oldone = top->top;
		top->top = top->top->a;
		(top->count)--;
		free(oldone);
	}
}

int bracecheck(){
	Head*top = CreateStack();
	int num = 0;
	char arr[101];
	scanf("%s", arr);
	char a = arr[0];
	while (a != '\0'){
		a = arr[num++];
		if (a == '{' || a == '[' || a == '('){
			push(top, a, num);
		}
		else if (a == '}'){
			if (StackTop(top) == '{')
				nopop(top);
			else
				return num;
		}
		else if (a == ']'){
			if (StackTop(top) == '[')
				nopop(top);
			else
				return num;
		}
		else if (a == ')'){
			if (StackTop(top) == '('){
				nopop(top);
			}
			else
				return num;
		}
		else;
	}

	if (top->count == 0)
		return 0;
	else
		return top->top->num;
}

int main(){
	int a = bracecheck();
	if (a == 0) printf("Correct!");
	else printf("%d th place is wrong",a);
}


