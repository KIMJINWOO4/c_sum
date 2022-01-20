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
	printf("���� ���� ���α׷�\n\n");
	printf("1. ���� �Է�\n");
	printf("2. ���� �˻� (�ڵ�,������ Ȥ�� ����)\n");
	printf("3. ���� ����\n");
	printf("4. ���� �ݳ�\n");
	printf("5. ���� ����\n");
	printf("6. ���� ����Ʈ\n");
	printf("7. ���� \n");
	scanf("%d", &i);
	return i;
}
int input(bookRec* p) {
	char i, j = 'n';
	unsigned code;
	while (1) {
		printf("������ �Է��Ͻÿ�.\n");
		printf("�����ڵ� ���� : ");
		scanf("%u", &code);
		p[booknum].bcode.cd.kubun = code;
		printf("�����ڵ� Ÿ�� : ");
		scanf("%u", &code);
		p[booknum].bcode.cd.type = code;
		printf("�����ڵ� ��ȣ : ");
		scanf("%u", &code);
		p[booknum].bcode.cd.number = code;
		p[booknum].bcode.cd.null = NULL;
		printf("������ : ");
		scanf("%s", p[booknum].bname);
		printf("���ڸ� : ");
		scanf("%s", p[booknum].bwriter);
		printf("�������� : ");
		scanf("%d", &p[booknum].bprice);
		p[booknum].brPart.borrow = OFF;
		printf("[%08X %s %s %d��] - Ȯ��? (Y/N)\n", p[booknum].bcode.code, p[booknum].bname, p[booknum].bwriter, p[booknum].bprice);
		i = _getch();
		if (i IS 'Y' OR i IS 'y') {
			booknum++;
			printf("������ �� �Է��Ͻðڽ��ϱ� ?(Y/N)\n");
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
	printf("Ű���� ����\n");
	printf("�ڵ�(1)\n");
	printf("������(2)\n");
	printf("�����̸�(3)\n");
	scanf("%d", &i);
	if (i IS 1) {
		printf("�˻��� �����ڵ带 �Է��ϼ���.\n");
		scanf("%x", &j);
		for (k = 0; k < booknum; k++) {
			if (j IS p[k].bcode.code) {
				if (p[k].brPart.borrow IS ON)
					printf("[%08X %s %s %d ���� ��]�� �½��ϱ�?(Y/N)\n", p[k].bcode.code, p[k].bname, p[k].bwriter, p[k].bprice);
				else
					printf("[%08X %s %s %d ���� ����]�� �½��ϱ�?(Y/N)\n", p[k].bcode.code, p[k].bname, p[k].bwriter, p[k].bprice);
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
		printf("�˻��� �������� �Է��ϼ���.\n");
		scanf("%s", temp);
		for (k = 0; k < booknum; k++) {
			if (strcmp(temp, p[k].bname) IS 0) {
				if (p[k].brPart.borrow IS ON)
					printf("[%08X %s %s %d ���� ��]�� �½��ϱ�?(Y/N)\n", p[k].bcode.code, p[k].bname, p[k].bwriter, p[k].bprice);
				else
					printf("[%08X %s %s %d ���� ����]�� �½��ϱ�?(Y/N)\n", p[k].bcode.code, p[k].bname, p[k].bwriter, p[k].bprice);
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
		printf("�˻��� �����̸��� �Է��ϼ���.\n");
		scanf("%s", temp);
		for (k = 0; k < booknum; k++) {
			if (strcmp(temp, p[k].bwriter) IS 0) {
				if (p[k].brPart.borrow IS ON)
					printf("[%08X %s %s %d ���� ��]�� �½��ϱ�?(Y/N)\n", p[k].bcode.code, p[k].bname, p[k].bwriter, p[k].bprice);
				else
					printf("[%08X %s %s %d ���� ����]�� �½��ϱ�?(Y/N)\n", p[k].bcode.code, p[k].bname, p[k].bwriter, p[k].bprice);
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
			printf("\n���� �˻� ����� [%08X %s %s %d ���� ��]\n", p[k].bcode.code, p[k].bname, p[k].bwriter, p[k].bprice);
		else
			printf("\n���� �˻� ����� [%08X %s %s %d ���� ����]\n", p[k].bcode.code, p[k].bname, p[k].bwriter, p[k].bprice);
		system("pause");
	}
	else {
		printf("�˻����� ���� Ű�����Դϴ�.\n�޴��� ���ư��ϴ�.\n");
		system("pause");
	}
	system("cls");
}
void borrow(bookRec* p) {
	char bname[BOOKNAME];
	int i, flag = 0;
	time_t tm;
	printf("�����Ͻ� ���� ���� �Է��ϼ���.\n");
	scanf("%s", bname);
	for (i = 0; i < booknum; i++) {
		if (strcmp(bname, p[i].bname) IS 0) {
			if (p[i].brPart.borrow IS OFF) {
				printf("%s å ���� �����մϴ�.\n������ �̸��� �Է��ϼ���.\n", bname);
				scanf("%s", p[i].brPart.bookBorrower);
				p[i].brPart.borrow = ON;
				tm = time(NULL);
				p[i].brPart.dateOfBorrowing = tm;
				printf("���� ���� ��¥ :");
				timeMgr(tm, 0);
				printf("\n");
				system("pause");
				flag = 1;
				break;
			}
			else {
				printf("���� �Ұ����մϴ�.\n�޴��� ���ư��ϴ�.\n");
				system("pause");
				flag = 1;
				break;
			}
		}
	}
	if (!flag) {
		printf("�������� �ʴ� �������Դϴ�.\n");
		printf("�޴��� ���ư��ϴ�.\n");
		system("pause");
	}
	system("cls");
}
void returning(bookRec* p) {
	char rname[WRITER], c = 'n';
	time_t tm, term;
	int j = 0, fee = 0;
	while (1) {
		printf("�ݳ��Ͻ� �������� �̸��� �Է����ּ���.\n");
		scanf("%s", rname);
		for (int i = 0; i < booknum; i++) {
			if (strcmp(rname, p[i].brPart.bookBorrower) IS 0) {
				tm = time(NULL);
				p[i].brPart.dateOfReturning = tm;
				printf("���� ��ȯ ��¥ : ");
				timeMgr(tm, 0);
				printf("\n");
				term = tm - p[i].brPart.dateOfBorrowing;
				printf("���� �Ⱓ : ");
				timeMgr(term, 1);
				printf("\n");
				fee = solvefee(int(term));
				printf("%s�� �������� : %d�� �Դϴ�.\n", rname, fee);
				strcpy(p[i].brPart.bookBorrower, "NULL");
				p[i].brPart.borrow = OFF;
				j++;
				break;
			}
		}
		if (j IS 0) {
			printf("�������� �ʴ� �����ڸ��Դϴ�.\n");
			printf("�ٽ� �Է��Ͻðڽ��ϱ�?(Y/N)\n");
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
		printf("������ ������ �̸��� �Է����ּ��� : ");
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
			printf("��ġ�ϴ� �������� �����ϴ�.\n�ٽ� �Է��Ͻðڽ��ϱ�?(Y/N)");
			j = _getch();
			if (j IS 'Y' OR j IS 'y')
				continue;
			else
				break;
		}
		else {
			printf("������ �Ϸ�Ǿ����ϴ�.\n");
			system("pause");
			break;
		}
	}
	system("cls");
	return booknum;
}
void disphead(void) {
	printf("�����ڵ�\t������\t���ڸ�\t�������� ������\t��������\n");
}
void lprint(bookRec* p) {
	int i, j;
	printf("����� ������ �������ּ���.\n");
	printf("1: ��ü ���� ���\n");
	printf("2: ���� ������ ������ ���\n");
	printf("3: ���� ���� ������ ���\n");
	scanf("%d", &i);
	switch (i) {
	case 1:
		printf("��ü ������ ����մϴ�.\n");
		disphead();
		for (j = 0; j < booknum; j++) {
			if (p[j].brPart.borrow IS ON) {
				printf("%08X\t%s\t%s\t%d\t%s\t", p[j].bcode.code, p[j].bname, p[j].bwriter, p[j].bprice, p[j].brPart.bookBorrower);
				timeMgr(p[j].brPart.dateOfBorrowing, 0);
				printf("\n");
			}
			else
				printf("%08X\t%s\t%s\t%d\t���� ����    -\n", p[j].bcode.code, p[j].bname, p[j].bwriter, p[j].bprice);
		}
		system("pause");
		break;
	case 2:
		printf("���� ������ ������ ����մϴ�.\n");
		disphead();
		for (j = 0; j < booknum; j++) {
			if (p[j].brPart.borrow IS OFF)
				printf("%08X\t%s\t%s\t%d\t���� ����    -\n", p[j].bcode.code, p[j].bname, p[j].bwriter, p[j].bprice);
		}
		system("pause");
		break;
	case 3:
		printf("���� ���� ������ ����մϴ�.\n");
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
		printf("�߸��� �Է��Դϴ�.\n�޴��� �̵��մϴ�.\n");
		system("pause");
	}
	system("cls");
}