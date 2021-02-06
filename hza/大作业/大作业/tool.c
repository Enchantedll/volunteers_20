#include <stdio.h>
#include <time.h>
#define EXAMPLE_MACRO_NAME
#pragma warning(disable:4996)


//将time_t格式时间，转换为"年-月-日 时-分"格式字符串
void timeToString(time_t t, char* pBuf) {

	struct tm * timeinfo;    //定义一个tm类型的结构体指针

	timeinfo = localtime(&t);    //获得tm结构体的时间
	strftime(pBuf, 20, "%Y-%m-%d %H:%M", timeinfo);     //将时间转换为"年-月-日 时-分"格式字符串

}

//将"年-月-日 时-分"格式字符串，转换为time_t格式时间
time_t stringToTime(char* pTime) {

	struct tm tm1;     //定义tm类型的结构体
	time_t time1;     //定义时间变量

	sscanf(pTime, "%d-%d-%d %d:%d", &tm1.tm_year, &tm1.tm_mon, &tm1.tm_mday, &tm1.tm_hour, &tm1.tm_min);      //将字符串格式的h时间保存到tm1变量中

	tm1.tm_year -= 1900;     //年份从1900年开始
	tm1.tm_mon -= 1;      //月份为1~12
	tm1.tm_sec = 0;
	tm1.tm_isdst = -1;

	time1 = mktime(&tm1);      //将struct tm类型变量的值转化为time_t类型变量的值

	return time1;     //返回转换后的格式时间

}
