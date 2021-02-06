#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "model.h"
#include "global.h"
#include "tool.h"
#define EXAMPLE_MACRO_NAME
#pragma warning(disable:4996)


int savecard(card *p, char *path) {


	FILE *fp = NULL;

	if ((fp = fopen(path, "ab")) == NULL) {   //��׷�ӵ�ģʽ���ļ��������ʧ�ܣ�����ֻд��ģʽ���ļ�

		if ((fp = fopen(path, "wb")) == NULL) {

			return FALSE;
		}

	}


	fwrite(p, sizeof(card), 1, fp);

	fclose(fp);

	return TRUE;

}




void showcard(card *p) {


	char lastTime[50];
	printf("����\t\t״̬\t\t���\t\t�ۼ�ʹ��\t\tʹ�ô���\t\t�ϴ�ʹ��ʱ��\n");
	timeToString(p->timeLast, lastTime);
	printf("%s\t\t%d\t\t%0.2f\t\t%.2f\t\t%d\t\t%s\n", p->number, p->status, p->balance, p->totalUse, p->useCount, lastTime);


}



int updateCard(card* p, char* path, int index)
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


int getCardCount(char* path)
{
	FILE* p = NULL;  // �ļ�ָ��
	int index = 0;   // ����Ϣ����
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





int isExsit(char* num, char* path)
{
	FILE* p = NULL;     // �ļ��ṹ��ָ��
	char number[18] = { 0 };       // ��Ŷ�ȡ���Ŀ���
	if ((p = fopen(path, "rb")) == NULL) {
		return FALSE;

	}
	while (!feof(p)) {
		// ��ȡ���ţ����ȽϿ����Ƿ�Ϊ��ǰ���ҵĿ���
		if (fread(number, sizeof(number), 1, p) != 0) {

			if (strcmp(number, num) == 0) {

				fclose(p);
				return TRUE;

			}
			else {
				fseek(p, sizeof(card) - sizeof(number), SEEK_CUR);
			}
		}
	}

	fclose(p);
	return FALSE;

}


void showallcards(char* path) {

	FILE* p = NULL;

	card* pCard = (card*)malloc(sizeof(struct card));
	if ((p = fopen(path, "rb")) == NULL) {
		printf("�򿪿��ļ�ʧ��!\n");

	}
	while (!feof(p)) {

		if (fread(pCard, sizeof(card), 1, p) != 0) {

			showcard(pCard);

		}

	}

	fclose(p);
	free(pCard);


}
