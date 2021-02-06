#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "model.h"
#include "global.h"
#include "tool.h"
#include "cardfile.h"
#define EXAMPLE_MACRO_NAME
#pragma warning(disable:4996)

card* initCardList(char* path) {

	card *head;
	head = (card*)malloc(sizeof(struct card));
	head->next = NULL;

	card* p = head;
	while (p->next != NULL) {
		p = p->next;
	}

	FILE* fp = NULL;
	if ((fp = fopen(path, "rb")) == NULL) {

		return head;
	}

	while (!feof(fp)) {
		card* pCard = (card*)malloc(sizeof(struct card));
		if (fread(pCard, sizeof(card), 1, fp) != 0) {
			p->next = pCard;
			p = p->next;
			p->next = NULL;
		}
	}

	fclose(fp);

	return head;

}


void releaseCardList(card* p) {        //释放卡信息链表

	free(p);

}

void queryCard(card* head) {       //在卡信息链表中，查询卡号相同的卡信息

	printf("\n----------查询卡-----------\n");

	printf("请输入要查询的卡号(长度为1~18)：");
	char number[18] = { 0 };   // 输入的卡号
	scanf("%s", number);

	card *p = head->next;
	while (p != NULL) {

		if (strcmp(p->number, number) == 0) {
			showcard(p);
			return;
		}

		p = p->next;
	}

	printf("此卡不存在!\n");

}

void queryCards(card* head) {        //根据输入的关键字，在卡信息链表中，查询卡号中包含关键字的卡信息

	printf("\n----------查询卡-----------\n");

	printf("请输入要查询的关键词(长度为1~18):");
	char number[18] = { 0 };
	scanf("%s", number);


	card* p = head->next;
	while (p != NULL) {

		if (strstr(p->number, number) != NULL) {

			showcard(p);

		}

		p = p->next;

	}

}

card* checkCard(char* number, char* password, card* head, int* index) {      //根据卡号和密码，在链表中查询卡信息，并获取查询到的卡信息在链表中的位置

	card *p = head->next;
	while (p != NULL) {

		(*index)++;

		if ((strcmp(p->number, number) == 0) && (strcmp(p->password, password) == 0)) {

			return p;
		}

		p = p->next;
	}

	return NULL;

}
