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
typedef struct user_st
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
}sUser;                     //用户数据

typedef struct Node1
{
	sUser * data;          //用户数据
	struct Node1* next;    //链表的下一个节点
}Node1;                    //用户数据链表节点

typedef struct user_log
{
	char    bName[18];      //卡号
	int     Kind;           //功能类型(0-注销，1-充值，2-退费)
	float   Re;             //操作前金额
	float   Af;             //操作后金额
	time_t  tEnd;           //结束时间
}lUser;                     //历史记录

typedef struct Node2
{
	lUser * data;
	struct Node2* next;
}Node2;                          //历史记录链表节点

//类型定义
typedef struct user_st   sUser;   //用户数据
typedef struct user_log  lUser;   //历史记录
typedef struct Node1      Node1;  //用户数据节点
typedef struct Node2      Node2;  //历史记录节点

//函数原型
char* s_gets(char*, int);                      //字符串输入
void menu1(void);                              //初始菜单
void menu2(void);							   //上机菜单
void adduser(Node1**, Node1**);				   //添加卡
void inquire(Node1*);						   //查询卡
Node1* login(Node1*, int*);					   //上机
void logout(Node1*, int*, Node2*);			   //下机
void recharge(Node2**, Node1*);				   //充值
void refund(Node2**, Node1*);				   //退费
void dele(Node2**, Node1*);					   //注销
void quit(Node1*, int*);					   //退出程序

#endif
```

