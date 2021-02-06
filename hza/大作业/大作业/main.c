#include <stdio.h>
#include <stdlib.h>
#include "model.h"
#include "menu.h"
#include "service.h"
#include "card_service.h"
#include "cardfile.h"
#include "billing_service.h"
#include "billing_file.h"


#define CARDPATH "‎⁨‎⁨card.txt"
#define BILLINGPATH "billing.txt"
#define MONEYPATH "money.txt"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int main() {

	card* head = initCardList(CARDPATH);
	billing* hb = initBillingList(BILLINGPATH);

	int nSelection = -1;
	printf("欢迎进入计费管理系统!\n");
	printf("\n");

	do {

		outputMenu();
		nSelection = -1;
		scanf("%d", &nSelection);

		switch (nSelection) {
		case 1:
		{
			add(head);  //添加卡
			break;

		}
		case 2:
		{
			query(head);   //查询卡
			break;

		}
		case 3:
		{
			logon(head, hb);    //上机
			break;

		}
		case 4:
		{
			settle(head, hb);    //下机
			break;

		}
		case 5:
		{
			addMoney(head);   //充值
			break;

		}
		case 6:
		{
			refundMoney(head);     //退费
			break;

		}
		case 7:
		{
			count(head);       //查询统计
			break;

		}
		case 8:
		{
			annul(head);       //注销卡
			break;

		}
		case 0:
		{
			exitApp();     //退出
			break;

		}

		default:
		{
			printf("输入的菜单编号错误!\n");
			break;
		}
		}
		printf("\n");

	} while (nSelection != 0);

	return 0;
}
