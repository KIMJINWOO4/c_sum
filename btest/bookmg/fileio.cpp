#include "pch.h"
#include <stdio.h>
#include <string.h>
#include "structfileio.h"
extern int booknum;
extern char filename[BOOKNAME];
int fileread(FILE* fp,bookRec* p) {
	fp = fopen(filename, "rb");
	if (fp != NULL) {
		booknum = fread(p, sizeof(bookRec), MAX, fp);
		fclose(fp);
		return booknum;
	}
	else {
		printf("%s파일이 존재하지 않습니다. 파일을 생성합니다.\n", filename);
		fp = fopen(filename, "wb");
		fclose(fp);
		return 0;
	}
}
void filewrite(FILE* fp, bookRec* p) {
	fp = fopen(filename, "wb");
	fwrite(p, sizeof(bookRec), booknum, fp);
	fclose(fp);
}

