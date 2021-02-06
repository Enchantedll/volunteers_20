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


void releaseCardList(card* p) {        //�ͷſ���Ϣ����

	free(p);

}

void queryCard(card* head) {       //�ڿ���Ϣ�����У���ѯ������ͬ�Ŀ���Ϣ

	printf("\n----------��ѯ��-----------\n");

	printf("������Ҫ��ѯ�Ŀ���(����Ϊ1~18)��");
	char number[18] = { 0 };   // ����Ŀ���
	scanf("%s", number);

	card *p = head->next;
	while (p != NULL) {

		if (strcmp(p->number, number) == 0) {
			showcard(p);
			return;
		}

		p = p->next;
	}

	printf("�˿�������!\n");

}

void queryCards(card* head) {        //��������Ĺؼ��֣��ڿ���Ϣ�����У���ѯ�����а����ؼ��ֵĿ���Ϣ

	printf("\n----------��ѯ��-----------\n");

	printf("������Ҫ��ѯ�Ĺؼ���(����Ϊ1~18):");
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

card* checkCard(char* number, char* password, card* head, int* index) {      //���ݿ��ź����룬�������в�ѯ����Ϣ������ȡ��ѯ���Ŀ���Ϣ�������е�λ��

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
