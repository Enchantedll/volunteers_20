#include<iostream>
#include<stdlib.h>

struct Node{
	int data,address;
	struct Node *next; //指向Node的指针 
};
struct Node* creatList(){
	struct Node* headNode=(struct Node*)malloc(sizeof(struct Node));
	headNode->next=NULL;  
	return headNode;
}
struct Node* creatNode(int data){ //返回值类型是struct node* 
	struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
	newNode->data=data;
	newNode->next=NULL;
	return newNode;
}
void printList(struct Node* headNode){
	struct Node* pMove=headNode->next;
	while(pMove){
		printf("%d",pMove->data);
		pMove=pMove->next;
	}
	printf("\n");
} 
void InsertNodebyhead(struct Node* headNode,int data){  //在头部插入一个节点 
	struct Node* newNode = creatNode(data);
	newNode->next = headNode->next;
	headNode->next = newNode;
}
void InsertNode(struct Node* headNode,int n,int data){
	struct Node* pMove = headNode -> next;
	int n2 = n - 2;
	while(n2--){
		pMove = pMove -> next;
	}
	struct Node* newnode = creatNode(data);
	newnode -> data = data;
	newnode -> next = pMove -> next;
	pMove -> next = newnode; 
} 
void DeleteNode(struct Node* headNode,int n){
	struct Node* pMove1 = headNode -> next;
	struct Node* pMove2 = headNode -> next;
	int n2 = n - 2;
	while(n2--){
		pMove1 = pMove1 -> next;
		pMove2 = pMove2 -> next;
	}
	pMove2 = pMove2 -> next;
	pMove1 -> next = pMove2 -> next;
}

int main(){
	struct Node* list = creatList();
	InsertNodebyhead(list, 4);
	InsertNodebyhead(list, 3);
	InsertNodebyhead(list, 2);
	InsertNodebyhead(list, 1);
	DeleteNode(list,2);//删除第二个节点 
	InsertNode(list,2,6);//在第二个插入一个6 
	printList(list);
}
