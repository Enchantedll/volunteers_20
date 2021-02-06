#ifndef cardfile_h
#define cardfile_h

int savecard(card *, char *);

void inputCard(card *);

void showcard(card *);

int updateCard(card*, char*, int);

int getCardCount(char*);

int isExsit(char*, char*);

void showallcards(char*);

#endif /* cardfile_h */
