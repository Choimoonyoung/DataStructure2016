#include<stdio.h>

long long a[101];

long long fibo(int n){
	if (a[n] != 0)
		return a[n];
	
	else{
		a[n] = fibo(n - 1) + fibo(n - 2);
		return a[n];
	}

}

int main(){
	a[1] = 0;
	a[2] = 1;
	a[3] = 1;
	for (int i = 50; i <= 59; i++){
		printf("%d : %lld\n", i, fibo(i));
	}
}