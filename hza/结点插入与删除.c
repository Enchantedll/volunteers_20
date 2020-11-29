#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stud_node {
    int num;
    char name[20];
    int data;
    struct stud_node*next;
};

struct stud_node *Creat_Stu_Doc();//新建链表
struct stud_node *InsertDoc (struct stud_node *head,struct stud_node *stud);//插入
struct stud_node * DeleteDoc (struct stud_node *head, int num);//删除

int main()
{

    struct stud_node *head, *p;
    int button,num ,data;
    char name[20];
    do{
        printf("1 -> Creat \n2 -> Insert \n3 -> Delete\n0 -> Exit\n");
        scanf("%d",&button);
        switch(button){
            case 1:
                head=Creat_Stu_Doc();
                break;
            case 2:
                printf("Input num, name and data:");
                scanf("%d%s%d",&num ,name ,&data);
                p = (struct stud_node *) malloc (sizeof (struct stud_node));
                p->num=num;
                strcpy(p->name,name);
                p->data=data;
                head=InsertDoc(head, p);
                break;
            case 3:
                printf("Input num: \n");
                scanf("%d",&num);
                head=DeleteDoc(head, p);
                break;
            case 0:
                break;
            }
    }while(button != 0);

    return 0;
}

struct stud_node *Creat_Stu_Doc()//新建链表
{
    struct stud_node *head, *p;
    int num, data;
    char name[20];

    head = NULL;
    printf("Input num, name and score: \n");
    scanf("%d%s%d",&num, name &data);
    while(num != 0) {
        p = (struct stud_node *) malloc(sizeof(struct stud_node));
        p->num = num;
        strcpy(p->name, name);
        p->data = data;
        head = InsertDoc (head, p);
        scanf("%d%s%d",&num, name, &data);
        }
    return head;
}

struct stud_node *InsertDoc (struct stud_node *head,struct stud_node *stud) //插入
{
    struct stud_node *ptr, *ptr1 , *ptr2;
    ptr2 = head;
    ptr = stud;//指向新学生的节点
    if(head==NULL){//原链表为空
        head=ptr;
        head->next=NULL;//
    }
    else{
        while((ptr->num>ptr2->num) && (ptr2->next!=NULL)){
            ptr1 = ptr2;
            ptr2 = ptr2->next;
        }
        if (ptr->num<=ptr2->num){//p1,p2之间插入结点
            if(head==ptr2) head = ptr;
            else ptr1->next = ptr;
            ptr ->next=ptr2;
        }
        else{
            ptr2->next = ptr;
            ptr->next = NULL;
        }
    }
    return head;
}

struct stud_node *DeleteDoc (struct stud_node *head, int num)//删除
{
    struct stud_node *ptr1, *ptr2;

    //删除头结点
    while(head!=NULL && head->num==num){
        ptr2=head;
        head=head->next;
        free(ptr2);
    }
    if(head==NULL)
        return NULL;
    //删除非表头结点
    ptr1=head;
    ptr2=head->next;
    while(ptr2!=NULL){
        if (ptr2->num==num){
            ptr1->next=ptr2->next;
            free(ptr2);
        }
        else
            ptr1=ptr2;
        ptr2 = ptr1->next;
    }
    return head;
}
