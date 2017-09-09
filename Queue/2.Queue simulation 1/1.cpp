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
}//��ü queue�� patience�� 1�� �����

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
			pre = pre->next;
	}
} //��ü queue���� �� ���� �����ϰ� ��� ��带 �˻��Ͽ� 0�� ���� �����

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

} //hotdog�� �������

int main(){
	HEAD* a = createqueue();
	int n;
	scanf("%d", &n);
	int pat;
	for (int i = 1; i <= n; i++){
		printf("Patience of customer : ");
		scanf("%d", &pat);
		Enqueue(a, pat);
		printf("\n");
	} // customer���� patience�Է�
	printf("We sell %d hotdogs",hotdogStand(a));


}