#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "model.h"
#include "global.h"
#include "tool.h"
#define EXAMPLE_MACRO_NAME
#pragma warning(disable:4996)

int savebilling(billing* p, char *path) {    //将计费信息保存到文件中

	FILE *fp = NULL;

	if ((fp = fopen(path, "ab")) == NULL) {   //以追加的模式打开文件，如果打开失败，则以只写的模式打开文件

		if ((fp = fopen(path, "wb")) == NULL) {

			return FALSE;
		}

	}

	fwrite(p, sizeof(billing), 1, fp);

	fclose(fp);

	return TRUE;

}


void showbilling(billing* bp, char* number, char* path) {     //从文件中读取计费信息

	char startTime[50];

	FILE* p = NULL;  // 文件指针
	billing* pb = (billing*)malloc(sizeof(billing));
	if ((p = fopen(path, "rb")) == NULL) {
		printf("打开文件失败!\n");
		return;

	}
	while (!feof(p)) {

		if (fread(pb, sizeof(card), 1, p) != 0)
			if (strcmp(pb->number, number) == 0) {

				printf("卡号\t\t状态\t\t消费状态\t\t删除标识\t\t上机时间\n");
				timeToString(pb->timeStart, startTime);

				printf("%s\t\t%d\t\t%d\t\t%d\t\t%s\n", pb->number, pb->status, pb->status, pb->del, startTime);

			}


	}

	fclose(p);
	free(pb);

}


int getbillingnum(billing* hp, char* path) {     //从文件中获取计费信息的数量

	FILE* p = NULL;  // 文件指针
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

	FILE* fp = NULL;    // 文件指针
	int line = 0;      // 文件卡信息数
	long position = 0;    // 文件位置标记
	card bBuf;

	if ((fp = fopen(path, "rb+")) == NULL) {
		return FALSE;
	}

	while ((!feof(fp)) && (line < index - 1)) {

		if (fread(&bBuf, sizeof(card), 1, fp) != 0)
		{      // 获取文件标识位置

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
		printf("打开计费信息文件失败!\n");
	}

	char startTime[50];
	char endTime[50];

	while (!feof(p)) {

		if (fread(bp, sizeof(billing), 1, p) != 0) {

			if (strcmp(bp->number, name) == 0) {
				printf("消费状态\t\t消费金额\t\t上机时间\t\t下机时间\t\t删除标识\n");
				timeToString(bp->timeStart, startTime);
				timeToString(bp->timeEnd, endTime);
				printf("%d\t\t\%f\t\t%s\t\t%s\t\t%d\n", bp->status, bp->amount, startTime, endTime, bp->del);
			}

		}

	}

	fclose(p);
	free(bp);

}
