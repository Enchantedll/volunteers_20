```c
#pragma once
#ifndef BANK_H
#define BANK_H

//常量
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define false 0
#define true 1

//结构声明
struct user_st
{
	char	aName[18];		//卡号
	char	aPwd[8];		//密码
	int		nStatus;		//卡状态（0-未上机；1-正在上机；2-已注销；3-失效）
	time_t	tStart;			//开卡时间
	time_t	tEnd;			//卡的截止时间
	float	fTotalUse;		//累计金额
	time_t	tLast;			//最后使用时间
	int		nUseCount;		//使用次数
	float	fBalance;		//余额
	int		nDel;			//删除标识 0-未删除，1-删除
};                          //用户数据
struct Node1
{
	sUser * data;          //用户数据
	Node1* next;           //链表的下一个节点
};                         //用户数据链表节点

struct user_log
{
	char    bName[18];      //卡号
	int     Kind;           //功能类型(0-注销，1-充值，2-退费)
	long    Re;             //操作前金额
	long    Af;             //操作后金额
	time_t  tEnd;           //结束时间
};                          //历史记录

struct Node2
{
	lUser * data;
	Node2* next;
};                          //历史记录链表节点

//类型定义
typedef struct user_st   sUser;   //用户数据
typedef struct user_log  lUser;   //历史记录
typedef struct Node1      Node1;  //用户数据节点
typedef struct Node2      Node2;  //历史记录节点

//函数原型
char* s_gets(char*, int);                      //字符串输入
void menu1(void);                              //初始菜单
void menu2(void);							   //上机菜单
void adduser(Node1* uhead, Node1* uend);	   //添加卡
void inquire(Node1* uhead);					   //查询卡
Node1* login(Node1* uhead, int* soon);		   //上机
void logout(Node1* on, int* soon,Node2* lend); //下机
void recharge(Node2* lend, Node1* on);		   //充值
void refund(Node2* lend, Node1* on);		   //退费
void dele(Node2* lend, Node1* on);			   //注销
void quit(Node1* on, int* soon);			   //退出程序

//外联函数
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

#endif
```

