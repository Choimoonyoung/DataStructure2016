#include<stdio.h>

void recur(int n){
	if (n == 1)
		printf("1");
	else if (n == 0)
		printf("0");
	else{
		recur(n / 2);
		printf("%d", n % 2);
	}
}

int main(){
	for (int i = 1; i <= 12; i++){
		printf("%d : ", i);
		recur(i);
		printf("\n");
	}
}