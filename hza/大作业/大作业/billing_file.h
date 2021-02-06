#ifndef billing_file_h
#define billing_file_h

int savebilling(billing*, char*);
void showbilling(billing*);
int getbillingnum(billing*, char*);
int updateBilling(billing*, char*, int);
void showinformation(char*, char*);

#endif /* billing_file_h */
