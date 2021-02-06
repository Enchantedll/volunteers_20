#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "model.h"
#include "global.h"
#include "tool.h"
#define EXAMPLE_MACRO_NAME
#pragma warning(disable:4996)

int savebilling(billing* p, char *path) {    //���Ʒ���Ϣ���浽�ļ���

	FILE *fp = NULL;

	if ((fp = fopen(path, "ab")) == NULL) {   //��׷�ӵ�ģʽ���ļ��������ʧ�ܣ�����ֻд��ģʽ���ļ�

		if ((fp = fopen(path, "wb")) == NULL) {

			return FALSE;
		}

	}

	fwrite(p, sizeof(billing), 1, fp);

	fclose(fp);

	return TRUE;

}


void showbilling(billing* bp, char* number, char* path) {     //���ļ��ж�ȡ�Ʒ���Ϣ

	char startTime[50];

	FILE* p = NULL;  // �ļ�ָ��
	billing* pb = (billing*)malloc(sizeof(billing));
	if ((p = fopen(path, "rb")) == NULL) {
		printf("���ļ�ʧ��!\n");
		return;

	}
	while (!feof(p)) {

		if (fread(pb, sizeof(card), 1, p) != 0)
			if (strcmp(pb->number, number) == 0) {

				printf("����\t\t״̬\t\t����״̬\t\tɾ����ʶ\t\t�ϻ�ʱ��\n");
				timeToString(pb->timeStart, startTime);

				printf("%s\t\t%d\t\t%d\t\t%d\t\t%s\n", pb->number, pb->status, pb->status, pb->del, startTime);

			}


	}

	fclose(p);
	free(pb);

}


int getbillingnum(billing* hp, char* path) {     //���ļ��л�ȡ�Ʒ���Ϣ������

	FILE* p = NULL;  // �ļ�ָ��
	int index = 0;
	card* pCard = (card*)malloc(sizeof(card));
	if ((p = fopen(path, "rb")) == NULL) {
		return 0;

	}

	while (!feof(p)) {

		if (fread(pCard, sizeof(card), 1, p) != 0)
			index++;

	}

	fclose(p);
	free(pCard);

	return index;


}


int updateBilling(billing* p, char* path, int index)
{

	FILE* fp = NULL;    // �ļ�ָ��
	int line = 0;      // �ļ�����Ϣ��
	long position = 0;    // �ļ�λ�ñ��
	card bBuf;

	if ((fp = fopen(path, "rb+")) == NULL) {
		return FALSE;
	}

	while ((!feof(fp)) && (line < index - 1)) {

		if (fread(&bBuf, sizeof(card), 1, fp) != 0)
		{      // ��ȡ�ļ���ʶλ��

			position = ftell(fp);
			line++;

		}
	}

	fseek(fp, position, 0);
	fwrite(p, sizeof(card), 1, fp);
	fclose(fp);

	return TRUE;

}

void showinformation(char* path, char* name) {

	FILE* p = NULL;

	billing* bp = (billing*)malloc(sizeof(struct billing));

	if ((p = fopen(path, "rb")) == NULL) {
		printf("�򿪼Ʒ���Ϣ�ļ�ʧ��!\n");
	}

	char startTime[50];
	char endTime[50];

	while (!feof(p)) {

		if (fread(bp, sizeof(billing), 1, p) != 0) {

			if (strcmp(bp->number, name) == 0) {
				printf("����״̬\t\t���ѽ��\t\t�ϻ�ʱ��\t\t�»�ʱ��\t\tɾ����ʶ\n");
				timeToString(bp->timeStart, startTime);
				timeToString(bp->timeEnd, endTime);
				printf("%d\t\t\%f\t\t%s\t\t%s\t\t%d\n", bp->status, bp->amount, startTime, endTime, bp->del);
			}

		}

	}

	fclose(p);
	free(bp);

}
