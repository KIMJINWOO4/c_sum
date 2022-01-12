#include "pch.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "timemg.h"
#include "structfileio.h"
#include "bookAdmin.h"


int booknum = 0;
char filename[BOOKNAME];

int main(int argc,char* argv[])
{
	FILE* fp = NULL;
	strcpy(filename,argv[1]);
	strcat(filename, ".bin");
	bookRec bookRecord[MAX];
	booknum = fileread(fp, bookRecord);
	while (1) {
		switch (menu()) {
		case 1:
			booknum = input(bookRecord);
			filewrite(fp, bookRecord);
			break;
		case 2:
			search(bookRecord);
			break;
		case 3:
			borrow(bookRecord);
			filewrite(fp, bookRecord);
			break;
		case 4:
			returning(bookRecord);
			filewrite(fp, bookRecord);
			break;
		case 5:
			booknum = remove(bookRecord);
			filewrite(fp, bookRecord);
			break;
		case 6:
			lprint(bookRecord);
			break;
		case 7:
			filewrite(fp, bookRecord);
			return 0;
		default:
			system("cls");
			break;
		}
	}
	return 0;
}


