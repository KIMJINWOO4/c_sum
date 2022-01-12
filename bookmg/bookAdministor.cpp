#include "pch.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "timemg.h"
#include "structfileio.h"
#include "bookAdmin.h"

#define OR ||
#define IS ==

#define solvefee(x) ((x/10)*100)

extern int booknum;
int menu(void) {
	int i;
	printf("도서 관리 프로그램\n\n");
	printf("1. 도서 입력\n");
	printf("2. 도서 검색 (코드,도서명 혹은 저자)\n");
	printf("3. 도서 대출\n");
	printf("4. 도서 반납\n");
	printf("5. 도서 삭제\n");
	printf("6. 도서 리스트\n");
	printf("7. 종료 \n");
	scanf("%d", &i);
	return i;
}
int input(bookRec* p) {
	char i, j = 'n';
	unsigned code;
	while (1) {
		printf("도서를 입력하시오.\n");
		printf("도서코드 구분 : ");
		scanf("%u", &code);
		p[booknum].bcode.cd.kubun = code;
		printf("도서코드 타입 : ");
		scanf("%u", &code);
		p[booknum].bcode.cd.type = code;
		printf("도서코드 번호 : ");
		scanf("%u", &code);
		p[booknum].bcode.cd.number = code;
		p[booknum].bcode.cd.null = NULL;
		printf("도서명 : ");
		scanf("%s", p[booknum].bname);
		printf("저자명 : ");
		scanf("%s", p[booknum].bwriter);
		printf("도서가격 : ");
		scanf("%d", &p[booknum].bprice);
		p[booknum].brPart.borrow = OFF;
		printf("[%08X %s %s %d원] - 확인? (Y/N)\n", p[booknum].bcode.code, p[booknum].bname, p[booknum].bwriter, p[booknum].bprice);
		i = _getch();
		if (i IS 'Y' OR i IS 'y') {
			booknum++;
			printf("도서를 더 입력하시겠습니까 ?(Y/N)\n");
			j = _getch();
			if (j IS 'Y' OR j IS 'y') {
				continue;
				system("cls");
			}
			else {
				system("cls");
				break;
			}
		}
		else continue;
	}
	system("cls");
	return booknum;
}
void search(bookRec* p) {
	int i, b = 0, k;
	unsigned j;
	char a = 'n', temp[BOOKNAME];
	printf("키워드 선택\n");
	printf("코드(1)\n");
	printf("도서명(2)\n");
	printf("저자이름(3)\n");
	scanf("%d", &i);
	if (i IS 1) {
		printf("검색할 도서코드를 입력하세요.\n");
		scanf("%x", &j);
		for (k = 0; k < booknum; k++) {
			if (j IS p[k].bcode.code) {
				if (p[k].brPart.borrow IS ON)
					printf("[%08X %s %s %d 대출 중]가 맞습니까?(Y/N)\n", p[k].bcode.code, p[k].bname, p[k].bwriter, p[k].bprice);
				else
					printf("[%08X %s %s %d 대출 가능]가 맞습니까?(Y/N)\n", p[k].bcode.code, p[k].bname, p[k].bwriter, p[k].bprice);
				a = _getch();
			}
			if (a IS 'Y' OR a IS 'y') {
				b = 1;
				break;
			}
			else continue;
		}
	}
	else if (i IS 2) {
		printf("검색할 도서명을 입력하세요.\n");
		scanf("%s", temp);
		for (k = 0; k < booknum; k++) {
			if (strcmp(temp, p[k].bname) IS 0) {
				if (p[k].brPart.borrow IS ON)
					printf("[%08X %s %s %d 대출 중]가 맞습니까?(Y/N)\n", p[k].bcode.code, p[k].bname, p[k].bwriter, p[k].bprice);
				else
					printf("[%08X %s %s %d 대출 가능]가 맞습니까?(Y/N)\n", p[k].bcode.code, p[k].bname, p[k].bwriter, p[k].bprice);
				a = _getch();
			}
			if (a IS 'Y' OR a IS 'y') {
				b = 1;
				break;
			}
			else continue;
		}
	}
	else if (i IS 3) {
		printf("검색할 저자이름을 입력하세요.\n");
		scanf("%s", temp);
		for (k = 0; k < booknum; k++) {
			if (strcmp(temp, p[k].bwriter) IS 0) {
				if (p[k].brPart.borrow IS ON)
					printf("[%08X %s %s %d 대출 중]가 맞습니까?(Y/N)\n", p[k].bcode.code, p[k].bname, p[k].bwriter, p[k].bprice);
				else
					printf("[%08X %s %s %d 대출 가능]가 맞습니까?(Y/N)\n", p[k].bcode.code, p[k].bname, p[k].bwriter, p[k].bprice);
				a = _getch();
			}
			if (a IS 'Y' OR a IS 'y') {
				b = 1;
				break;
			}
			else continue;
		}
	}
	if (b IS 1) {
		if (p[k].brPart.borrow IS ON)
			printf("\n최종 검색 결과는 [%08X %s %s %d 대출 중]\n", p[k].bcode.code, p[k].bname, p[k].bwriter, p[k].bprice);
		else
			printf("\n최종 검색 결과는 [%08X %s %s %d 대출 가능]\n", p[k].bcode.code, p[k].bname, p[k].bwriter, p[k].bprice);
		system("pause");
	}
	else {
		printf("검색되지 않은 키워드입니다.\n메뉴로 돌아갑니다.\n");
		system("pause");
	}
	system("cls");
}
void borrow(bookRec* p) {
	char bname[BOOKNAME];
	int i, flag = 0;
	time_t tm;
	printf("대출하실 도서 명을 입력하세요.\n");
	scanf("%s", bname);
	for (i = 0; i < booknum; i++) {
		if (strcmp(bname, p[i].bname) IS 0) {
			if (p[i].brPart.borrow IS OFF) {
				printf("%s 책 대출 가능합니다.\n대출자 이름을 입력하세요.\n", bname);
				scanf("%s", p[i].brPart.bookBorrower);
				p[i].brPart.borrow = ON;
				tm = time(NULL);
				p[i].brPart.dateOfBorrowing = tm;
				printf("도서 대출 날짜 :");
				timeMgr(tm, 0);
				printf("\n");
				system("pause");
				flag = 1;
				break;
			}
			else {
				printf("대출 불가능합니다.\n메뉴로 돌아갑니다.\n");
				system("pause");
				flag = 1;
				break;
			}
		}
	}
	if (!flag) {
		printf("존재하지 않는 도서명입니다.\n");
		printf("메뉴로 돌아갑니다.\n");
		system("pause");
	}
	system("cls");
}
void returning(bookRec* p) {
	char rname[WRITER], c = 'n';
	time_t tm, term;
	int j = 0, fee = 0;
	while (1) {
		printf("반납하실 대출자의 이름을 입력해주세요.\n");
		scanf("%s", rname);
		for (int i = 0; i < booknum; i++) {
			if (strcmp(rname, p[i].brPart.bookBorrower) IS 0) {
				tm = time(NULL);
				p[i].brPart.dateOfReturning = tm;
				printf("도서 반환 날짜 : ");
				timeMgr(tm, 0);
				printf("\n");
				term = tm - p[i].brPart.dateOfBorrowing;
				printf("대출 기간 : ");
				timeMgr(term, 1);
				printf("\n");
				fee = solvefee(int(term));
				printf("%s님 대출요금은 : %d원 입니다.\n", rname, fee);
				strcpy(p[i].brPart.bookBorrower, "NULL");
				p[i].brPart.borrow = OFF;
				j++;
				break;
			}
		}
		if (j IS 0) {
			printf("존재하지 않는 대출자명입니다.\n");
			printf("다시 입력하시겠습니까?(Y/N)\n");
			c = _getch();
			if (c IS 'Y' OR c IS 'y')
				continue;
			else
				break;
		}
		else
			break;
	}
	system("pause");
	system("cls");
}
int remove(bookRec* p) {
	char bname[BOOKNAME], j = 'n';
	int k = 0;
	while (1) {
		printf("삭제할 도서의 이름을 입력해주세요 : ");
		scanf("%s", bname);
		for (int i = 0; i < booknum; i++) {
			if (strcmp(bname, p[i].bname) IS 0) {
				strcpy(p[i].bname, p[booknum - 1].bname);
				booknum--;
				k = 1;
				break;
			}
		}
		if (k IS 0) {
			printf("일치하는 도서명이 없습니다.\n다시 입력하시겠습니까?(Y/N)");
			j = _getch();
			if (j IS 'Y' OR j IS 'y')
				continue;
			else
				break;
		}
		else {
			printf("삭제가 완료되었습니다.\n");
			system("pause");
			break;
		}
	}
	system("cls");
	return booknum;
}
void disphead(void) {
	printf("도서코드\t도서명\t저자명\t도서가격 대출자\t대출일자\n");
}
void lprint(bookRec* p) {
	int i, j;
	printf("출력할 유형을 선택해주세요.\n");
	printf("1: 전체 도서 출력\n");
	printf("2: 대출 가능한 도서만 출력\n");
	printf("3: 대출 중인 도서만 출력\n");
	scanf("%d", &i);
	switch (i) {
	case 1:
		printf("전체 도서를 출력합니다.\n");
		disphead();
		for (j = 0; j < booknum; j++) {
			if (p[j].brPart.borrow IS ON) {
				printf("%08X\t%s\t%s\t%d\t%s\t", p[j].bcode.code, p[j].bname, p[j].bwriter, p[j].bprice, p[j].brPart.bookBorrower);
				timeMgr(p[j].brPart.dateOfBorrowing, 0);
				printf("\n");
			}
			else
				printf("%08X\t%s\t%s\t%d\t대출 가능    -\n", p[j].bcode.code, p[j].bname, p[j].bwriter, p[j].bprice);
		}
		system("pause");
		break;
	case 2:
		printf("대출 가능한 도서만 출력합니다.\n");
		disphead();
		for (j = 0; j < booknum; j++) {
			if (p[j].brPart.borrow IS OFF)
				printf("%08X\t%s\t%s\t%d\t대출 가능    -\n", p[j].bcode.code, p[j].bname, p[j].bwriter, p[j].bprice);
		}
		system("pause");
		break;
	case 3:
		printf("대출 중인 도서만 출력합니다.\n");
		disphead();
		for (j = 0; j < booknum; j++) {
			if (p[j].brPart.borrow IS ON) {
				printf("%08X\t%s\t%s\t%d\t%s\t", p[j].bcode.code, p[j].bname, p[j].bwriter, p[j].bprice, p[j].brPart.bookBorrower);
				timeMgr(p[j].brPart.dateOfBorrowing, 0);
				printf("\n");
			}
		}
		system("pause");
		break;
	default:
		printf("잘못된 입력입니다.\n메뉴로 이동합니다.\n");
		system("pause");
	}
	system("cls");
}