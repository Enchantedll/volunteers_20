#ifndef card_service_h
#define card_service_h

#include "model.h"

card* initCardList(char*);     //初始化卡信息链表
void releaseCardList(card*);       //释放卡信息链表
void queryCard(card*);      //在卡信息链表中，查询卡号相同的卡信息
void queryCards(card*);       //根据输入的关键字，在卡信息链表中，查询卡号中包含关键字的卡信息
card* checkCard(char*, char*, card*, int*);     //根据卡号和密码，在链表中查询卡信息，并获取查询到的卡信息在链表中的位置


#endif /* card_service_h */
