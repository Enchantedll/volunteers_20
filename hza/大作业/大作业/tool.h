#ifndef tool_h
#define tool_h


void timeToString(time_t t, char * pBuf);//将time_t格式时间，转换为"年-月-日 时-分"格式字符串
time_t stringToTime(char* pTime);//将"年-月-日 时-分"格式字符串，转换为time_t格式时间

#endif /* tool_h */
