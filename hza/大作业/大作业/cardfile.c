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

	if ((fp = fopen(path, "ab")) == NULL) {   //以追加的模式打开文件，如果打开失败，则以只写的模式打开文件

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
	printf("卡号\t\t状态\t\t余额\t\t累计使用\t\t使用次数\t\t上次使用时间\n");
	timeToString(p->timeLast, lastTime);
	printf("%s\t\t%d\t\t%0.2f\t\t%.2f\t\t%d\t\t%s\n", p->number, p->status, p->balance, p->totalUse, p->useCount, lastTime);


}



int updateCard(card* p, char* path, int index)
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


int getCardCount(char* path)
{
	FILE* p = NULL;  // 文件指针
	int index = 0;   // 卡信息数量
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
	FILE* p = NULL;     // 文件结构体指针
	char number[18] = { 0 };       // 存放读取出的卡号
	if ((p = fopen(path, "rb")) == NULL) {
		return FALSE;

	}
	while (!feof(p)) {
		// 读取卡号，并比较卡号是否为当前查找的卡号
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
		printf("打开卡文件失败!\n");

	}
	while (!feof(p)) {

		if (fread(pCard, sizeof(card), 1, p) != 0) {

			showcard(pCard);

		}

	}

	fclose(p);
	free(pCard);


}
