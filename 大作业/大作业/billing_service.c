#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "model.h"
#include "global.h"
#include "tool.h"
#define EXAMPLE_MACRO_NAME
#pragma warning(disable:4996)
billing* initBillingList(char* path) {

	billing* head;
	head = (billing*)malloc(sizeof(billing));
	head->next = NULL;

	billing* p = head;
	while (p->next != NULL) {
		p = p->next;
	}

	FILE* fp = NULL;
	if ((fp = fopen(path, "rb")) == NULL) {

		return head;
	}

	while (!feof(fp)) {
		billing* pBilling = (billing*)malloc(sizeof(struct billing));
		if (fread(pBilling, sizeof(billing), 1, fp) != 0) {
			p->next = pBilling;
			p = p->next;
			p->next = NULL;
		}
	}
	fclose(fp);

	return head;

}


void releaseBillingList(billing* p) {        //�ͷżƷ���Ϣ����

	free(p);

}


int getbilling(billing* hp, char* path, char* num) {     //�ӼƷ���Ϣ�ļ���ȡ�Ʒ���Ϣ���浽�Ʒ�������


	FILE* p = NULL;
	if ((p = fopen(path, "rb")) == NULL) {
		return FALSE;

	}

	billing* pp = hp;
	while (pp->next != NULL) {
		pp = pp->next;
	}

	billing* pnew = (billing*)malloc(sizeof(struct billing));

	while (!feof(p)) {

		if (fread(pnew, sizeof(billing), 1, p) != 0)

			if (strcmp(pnew->number, num) == 0) {

				pp->next = pnew;
				pp = pp->next;
				pp->next = NULL;

				fclose(p);
				return TRUE;

			}

	}

	fclose(p);
	return FALSE;

}


billing* checkBilling(char* number, billing* hp, int* index) {     //�ڼƷ���Ϣ�����У���ѯ��Ӧ���ļƷ���Ϣ������ȡ�üƷ���Ϣ�������е�������

	billing *p = hp->next;
	while (p != NULL) {

		(*index)++;

		if (strcmp(p->number, number) == 0) {

			return p;
		}

		p = p->next;
	}

	return NULL;

}
