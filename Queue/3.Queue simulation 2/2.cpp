#include<stdio.h>
#include<stdlib.h>
#include"Queue.h"
#pragma warning(disable:4996)

void decreasepatience(HEAD*a){
	NODE* q = a->front;
	while (q != a->rear){
		q->info--;
		q = q->next;
	}
	q->info--;
}

void deleteZero(HEAD*a){
	if (a->count <= 1) return;
	NODE* old = NULL;
	NODE* pre = a->front;
	while (pre->next != NULL){
		if (pre->next->info == 0){
			old = pre->next;
			if (pre->next == a->rear){
				pre->next = NULL;
				a->rear = pre;
			}
			else
				pre->next = pre->next->next;
			free(old);
			a->count--;
		}
		else
			pre=pre->next;
	}
}

int hotdogStand(HEAD*a){
	int hotdog = 0;
	while (a->count != 0){
		decreasepatience(a);
		if (a->front->info >= -1){
			Dequeue(a);
			hotdog++;
		}
		deleteZero(a);
	}
	return hotdog;

}

int main(){
	HEAD* first = createqueue();
	HEAD*second = createqueue();
	int n;
	scanf("%d", &n);
	int pat;
	element arr[100];//patience�� ����
	int hotdog[100];//hotdog�� ����
	for (int i = 0; i < n; i++){
		printf("Patience of customer : ");
		scanf("%d", &arr[i]);
		printf("\n");
	} // customer���� patience�Է�, ���� first�� ����

	for (int k = 1; k < n; k++){
		for (int kk = 0; kk < n;kk++)
			Enqueue(first, arr[kk]);//Enqueue�� ���� ����
		for (int i = 0; i < k; i++)
			Enqueue(second, Dequeue(first));
		hotdog[k - 1] = hotdogStand(first) + hotdogStand(second);
	}//hotdog�� ��� ����� �� ����

	int max = hotdog[0];
	for (int i = 1; i < n - 1; i++){
		if (max < hotdog[i])
			max = hotdog[i];
	}

	printf("I can sell maximum %d hotdog",max);
}