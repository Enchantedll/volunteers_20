#ifndef card_service_h
#define card_service_h

#include "model.h"

card* initCardList(char*);     //��ʼ������Ϣ����
void releaseCardList(card*);       //�ͷſ���Ϣ����
void queryCard(card*);      //�ڿ���Ϣ�����У���ѯ������ͬ�Ŀ���Ϣ
void queryCards(card*);       //��������Ĺؼ��֣��ڿ���Ϣ�����У���ѯ�����а����ؼ��ֵĿ���Ϣ
card* checkCard(char*, char*, card*, int*);     //���ݿ��ź����룬�������в�ѯ����Ϣ������ȡ��ѯ���Ŀ���Ϣ�������е�λ��


#endif /* card_service_h */
