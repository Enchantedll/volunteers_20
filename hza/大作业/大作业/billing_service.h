#ifndef billing_service_h
#define billing_service_h


billing* initBillingList(char*);
void releaseBillingList(billing*);
int getbilling(billing*, char*, char*);
billing* checkBilling(char*, billing*, int*);

#endif /* billing_service_h */
