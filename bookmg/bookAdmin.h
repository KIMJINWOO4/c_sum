#ifndef bookAdmin_h
#define bookAdmin_h
int menu(void);
int input(bookRec* p);
void search(bookRec* p);
void borrow(bookRec* p);
void returning(bookRec* p);
int remove(bookRec* p);
void lprint(bookRec* p);
void disphead(void);
#endif