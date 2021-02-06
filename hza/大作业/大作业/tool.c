#include <stdio.h>
#include <time.h>
#define EXAMPLE_MACRO_NAME
#pragma warning(disable:4996)


//��time_t��ʽʱ�䣬ת��Ϊ"��-��-�� ʱ-��"��ʽ�ַ���
void timeToString(time_t t, char* pBuf) {

	struct tm * timeinfo;    //����һ��tm���͵Ľṹ��ָ��

	timeinfo = localtime(&t);    //���tm�ṹ���ʱ��
	strftime(pBuf, 20, "%Y-%m-%d %H:%M", timeinfo);     //��ʱ��ת��Ϊ"��-��-�� ʱ-��"��ʽ�ַ���

}

//��"��-��-�� ʱ-��"��ʽ�ַ�����ת��Ϊtime_t��ʽʱ��
time_t stringToTime(char* pTime) {

	struct tm tm1;     //����tm���͵Ľṹ��
	time_t time1;     //����ʱ�����

	sscanf(pTime, "%d-%d-%d %d:%d", &tm1.tm_year, &tm1.tm_mon, &tm1.tm_mday, &tm1.tm_hour, &tm1.tm_min);      //���ַ�����ʽ��hʱ�䱣�浽tm1������

	tm1.tm_year -= 1900;     //��ݴ�1900�꿪ʼ
	tm1.tm_mon -= 1;      //�·�Ϊ1~12
	tm1.tm_sec = 0;
	tm1.tm_isdst = -1;

	time1 = mktime(&tm1);      //��struct tm���ͱ�����ֵת��Ϊtime_t���ͱ�����ֵ

	return time1;     //����ת����ĸ�ʽʱ��

}
