#include<stdio.h>
#include<stdlib.h>
typedef struct node{
	int person;
	struct node *next;
}linklist; 
linklist *creat(int n){
	linklist *head,*next;
	head=(linklist *)malloc(sizeof(linklist));
	head->person =1;
	head->next =NULL;
	linklist *p=head;
	int i;
	for(i=2;i<=n;i++){
		linklist *student=(linklist*)malloc(sizeof(linklist));
		student->person =i;
		student->next =NULL;
		p->next=student;
		p=p->next ;
	}
	p->next =head;
	return head;
}
void remove(linklist *head,int g,int o){
	linklist *re=head;
	while(re->next!=head){
		re=re->next ;
	}
	linklist *q=head;
	while(q->person !=g){
		re=q;
		q=q->next ;
	}
	while(q->next !=q){
		for(int i=1;i<o;i++){
			re=q;
			q=q->next; 
		}
		re->next =q->next ;
		printf("���������ǣ�%d\n",q->person );
		free(q);
		q=re->next ;
	}
	printf("���������ǣ�%d",q->person );
	free(q);	
}
int main(){
	int n;
	printf("�ж�����Χ��������"); 
	scanf("%d",&n);
	linklist *head=creat(n);
	printf("�ӵڼ����˿�ʼ������");
	int m;
	scanf("%d",&m);
	printf("ÿ�������˱�һ����:");
	int k;
	scanf("%d",&k);
	remove(head,m,k);
	return 0;
}















