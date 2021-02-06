```c
#include "bank.h"

int main()
{
	int i,soon;              //标志位
	char ele;                //选择
	Node1* uhead;            //用户数据链表头指针
	Node1* uend;             //用户数据链表尾指针
	Node1* current1;         //建立用户数据链表用的中间指针
	Node1* current2;         //建立用户数据链表时用的中间指针
	Node1* on;               //指向正在上机的用户数据的指针
	Node2* lhead;            //历史记录链表头指针
	Node2* lend;             //历史记录链表尾指针
	Node2* Current1;         //建立历史记录链表时用到的中间指针
	Node2* Current2;         //建立历史记录链表时用到的中间指针
	FILE*  fp1;              //指向用户数据文件的指针
	FILE*  fp2;              //指向历史记录文件的指针
	
	//初始化
	i = 0;					 //继续标志位初始为假
	soon = 1;				 //快捷标志为初始为真
	uhead    = NULL;
	uend     = NULL;
	current1 = NULL;
	current2 = NULL;
	on       = NULL;
	lhead    = NULL;
	lend     = NULL;
	Current1 = NULL;
	Current2 = NULL;
	
	//打开用户数据文件
	if ((fp1 = fopen("users'data", "r")) == NULL)
	{
		printf("打开文件失败\n");
		exit(EXIT_FAILURE);
	}

	//打开历史记录文件
	if ((fp2 = fopen("using log", "r")) == NULL)
	{
		printf("打开文件失败\n");
		exit(EXIT_FAILURE);
	}

	//创建用户数据链表
	uhead = (Node1*)malloc(sizeof(Node1));
	if ((fscanf(fp1, "%18s %8s %d %ld %ld %f %ld %d %f %d", uhead->data->aName, uhead->data->aPwd, uhead->data->nStatus, uhead->data->tStart, uhead->data->tEnd, uhead->data->fTotalUse, uhead->data->tLast, uhead->data->nUseCount, uhead->data->fBalance, uhead->data->nDel)) != EOF)
	{
		uhead->next = NULL;
		current1 = (Node1*)malloc(sizeof(Node1));
		while ((fscanf(fp1, "%18s %8s %d %ld %ld %f %ld %d %f %d", current1->data->aName, current1->data->aPwd, current1->data->nStatus, current1->data->tStart, current1->data->tEnd, current1->data->fTotalUse, current1->data->tLast, current1->data->nUseCount, current1->data->fBalance, current1->data->nDel)) != EOF)
		{
			if (uhead->next == NULL)
			{
				uhead->next = current1;
				current2 = current1;
				current1->next = NULL;
				current1 = (Node1*)malloc(sizeof(Node1));
			}
			else
			{
				current2->next = current1;
				current1->next = NULL;
				current2 = current1;
				current1 = (Node1*)malloc(sizeof(Node1));
			}
		}
		uend = current2;
		free(current1);
	}
	else
	{
		uhead->next = NULL;
		uend = uhead;
	}

	//创建历史记录链表
	lhead = (Node2*)malloc(sizeof(Node2));
	if ((fscanf(fp2, "%18s %d %ld %ld %ld", lhead->data->bName, lhead->data->Kind, lhead->data->Re, lhead->data->Af, lhead->data->tEnd)) != EOF)
	{
		lhead->next = NULL;
		Current1 = (Node2*)malloc(sizeof(Node2));
		while ((fscanf(fp2, "%18s %d %ld %ld %ld", Current1->data->bName, Current1->data->Kind, Current1->data->Re, Current1->data->Af, Current1->data->tEnd)) != EOF)
		{
			if (lhead->next == NULL)
			{
				lhead->next = Current1;
				Current2 = Current1;
				Current1->next = NULL;
				Current1 = (Node2*)malloc(sizeof(Node2));
			}
			else
			{
				Current2->next = Current1;
				Current1->next = NULL;
				Current2 = Current1;
				Current1 = (Node2*)malloc(sizeof(Node2));
			}
		}
		lend = Current2;
		free(Current1);
	}
	else
	{
		lhead->next = NULL;
		lend = lhead;
	}

	//初始菜单选择
	do {
		menu1();
		scanf("%c", &ele);
		if (ele <= '4' && ele >= '1')
		{
			switch (ele)
			{
			case '1':
				adduser(uhead, uend);
				break;
			case '2':
				inquire(uhead);
				break;
			case'3':
				on = login(uhead,&soon);
				break;
			case'4':
				soon = false;
				break;
			}

			if (soon)
			{
				printf("是否继续使用（是=1，否=0）:");
				scanf("%d", &i);
			}
			else
			{
				i = false;
			}
		}
		else
		{
			printf("无对应的功能模块，请重新登入系统！");
			i = false;
		}
	}while (on==NULL && i==1);

	soon = 1;//重复使用快捷标签

	//上机菜单选择
	if (on != NULL)
	{
		do {
			menu2();
			scanf("%c", &ele);
			if (ele <= '5' && ele >= '1')
			{
				switch (ele)
				{
				case '1':
					logout(on, &soon, lend);
					break;
				case '2':
					recharge(lend, on);
					break;
				case'3':
					refund(lend, on);
					break;
				case'4':
					dele(lend, on);
					break;
				case'5':
					quit(on, &soon);
					break;
				}

				if (soon)
				{
					printf("是否继续使用（是=1，否=0）:");
					scanf("%d", &i);
					if (i == 0)
					{
						on->data->tLast = time(NULL);
						on->data->nStatus = 0;
						on->data->nUseCount++;
					}
				}
				else
				{
					printf("已下机！\n");
					i = false;
				}
			}
		} while (i);
	}

	//关闭文件
	if (fclose("users'data") != 0)
		printf("关闭文件\"users'data\"时出现问题!\n");
	if (fclose("using log") != 0)
		printf("关闭文件\"using log\"时出现问题!\n");

	//重新打开文件
	if ((fp1 = fopen("users'data", "w")) == NULL)
	{
		printf("打开文件失败\n");
		exit(EXIT_FAILURE);
	}

	if ((fp2 = fopen("using log", "w")) == NULL)
	{
		printf("打开文件失败\n");
		exit(EXIT_FAILURE);
	}

	//将新数据写入文件
	current1 = uhead;
	if (uhead->next != NULL)
	{
		do{
			fprintf(fp1, "%18s %8s %d %ld %ld %f %ld %d %f %d", current1->data->aName, current1->data->aPwd, current1->data->nStatus, current1->data->tStart, current1->data->tEnd, current1->data->fTotalUse, current1->data->tLast, current1->data->nUseCount, current1->data->fBalance, current1->data->nDel);
			current2 = current1->next ;
			free(current1);
			current1 = current2;
		} while (current1 != NULL);
	}
	else
	{
		fprintf(fp1, "%18s %8s %d %ld %ld %f %ld %d %f %d", uhead->data->aName, uhead->data->aPwd, uhead->data->nStatus, uhead->data->tStart, uhead->data->tEnd, uhead->data->fTotalUse, uhead->data->tLast, uhead->data->nUseCount, uhead->data->fBalance, uhead->data->nDel);
		free(uhead);
	}

	Current1 = lhead;
	if (lhead->next != NULL)
	{
		do {
			fprintf(fp2, "%18s %d %ld %ld %ld", Current1->data->bName, Current1->data->Kind, Current1->data->Re, Current1->data->Af, Current1->data->tEnd);
			Current2 = Current1->next;
			free(Current1);
			Current1 = Current2;
		} while (Current1 != NULL);
	}
	else
	{
		fprintf(fp2, "%18s %d %ld %ld %ld", lhead->data->bName, lhead->data->Kind, lhead->data->Re, lhead->data->Af, lhead->data->tEnd);
		free(lhead);
	}

	printf("感谢使用!\n");

	return 0;
}
```

