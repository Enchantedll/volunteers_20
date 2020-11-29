#include <stdio.h>
#include <stdlib.h> 
typedef struct node{
	int data;
	struct node *next;
}list;

list *creat(){
	int i,dat,n;
	list *head,*p,*q;
	head=NULL;
	printf("链表长度：");
	scanf("%d",&n);
	printf("输入需要输入的数据：");
	for(i=0;i<n;i++){
		scanf("%d",&dat);
		p=(list *)malloc(sizeof(list));
		p->data=dat;
		if(head==NULL)q=p,head=q;
		else q->next=p;
		q=p;
	} 
	p->next=NULL;
	return head;
}

list *reverse(list *head){
	list *p,*q,*k;
	p=head;
	q=k=NULL;
	while(p!=NULL){
		q=p->next ;
		p->next =k;
		k=p;
		p=q;
	}
	return k;
}

void print(list *head){
	list *p;
	p=head;
	while(p!=NULL){
		printf("%d ",p->data );
		p=p->next ;
	}
}

int main(){
	list *head;
	head=creat();
	printf("请输入数据");
	print(head);
	head=reverse(head);
	printf("\n逆置后数据：");
	print(head);
	return 0; 
}
















