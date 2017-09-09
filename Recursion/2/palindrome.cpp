#include<stdio.h>
#pragma warning(disable:4996)

int string_length(char*a, int*n){
	if (a[0] == '\0')
		return 0;
	else{
		(*n)++;
		string_length(a + 1, n);
	}
}

void palindrome(char *a, char*b){
	if (a[0]=='\0'){
		printf("The string is palindrome\n");
	}
	else{
		if (a[0] == b[0])
			palindrome(a + 1, b - 1);
		else
			printf("The string is not palindrome\n");
	}
	
}

int main(){
	int n = 0;
	int*ptr = &n;
	string_length("string", ptr);
	printf("%d\n", n);
	while (true){
		char a[50];
		scanf("%s", a);
		int i = 0;
		int*ptrd = &i;
		string_length(a,ptrd);
		palindrome(a, a + *ptrd - 1);
	}
}