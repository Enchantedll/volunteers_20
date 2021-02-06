#ifndef service_h
#define service_h

#include "model.h"

void add(card*);
void query(card*);
void logon(card*, billing*);
void settle(card*, billing*);
void addMoney(card*);
void refundMoney(card*);
void count(card*);
void annul(card*);
void exitApp(void);


#endif /* service_h */
