#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "model.h"
#include "global.h"
#include "tool.h"
#include "cardfile.h"
#include "card_service.h"
#include "billing_file.h"
#include "billing_service.h"

#define CARDPATH "‎⁨‎⁨card.txt"
#define BILLINGPATH "billing.txt"
#define INFORPATH "information.txt"
#define EXAMPLE_MACRO_NAME
#pragma warning(disable:4996)

void add(card* head)
{

	card * pNew = (card*)malloc(sizeof(card));

	printf("\n----------添加卡-----------\n");

	printf("请输入卡号(长度为1~18)：");
	char number[18] = { 0 };   // 输入的卡号
	scanf("%s", number);

	if (isExsit(number, CARDPATH) == TRUE) {

		printf("此卡已存在!添加卡失败!\n");
		return;

	}

	strcpy(pNew->number, number);

	printf("请输入密码(长度为1~8)：");
	char password[8] = { 0 };    // 输入的密码
	scanf("%s", password);
	strcpy(pNew->password, password);

	printf("请输入开卡金额(RMB)：");
	float m;
	scanf("%f", &m);
	pNew->balance = m;


	pNew->totalUse = pNew->balance;    // 添加卡时，累计金额等于开卡金额
	pNew->del = 0;                     // 删除标识
	pNew->status = 0;                  // 卡状态
	pNew->useCount = 0;                // 使用次数
	pNew->timeEnd = pNew->timeLast = pNew->timeStart = time(NULL);
	// 开卡时间，截止时间，最后使用时间都默认为当前时间。
	// 根据开卡时间，计算截止时间，每张卡的有效期为一年

	struct tm *endtime;     // 截止时间
	struct tm *starttime;   // 开卡时间

	starttime = localtime(&(pNew->timeStart));
	endtime = localtime(&(pNew->timeEnd));
	endtime->tm_year = starttime->tm_year + 1;
	pNew->timeEnd = mktime(endtime);      //截止时间为开卡时间的后一年整

	if (savecard(pNew, CARDPATH) == FALSE) {
		printf("添加卡失败!\n");
	}
	else {
		printf("添加卡成功!\n\n");
	}


	printf("\n------添加的卡信息如下------\n");
	printf("卡号\t\t密码\t\t状态\t\t开卡金额\n");
	printf("%s\t\t%s\t\t0\t\t%.2f\n", pNew->number, pNew->password, pNew->balance);

	printf("\n");


	card *p = head;
	while (p->next != NULL) {
		p = p->next;
	}

	p->next = pNew;
	p = p->next;
	p->next = NULL;


}


void query(card* head)
{

	printf("\n----------查询卡-----------\n");

	printf("请选择查询的方式：\n");
	printf("1.精确查询\n");
	printf("2.模糊查询\n");
	printf("请输入选择(1或2)：");
	int item;
	scanf("%d", &item);

	if (item == 1) {
		queryCard(head);
	}
	else if (item == 2) {
		queryCards(head);
	}
	else {
		printf("输入错误!\n");
	}


}



void logon(card* head, billing* pb)
{

	printf("\n----------上机-----------\n");

	card* p = NULL;
	int index = 0;     //卡信息在链表中的索引

	printf("请输入卡号<长度为1~18>:");
	char number[18];
	scanf("%s", number);
	printf("请输入密码(长度为1~8)：");
	char password[8];    // 输入的密码
	scanf("%s", password);

	//根据卡号和密码，从链表中获取卡信息和卡信息在链表中的索引
	p = checkCard(number, password, head, &index);

	//如果卡信息为空，表示没有该卡信息，上机失败
	if (p == NULL) {
		printf("该卡信息不存在!上机失败!\n");
		return;
	}
	//如果卡状态不为0，表示该卡不能上机
	if (p->status != 0) {
		printf("该卡不能上机!上机失败!\n");
		return;
	}
	//如果卡余额为0，不能上机
	if (p->balance == 0) {
		printf("你个穷鬼还想上网???充钱去吧!!!\n");
		return;
	}

	//如果可以上机，更新卡信息
	p->status = 1;      //状态为正在使用
	p->useCount++;     //使用次数加1
	p->timeLast = time(NULL);      //更新最后使用时间为当前时间

	//更新文件中的卡信息
	if (updateCard(p, CARDPATH, index) == FALSE) {
		printf("无法更新!\n");
		return;
	}

	billing* pnew;
	pnew = (billing*)malloc(sizeof(struct billing));
	strcpy(pnew->number, p->number);
	pnew->timeStart = time(NULL);
	pnew->timeEnd = 0;
	pnew->amount = 0;
	pnew->status = 0;
	pnew->del = 0;

	if (savebilling(pnew, BILLINGPATH) == FALSE) {
		printf("计费信息添加失败!\n");
		return;
	}

	billing* pp = pb;
	while (pp->next != NULL) {
		pp = pp->next;
	}

	pp->next = pnew;
	pp = pp->next;
	pp->next = NULL;

	printf("上机成功!\n");


}

void settle(card* head, billing* hp)
{
	printf("\n----------下机-----------\n");

	card* p = NULL;
	int index = 0;

	printf("请输入卡号<长度为1~18>:");
	char number[18];
	scanf("%s", number);
	printf("请输入密码(长度为1~8)：");
	char password[8];
	scanf("%s", password);

	//根据卡号和密码，从链表中获取卡信息和卡信息在链表中的索引
	p = checkCard(number, password, head, &index);


	//如果卡信息为空，表示没有该卡信息，下机失败
	if (p == NULL) {
		printf("该卡信息不存在!下机失败!\n");
		return;
	}
	//如果卡状态不为1，表示该卡不能下机
	if (p->status != 1) {
		printf("该卡不能下机!下机失败!\n");
		return;
	}

	//如果可以下机，更新卡信息
	p->status = 0;      //状态为未上机
	p->useCount++;     //使用次数加1
	p->timeLast = time(NULL);      //更新最后使用时间为当前时间

	int index2 = 0;
	billing* bp = NULL;
	bp = checkBilling(number, hp, &index2);

	//如果一分钟一元
	float every = 1;

	time_t now;
	time_t starttime;
	time(&now);
	starttime = bp->timeStart;
	double c;
	int minute = 0;
	c = difftime(now, starttime);
	minute = c / 60;

	p->balance = p->balance - every * minute;
	p->totalUse += every * minute;

	bp->amount = every * minute;
	bp->timeStart = p->timeStart;
	bp->timeEnd = time(NULL);

	if (savebilling(bp, INFORPATH) == FALSE) {
		printf("添加卡信息失败!\n");
		return;
	}


	//更新卡文件中的卡信息
	if (updateCard(p, CARDPATH, index) == FALSE) {
		printf("更新卡信息失败!下机失败!\n");
		return;
	}
	//更新计费文件中计费信息
	if (updateBilling(bp, BILLINGPATH, index) == FALSE) {
		printf("更新计费信息失败!下机失败!\n");
		return;
	}

	printf("应付金额:%.2f\n", every * minute);
	printf("卡中剩余余额:%.2f\n", p->balance);
	printf("下机成功!\n");



	return;
}

void addMoney(card* head)
{
	printf("\n----------充值-----------\n");

	printf("请输入卡号<长度为1~18>:");
	char number[18];
	scanf("%s", number);

	printf("请输入充值金额:");
	float money;
	scanf("%f", &money);


	FILE * fp = NULL;

	if ((fp = fopen(CARDPATH, "rb")) == NULL) {
		printf("卡文件打开失败!\n");
	}


	card *q = head->next;
	while (q != NULL) {

		if (strcmp(q->number, number) == 0) {
			q->balance += money;
			q->totalUse += money;
		}

		q = q->next;
	}


	int index = 0;
	card* p = (card*)malloc(sizeof(card));
	p->next = NULL;
	while (!feof(fp)) {

		index++;

		if (fread(p, sizeof(card), 1, fp) != 0) {

			if (strcmp(p->number, number) == 0) {

				break;

			}
		}
	}

	p->balance += money;
	p->totalUse += money;

	if (updateCard(p, CARDPATH, index) == TRUE) {
		printf("充值成功!\n");
	}

	free(p);
	fclose(fp);


}

void refundMoney(card* head)
{
	printf("\n----------退费-----------\n");
	printf("请输入卡号<长度为1~18>:");
	char number[18];
	scanf("%s", number);

	printf("请输入要退的金额:");
	float money;
	scanf("%f", &money);


	card *q = head->next;
	while (q != NULL) {

		if (strcmp(q->number, number) == 0) {
			if (q->balance < money) {
				printf("余额不足!\n");
				printf("请充值!\n");
				return;
			}
			else {
				q->balance -= money;
				q->timeLast = time(NULL);
			}
		}

		q = q->next;
	}



	FILE * fp = NULL;

	if ((fp = fopen(CARDPATH, "rb")) == NULL) {
		printf("卡文件打开失败!\n");
	}

	int index = 0;
	card* p = (card*)malloc(sizeof(card));
	while (!feof(fp)) {

		index++;

		if (fread(p, sizeof(card), 1, fp) != 0) {

			if (strcmp(p->number, number) == 0) {

				break;

			}
		}
	}


	p->balance -= money;
	if (updateCard(p, CARDPATH, index) == TRUE) {
		printf("退费成功!\n");
	}

	free(p);
	fclose(fp);
}

void count(card* head)
{
	printf("\n----------查询统计菜单-----------\n");
	printf("1.总卡数\n");
	printf("2.所有卡的信息\n");
	printf("3.卡总充值金额\n");
	printf("4.总营业额\n");
	printf("5.查询消费记录\n");
	printf("-------------------------\n");
	printf("请输入1-4数字编号:");
	int num;
	scanf("%d", &num);
	switch (num) {
	case 1: {
		printf("一共有%d张卡\n", getCardCount(CARDPATH));
		break;
	}
	case 2: {
		showallcards(CARDPATH);
		break;
	}
	case 3: {
		card* p = head->next;
		float sum = 0;
		while (p->next != NULL) {
			sum += p->totalUse;
			p = p->next;
		}
		printf("所有卡的充值金额为%f\n", sum);
		break;
	}
	case 4: {
		card* p = head->next;
		float sum = 0, del = 0, re = 0;
		while (p->next != NULL) {
			sum += p->totalUse;
			del += p->balance;
			p = p->next;
		}
		re = sum - del;
		printf("总营业额为%f\n", re);
		break;
	}
	case 5: {
		printf("请输入要查询的卡号:");
		char name[18];
		scanf("%s", name);
		showinformation(INFORPATH, name);
		break;

	}
	default: {
		printf("输入的数字错误!\n");
		break;
	}

	}


}

void annul(card* head)
{

	printf("\n----------注销卡-----------\n");
	printf("请输入卡号<长度为1~18>:");
	char number[18];
	scanf("%s", number);

	card *q = head->next;
	while (q != NULL) {

		if (strcmp(q->number, number) == 0) {
			q->status = 2;
		}

		q = q->next;
	}


	FILE * fp = NULL;

	if ((fp = fopen(CARDPATH, "rb")) == NULL) {
		printf("卡文件打开失败!\n");
	}

	int index = 0;
	card* p = (card*)malloc(sizeof(card));
	p->next = NULL;
	while (!feof(fp)) {

		index++;

		if (fread(p, sizeof(card), 1, fp) != 0) {

			if (strcmp(p->number, number) == 0) {

				p->status = 2;
				printf("剩余金额：%f，退费金额：%f\n", p->balance, p->balance);
				printf("退费成功!\n");

				if (updateCard(p, CARDPATH, index) == TRUE) {
					printf("注销成功!\n");
				}

				free(p);
				fclose(fp);

				return;

			}
		}
	}

	printf("此卡不存在\n!");

	free(p);
	fclose(fp);


}

void exitApp()
{

	printf("\n----------退出系统-----------\n");
	printf("谢谢使用!\n");
	exit(0);

}
