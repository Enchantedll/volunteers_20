```c
#include "bank.h"
//菜单1
void menu1(void)
{
	printf("------菜单------");
	printf("\n1:添加卡\n2:查询卡\n3:上机\n4:退出程序\n");
	printf("请选择您所需功能的菜单编号：");
};

//菜单2
void menu2(void)
{
	printf("------菜单------");
	printf("\n1.下机\n2.充值\n3.退费\n4.注销账户卡\n5.退出程序\n");
	printf("请选择您所需功能的菜单编号：");
}

//添加卡
void adduser(Node1* uhead, Node1* uend)
{
	char lname[18], lpwd1[8],lpwd2[8];
	int i;
	Node1* user;

	user = (Node1*)malloc(sizeof(Node1));

	printf("------添加卡------\n");

	do {
		i = false;
		printf("请输入卡号<长度为1~18>：");
		s_gets(lname, 18);
		for (Node1* i = uhead; i != NULL; i = i->next)
		{
			if (strcmp(lname, i->data->aName))
			{
				continue;
			}
			else
			{
				i = true;
				printf("该卡号已被注册\n");
				break;
			}
		}
	} while (i);
	printf("卡号申请成功\n");
	printf("请设置密码：");
	s_gets(lpwd1, 8);
	printf("请确认密码：");
	s_gets(lpwd2, 8);
	if (strcmp(lpwd1, lpwd2))
	{
		do {
			printf("前后输入不一致,请重新输入密码:");
			s_gets(lpwd1, 8);
			printf("请确认密码：");
			s_gets(lpwd2, 8);
		} while (strcmp(lpwd1, lpwd2)!=0);
	}
	else;

	//补全添加卡的资料
	for (int j = 0; j < 18; j++)
	{
		user->data->aName[j] = lname[j];
	}
	for (int j = 0; j < 8; j++)
	{
		user->data->aPwd[j] = lpwd1[j];
	}
	user->data ->tStart = time(NULL);
	user->data->fBalance = 0;
	user->data->tEnd = (long)user->data->tStart + (long)31536000;
	user->data->nStatus = 0;
	user->data->tLast = time(NULL);
	user->data->nUseCount = 0;
	user->data->nDel = 0;

	//将添加的卡加入链表尾
	uend->next = user;
	user->next = NULL;
	uend = user;

	printf("开卡成功，有效期一年\n");
}

//查询卡
void inquire(Node1* uhead)
{
	int ct=0;            //记录查询结果个数
	char dname[18];
	Node1* current;
	Node1* n_current;

	current = uhead;

	printf("------查询卡------\n");
	printf("请输入要查询的卡号：");
	s_gets(dname, 18);
	printf("%20s %10s %12s %15s %20s\n", "卡号", "余额", "累计使用金额", "累计使用次数", "上次使用时间");
	do {
		if (strncmp(current->data->aName, dname, strlen(dname)) == 0)
		{
			printf("%20s ", current->data->aName);
			printf("%10f ", current->data->fBalance);
			printf("%12f ", current->data->fTotalUse);
			printf("%15d ", current->data->nUseCount);
			printf("%s\n", asctime(localtime(&(current->data->tLast))));

			n_current = current->next;
			current = n_current;

			ct++;
		}
		else
		{
			n_current = current->next;
			current = n_current;
		}
	} while (current != NULL);

	if (ct);
	else
		printf("无相关结果!\n");
}

//上机
Node1* login(Node1* uhead,int * soon)
{
	char usingname[18];
	char u_pwd[8];
	Node1* current;
	Node1* n_current;
	Node1* on;

	on = NULL;
	current = uhead;

	printf("------上机------\n");
	printf("请输入卡号：");
	s_gets(usingname,18);
	do {
		if (strcmp(usingname, current->data->aName))
		{
			n_current = current->next;
			current = n_current;
		}
		else
		{
			on = current;
			break;
		}
	} while (current != NULL);
	if (current == NULL)
	{
		printf("请检查你输入的卡号是否正确！\n（为避免非本人操作，将结束此次上机）\n");
	}
	else
	{
		printf("请输入密码：");
		s_gets(u_pwd, 8);
		if (strcmp(u_pwd, on->data->aPwd))
		{
			printf("密码错误！\n（为避免非本人操作，本次操作结束）\n");
		}
		else
		{
			on->data->nStatus = 1;
			*soon = 0;
			printf("上机成功——\n");
		}
	}

	return on;
}

//下机
void logout(Node1* on,int*soon,Node2*lend)
{
	printf("------下机------\n");
	if (on->data->fBalance)
	{
		*soon = false;
		on->data->tLast = time(NULL);
		on->data->nUseCount++;
	}
	else
	{
		do {
			printf("余额为零，请充值后将进行正常的下机操作：\n");
			recharge(lend, on);
		} while (on->data->fBalance == 0);
	}
}

//充值
void recharge(Node2* lend, Node1* on)
{
	Node2* current;
	long ch;
	
	current = (Node2*)malloc(sizeof(Node2));

	printf("------充值------\n");
	for (int i = 0; i < 18; i++)
	{
		current->data->bName[i] = on->data->aName[i];
	}
	current->data->Kind = 1;
	current->data->Re = on->data->fBalance;

	printf("请输入充值金额：");
	scanf("%ld", &ch);
	current->data->Af = current->data->Re + ch;
	on->data->fBalance += ch;

	current->data->tEnd = time(NULL);

	lend->next = current;
	current->next = NULL;
	lend = current;
	free(current);
}

//退费
void refund(Node2* lend, Node1* on)
{
	Node2* current;

	current = (Node2*)malloc(sizeof(Node2));

	printf("------退费------\n");
	for (int i = 0; i < 18; i++)
	{
		current->data->bName[i] = on->data->aName[i];
	}
	current->data->Kind = 2;
	current->data->Re = on->data->fBalance;

	if (on->data->fBalance > 0)
	{
		printf("正在退费。。。\n");
		printf("退费金额：%d\n", on->data->fBalance);
		current->data->Af = 0;
		on->data->fTotalUse += on->data->fBalance;
		on->data->fBalance = 0;
	}
	else
	{
		printf("余额为0！无法退费。\n");
		current->data->Af = 0;
	}

	current->data->tEnd = time(NULL);

	lend->next = current;
	current->next = NULL;
	lend = current;
	free(current);
}

//注销
void dele(Node2* lend, Node1* on)
{
	Node2* current;

	current = (Node2*)malloc(sizeof(Node2));

	printf("------注销------\n");
	for (int i = 0; i < 18; i++)
	{
		current->data->bName[i] = on->data->aName[i];
	}
	current->data->Kind = 0;
	current->data->Re = on->data->fBalance;

	printf("卡号                退费金额\n");
	printf("%18s  %f", on->data->aName, on->data->fBalance);

	current->data->Af = 0;
	current->data->tEnd = time(NULL);

	on->data->nStatus = 2;
	on->data->nDel = 1;

	lend->next = current;
	current->next = NULL;
	lend = current;
	free(current);
}

//退出程序
void quit(Node1* on, int* soon)
{
	*soon = false;  
	on->data->nStatus = 0;
	on->data->tLast = time(NULL);
	on->data->nUseCount++;
}
```

