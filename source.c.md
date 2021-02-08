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
void adduser(Node1** auhead, Node1** auend)
{
	char lname[18], lpwd1[8],lpwd2[8];
	int ai;
	Node1* a_user;
	Node1* te_user;

	a_user = (Node1*)malloc(sizeof(Node1));
	if (a_user != NULL) 
	{
		a_user->data = (sUser*)malloc(sizeof(sUser));
	}
	else
	{
		printf("内存申请失败\n");
		exit(EXIT_FAILURE);
	}

	te_user = (*auhead);

	if (a_user->data != NULL)
	{
		printf("------添加卡------\n");
		do {
			ai = false;
			printf("请输入卡号<长度为1~18>：");
			s_gets(lname, 18);
			if (te_user->data  != NULL)
			{
				for (; te_user != NULL; te_user = te_user->next)
				{
					if (strcmp(lname, te_user->data->aName))
					{
						continue;
					}
					else
					{
						ai = true;
						printf("该卡号已被注册\n");
						break;
					}
				}
			}
			else;
		} while (ai);
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
			a_user->data->aName[j] = lname[j];
		}
		for (int j = 0; j < 8; j++)
		{
			a_user->data->aPwd[j] = lpwd1[j];
		}
		a_user->data ->tStart = time(NULL);
		a_user->data->fBalance = 0;
		a_user->data->tEnd = a_user->data->tStart + (long)31536000;
		a_user->data->nStatus = 0;
		a_user->data->tLast = time(NULL);
		a_user->data->nUseCount = 0;
		a_user->data->nDel = 0;

		//将添加的卡加入链表尾
		if ((*auhead) != NULL)
		{
			if ((*auhead)->data != NULL)
			{
				(*auend)->next = a_user;
				a_user->next = NULL;
				(*auend) = a_user;
			}
			else
			{
				free((*auhead)->data);
				free((*auhead));
				(*auhead) = a_user;
				a_user->next = NULL;
				(*auend) = a_user;
			}
		}
		else
		{
			printf("内存申请失败\n");
			exit(EXIT_FAILURE);
		}

		printf("开卡成功，有效期一年\n");
	}
	else
	{
		printf("内存申请失败\n");
		exit(EXIT_FAILURE);
	}
}

//查询卡
void inquire(Node1* i_uhead)
{
	int ct=0;            //记录查询结果个数
	char dname[18];
	Node1* i_current;
	Node1* n_current;

	i_current = i_uhead;

	printf("------查询卡------\n");
	printf("请输入要查询的卡号：");
	s_gets(dname, 18);
	printf("%20s %10s %12s %15s %20s\n", "卡号", "余额", "累计使用金额", "累计使用次数", "上次使用时间");
	do {
		if (strncmp(i_current->data->aName, dname, strlen(dname)) == 0)
		{
			printf("%20s ", i_current->data->aName);
			printf("%10f ", i_current->data->fBalance);
			printf("%12f ", i_current->data->fTotalUse);
			printf("%15d ", i_current->data->nUseCount);
			printf("%s\n", asctime(localtime(&(i_current->data->tLast))));

			n_current = i_current->next;
			i_current = n_current;

			ct++;
		}
		else
		{
			n_current = i_current->next;
			i_current = n_current;
		}
	} while (i_current != NULL);

	if (ct);
	else
		printf("无相关结果!\n");
}

//上机
Node1* login(Node1* l_uhead,int * l_soon)
{
	char usingname[18];
	char u_pwd[8];
	int sign;
	Node1* l_current;
	Node1* n_current;
	Node1* on;

	sign = 1;
	on = NULL;
	l_current = l_uhead;

	printf("------上机------\n");
	printf("请输入卡号：");
	s_gets(usingname,18);
	do {
		if (strcmp(usingname, l_current->data->aName))
		{
			n_current = l_current->next;
			l_current = n_current;
		}
		else
		{
			on = l_current;
			break;
		}
	} while (l_current != NULL);
	if (l_current == NULL)
	{
		printf("请检查你输入的卡号是否正确！\n（为避免非本人操作，将结束此次上机）\n");
		sign = 0;
	}
	else
	{
		printf("请输入密码：");
		s_gets(u_pwd, 8);
		if (strcmp(u_pwd, on->data->aPwd))
		{
			printf("密码错误！\n（为避免非本人操作，本次操作结束）\n");
			sign = 0;
		}
		else
		{
			on->data->nStatus = 1;
			*l_soon = 0;
			printf("上机成功——\n");
		}
	}
	if (sign)
	{
		return on;
	}
	else
	{
		return NULL;
	}
}

//下机
void logout(Node1* l_on,int*lsoon,Node2*llend)
{
	printf("------下机------\n");
	if (l_on->data->fBalance)
	{
		*lsoon = false;
		l_on->data->tLast = time(NULL);
		l_on->data->nUseCount++;
	}
	else
	{
		do {
			printf("余额为零，请充值后将进行正常的下机操作：\n");
			recharge(llend, l_on);
		} while (l_on->data->fBalance == 0);

		*lsoon = false;
		l_on->data->tLast = time(NULL);
		l_on->data->nUseCount++;
	}
}

//充值
void recharge(Node2** r_lend, Node1* r_on)
{
	Node2* r_current;
	long ch;
	
	r_current = (Node2*)malloc(sizeof(Node2));
	if (r_current != NULL)
	{
		 r_current->data= (lUser*)malloc(sizeof(lUser));
	}
	else
	{
		printf("内存申请失败\n");
		exit(EXIT_FAILURE);
	}

	if (r_current->data != NULL)
	{
		printf("------充值------\n");
		for (int i = 0; i < 18; i++)
		{
			r_current->data->bName[i] = r_on->data->aName[i];
		}
		r_current->data->Kind = 1;
		r_current->data->Re = r_on->data->fBalance;

		printf("请输入充值金额：");
		if ((scanf("%ld", &ch)) == 1);
		else
		{
			do {
				printf("接收错误，请再次输入：");
			} while ((scanf("%ld", &ch)) != 1);
		}
		r_current->data->Af = r_current->data->Re + ch;
		r_on->data->fBalance += ch;
	
		r_current->data->tEnd = time(NULL);

		(*r_lend)->next = r_current;
		r_current->next = NULL;
		(*r_lend) = r_current;
	}
	else
	{
		printf("内存申请失败\n");
		exit(EXIT_FAILURE);
	}
}

//退费
void refund(Node2** re_lend, Node1* re_on)
{
	Node2* re_current;

	re_current = (Node2*)malloc(sizeof(Node2));
	if (re_current != NULL)
	{
		re_current->data = (lUser*)malloc(sizeof(lUser));
	}
	else
	{
		printf("内存申请失败\n");
		exit(EXIT_FAILURE);
	}

	if (re_current->data != NULL)
	{
		printf("------退费------\n");
		for (int i = 0; i < 18; i++)
		{
			re_current->data->bName[i] = re_on->data->aName[i];
		}
		re_current->data->Kind = 2;
		re_current->data->Re = re_on->data->fBalance;

		if (re_on->data->fBalance > 0)
		{
			printf("正在退费。。。\n");
			printf("退费金额：%f \n", re_on->data->fBalance);
			re_current->data->Af = 0;
			re_on->data->fTotalUse += re_on->data->fBalance;
			re_on->data->fBalance = 0;
		}
		else
		{
			printf("余额为0！无法退费。\n");
			re_current->data->Af = 0;
		}

		re_current->data->tEnd = time(NULL);

		(*re_lend)->next = re_current;
		re_current->next = NULL;
		(*re_lend) = re_current;
	}
	else
	{
		printf("内存申请失败\n");
		exit(EXIT_FAILURE);
	}
}

//注销
void dele(Node2** d_lend, Node1* d_on)
{
	Node2* d_current;

	d_current = (Node2*)malloc(sizeof(Node2));
	if (d_current != NULL)
	{
		d_current->data = (lUser*)malloc(sizeof(lUser));
	}
	else
	{
		printf("内存申请失败\n");
		exit(EXIT_FAILURE);
	}
	if (d_current->data != NULL)
	{
		printf("------注销------\n");
		for (int i = 0; i < 18; i++)
		{
			d_current->data->bName[i] = d_on->data->aName[i];
		}
		d_current->data->Kind = 0;
		d_current->data->Re = d_on->data->fBalance;

		printf("卡号                退费金额\n");
		printf("%18s  %f", d_on->data->aName, d_on->data->fBalance);

		d_current->data->Af = 0;
		d_current->data->tEnd = time(NULL);

		d_on->data->nStatus = 2;
		d_on->data->nDel = 1;

		(*d_lend)->next = d_current;
		d_current->next = NULL;
		(*d_lend) = d_current;
	}
	else
	{
		printf("申请内存失败\n");
		exit(EXIT_FAILURE);
	}
}

//退出程序
void quit(Node1* q_on, int* q_soon)
{
	*q_soon = false;  
	q_on->data->nStatus = 0;
	q_on->data->tLast = time(NULL);
	q_on->data->nUseCount++;
}

//字符串输入
char* s_gets(char* st, int n)
{
	char* ret_val;
	int i = 0;

	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		while (st[i] != '\n' && st[i] != '\0')
			i++;
		if (st[i] == '\n')
			st[i] = '\0';
		else
			while (getchar() != '\n')
				continue;

	}
	return ret_val;
}
```

